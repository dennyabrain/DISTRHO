/*
 * DISTRHO Plugin Toolkit (DPT)
 * Copyright (C) 2012-2013 Filipe Coelho <falktx@falktx.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "DistrhoPluginInternal.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------
// Static data

uint32_t d_lastBufferSize = 0;
double   d_lastSampleRate = 0.0;

// -----------------------------------------------------------------------
// Static, fallback data

const d_string        PluginInternal::sFallbackString;
const ParameterRanges PluginInternal::sFallbackRanges;

// -----------------------------------------------------------------------
// Plugin

Plugin::Plugin(uint32_t parameterCount, uint32_t programCount, uint32_t stateCount)
    : pData(new PrivateData())
{
    if (parameterCount > 0)
    {
        pData->parameterCount = parameterCount;
        pData->parameters     = new Parameter[parameterCount];
    }

    if (programCount > 0)
    {
#if DISTRHO_PLUGIN_WANT_PROGRAMS
        pData->programCount = programCount;
        pData->programNames = new d_string[programCount];
#endif
    }

    if (stateCount > 0)
    {
#if DISTRHO_PLUGIN_WANT_STATE
        pData->stateCount = stateCount;
        pData->stateKeys  = new d_string[stateCount];
#endif
    }
}

Plugin::~Plugin()
{
    delete pData;
}

// -----------------------------------------------------------------------
// Host state

uint32_t Plugin::d_getBufferSize() const noexcept
{
    return pData->bufferSize;
}

double Plugin::d_getSampleRate() const noexcept
{
    return pData->sampleRate;
}

#if DISTRHO_PLUGIN_WANT_TIMEPOS
const TimePos& Plugin::d_getTimePos() const noexcept
{
    return pData->timePos;
}
#endif

#if DISTRHO_PLUGIN_WANT_LATENCY
void Plugin::d_setLatency(uint32_t frames) noexcept
{
    pData->latency = frames;
}
#endif

// -----------------------------------------------------------------------
// Callbacks

void Plugin::d_bufferSizeChanged(uint32_t)
{
}

void Plugin::d_sampleRateChanged(double)
{
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
