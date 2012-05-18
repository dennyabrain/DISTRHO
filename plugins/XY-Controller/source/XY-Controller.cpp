/*
 * Qt4 Demo plugin by falkTX <falktx@gmail.com>
 */

#include "XY-Controller.h"

long CCONST(int a, int b, int c, int d)
{
    return (a << 24) | (b << 16) | (c << 8) | (d << 0);
}

// ---------------------------------------------------------------------------------------------

XYController::XYController() :
    DistrhoPluginBase(PARAMETER_COUNT, 0)
{
    smooth = false;
    in_x = in_y = out_x = out_y = 0.0f;
}

// -------------------------------------------------

// Information
const char* XYController::d_name()
{
    return "XY Controller";
}

const char* XYController::d_label()
{
    return "XY-Controller";
}

const char* XYController::d_maker()
{
    return "DISTRHO";
}

const char* XYController::d_license()
{
    return "";
}

uint32_t XYController::d_version()
{
    return 0x1000;
}

long XYController::d_uniqueId()
{
    return CCONST('D', 'X', 'Y', 'C');
}

// -------------------------------------------------

// Internal data
float XYController::d_parameterValue(uint32_t index)
{
    switch (index)
    {
    case PARAMETER_SMOOTH:
        return smooth ? 1.0f : 0.0f;
    case PARAMETER_IN_X:
        return in_x;
    case PARAMETER_IN_Y:
        return in_y;
    case PARAMETER_OUT_X:
        return out_x;
    case PARAMETER_OUT_Y:
        return out_y;
    default:
        return 0.0f;
    }
}

void XYController::d_setParameterValue(uint32_t index, float value)
{
    if (value < -1.0f)
        value = -1.0f;
    else if (value > 1.0f)
        value = 1.0f;

    switch (index)
    {
    case PARAMETER_SMOOTH:
        smooth =  (value >= 0.5f);
        break;
    case PARAMETER_IN_X:
        in_x = value;
        break;
    case PARAMETER_IN_Y:
        in_y = value;
        break;
    }
}

void XYController::d_setProgram(uint32_t)
{
}

// -------------------------------------------------

// Init
void XYController::d_init()
{
    p_paramsInfo[PARAMETER_SMOOTH].hints     = PARAMETER_IS_AUTOMABLE | PARAMETER_IS_BOOLEAN;
    p_paramsInfo[PARAMETER_SMOOTH].name      = strdup("Smooth");
    p_paramsInfo[PARAMETER_SMOOTH].symbol    = strdup("smooth");
    p_paramsInfo[PARAMETER_SMOOTH].unit      = nullptr;

    p_paramsInfo[PARAMETER_SMOOTH].range.def = 0.0f;
    p_paramsInfo[PARAMETER_SMOOTH].range.min = 0.0f;
    p_paramsInfo[PARAMETER_SMOOTH].range.max = 1.0f;

    p_paramsInfo[PARAMETER_IN_X].hints       = PARAMETER_IS_AUTOMABLE;
    p_paramsInfo[PARAMETER_IN_X].name        = strdup("In X");
    p_paramsInfo[PARAMETER_IN_X].symbol      = strdup("in_x");
    p_paramsInfo[PARAMETER_IN_X].unit        = nullptr;

    p_paramsInfo[PARAMETER_IN_X].range.def   = 0.0f;
    p_paramsInfo[PARAMETER_IN_X].range.min   = -1.0f;
    p_paramsInfo[PARAMETER_IN_X].range.max   = 1.0f;

    p_paramsInfo[PARAMETER_IN_Y].hints       = PARAMETER_IS_AUTOMABLE;
    p_paramsInfo[PARAMETER_IN_Y].name        = strdup("In Y");
    p_paramsInfo[PARAMETER_IN_Y].symbol      = strdup("in_y");
    p_paramsInfo[PARAMETER_IN_Y].unit        = nullptr;

    p_paramsInfo[PARAMETER_IN_Y].range.def   = 0.0f;
    p_paramsInfo[PARAMETER_IN_Y].range.min   = -1.0f;
    p_paramsInfo[PARAMETER_IN_Y].range.max   = 1.0f;

    p_paramsInfo[PARAMETER_OUT_X].hints      = PARAMETER_IS_AUTOMABLE | PARAMETER_IS_OUTPUT;
    p_paramsInfo[PARAMETER_OUT_X].name       = strdup("Out X");
    p_paramsInfo[PARAMETER_OUT_X].symbol     = strdup("out_x");
    p_paramsInfo[PARAMETER_OUT_X].unit       = nullptr;

    p_paramsInfo[PARAMETER_OUT_X].range.def  = 0.0f;
    p_paramsInfo[PARAMETER_OUT_X].range.min  = -1.0f;
    p_paramsInfo[PARAMETER_OUT_X].range.max  = 1.0f;

    p_paramsInfo[PARAMETER_OUT_Y].hints      = PARAMETER_IS_AUTOMABLE | PARAMETER_IS_OUTPUT;
    p_paramsInfo[PARAMETER_OUT_Y].name       = strdup("Out Y");
    p_paramsInfo[PARAMETER_OUT_Y].symbol     = strdup("out_y");
    p_paramsInfo[PARAMETER_OUT_Y].unit       = nullptr;

    p_paramsInfo[PARAMETER_OUT_Y].range.def  = 0.0f;
    p_paramsInfo[PARAMETER_OUT_Y].range.min  = -1.0f;
    p_paramsInfo[PARAMETER_OUT_Y].range.max  = 1.0f;
}

void XYController::d_cleanup()
{
}

// -------------------------------------------------

// Process
void XYController::d_activate() {}
void XYController::d_deactivate() {}

void XYController::d_run(float**, float**, uint32_t, uint32_t, MidiEvent*)
{
    out_x = in_x;
    out_y = in_y;
}

// ---------------------------------------------------------------------------------------------

DistrhoPluginBase* createDistrhoPlugin()
{
    return new XYController();
}
