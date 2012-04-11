/*
 * Qt4 Demo plugin by falkTX <falktx@gmail.com>
 *
 * Released under the Public Domain
 */

#ifdef AUDIOGAIN_JACK

#include <QtGui/QApplication>
#include <jack/jack.h>

#include "audiogain.h"

#ifndef WIN32
inline float abs (float x)
{
    return ( x<0 ? -x:x);
}
#endif

class JackAudioGainW : public AudioGainW
{
public:
    JackAudioGainW() :
        AudioGainW()
    {
        x_left = x_right = 1.0f;
        v_left = v_right = 0.0f;

        client = jack_client_open("jackmeter", JackNullOption, 0);
        in_portL = jack_port_register(client, "in-left", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
        in_portR = jack_port_register(client, "in-right", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
        out_portL = jack_port_register(client, "out-left", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
        out_portR = jack_port_register(client, "out-right", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

        jack_set_process_callback(client, process_callback, this);
        jack_activate(client);
    }

    ~JackAudioGainW()
    {
        jack_deactivate(client);
        jack_client_close(client);
    }

    float getPeakValueL()
    {
        return v_left;
    }

    float getPeakValueR()
    {
        return v_right;
    }

    void setProcessValueL(float value)
    {
        x_left = value;
    }

    void setProcessValueR(float value)
    {
        x_right = value;
    }

    static int process_callback(jack_nframes_t nframes, void* arg)
    {
        if (arg)
        {
            JackAudioGainW* plugin = (JackAudioGainW*)arg;

            float v_leftx, v_rightx;
            v_leftx = v_rightx = 0.0f;

            const jack_default_audio_sample_t* const p_inL = (jack_default_audio_sample_t*)jack_port_get_buffer(plugin->in_portL, nframes);
            const jack_default_audio_sample_t* const p_inR = (jack_default_audio_sample_t*)jack_port_get_buffer(plugin->in_portR, nframes);
            jack_default_audio_sample_t* const p_outL = (jack_default_audio_sample_t*)jack_port_get_buffer(plugin->out_portL, nframes);
            jack_default_audio_sample_t* const p_outR = (jack_default_audio_sample_t*)jack_port_get_buffer(plugin->out_portR, nframes);

            for (jack_nframes_t i=0; i<nframes; i++)
            {
                p_outL[i] = p_inL[i]*plugin->x_left;
                p_outR[i] = p_inR[i]*plugin->x_right;

                if (abs(p_outL[i]) > v_leftx)
                    v_leftx = abs(p_outL[i]);

                if (abs(p_outR[i]) > v_rightx)
                    v_rightx = abs(p_outR[i]);
            }

            if (v_leftx > 1.0f)
              v_leftx = 1.0f;

            if (v_rightx > 1.0f)
              v_rightx = 1.0f;

            plugin->v_left  = v_leftx;
            plugin->v_right = v_rightx;
        }

        return 0;
    }

private:
    float x_left, x_right;
    float v_left, v_right;

    jack_client_t* client;
    jack_port_t* in_portL;
    jack_port_t* in_portR;
    jack_port_t* out_portL;
    jack_port_t* out_portR;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    JackAudioGainW plugin;
    plugin.show();

    return app.exec();
}

#endif // AUDIOGAIN_STANTDALONE
