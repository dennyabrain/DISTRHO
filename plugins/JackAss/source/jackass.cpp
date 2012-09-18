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

static jack_client_t* global_client = nullptr;
static bool need_resend = false;

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

        if (global_client && jport)
            jack_port_unregister(global_client, jport);
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
        void* portBuffer = jack_port_get_buffer(jport, nframes);
        jack_midi_clear_buffer(portBuffer);

        pthread_mutex_lock(&mutex);

        for (int i=0; i<MAX_MIDI_EVENTS; i++)
        {
            if (data[i].status != 0)
            {
                unsigned char* const buffer = jack_midi_event_reserve(portBuffer, data[i].time, 3);
                buffer[0] = data[i].status;
                buffer[1] = data[i].data1;
                buffer[2] = data[i].data2;

                data[i].status = 0;
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
typedef std::list<JackAssInstance*>::iterator ins;

// -------------------------------------------------
// JACK calls

static int jprocess_callback(const jack_nframes_t nframes, void*)
{
    for (ins it = instances.begin(); it != instances.end(); ++it)
        (*it)->process(nframes);

    return 0;
}

static void jconnect_callback(const jack_port_id_t a, const jack_port_id_t b, const int connect, void*)
{
    if (! connect)
        return;

    if (jack_port_is_mine(global_client, jack_port_by_id(global_client, a)) || jack_port_is_mine(global_client, jack_port_by_id(global_client, b)))
        need_resend = true;
}

void init_jack(const char* const clientName)
{
    if (global_client)
        return;

    global_client = jack_client_open(clientName, JackNullOption, nullptr);
    jack_set_port_connect_callback(global_client, jconnect_callback, nullptr);
    jack_set_process_callback(global_client, jprocess_callback, nullptr);
    jack_activate(global_client);
}

void close_jack()
{
    if (instances.size() > 0 || ! global_client)
        return;

    jack_deactivate(global_client);
    jack_client_close(global_client);
    global_client = nullptr;
}

// -------------------------------------------------
// JackAss plugin

class JackAss : public AudioEffectX
{
public:
    JackAss(audioMasterCallback audioMaster)
        : AudioEffectX(audioMaster, 0, paramCount),
          instance(nullptr)
    {
        for (int i=0; i < paramCount; i++)
            paramBuffers[i] = 0.0f;

        paramBuffers[7]  = float(100)/127; // volume
        paramBuffers[8]  = 0.5f;           // balance (centered)
        paramBuffers[10] = 0.5f;           // pan (centered)

        if (! audioMaster)
            return;

        isSynth();

        setNumInputs(0);
        setNumOutputs(2); // For Hosts that don't support MIDI plugins
        setUniqueID(CCONST('J', 'A', 's', 's'));

        char strBuf[kVstMaxProductStrLen] = { 0 };

        // Register global JACK client if needed
        if (! getHostProductString(strBuf))
            strcpy(strBuf, "JackAss");

        init_jack(strBuf);

        // Create instance+port for this plugin
        sprintf(strBuf, "midi-out_%02lu", instances.size()+1);
        jack_port_t* const jport = jack_port_register(global_client, strBuf, JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);

        instance = new JackAssInstance(jport);
        instances.push_back(instance);
    }

    ~JackAss()
    {
        if (instance)
        {
            instances.remove(instance);
            delete instance;
        }

        close_jack();
    }

    void processReplacing(float** /*inputs*/, float** const outputs, const VstInt32 sampleFrames)
    {
        // Silent output
        float* out1 = outputs[0];
        float* out2 = outputs[1];
        memset(out1, 0, sizeof(float)*sampleFrames);
        memset(out2, 0, sizeof(float)*sampleFrames);

        if (need_resend)
        {
            for (int i=0; i < paramCount; i++)
                instance->putEvent(0xB0, i, int(paramBuffers[i]*127), 0);

            need_resend = false;
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

    void setParameter(const VstInt32 index, const float value)
    {
        if (index >= paramCount)
            return;

        paramBuffers[index] = value;
        instance->putEvent(0xB0, index, int(value*127), 0);
    }

    float getParameter(const VstInt32 index)
    {
        if (index < paramCount)
            return paramBuffers[index];

        return 0.0f;
    }

    void getParameterLabel(const VstInt32 index, char* const label)
    {
        AudioEffectX::getParameterLabel(index, label);
    }

    void getParameterDisplay(const VstInt32 index, char* const text)
    {
        if (index < paramCount)
        {
            char strBuf[kVstMaxParamStrLen] = { 0 };
            snprintf(strBuf,kVstMaxParamStrLen,  "%i", int(paramBuffers[index]*127));

            vst_strncpy(text, strBuf, kVstMaxParamStrLen);
        }
        else
            AudioEffectX::getParameterDisplay(index, text);
    }

    void getParameterName(const VstInt32 index, char* const text)
    {
        switch (index)
        {
        case 0:
            vst_strncpy(text, "Bank Select", kVstMaxParamStrLen);
            break;
        case 1:
            vst_strncpy(text, "Modulation", kVstMaxParamStrLen);
            break;
        case 2:
            vst_strncpy(text, "Breath", kVstMaxParamStrLen);
            break;
        default:
            AudioEffectX::getParameterName(index, text);
            break;
        }
    }

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
        vst_strncpy(text, "falkTX", kVstMaxVendorStrLen);
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
        else if (strcmp(text, "receiveVstMidiEvent") == 0)
            return 1;
        else
            return -1;
    }

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

    static const int paramCount = 32;
    float paramBuffers[paramCount];
};

// -------------------------------------------------
// DLL entry point

AudioEffect* createEffectInstance(audioMasterCallback audioMaster)
{
    return new JackAss(audioMaster);
}
