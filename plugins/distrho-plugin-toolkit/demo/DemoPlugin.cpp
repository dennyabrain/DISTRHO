// demo plugin

#include "DemoPlugin.h"

// -------------------------------------------------

DemoPlugin::DemoPlugin() : DISTRHO::Plugin(PARAMETER_COUNT, 1)
{
    x_left  = x_right  = 1.0f;
    vu_left = vu_right = 0.0f;
}

DemoPlugin::~DemoPlugin()
{
}

// -------------------------------------------------
// Init

void DemoPlugin::d_initParameter(uint32_t index, DISTRHO::Parameter& parameter)
{
    switch (index)
    {
    case PARAMETER_LEFT:
        parameter.hints       = DISTRHO::PARAMETER_IS_AUTOMABLE;
        parameter.name        = strdup("Left Gain");
        parameter.symbol      = strdup("left_gain");
        parameter.ranges.def  = 1.0f;
        parameter.ranges.min  = 0.0f;
        parameter.ranges.max  = 2.0f;
        break;

    case PARAMETER_RIGHT:
        parameter.hints       = DISTRHO::PARAMETER_IS_AUTOMABLE;
        parameter.name        = strdup("Right Gain");
        parameter.symbol      = strdup("right_gain");
        parameter.ranges.def  = 1.0f;
        parameter.ranges.min  = 0.0f;
        parameter.ranges.max  = 2.0f;
        break;

    case PARAMETER_VU_LEFT:
        parameter.hints       = DISTRHO::PARAMETER_IS_AUTOMABLE | DISTRHO::PARAMETER_IS_OUTPUT;
        parameter.name        = strdup("Left Meter");
        parameter.symbol      = strdup("left_meter");
        parameter.ranges.def  = 0.0f;
        parameter.ranges.min  = 0.0f;
        parameter.ranges.max  = 1.0f;
        break;

    case PARAMETER_VU_RIGHT:
        parameter.hints      = DISTRHO::PARAMETER_IS_AUTOMABLE | DISTRHO::PARAMETER_IS_OUTPUT;
        parameter.name       = strdup("Right Meter");
        parameter.symbol     = strdup("right_meter");
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 1.0f;
        break;

    default:
        break;
    }
}

void DemoPlugin::d_initProgramName(uint32_t index, const char*& programName)
{
    if (index > 0)
        return;

    programName = strdup("default");
}

// -------------------------------------------------
// Internal data

float DemoPlugin::d_parameterValue(uint32_t index)
{
    switch (index)
    {
    case PARAMETER_LEFT:
        return x_left;
    case PARAMETER_RIGHT:
        return x_right;
    case PARAMETER_VU_LEFT:
        return vu_left;
    case PARAMETER_VU_RIGHT:
        return vu_right;
    default:
        return 0.0f;
    }
}

void DemoPlugin::d_setParameterValue(uint32_t index, float value)
{
    if (value < 0.0f)
        value = 0.0f;
    else if (value > 2.0f)
        value = 2.0f;

    switch (index)
    {
    case PARAMETER_LEFT:
        x_left = value;
        break;
    case PARAMETER_RIGHT:
        x_right = value;
        break;
    }
}

void DemoPlugin::d_setProgram(uint32_t index)
{
    if (index > 0)
        return;

    x_left = x_right = 1.0f;
}

// -------------------------------------------------
// Process

void DemoPlugin::d_activate()
{
}

void DemoPlugin::d_deactivate()
{
}

void DemoPlugin::d_run(const float* const* inputs, float* const* outputs, uint32_t frames, uint32_t, const DISTRHO::MidiEvent*)
{
    const float* const p_inL = inputs[0];
    const float* const p_inR = inputs[1];
    float* const p_outL = outputs[0];
    float* const p_outR = outputs[1];

    vu_left = vu_right = 0.0f;

    for (uint32_t i=0; i < frames; i++)
    {
        p_outL[i] = p_inL[i]*x_left;
        p_outR[i] = p_inR[i]*x_right;

        if (abs_f(p_outL[i]) > vu_left)
            vu_left = abs_f(p_outL[i]);

        if (abs_f(p_outR[i]) > vu_right)
            vu_right = abs_f(p_outR[i]);
    }

    if (vu_left > 1.0f)
        vu_left = 1.0f;

    if (vu_right > 1.0f)
        vu_right = 1.0f;
}

// -------------------------------------------------
// Callbacks

void DemoPlugin::d_bufferSizeChanged(uint32_t)
{
}

void DemoPlugin::d_stateChanged(const char*, const char*)
{
}

// -------------------------------------------------

START_NAMESPACE_DISTRHO

Plugin* createPlugin()
{
    return new DemoPlugin;
}

END_NAMESPACE_DISTRHO
