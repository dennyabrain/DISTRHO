/*
 * DISTRHO 3BandEQ Plugin, based on 3BandEQ by Michael Gruhn
 * Copyright (C) 2007 Michael Gruhn <michael-gruhn@web.de>
 * Copyright (C) 2012 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * For a full copy of the license see the LGPL.txt file
 */

#include "DistrhoPlugin3BandEQ.h"

#include <cmath>

const float cfAMP_DB = 8.656170245f;
const float cfDC_ADD = 1e-30f;
const float cfPI     = 3.141592654f;

// -------------------------------------------------

DistrhoPlugin3BandEQ::DistrhoPlugin3BandEQ()
    : DISTRHO::Plugin(paramCount, 1, 0) // 1 program, 0 states
{
    // set default values
    d_setProgram(0);

    // reset
    d_deactivate();
}

DistrhoPlugin3BandEQ::~DistrhoPlugin3BandEQ()
{
}

// -------------------------------------------------
// Init

void DistrhoPlugin3BandEQ::d_initParameter(uint32_t index, DISTRHO::Parameter& parameter)
{
    switch (index)
    {
    case paramLow:
        parameter.hints      = DISTRHO::PARAMETER_IS_AUTOMABLE;
        parameter.name       = "Low";
        parameter.symbol     = "low";
        parameter.unit       = "dB";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = -24.0f;
        parameter.ranges.max = 24.0f;
        break;

    case paramMid:
        parameter.hints      = DISTRHO::PARAMETER_IS_AUTOMABLE;
        parameter.name       = "Mid";
        parameter.symbol     = "mid";
        parameter.unit       = "dB";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = -24.0f;
        parameter.ranges.max = 24.0f;
        break;

    case paramHigh:
        parameter.hints      = DISTRHO::PARAMETER_IS_AUTOMABLE;
        parameter.name       = "High";
        parameter.symbol     = "high";
        parameter.unit       = "dB";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = -24.0f;
        parameter.ranges.max = 24.0f;
        break;

    case paramMaster:
        parameter.hints      = DISTRHO::PARAMETER_IS_AUTOMABLE;
        parameter.name       = "Master";
        parameter.symbol     = "master";
        parameter.unit       = "dB";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = -24.0f;
        parameter.ranges.max = 24.0f;
        break;

    case paramLowMidFreq:
        parameter.hints      = DISTRHO::PARAMETER_IS_AUTOMABLE;
        parameter.name       = "Low-Mid Freq";
        parameter.symbol     = "low_mid";
        parameter.unit       = "Hz";
        parameter.ranges.def = 440.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 1000.0f;
        break;

    case paramMidHighFreq:
        parameter.hints      = DISTRHO::PARAMETER_IS_AUTOMABLE;
        parameter.name       = "Mid-High Freq";
        parameter.symbol     = "mid_high";
        parameter.unit       = "Hz";
        parameter.ranges.def = 1000.0f;
        parameter.ranges.min = 1000.0f;
        parameter.ranges.max = 20000.0f;
        break;
    }
}

void DistrhoPlugin3BandEQ::d_initProgramName(uint32_t index, d_string& programName)
{
    if (index != 0)
        return;

    programName = "Default";
}

// -------------------------------------------------
// Internal data

float DistrhoPlugin3BandEQ::d_parameterValue(uint32_t index)
{
    switch (index)
    {
    case paramLow:
        return fLow;
    case paramMid:
        return fMid;
    case paramHigh:
        return fHigh;
    case paramMaster:
        return fMaster;
    case paramLowMidFreq:
        return fLowMidFreq;
    case paramMidHighFreq:
        return fMidHighFreq;
    default:
        return 0.0f;
    }
}

