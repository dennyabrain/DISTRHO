/*
 * DISTHRO Plugin Toolkit (DPT)
 * Copyright (C) 2012 Filipe Coelho <falktx@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * A copy of the license is included with this software, or can be
 * found online at www.gnu.org/licenses.
 */

#include "DistrhoPluginInternal.h"

#include <cassert>

START_NAMESPACE_DISTRHO

static TimePos fallbackTimePos;

// -------------------------------------------------

Plugin::Plugin(uint32_t parameterCount, uint32_t programCount)
{
    data = new PluginPrivateData;
    assert(data);

    if (! data)
        return;

    data->parameterCount = parameterCount;

    if (parameterCount > 0)
        data->parameters = new Parameter [parameterCount];

#if DISTRHO_PLUGIN_WANT_PROGRAMS
    data->programCount = programCount;

    if (programCount > 0)
        data->programNames = new const char* [programCount];
#else
    (void)programCount;
#endif
}

Plugin::~Plugin()
{
    if (data)
        delete data;
}

// -------------------------------------------------
// Host state

uint32_t Plugin::d_bufferSize() const
{
    return data ? data->bufferSize : 512;
}

double Plugin::d_sampleRate() const
{
    return data ? data->sampleRate : 44100.0;
}

const TimePos* Plugin::d_timePos() const
{
    return data ? &data->timePos : &fallbackTimePos;
}

void Plugin::d_setLatency(uint32_t samples)
{
    if (data)
        data->latency = samples;
}

// -------------------------------------------------

END_NAMESPACE_DISTRHO
