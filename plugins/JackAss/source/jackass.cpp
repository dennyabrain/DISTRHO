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
};

// -------------------------------------------------
// Global JACK client

static jack_client_t* global_client = nullptr;

// -------------------------------------------------
// JackAss instance, containing 1 JACK MIDI port

class JackAssInstance
{
public:
    JackAssInstance(jack_port_t* port) :
        jport(port)
    {
        pthread_mutex_init(&midi_mutex, nullptr);
        clear_events();
    }

    ~JackAssInstance()
    {
        clear_events();
        pthread_mutex_destroy(&midi_mutex);

        jack_port_unregister(global_client, jport);
    }

    void clear_events()
    {
        pthread_mutex_lock(&midi_mutex);
        memset(&midi_data, 0, sizeof(midi_data_t)*MAX_MIDI_EVENTS);
        pthread_mutex_unlock(&midi_mutex);
    }

    void put_event(unsigned char status, unsigned char data1, unsigned char data2, VstInt32 time)
    {
        pthread_mutex_lock(&midi_mutex);

        for (int i=0; i<MAX_MIDI_EVENTS; i++)
        {
            if (midi_data[i].status == 0)
            {
                midi_data[i].status = status;
                midi_data[i].data1  = data1;
                midi_data[i].data2  = data2;
                midi_data[i].time   = time;
                break;
            }
        }

        pthread_mutex_unlock(&midi_mutex);
    }

    void process(jack_nframes_t nframes)
    {
        unsigned char* buffer;
        void* port_buffer = jack_port_get_buffer(jport, nframes);
        jack_midi_clear_buffer(port_buffer);

        pthread_mutex_lock(&midi_mutex);

        for (int i=0; i<MAX_MIDI_EVENTS; i++)
        {
            if (midi_data[i].status != 0)
            {
                buffer = jack_midi_event_reserve(port_buffer, midi_data[i].time, 3);
                buffer[0] = midi_data[i].status;
                buffer[1] = midi_data[i].data1;
                buffer[2] = midi_data[i].data2;

                midi_data[i].status = 0;
            }
            else
                break;
        }

        pthread_mutex_unlock(&midi_mutex);
    }

private:
    midi_data_t midi_data[MAX_MIDI_EVENTS];
    pthread_mutex_t midi_mutex;
    jack_port_t* const jport;
};

static std::list<JackAssInstance*> instances;
typedef std::list<JackAssInstance*>::iterator ins;

// -------------------------------------------------
// JACK calls

static int jprocess_callback(jack_nframes_t nframes, void *arg)
{
    for (ins it = instances.begin(); it != instances.end(); ++it)
        (*it)->process(nframes);

    return 0;
}

void init_jack(const char* client_name)
{
    if (! global_client)
    {
        global_client = jack_client_open(client_name, JackNullOption, nullptr);
        jack_set_process_callback(global_client, jprocess_callback, nullptr);
        jack_activate(global_client);
    }
}

void close_jack()
{
    if (global_client && instances.size() == 0)
    {
        jack_deactivate(global_client);
        jack_client_close(global_client);
        global_client = nullptr;
    }
}

// -------------------------------------------------
// JackAss plugin

class JackAss : public AudioEffectX
{
public:
    JackAss(audioMasterCallback audioMaster) :
        AudioEffectX(audioMaster, 0, 0),
        instance(nullptr)
    {
        if (audioMaster)
        {
            isSynth();

            setNumInputs(0);
            setNumOutputs(2); // For Hosts that don't support MIDI plugins
            setUniqueID(CCONST('J', 'A', 's', 's'));

            char buf_str[64] = { 0 };

            // Register global JACK client if needed
            if (getHostProductString(buf_str) == false)
                strcpy(buf_str, "JackAss");

            init_jack(buf_str);

            // Create instance+port for this plugin
#if __LP64__
            sprintf(buf_str, "midi-out_%02lu", instances.size()+1);
#else
            sprintf(buf_str, "midi-out_%02lu", instances.size()+1);
#endif

            //jack_deactivate(global_client);
            jack_port_t* jport = jack_port_register(global_client, buf_str, JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);
            //jack_activate(global_client);

            instance = new JackAssInstance(jport);
            instances.push_back(instance);
        }
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

    void processReplacing(float** /*inputs*/, float** outputs, VstInt32 sampleFrames)
    {
        // Silent output
        float* out1 = outputs[0];
        float* out2 = outputs[1];
        memset(out1, 0, sizeof(float)*sampleFrames);
        memset(out2, 0, sizeof(float)*sampleFrames);
    }

    VstInt32 processEvents(VstEvents* ev)
    {
        for (VstInt32 i=0; i < ev->numEvents; i++)
        {
            if (ev->events[i]->type == kVstMidiType)
            {
                const VstMidiEvent* event = (VstMidiEvent*)ev->events[i];
                instance->put_event(event->midiData[0], event->midiData[1], event->midiData[2], event->deltaFrames);
            }
        }
        return 0;
    }

    bool getEffectName(char* name)
    {
        vst_strncpy(name, "JackAss", kVstMaxEffectNameLen);
        return true;
    }

    bool getProductString(char* text)
    {
        vst_strncpy(text, "JackAss", kVstMaxProductStrLen);
        return true;
    }

    bool getVendorString(char* text)
    {
        vst_strncpy(text, "falkTX", kVstMaxVendorStrLen);
        return true;
    }

    VstInt32 getVendorVersion()
    {
        return 1000;
    }

    VstInt32 canDo(char* text)
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
};

// -------------------------------------------------
// DLL entry point

AudioEffect* createEffectInstance(audioMasterCallback audioMaster)
{
    return new JackAss(audioMaster);
}
