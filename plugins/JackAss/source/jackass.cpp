/*
 * JackAss VST plugin
 */

/* Fix for VST includes */
#ifdef __linux__
#ifndef __cdecl
#define __cdecl
#endif
#endif

#include "public.sdk/source/vst2.x/audioeffect.cpp"
#include "public.sdk/source/vst2.x/audioeffectx.cpp"
#include "public.sdk/source/vst2.x/vstplugmain.cpp"

#include <cstdio>
#include <cstring>
#include <list>
#include <pthread.h>

#include <jack/jack.h>
#include <jack/midiport.h>

// -------------------------------------------------
// Parameters

static const unsigned char paramMap[] = {
    0x01, 0x02, 0x03, 0x04, 0x05, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F
};

static const int paramVolume  = 5;
static const int paramBalance = 6;
static const int paramPan     = 8;

static const int paramCount   = sizeof(paramMap);
static const int programCount = 128;

// -------------------------------------------------
// Midi data

#define MAX_MIDI_EVENTS 512

struct midi_data_t {
    unsigned char status;
    unsigned char data1;
    unsigned char data2;
    VstInt32 time;

    midi_data_t()
        : status(0),
          data1(0),
          data2(0),
          time(0) {}
};

// -------------------------------------------------
// Global JACK client

static jack_client_t* globalJackClient = nullptr;
static bool needMidiResend = false;

// -------------------------------------------------
// single JackAss instance, containing 1 MIDI port

class JackAssInstance
{
public:
    JackAssInstance(jack_port_t* const port)
        : jport(port)
    {
        pthread_mutex_init(&mutex, nullptr);
    }

    ~JackAssInstance()
    {
        pthread_mutex_destroy(&mutex);

        if (globalJackClient && jport)
            jack_port_unregister(globalJackClient, jport);
    }

    void putEvent(const unsigned char status, const unsigned char data1, const unsigned char data2, const VstInt32 time)
    {
        pthread_mutex_lock(&mutex);

        for (int i=0; i < MAX_MIDI_EVENTS; i++)
        {
            if (data[i].status == 0)
            {
                data[i].status = status;
                data[i].data1  = data1;
                data[i].data2  = data2;
                data[i].time   = time;
                break;
            }
        }

        pthread_mutex_unlock(&mutex);
    }

    void process(const jack_nframes_t nframes)
    {
        void* const portBuffer = jack_port_get_buffer(jport, nframes);

        jack_midi_clear_buffer(portBuffer);

        pthread_mutex_lock(&mutex);

        for (int i=0; i < MAX_MIDI_EVENTS; i++)
        {
            if (data[i].status != 0)
            {
                unsigned char* const buffer = jack_midi_event_reserve(portBuffer, data[i].time, 3);
                buffer[0] = data[i].status;
                buffer[1] = data[i].data1;
                buffer[2] = data[i].data2;

                data[i].status = 0; // set as invalid
            }
            else
                break;
        }

        pthread_mutex_unlock(&mutex);
    }

private:
    jack_port_t* const jport;

    midi_data_t     data[MAX_MIDI_EVENTS];
    pthread_mutex_t mutex;
};

static  std::list<JackAssInstance*> instances;

// -------------------------------------------------
// JACK calls

static int jprocess_callback(const jack_nframes_t nframes, void*)
{
    for (auto it = instances.begin(); it != instances.end(); ++it)
        (*it)->process(nframes);

    return 0;
}

static void jconnect_callback(const jack_port_id_t a, const jack_port_id_t b, const int connect, void*)
{
    if (! connect)
        return;

    if (jack_port_is_mine(globalJackClient, jack_port_by_id(globalJackClient, a)) || jack_port_is_mine(globalJackClient, jack_port_by_id(globalJackClient, b)))
        needMidiResend = true;
}

// -------------------------------------------------
// JackAss plugin

