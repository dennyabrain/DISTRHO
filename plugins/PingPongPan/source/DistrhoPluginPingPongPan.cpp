/*
 * DISTRHO PingPongPan Plugin, based on PingPongPan by Michael Gruhn
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

#include "DistrhoPluginPingPongPan.h"

#include <cmath>

const float cf2PI = 6.283185307f;

// -------------------------------------------------

DistrhoPluginPingPongPan::DistrhoPluginPingPongPan()
    : DISTRHO::Plugin(paramCount, 1, 0) // 1 program, 0 states
{
    // set default values
    d_setProgram(0);

    // reset
    d_deactivate();
}

DistrhoPluginPingPongPan::~DistrhoPluginPingPongPan()
{
}

// -------------------------------------------------
// Init

void DistrhoPluginPingPongPan::d_initParameter(uint32_t index, DISTRHO::Parameter& parameter)
{
    switch (index)
    {
    case paramFreq:
        parameter.hints      = DISTRHO::PARAMETER_IS_AUTOMABLE;
        parameter.name       = "Frequency";
        parameter.symbol     = "freq";
        parameter.ranges.def = 50.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 100.0f;
        break;

    case paramWidth:
        parameter.hints      = DISTRHO::PARAMETER_IS_AUTOMABLE;
        parameter.name       = "Width";
        parameter.symbol     = "with";
        parameter.unit       = "%";
        parameter.ranges.def = 75.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 100.0f;
        break;
    }
}

void DistrhoPluginPingPongPan::d_initProgramName(uint32_t index, d_string& programName)
{
    if (index != 0)
        return;

    programName = "Default";
}

// -------------------------------------------------
// Internal data

float DistrhoPluginPingPongPan::d_parameterValue(uint32_t index)
{
    switch (index)
    {
    case paramFreq:
        return fFreq;
    case paramWidth:
        return fWidth;
    default:
        return 0.0f;
    }
}

void DistrhoPluginPingPongPan::d_setParameterValue(uint32_t index, float value)
{
    if (d_sampleRate() <= 0.0)
        return;

    switch (index)
    {
    case paramFreq:
        fFreq = value;
        waveSpeed = (cf2PI * fFreq / 100.0f)/d_sampleRate();
        break;
    case paramWidth:
        fWidth = value;
        break;
    }
}

void DistrhoPluginPingPongPan::d_setProgram(uint32_t index)
{
    if (index != 0)
        return;

    // Default values
    fFreq  = 50.0f;
    fWidth = 75.0f;

    // reset filter values
    d_activate();
}

// -------------------------------------------------
// Process

void DistrhoPluginPingPongPan::d_activate()
{
    waveSpeed = (cf2PI * fFreq / 100.0f)/d_sampleRate();
}

void DistrhoPluginPingPongPan::d_deactivate()
{
    wavePos = 0.0f;
}

void DistrhoPluginPingPongPan::d_run(const float** inputs, float** outputs, uint32_t frames, uint32_t, const DISTRHO::MidiEvent*)
{
    const float* in1 = inputs[0];
    const float* in2 = inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

    for (uint32_t i=0; i < frames; i++)
    {
        pan = d_minf(d_maxf(sin(wavePos) * (fWidth/100.0f), -1.0f), 1.0f);

        if ((wavePos += waveSpeed) >= cf2PI)
            wavePos -= cf2PI;

        out1[i] = in1[i] * (pan > 0.0f ? 1.0f-pan : 1.0f);
        out2[i] = in2[i] * (pan < 0.0f ? 1.0f+pan : 1.0f);
    }
}

// -------------------------------------------------

START_NAMESPACE_DISTRHO

Plugin* createPlugin()
{
    return new DistrhoPluginPingPongPan();
}

END_NAMESPACE_DISTRHO
