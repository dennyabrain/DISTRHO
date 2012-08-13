// demo plugin

#ifndef __DEMO_PLUGIN_H__
#define __DEMO_PLUGIN_H__

#include "DistrhoPlugin.h"
#include "DistrhoPluginUtils.h"

// -------------------------------------------------

class DemoPlugin : public DISTRHO::Plugin
{
public:
    enum Parameters {
        PARAMETER_LEFT     = 0,
        PARAMETER_RIGHT    = 1,
        PARAMETER_VU_LEFT  = 2,
        PARAMETER_VU_RIGHT = 3,
        PARAMETER_COUNT    = 4
    };

    DemoPlugin();
    ~DemoPlugin();

    // ---------------------------------------------
protected:

    // Information
    const char* d_name()
    {
        return "Stereo Audio Gain";
    }

    const char* d_label()
    {
        return "StereoAudioGain";
    }

    const char* d_maker()
    {
        return "DISTRHO";
    }

    const char* d_license()
    {
        return "";
    }

    uint32_t d_version()
    {
        return 0x1000;
    }

    long d_uniqueId()
    {
        return CCONST('D', 'S', 'A', 'G');
    }

    // Init
    void d_initParameter(uint32_t index, DISTRHO::Parameter& parameter);
    void d_initProgramName(uint32_t index, const char*& programName);

    // Internal data
    float d_parameterValue(uint32_t index);
    void d_setParameterValue(uint32_t index, float value);
    void d_setProgram(uint32_t index);

    // Process
    void d_activate();
    void d_deactivate();
    void d_run(const float* const* inputs, float* const* outputs, uint32_t frames, uint32_t midiEventCount, const DISTRHO::MidiEvent* midiEvents);

    // Callbacks
    void d_bufferSizeChanged(uint32_t);
    void d_stateChanged(const char* key, const char* value);

private:
    float x_left, x_right, vu_left, vu_right;
};

// -------------------------------------------------

#endif // __DEMO_PLUGIN_H__