class JackAss : public AudioEffectX
{
public:
    JackAss(audioMasterCallback audioMaster)
        : AudioEffectX(audioMaster, programCount, paramCount),
          instance(nullptr)
    {
        for (int i=0; i < paramCount; i++)
            paramBuffers[i] = 0.0f;

        paramBuffers[paramVolume]  = float(100)/127;
        paramBuffers[paramBalance] = 0.5f;
        paramBuffers[paramPan]     = 0.5f;

        for (int i=0; i < programCount; i++)
        {
            programNames[i] = new char[32];
            snprintf(programNames[i], 32, "Program #%i", i+1);
        }

        if (! audioMaster)
            return;

        isSynth();

        setNumInputs(0);
        setNumOutputs(2); // For hosts that don't support MIDI plugins
        setUniqueID(CCONST('J', 'A', 's', 's'));

        char strBuf[128] = { 0 };

        // Register global JACK client if needed
        if (! globalJackClient)
        {
            if (! getHostProductString(strBuf))
                strcpy(strBuf, "JackAss");

            globalJackClient = jack_client_open(strBuf, JackNullOption, nullptr);
            jack_set_port_connect_callback(globalJackClient, jconnect_callback, nullptr);
            jack_set_process_callback(globalJackClient, jprocess_callback, nullptr);
            jack_activate(globalJackClient);
        }

        // Create instance + jack-port for this plugin
        sprintf(strBuf, "midi-out_%02lu", instances.size()+1);
        jack_port_t* const jport = jack_port_register(globalJackClient, strBuf, JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);

        instance = new JackAssInstance(jport);
        instances.push_back(instance);
    }

    ~JackAss()
    {
        for (int i=0; i < programCount; i++)
        {
            delete[] programNames[i];
        }

        if (instance)
        {
            instances.remove(instance);
            delete instance;
        }

        // Close global JACK client if needed
        if (globalJackClient && instances.size() == 0)
        {
            jack_deactivate(globalJackClient);
            jack_client_close(globalJackClient);
            globalJackClient = nullptr;
        }
    }

    // ---------------------------------------------

    void process(float** const inputs, float** const outputs, const VstInt32 sampleFrames)
    {
        processReplacing(inputs, outputs, sampleFrames);
    }

    void processReplacing(float** /*inputs*/, float** const outputs, const VstInt32 sampleFrames)
    {
        // Silent output
        float* out1 = outputs[0];
        float* out2 = outputs[1];

        for (VstInt32 i=0; i < sampleFrames; i++)
            out1[i] = out2[i] = 0.0f;

        if (needMidiResend)
        {
            for (int i=0; i < paramCount; i++)
                instance->putEvent(0xB0, paramMap[i], int(paramBuffers[i]*127), 0);

            needMidiResend = false;
        }
    }

    VstInt32 processEvents(VstEvents* const ev)
    {
        for (VstInt32 i=0; i < ev->numEvents; i++)
        {
            if (ev->events[i]->type == kVstMidiType)
            {
                const VstMidiEvent* event = (VstMidiEvent*)ev->events[i];
                instance->putEvent(event->midiData[0], event->midiData[1], event->midiData[2], event->deltaFrames);
            }
        }

        return 0;
    }

    // ---------------------------------------------

    void setProgram(const VstInt32 program)
    {
        if (curProgram < 0 || curProgram > programCount)
            return;

#if 0
        // bank select
        instance->putEvent(0xB0, 0x00, 0, 0);
        // program select
        instance->putEvent(0xC0, program, 0, 0);
#endif

        AudioEffectX::setProgram(program);
    }

    void setProgramName(char* const name)
    {
        if (curProgram < 0 || curProgram > programCount)
            return;

        strncpy(programNames[curProgram], name, 32);
    }

    void getProgramName(char* const name)
    {
        if (curProgram < 0 || curProgram > programCount)
            return AudioEffectX::getProgramName(name);

        strncpy(name, programNames[curProgram], kVstMaxProgNameLen);
    }

    // ---------------------------------------------

    void setParameter(const VstInt32 index, const float value)
    {
        if (index < 0 || index >= paramCount)
            return;

        paramBuffers[index] = value;
        instance->putEvent(0xB0, paramMap[index], int(value*127), 0);
    }

    float getParameter(const VstInt32 index)
    {
        if (index < 0 || index < paramCount)
            return paramBuffers[index];

        return 0.0f;
    }

    void getParameterLabel(const VstInt32 index, char* const label)
    {
        // TODO
        AudioEffectX::getParameterLabel(index, label);
    }

