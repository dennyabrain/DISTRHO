/*
 * JackAss VST plugin
 */

/* Fix for VST includes */
#ifdef __linux__
#define __cdecl
#endif

#ifndef nullptr
#define nullptr 0
#endif

#include "public.sdk/source/vst2.x/audioeffect.h"
#include "public.sdk/source/vst2.x/audioeffect.cpp"
#include "public.sdk/source/vst2.x/audioeffectx.h"
#include "public.sdk/source/vst2.x/audioeffectx.cpp"
#include "public.sdk/source/vst2.x/vstplugmain.cpp"

#include <jack/jack.h>
#include <jack/midiport.h>

#include <pthread.h>
#include <string.h>

#define MAX_MIDI_EVENTS 1024

// Shared Stuff
struct midi_data_t {
    unsigned char status;
    unsigned char note;
    unsigned char velo;
    VstInt32 time;
};

// VST Stuff
class JackAss : public AudioEffectX
{
public:
    JackAss(audioMasterCallback audioMaster) :
        AudioEffectX(audioMaster, 0, 0)
    {
        if (audioMaster)
        {
            isSynth();

            setNumInputs(0);
            setNumOutputs(2); // For Hosts that don't support MIDI plugins
            setUniqueID(CCONST('J', 'A', 's', 's'));

            pthread_mutex_init(&midi_mutex, nullptr);
            clear_midi_buffer();
            init_jack();
        }
    }

    ~JackAss()
    {
        close_jack();
        pthread_mutex_destroy(&midi_mutex);
    }

    void processReplacing(float** /*inputs*/, float** outputs, VstInt32 sampleFrames)
    {
        // Silent output
        float* out1 = outputs[0];
        float* out2 = outputs[1];

        while (--sampleFrames >= 0)
            out1[sampleFrames] = out2[sampleFrames] = 0.0f;
    }

    VstInt32 processEvents(VstEvents* ev)
    {
        pthread_mutex_lock(&midi_mutex);
        VstInt32 i, j=0, k=0;

        // Find initial pos where to put events
        for (i=0; i<MAX_MIDI_EVENTS; i++)
        {
            if (midi_data[i].status == 0)
            {
                k = i;
                break;
            }
        }

        for (i=0; i < ev->numEvents && k+i < MAX_MIDI_EVENTS; i++)
        {
            if ((ev->events[i])->type != kVstMidiType)
            {
                j++;
                continue;
            }

            VstMidiEvent* event = (VstMidiEvent*)ev->events[i];
            char* midiData = event->midiData;

            midi_data[k+i-j].status = midiData[0];
            midi_data[k+i-j].note   = midiData[1];
            midi_data[k+i-j].velo   = midiData[2];
            midi_data[k+i-j].time   = event->deltaFrames;
        }

        // Set last event
        midi_data[k+i-j+1].status = 0;
        pthread_mutex_unlock(&midi_mutex);

        return 1;
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

    static int jprocess_callback(jack_nframes_t nframes, void *arg)
    {
        if (arg == nullptr)
          return 0;

        JackAss* ass = (JackAss*)arg;

        void* port_buffer = jack_port_get_buffer(ass->jport, nframes);
        jack_midi_clear_buffer(port_buffer);
        unsigned char* buffer;

        // make a copy of the events, so we can unlock the mutex asap
        midi_data_t midi_data_tmp[MAX_MIDI_EVENTS];

        pthread_mutex_lock(&ass->midi_mutex);
        memcpy(&midi_data_tmp, &ass->midi_data, sizeof(midi_data_t)*MAX_MIDI_EVENTS);
        memset(&ass->midi_data, 0, sizeof(midi_data_t)*MAX_MIDI_EVENTS);
        pthread_mutex_unlock(&ass->midi_mutex);

        for (int i=0; i<MAX_MIDI_EVENTS; i++)
        {
            midi_data_t* mevent = &midi_data_tmp[i];

            if (mevent->status != 0)
            {
                buffer = jack_midi_event_reserve(port_buffer, mevent->time, 3);
                buffer[0] = mevent->status;
                buffer[1] = mevent->note;
                buffer[2] = mevent->velo;
            }
            else
                break;
        }
        return 0;
    }

protected:
    jack_client_t* jclient;
    jack_port_t* jport;
    midi_data_t midi_data[MAX_MIDI_EVENTS];
    pthread_mutex_t midi_mutex;

private:
    void init_jack()
    {
        char host_name[64] = { 0 };

        if (getHostProductString(host_name) == false)
        {
            host_name[0] = 'J';
            host_name[1] = 'a';
            host_name[2] = 'c';
            host_name[3] = 'k';
            host_name[4] = 'A';
            host_name[5] = 's';
            host_name[6] = 's';
            host_name[7] = '\0';
        }

        jclient = jack_client_open(host_name, JackNullOption, 0);
        jport   = jack_port_register(jclient, "midi_out", JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);
        jack_set_process_callback(jclient, jprocess_callback, this);
        jack_activate(jclient);
    }

    void close_jack()
    {
        jack_deactivate(jclient);
        jack_client_close(jclient);
        jclient = nullptr;
    }

    void clear_midi_buffer()
    {
        pthread_mutex_lock(&midi_mutex);
        memset(&midi_data, 0, sizeof(midi_data_t)*MAX_MIDI_EVENTS);
        pthread_mutex_unlock(&midi_mutex);
    }
};

AudioEffect* createEffectInstance(audioMasterCallback audioMaster)
{
    return new JackAss(audioMaster);
}
