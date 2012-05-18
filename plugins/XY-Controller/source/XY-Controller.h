/*
 * Qt4 Demo plugin by falkTX <falktx@gmail.com>
 */

#ifndef XYCONTROLLER_H
#define XYCONTROLLER_H

#include "PluginBase.h"

class XYController : public DistrhoPluginBase
{
public:
    enum Params {
        PARAMETER_SMOOTH = 0,
        PARAMETER_IN_X   = 1,
        PARAMETER_IN_Y   = 2,
        PARAMETER_OUT_X  = 3,
        PARAMETER_OUT_Y  = 4,
        PARAMETER_COUNT  = 5
    };

    XYController();

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
    void  d_setProgram(uint32_t index);

    // -------------------------------------------------

    // Init
    void d_init();
    void d_cleanup();

    // -------------------------------------------------

    // Process
    void d_activate();
    void d_deactivate();
    void d_run(float** inputs, float** outputs, uint32_t frames, uint32_t midiEventCount, MidiEvent* midiEvents);

    // -------------------------------------------------

private:
    bool smooth;
    float in_x, in_y, out_x, out_y;
};

#endif // XYCONTROLLER_H