    void getParameterDisplay(const VstInt32 index, char* const text)
    {
        if (index < 0 || index >= paramCount)
            return AudioEffectX::getParameterDisplay(index, text);

        char strBuf[kVstMaxParamStrLen] = { 0 };
        snprintf(strBuf, kVstMaxParamStrLen, "%i", int(paramBuffers[index]*127));

        vst_strncpy(text, strBuf, kVstMaxParamStrLen);
    }

    void getParameterName(const VstInt32 index, char* const text)
    {
        if (index < 0 || index >= paramCount)
            return AudioEffectX::getParameterName(index, text);

        switch (paramMap[index])
        {
        case 0x01:
            vst_strncpy(text, "0x01 Modulation", kVstMaxParamStrLen);
            break;
        case 0x02:
            vst_strncpy(text, "0x02 Breath", kVstMaxParamStrLen);
            break;
        case 0x03:
            vst_strncpy(text, "0x03 (Undefined)", kVstMaxParamStrLen);
            break;
        case 0x04:
            vst_strncpy(text, "0x04 Foot", kVstMaxParamStrLen);
            break;
        case 0x05:
            vst_strncpy(text, "0x05 Portamento", kVstMaxParamStrLen);
            break;
        case 0x07:
            vst_strncpy(text, "0x07 Volume", kVstMaxParamStrLen);
            break;
        case 0x08:
            vst_strncpy(text, "0x08 Balance", kVstMaxParamStrLen);
            break;
        case 0x09:
            vst_strncpy(text, "0x09 (Undefined)", kVstMaxParamStrLen);
            break;
        case 0x0A:
            vst_strncpy(text, "0x0A Pan", kVstMaxParamStrLen);
            break;
        case 0x0B:
            vst_strncpy(text, "0x0B Expression", kVstMaxParamStrLen);
            break;
        case 0x0C:
            vst_strncpy(text, "0x0C FX Control 1", kVstMaxParamStrLen);
            break;
        case 0x0D:
            vst_strncpy(text, "0x0D FX Control 2", kVstMaxParamStrLen);
            break;
        case 0x0E:
            vst_strncpy(text, "0x0E (Undefined)", kVstMaxParamStrLen);
            break;
        case 0x0F:
            vst_strncpy(text, "0x0F (Undefined)", kVstMaxParamStrLen);
            break;
        case 0x10:
            vst_strncpy(text, "0x10 General Purpose 1", kVstMaxParamStrLen);
            break;
        case 0x11:
            vst_strncpy(text, "0x11 General Purpose 2", kVstMaxParamStrLen);
            break;
        case 0x12:
            vst_strncpy(text, "0x12 General Purpose 3", kVstMaxParamStrLen);
            break;
        case 0x13:
            vst_strncpy(text, "0x13 General Purpose 4", kVstMaxParamStrLen);
            break;
        case 0x14:
            vst_strncpy(text, "0x14 (Undefined)", kVstMaxParamStrLen);
            break;
        case 0x15:
            vst_strncpy(text, "0x15 (Undefined)", kVstMaxParamStrLen);
            break;
        case 0x16:
            vst_strncpy(text, "0x16 (Undefined)", kVstMaxParamStrLen);
            break;
        case 0x17:
            vst_strncpy(text, "0x17 (Undefined)", kVstMaxParamStrLen);
            break;
        case 0x18:
            vst_strncpy(text, "0x18 (Undefined)", kVstMaxParamStrLen);
            break;
        case 0x19:
            vst_strncpy(text, "0x19 (Undefined)", kVstMaxParamStrLen);
            break;
        case 0x1A:
            vst_strncpy(text, "0x1A (Undefined)", kVstMaxParamStrLen);
            break;
        case 0x1B:
            vst_strncpy(text, "0x1B (Undefined)", kVstMaxParamStrLen);
            break;
        case 0x1C:
            vst_strncpy(text, "0x1C (Undefined)", kVstMaxParamStrLen);
            break;
        case 0x1D:
            vst_strncpy(text, "0x1D (Undefined)", kVstMaxParamStrLen);
            break;
        case 0x1E:
            vst_strncpy(text, "0x1E (Undefined)", kVstMaxParamStrLen);
            break;
        case 0x1F:
            vst_strncpy(text, "0x1F (Undefined)", kVstMaxParamStrLen);
            break;
        case 0x46:
            vst_strncpy(text, "0x46 Control 1 [Variation]", kVstMaxParamStrLen);
            break;
        case 0x47:
            vst_strncpy(text, "0x47 Control 2 [Timbre]", kVstMaxParamStrLen);
            break;
        case 0x48:
            vst_strncpy(text, "0x48 Control 3 [Release]", kVstMaxParamStrLen);
            break;
        case 0x49:
            vst_strncpy(text, "0x49 Control 4 [Attack]", kVstMaxParamStrLen);
            break;
        case 0x4A:
            vst_strncpy(text, "0x4A Control 5 [Brightness]", kVstMaxParamStrLen);
            break;
        case 0x4B:
            vst_strncpy(text, "0x4B Control 6 [Decay]", kVstMaxParamStrLen);
            break;
        case 0x4C:
            vst_strncpy(text, "0x4C Control 7 [Vib Rate]", kVstMaxParamStrLen);
            break;
        case 0x4D:
            vst_strncpy(text, "0x4D Control 8 [Vib Depth]", kVstMaxParamStrLen);
            break;
        case 0x4E:
            vst_strncpy(text, "0x4E Control 9 [Vib Delay]", kVstMaxParamStrLen);
            break;
        case 0x4F:
            vst_strncpy(text, "0x4F Control 10 [Undefined]", kVstMaxParamStrLen);
            break;
        case 0x50:
            vst_strncpy(text, "0x50 General Purpose 5", kVstMaxParamStrLen);
            break;
        case 0x51:
            vst_strncpy(text, "0x51 General Purpose 6", kVstMaxParamStrLen);
            break;
        case 0x52:
            vst_strncpy(text, "0x52 General Purpose 7", kVstMaxParamStrLen);
            break;
        case 0x53:
            vst_strncpy(text, "0x53 General Purpose 8", kVstMaxParamStrLen);
            break;
        case 0x54:
            vst_strncpy(text, "0x54 Portamento Control", kVstMaxParamStrLen);
            break;
        case 0x5B:
            vst_strncpy(text, "0x5B FX 1 Depth [Reverb]", kVstMaxParamStrLen);
            break;
        case 0x5C:
            vst_strncpy(text, "0x5C FX 2 Depth [Tremolo]", kVstMaxParamStrLen);
            break;
        case 0x5D:
            vst_strncpy(text, "0x5D FX 3 Depth [Chorus]", kVstMaxParamStrLen);
            break;
        case 0x5E:
            vst_strncpy(text, "0x5E FX 4 Depth [Detune]", kVstMaxParamStrLen);
            break;
        case 0x5F:
            vst_strncpy(text, "0x5F FX 5 Depth [Phaser]", kVstMaxParamStrLen);
            break;
        default:
            AudioEffectX::getParameterName(index, text);
            break;
        }
    }

