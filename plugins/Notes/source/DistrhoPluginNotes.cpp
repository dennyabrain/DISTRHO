/*
 * DISTRHO Notes Plugin
 * Copyright (C) 2012 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * For a full copy of the license see the GPL.txt file
 */

#include "DistrhoPluginNotes.h"

#include <cmath>

// -------------------------------------------------

DistrhoPluginNotes::DistrhoPluginNotes()
    : DISTRHO::Plugin(1, 0) // 1 parameter, 0 programs
{
    curPage = 0;
}

DistrhoPluginNotes::~DistrhoPluginNotes()
{
}

// -------------------------------------------------
// Init

void DistrhoPluginNotes::d_initParameter(uint32_t index, DISTRHO::Parameter& parameter)
{
    if (index != 0)
        return;

    parameter.hints      = DISTRHO::PARAMETER_IS_AUTOMABLE | DISTRHO::PARAMETER_IS_INTEGER;
    parameter.name       = "Page";
    parameter.symbol     = "page";
    parameter.ranges.def = 1;
    parameter.ranges.min = 1;
    parameter.ranges.max = 100;
    parameter.ranges.step = 1;
    parameter.ranges.stepSmall = 1;
    parameter.ranges.stepLarge = 10;
}

// -------------------------------------------------
// Internal data

float DistrhoPluginNotes::d_parameterValue(uint32_t index)
{
    if (index != 0)
        return 0.0f;

    return curPage;
}

void DistrhoPluginNotes::d_setParameterValue(uint32_t index, float value)
{
    if (index != 0)
        return;

    curPage = rint(value);
}

// -------------------------------------------------
// Process

void DistrhoPluginNotes::d_activate()
{
}

void DistrhoPluginNotes::d_deactivate()
{
}

void DistrhoPluginNotes::d_run(const float** inputs, float** outputs, uint32_t frames, uint32_t, const DISTRHO::MidiEvent*)
{
    const float* in1 = inputs[0];
    const float* in2 = inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

    memcpy(out1, in1, sizeof(float)*frames);
    memcpy(out2, in2, sizeof(float)*frames);
}

// -------------------------------------------------
// Callbacks

void DistrhoPluginNotes::d_stateChanged(const char*, const char*)
{
    // do nothing, used only for UI state
}

// -------------------------------------------------

START_NAMESPACE_DISTRHO

Plugin* createPlugin()
{
    return new DistrhoPluginNotes();
}

END_NAMESPACE_DISTRHO
