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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * For a full copy of the license see the GPL.txt file
 */

#ifndef __DISTRHO_PLUGIN_INTERNAL_H__
#define __DISTRHO_PLUGIN_INTERNAL_H__

#include "DistrhoPlugin.h"

#include <cassert>

START_NAMESPACE_DISTRHO

// -------------------------------------------------

#define MAX_MIDI_EVENTS 512

struct PluginPrivateData {
    uint32_t bufferSize;
    double   sampleRate;

    uint32_t   parameterCount;
    Parameter* parameters;

#if DISTRHO_PLUGIN_WANT_PROGRAMS
    uint32_t  programCount;
    d_string* programNames;
#endif

    TimePos  timePos;
    uint32_t latency;

    PluginPrivateData()
        : bufferSize(512),
          sampleRate(44100.0),
          parameterCount(0),
          parameters(nullptr),
#if DISTRHO_PLUGIN_WANT_PROGRAMS
          programCount(0),
          programNames(nullptr),
#endif
          timePos(),
          latency(0) {}

    ~PluginPrivateData()
    {
        if (parameterCount > 0 && parameters)
            delete[] parameters;

#if DISTRHO_PLUGIN_WANT_PROGRAMS
        if (programCount > 0 && programNames)
            delete[] programNames;
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
        assert(plugin);
        return plugin ? plugin->d_name() : "";
    }

    const char* label()
    {
        assert(plugin);
        return plugin ? plugin->d_label() : "";
    }

    const char* maker()
    {
        assert(plugin);
        return plugin ? plugin->d_maker() : "";
    }

    const char* license()
    {
        assert(plugin);
        return plugin ? plugin->d_license() : "";
    }

    uint32_t version()
    {
        assert(plugin);
        return plugin ? plugin->d_version() : 1000;
    }

    long uniqueId()
    {
        assert(plugin);
        return plugin ? plugin->d_uniqueId() : 0;
    }

    // ---------------------------------------------

    uint32_t latency() const
    {
        assert(data);
        return data ? data->latency : 0;
    }

    uint32_t parameterCount() const
    {
        assert(data);
        return data ? data->parameterCount : 0;
    }

    uint32_t parameterHints(uint32_t index) const
    {
        assert(data && index < data->parameterCount);
        return (data && index < data->parameterCount) ? data->parameters[index].hints : 0x0;
    }

    bool parameterIsOutput(uint32_t index) const
    {
        uint32_t hints = parameterHints(index);
        return bool(hints & PARAMETER_IS_OUTPUT);
    }

    const d_string& parameterName(uint32_t index) const
    {
        assert(data && index < data->parameterCount);
        return (data && index < data->parameterCount) ? data->parameters[index].name : fallbackString;
    }

    const d_string& parameterSymbol(uint32_t index) const
    {
        assert(data && index < data->parameterCount);
        return (data && index < data->parameterCount) ? data->parameters[index].symbol : fallbackString;
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
        assert(data);
        return data ? data->programCount : 0;
    }

    const d_string& programName(uint32_t index) const
    {
        assert(data && index < data->programCount);
        return (data && index < data->programCount) ? data->programNames[index].asChar() : fallbackString.asChar();
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
        assert(plugin);

        if (plugin)
            plugin->d_activate();
    }

    void deactivate()
    {
        assert(plugin);

        if (plugin)
            plugin->d_deactivate();
    }

    void run(const float** inputs, float** outputs, uint32_t frames, uint32_t midiEventCount, const MidiEvent* midiEvents)
    {
        assert(plugin && frames >= 2);

        if (plugin)
            plugin->d_run(inputs, outputs, frames, midiEventCount, midiEvents);
    }

    void setBufferSize(uint32_t bufferSize, bool callback = false)
    {
        assert(data && plugin && bufferSize >= 2);

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
        assert(data && sampleRate > 0.0);

        if (data)
            data->sampleRate = sampleRate;
    }

    // ---------------------------------------------

#if DISTRHO_PLUGIN_WANT_STATE
    void changeState(const char* key, const char* value)
    {
        assert(plugin && key && value);

        if (plugin)
            plugin->d_stateChanged(key, value);
    }
#endif

protected:
    Plugin* const plugin;
    PluginPrivateData* data;

private:
    static const d_string        fallbackString;
    static const ParameterRanges fallbackRanges;
};

// -------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // __DISTRHO_PLUGIN_INTERNAL_H__