    // ---------------------------------------------

    bool getEffectName(char* const name)
    {
        vst_strncpy(name, "JackAss", kVstMaxEffectNameLen);
        return true;
    }

    bool getProductString(char* const text)
    {
        vst_strncpy(text, "JackAss", kVstMaxProductStrLen);
        return true;
    }

    bool getVendorString(char* const text)
    {
        vst_strncpy(text, "DISTRHO", kVstMaxVendorStrLen);
        return true;
    }

    VstInt32 getVendorVersion()
    {
        return 1000;
    }

    VstInt32 canDo(char* const text)
    {
        if (strcmp(text, "receiveVstEvents") == 0)
            return 1;
        if (strcmp(text, "receiveVstMidiEvent") == 0)
            return 1;

        return -1;
    }

    VstPlugCategory getPlugCategory()
    {
        return kPlugCategSynth;
    }

    // ---------------------------------------------

    VstInt32 getNumMidiInputChannels()
    {
        return 16;
    }

    VstInt32 getNumMidiOutputChannels()
    {
        return 0;
    }

private:
    JackAssInstance* instance;

    float paramBuffers[paramCount];
    char* programNames[programCount];
};

// -------------------------------------------------
// DLL entry point

AudioEffect* createEffectInstance(audioMasterCallback audioMaster)
{
    return new JackAss(audioMaster);
}
