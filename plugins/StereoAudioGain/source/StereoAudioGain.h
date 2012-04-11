/*
 * Qt4 Demo plugin by falkTX <falktx@gmail.com>
 *
 * Released under the Public Domain
 */

#ifndef STEREOAUDIOGAIN_H
#define STEREOAUDIOGAIN_H

#include "pluginbase.h"

class StereoAudioGain : public DistrhoPluginBase
{
public:
    StereoAudioGain();

    // Information
    virtual const char* d_name();
    virtual const char* d_maker();
    virtual const char* d_license();
    virtual int32_t d_version();
    virtual long d_uniqueId();

    // Internal data
    virtual float d_parameterValue(uint32_t index);
    virtual void d_setParameterValue(uint32_t index, float value);
    virtual void d_setCurrentProgram(uint32_t index);

    // init
    virtual bool d_init();
    virtual bool d_cleanup();

    // Process stuff
    virtual void d_activate();
    virtual void d_deactivate();
    virtual void d_run(const float** const inputs, float** const outputs, uint32_t frames);

private:
    enum Params {
        PARAMETER_LEFT     = 0,
        PARAMETER_RIGHT    = 1,
        PARAMETER_VU_LEFT  = 2,
        PARAMETER_VU_RIGHT = 3,
        PARAMETER_COUNT    = 4
    };

    float x_left, x_right, vu_left, vu_right;
};

#endif // STEREOAUDIOGAIN_H
