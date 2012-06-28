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

#ifndef __DISTRHO_PLUGIN_BASE__
#define __DISTRHO_PLUGIN_BASE__

#include "src/includes.h"

START_NAMESPACE_DISTRHO

#if 0
} /* adjust editor indent */
#endif

// ---------------------------------------------------------------------------------------------

// Parameter Hints
const uint32_t PARAMETER_IS_AUTOMABLE = 1 << 0;
const uint32_t PARAMETER_IS_BOOLEAN   = 1 << 1;
const uint32_t PARAMETER_IS_INTEGER   = 1 << 2;
const uint32_t PARAMETER_IS_OUTPUT    = 1 << 3;

struct ParameterInfo {
    uint32_t    hints;
    const char* name;
    const char* symbol;
    const char* unit;
    struct {
        float def;
        float min;
        float max;
        float step;
        float stepSmall;
        float stepLarge;
    } range;
};

struct MidiEvent {
    uint32_t frame;
    char buffer[3];
};

struct TimePos {
    double bpm;
};

// ---------------------------------------------------------------------------------------------

class DistrhoPluginBase
{
public:
    DistrhoPluginBase(uint32_t parameterCount, uint32_t programCount);
    virtual ~DistrhoPluginBase();

    // -------------------------------------------------

    // Information
    virtual const char* d_name()  = 0;
    virtual const char* d_label() = 0;
    virtual const char* d_maker() = 0;
    virtual const char* d_license() = 0;
    virtual uint32_t    d_version() = 0;
    virtual long        d_uniqueId() = 0;

    // Internal data
    virtual float d_parameterValue(uint32_t index) = 0;
    virtual void  d_setParameterValue(uint32_t index, float value) = 0;
    virtual void  d_setProgram(uint32_t index) = 0;

    // Init
    virtual void d_init() = 0;
    virtual void d_cleanup() = 0;

    // Process
    virtual void d_activate() = 0;
    virtual void d_deactivate() = 0;
    virtual void d_run(float** inputs, float** outputs, uint32_t frames, uint32_t midiEventCount, MidiEvent* midiEvents) = 0;

    // -------------------------------------------------

    // Parameters
    uint32_t             d_parameterCount() const;
    const ParameterInfo* d_parameterInfo(uint32_t index) const;

    // Programs
    uint32_t    d_programCount() const;
    const char* d_programName(uint32_t index) const;

    // Host state
    uint32_t       d_bufferSize() const;
    double         d_sampleRate() const;
    const TimePos* d_timePos() const;
    void           d_setLatency(uint32_t samples);

    // -------------------------------------------------

    // internal use only
    void __setSampleRate(double sampleRate);
    void __setBufferSize(uint32_t bufferSize);
    uint32_t __latency() const;

protected:
    ParameterInfo* p_paramsInfo;
    const char**   p_programNames;

private:
    uint32_t m_parameterCount;
    uint32_t m_programCount;
    uint32_t m_bufferSize;
    double   m_sampleRate;
    TimePos  m_timePos;
    uint32_t m_latency;
};

// ---------------------------------------------------------------------------------------------

extern DistrhoPluginBase* createDistrhoPlugin();

END_NAMESPACE_DISTRHO

#endif // __DISTRHO_PLUGIN_BASE__
