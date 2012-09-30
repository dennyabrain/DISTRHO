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

#ifndef __DISTRHO_PLUGIN_INTERNAL_H__
#define __DISTRHO_PLUGIN_INTERNAL_H__

#include "DistrhoPlugin.h"

#include <cassert>
#include <cstdlib>

START_NAMESPACE_DISTRHO

// -------------------------------------------------

#define MAX_MIDI_EVENTS 512

static ParameterRanges fallbackRanges;

struct PluginPrivateData {
    uint32_t   parameterCount;
    uint32_t   bufferSize;
    double     sampleRate;
    TimePos    timePos;
    uint32_t   latency;
    Parameter* parameters;

#if DISTRHO_PLUGIN_WANT_PROGRAMS
    uint32_t     programCount;
    const char** programNames;
#endif

    PluginPrivateData()
        : parameterCount(0),
          bufferSize(512),
          sampleRate(44100),
          latency(0),
#if DISTRHO_PLUGIN_WANT_PROGRAMS
          parameters(nullptr),
          programCount(0),
          programNames(nullptr) {}
#else
          parameters(nullptr) {}
#endif

    ~PluginPrivateData()
    {
        if (parameterCount > 0 && parameters)
        {
            for (uint32_t i = 0; i < parameterCount; i++)
            {
                Parameter* const parameter = &parameters[i];

                if (! parameter)
                    continue;

                if (parameter->name)
                    free((void*)parameter->name);
                if (parameter->symbol)
                    free((void*)parameter->symbol);
                if (parameter->unit)
                    free((void*)parameter->unit);
            }

            delete[] parameters;
        }

#if DISTRHO_PLUGIN_WANT_PROGRAMS
        if (programCount > 0 && programNames)
        {
            for (uint32_t i = 0; i < programCount; i++)
            {
                const char* const programName = programNames[i];

                if (programName)
                    free((void*)programName);
            }

            delete[] programNames;
        }
#endif
    }
};

// -------------------------------------------------

class PluginInternal
{
public:
    PluginInternal()
        : plugin(createPlugin()),
          data(nullptr)
    {
        assert(plugin);

        if (! plugin)
            return;

        data = plugin->data;
        assert(data);

        if (! data)
            return;

        for (uint32_t i=0; i < data->parameterCount; i++)
            plugin->d_initParameter(i, data->parameters[i]);

#if DISTRHO_PLUGIN_WANT_PROGRAMS
        for (uint32_t i=0; i < data->programCount; i++)
            plugin->d_initProgramName(i, data->programNames[i]);
#endif
    }

    // ---------------------------------------------

    const char* name()
    {
        return plugin ? plugin->d_name() : "";
    }

    const char* label()
    {
        return plugin ? plugin->d_label() : "";
    }

    const char* maker()
    {
        return plugin ? plugin->d_maker() : "";
    }

    const char* license()
    {
        return plugin ? plugin->d_license() : "";
    }

    uint32_t version()
    {
        return plugin ? plugin->d_version() : 1000;
    }

    long uniqueId()
    {
        return plugin ? plugin->d_uniqueId() : 0;
    }

    // ---------------------------------------------

    uint32_t latency() const
    {
        return data ? data->latency : 0;
    }

    uint32_t parameterCount() const
    {
        return data ? data->parameterCount : 0;
    }

    uint32_t parameterHints(uint32_t index) const
    {
        assert(data && index < data->parameterCount);
        return (data && index < data->parameterCount) ? data->parameters[index].hints : 0;
    }

    bool parameterIsOutput(uint32_t index) const
    {
        uint32_t hints = parameterHints(index);
        return bool(hints & PARAMETER_IS_OUTPUT);
    }

    const char* parameterName(uint32_t index) const
    {
        assert(data && index < data->parameterCount);
        return (data && index < data->parameterCount) ? data->parameters[index].name : "";
    }

    const char* parameterSymbol(uint32_t index) const
    {
        assert(data && index < data->parameterCount);
        return (data && index < data->parameterCount) ? data->parameters[index].symbol : nullptr;
    }

    const ParameterRanges* parameterRanges(uint32_t index) const
    {
        assert(data && index < data->parameterCount);
        return (data && index < data->parameterCount) ? &data->parameters[index].ranges : &fallbackRanges;
    }

    float parameterValue(uint32_t index)
    {
        assert(plugin && index < data->parameterCount);
        return (plugin && index < data->parameterCount) ? plugin->d_parameterValue(index) : 0.0f;
    }

    void setParameterValue(uint32_t index, float value)
    {
        assert(plugin && index < data->parameterCount);
        if (plugin && index < data->parameterCount)
            plugin->d_setParameterValue(index, value);
    }

#if DISTRHO_PLUGIN_WANT_PROGRAMS
    uint32_t programCount() const
    {
        return data ? data->programCount : 0;
    }

    const char* programName(uint32_t index) const
    {
        assert(index < data->programCount);
        return (index < data->programCount) ? data->programNames[index] : nullptr;
    }

    void setProgram(uint32_t index)
    {
        assert(plugin && index < data->programCount);
        if (plugin && index < data->programCount)
            plugin->d_setProgram(index);
    }
#endif

    // ---------------------------------------------

    void activate()
    {
        if (plugin)
            plugin->d_activate();
    }

    void deactivate()
    {
        if (plugin)
            plugin->d_deactivate();
    }

    void run(const float** inputs, float** outputs, uint32_t frames, uint32_t midiEventCount, const MidiEvent* midiEvents)
    {
        assert(frames >= 2);

        if (plugin)
            plugin->d_run(inputs, outputs, frames, midiEventCount, midiEvents);
    }

    void setBufferSize(uint32_t bufferSize, bool callback = false)
    {
        assert(bufferSize >= 2);

        if (data)
            data->bufferSize = bufferSize;

        if (plugin && callback)
        {
            plugin->d_deactivate();
            plugin->d_bufferSizeChanged(bufferSize);
            plugin->d_activate();
        }
    }

    void setSampleRate(double sampleRate)
    {
        assert(sampleRate > 0.0);

        if (data)
            data->sampleRate = sampleRate;
    }

    // ---------------------------------------------

#if DISTRHO_PLUGIN_WANT_STATE
    void changeState(const char* key, const char* value)
    {
        assert(key);
        assert(value);

        if (plugin)
            plugin->d_stateChanged(key, value);
    }
#endif

protected:
    Plugin* const plugin;
    PluginPrivateData* data;
};

// -------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // __DISTRHO_PLUGIN_INTERNAL_H__
