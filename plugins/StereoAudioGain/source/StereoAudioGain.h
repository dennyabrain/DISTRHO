/*
 * Qt4 Demo plugin by falkTX <falktx@gmail.com>
 */

#ifndef STEREOAUDIOGAIN_H
#define STEREOAUDIOGAIN_H

#include "PluginBase.h"

class StereoAudioGain : public DistrhoPluginBase
{
public:
    enum Params {
        PARAMETER_LEFT     = 0,
        PARAMETER_RIGHT    = 1,
        PARAMETER_VU_LEFT  = 2,
        PARAMETER_VU_RIGHT = 3,
        PARAMETER_COUNT    = 4
    };

    StereoAudioGain();

    // -------------------------------------------------

    // Information
    const char* d_name();
    const char* d_label();
    const char* d_maker();
    const char* d_license();
    uint32_t    d_version();
    long        d_uniqueId();

    // -------------------------------------------------

    // Internal data
    float d_parameterValue(uint32_t index);
    void  d_setParameterValue(uint32_t index, float value);
    void  d_setCurrentProgram(uint32_t index);

    // -------------------------------------------------

    // Init
    void d_init();
    void d_cleanup();

    // -------------------------------------------------

    // Process stuff
    void d_activate();
    void d_deactivate();
    void d_run(float** inputs, float** outputs, uint32_t frames);

    // -------------------------------------------------

private:
    float x_left, x_right, vu_left, vu_right;
};

#endif // STEREOAUDIOGAIN_H
