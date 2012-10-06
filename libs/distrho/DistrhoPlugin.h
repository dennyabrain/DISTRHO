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

#ifndef __DISTRHO_PLUGIN_H__
#define __DISTRHO_PLUGIN_H__

#include "DistrhoUtils.h"

START_NAMESPACE_DISTRHO

// -------------------------------------------------

// Parameter Hints
const uint32_t PARAMETER_IS_AUTOMABLE = 1 << 0;
const uint32_t PARAMETER_IS_BOOLEAN   = 1 << 1;
const uint32_t PARAMETER_IS_INTEGER   = 1 << 2;
const uint32_t PARAMETER_IS_OUTPUT    = 1 << 3;

// Parameter Ranges
struct ParameterRanges {
    float def;
    float min;
    float max;
    float step;
    float stepSmall;
    float stepLarge;

    ParameterRanges()
        : def(0.0f),
          min(0.0f),
          max(1.0f),
          step(0.001f),
          stepSmall(0.00001f),
          stepLarge(0.01f) {}

    ParameterRanges(float def, float min, float max)
        : step(0.001f),
          stepSmall(0.00001f),
          stepLarge(0.01f)
    {
        this->def = def;
        this->min = min;
        this->max = max;
    }

    void fixRange(float& value) const
    {
        if (value < min)
            value = min;
        else if (value > max)
            value = max;
    }
};

// Parameter
struct Parameter {
    uint32_t hints;
    d_string name;
    d_string symbol;
    d_string unit;
    ParameterRanges ranges;

    Parameter()
        : hints(0x0),
          name(nullptr),
          symbol(nullptr),
          unit(nullptr) {}
};

// MidiEvent
struct MidiEvent {
    uint32_t frame;
    uint8_t  buffer[3];

    MidiEvent()
#if 0
        : frame(0),
          buffer{0} {}
#else
        : frame(0) { buffer[0] = buffer[1] = buffer[2] = 0; }
#endif
};

// TimePos
struct TimePos {
    double bpm;

    TimePos()
        : bpm(120.0) {}
};

// -------------------------------------------------

struct PluginPrivateData;

class Plugin
{
public:
    Plugin(uint32_t parameterCount, uint32_t programCount);
    virtual ~Plugin();

    // ---------------------------------------------

    // Host state
    uint32_t       d_bufferSize() const;
    double         d_sampleRate() const;
    const TimePos* d_timePos() const;
    void           d_setLatency(uint32_t samples);

    // ---------------------------------------------

protected:
    // Information
    virtual const char* d_name()  = 0;
    virtual const char* d_label() = 0;
    virtual const char* d_maker() = 0;
    virtual const char* d_license() = 0;
    virtual uint32_t    d_version() = 0;
    virtual long        d_uniqueId() = 0;

    // Init
    virtual void d_initParameter(uint32_t index, Parameter& parameter) = 0;
#if DISTRHO_PLUGIN_WANT_PROGRAMS
    virtual void d_initProgramName(uint32_t index, d_string& programName) = 0;
#endif

    // Internal data
    virtual float d_parameterValue(uint32_t index) = 0;
    virtual void  d_setParameterValue(uint32_t index, float value) = 0;
#if DISTRHO_PLUGIN_WANT_PROGRAMS
    virtual void  d_setProgram(uint32_t index) = 0;
#endif

    // Process
    virtual void d_activate() = 0;
    virtual void d_deactivate() = 0;
    virtual void d_run(const float** inputs, float** outputs, uint32_t frames, uint32_t midiEventCount, const MidiEvent* midiEvents) = 0;

    // Callbacks
    virtual void d_bufferSizeChanged(uint32_t newBufferSize);
#if DISTRHO_PLUGIN_WANT_STATE
    virtual void d_stateChanged(const char* key, const char* value) = 0;
#endif

    // ---------------------------------------------

private:
    PluginPrivateData* data;
    friend class PluginInternal;
};

Plugin* createPlugin();

// -------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // __DISTRHO_PLUGIN_H__
