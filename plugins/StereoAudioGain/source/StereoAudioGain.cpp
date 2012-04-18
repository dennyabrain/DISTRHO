/*
 * Qt4 Demo plugin by falkTX <falktx@gmail.com>
 */

#include "StereoAudioGain.h"

double abs_d(double value)
{
    return (value < 0.0) ? -value : value;
}

StereoAudioGain::StereoAudioGain() :
    DistrhoPluginBase(PARAMETER_COUNT, 0)
{
    x_left  = x_right  = 1.0f;
    vu_left = vu_right = 0.0f;

    p_paramsInfo[PARAMETER_LEFT].hints      = PARAMETER_IS_ENABLED | PARAMETER_IS_AUTOMABLE;
    p_paramsInfo[PARAMETER_LEFT].name       = strdup("Left Gain");
    p_paramsInfo[PARAMETER_LEFT].symbol     = strdup("left_gain");
    p_paramsInfo[PARAMETER_LEFT].unit       = nullptr;

    p_paramsInfo[PARAMETER_LEFT].range.def  = 1.0f;
    p_paramsInfo[PARAMETER_LEFT].range.min  = 0.0f;
    p_paramsInfo[PARAMETER_LEFT].range.max  = 2.0f;
    p_paramsInfo[PARAMETER_LEFT].range.step = 0.01f;
    p_paramsInfo[PARAMETER_LEFT].range.stepSmall = 0.0001f;
    p_paramsInfo[PARAMETER_LEFT].range.stepLarge = 0.1f;

    p_paramsInfo[PARAMETER_RIGHT].hints      = PARAMETER_IS_ENABLED | PARAMETER_IS_AUTOMABLE;
    p_paramsInfo[PARAMETER_RIGHT].name       = strdup("Right Gain");
    p_paramsInfo[PARAMETER_RIGHT].symbol     = strdup("right_gain");
    p_paramsInfo[PARAMETER_RIGHT].unit       = nullptr;

    p_paramsInfo[PARAMETER_RIGHT].range.def  = 1.0f;
    p_paramsInfo[PARAMETER_RIGHT].range.min  = 0.0f;
    p_paramsInfo[PARAMETER_RIGHT].range.max  = 2.0f;
    p_paramsInfo[PARAMETER_RIGHT].range.step = 0.01f;
    p_paramsInfo[PARAMETER_RIGHT].range.stepSmall = 0.0001f;
    p_paramsInfo[PARAMETER_RIGHT].range.stepLarge = 0.1f;

    p_paramsInfo[PARAMETER_VU_LEFT].hints      = PARAMETER_IS_ENABLED | PARAMETER_IS_AUTOMABLE | PARAMETER_IS_OUTPUT;
    p_paramsInfo[PARAMETER_VU_LEFT].name       = strdup("Left Meter");
    p_paramsInfo[PARAMETER_VU_LEFT].symbol     = strdup("left_meter");
    p_paramsInfo[PARAMETER_VU_LEFT].unit       = nullptr;

    p_paramsInfo[PARAMETER_VU_LEFT].range.def  = 0.0f;
    p_paramsInfo[PARAMETER_VU_LEFT].range.min  = 0.0f;
    p_paramsInfo[PARAMETER_VU_LEFT].range.max  = 1.0f;

    p_paramsInfo[PARAMETER_VU_RIGHT].hints     = PARAMETER_IS_ENABLED | PARAMETER_IS_AUTOMABLE | PARAMETER_IS_OUTPUT;
    p_paramsInfo[PARAMETER_VU_RIGHT].name      = strdup("Right Meter");
    p_paramsInfo[PARAMETER_VU_RIGHT].symbol    = strdup("right_meter");
    p_paramsInfo[PARAMETER_VU_RIGHT].unit      = nullptr;

    p_paramsInfo[PARAMETER_VU_RIGHT].range.def = 0.0f;
    p_paramsInfo[PARAMETER_VU_RIGHT].range.min = 0.0f;
    p_paramsInfo[PARAMETER_VU_RIGHT].range.max = 1.0f;
}

// Information
const char* StereoAudioGain::d_name()
{
    return "Stereo Audio Gain";
}

const char* StereoAudioGain::d_maker()
{
    return "DISTRHO";
}

const char* StereoAudioGain::d_license()
{
    return "";
}

uint32_t StereoAudioGain::d_version()
{
    return 0x1000;
}

long StereoAudioGain::d_uniqueId()
{
    return 0;
}

// Internal data
float StereoAudioGain::d_parameterValue(uint32_t index)
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

void StereoAudioGain::d_setParameterValue(uint32_t index, float value)
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

void StereoAudioGain::d_setCurrentProgram(uint32_t)
{
}

// Process stuff
void StereoAudioGain::d_activate() {}
void StereoAudioGain::d_deactivate() {}

void StereoAudioGain::d_run(float** inputs, float** outputs, uint32_t frames)
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

        if (abs_d(p_outL[i]) > vu_left)
            vu_left = abs_d(p_outL[i]);

        if (p_outR[i] > vu_right)
            vu_right = abs_d(p_outR[i]);
    }

    if (vu_left > 1.0f)
        vu_left = 1.0f;

    if (vu_right > 1.0f)
        vu_right = 1.0f;
}

// ---------------------------------------------------------------------------------------------

DistrhoPluginBase* createDistrhoPlugin()
{
    return new StereoAudioGain();
}