void DistrhoPlugin3BandEQ::d_setParameterValue(uint32_t index, float value)
{
    if (d_sampleRate() <= 0.0)
        return;

    switch (index)
    {
    case paramLow:
        fLow = value;
        lowVol = exp( (fLow/48.0f) * 48 / cfAMP_DB);
        break;
    case paramMid:
        fMid = value;
        midVol = exp( (fMid/48.0f) * 48 / cfAMP_DB);
        break;
    case paramHigh:
        fHigh = value;
        highVol = exp( (fHigh/48.0f) * 48 / cfAMP_DB);
        break;
    case paramMaster:
        fMaster = value;
        outVol = exp( (fMaster/48.0f) * 48 / cfAMP_DB);
        break;
    case paramLowMidFreq:
        fLowMidFreq = d_minf(value, fMidHighFreq);
        freqLP = fLowMidFreq; //fLowMidFreq * (fLowMidFreq / 24000.0f) * (fLowMidFreq / 24000.0f);
        xLP  = exp(-2.0 * cfPI * freqLP / d_sampleRate());
        a0LP = 1.0 - xLP;
        b1LP = -xLP;
        break;
    case paramMidHighFreq:
        fMidHighFreq = d_maxf(value, fLowMidFreq);
        freqHP = fMidHighFreq; //fMidHighFreq * (fMidHighFreq / 24000.0f) * (fMidHighFreq / 24000.0f);
        xHP  = exp(-2.0 * cfPI * freqHP / d_sampleRate());
        a0HP = 1.0 - xHP;
        b1HP = -xHP;
        break;
    }
}

void DistrhoPlugin3BandEQ::d_setProgram(uint32_t index)
{
    if (index != 0)
        return;

    // Default values
    fLow = 0.0f;
    fMid = 0.0f;
    fHigh = 0.0f;
    fMaster = 0.0f;
    fLowMidFreq = 220.0f;
    fMidHighFreq = 2000.0f;

    // Internal stuff
    lowVol = midVol = highVol = outVol = 1.0f;
    freqLP = 200.0f;
    freqHP = 2000.0f;

    // reset filter values
    d_activate();
}

// -------------------------------------------------
// Process

void DistrhoPlugin3BandEQ::d_activate()
{
    xLP  = exp(-2.0 * cfPI * freqLP / d_sampleRate());
    a0LP = 1.0f - xLP;
    b1LP = -xLP;

    xHP  = exp(-2.0 * cfPI * freqHP / d_sampleRate());
    a0HP = 1.0f - xHP;
    b1HP = -xHP;
}

void DistrhoPlugin3BandEQ::d_deactivate()
{
    out1LP = out2LP = out1HP = out2HP = 0.0f;
    tmp1LP = tmp2LP = tmp1HP = tmp2HP = 0.0f;
}

void DistrhoPlugin3BandEQ::d_run(const float** inputs, float** outputs, uint32_t frames, uint32_t, const DISTRHO::MidiEvent*)
{
    const float* in1 = inputs[0];
    const float* in2 = inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

    for (uint32_t i=0; i < frames; i++)
    {
        tmp1LP = a0LP * in1[i] - b1LP * tmp1LP + cfDC_ADD;
        tmp2LP = a0LP * in2[i] - b1LP * tmp2LP + cfDC_ADD;
        out1LP = tmp1LP - cfDC_ADD;
        out2LP = tmp2LP - cfDC_ADD;

        tmp1HP = a0HP * in1[i] - b1HP * tmp1HP + cfDC_ADD;
        tmp2HP = a0HP * in2[i] - b1HP * tmp2HP + cfDC_ADD;
        out1HP = in1[i] - tmp1HP - cfDC_ADD;
        out2HP = in2[i] - tmp2HP - cfDC_ADD;

        out1[i] = (out1LP*lowVol + (in1[i] - out1LP - out1HP)*midVol + out1HP*highVol) * outVol;
        out2[i] = (out2LP*lowVol + (in2[i] - out2LP - out2HP)*midVol + out2HP*highVol) * outVol;
    }
}

// -------------------------------------------------

START_NAMESPACE_DISTRHO

Plugin* createPlugin()
{
    return new DistrhoPlugin3BandEQ();
}

END_NAMESPACE_DISTRHO
