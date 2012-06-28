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

#ifndef __DISTRHO_PORT_VST__
#define __DISTRHO_PORT_VST__

#include "PluginBase.h"

#include <cmath>
#include <iostream>

// ---------------------------------------------------------------------------------------------

using namespace DISTRHO;

#if DISTRHO_PLUGIN_IS_SYNTH
#define MAX_VST_EVENTS 512
#else
#define MAX_VST_EVENTS 0
#endif

#define vst_strncpy strncpy

#define kVstMaxProgNameLen   24
#define kVstMaxParamStrLen   8
#define kVstMaxVendorStrLen  64
#define kVstMaxProductStrLen 64
#define kVstMaxEffectNameLen 32

#define VST_2_4_EXTENSIONS 1

// VST Plugin Hints
const uint32_t PLUGIN_CAN_REPLACE        = 1 << 0;
const uint32_t PLUGIN_CAN_DOUBLE_REPLACE = 1 << 1;
const uint32_t PLUGIN_USES_CHUNKS        = 1 << 2;

enum VstEventType {
    kVstNullType = 0,
    kVstMidiType = 1
};

enum VstPlugCategory {
  kPlugCategEffect = 0
};

struct VstMidiEvent {
    VstEventType type;
    int32_t deltaFrames;
    char midiData[4];
};

struct VstEvents {
    int32_t numEvents;
    VstMidiEvent* events[MAX_VST_EVENTS];
};

struct VstPinProperties {};
struct VstTimeInfo {};

typedef int32_t VstInt32;
typedef void* audioMasterCallback;
typedef DistrhoPluginBase AudioEffect;

// ---------------------------------------------------------------------------------------------

static inline void name_to_symbol(char* text)
{
    for (size_t i = 0, len = strlen(text); i < len; i++)
    {
        if (std::isalpha(text[i]))
        {
            // to lower case
            if (text[i] <= 'Z')
                text[i] += 'z' - 'Z';
        }
        else if (std::isdigit(text[i]))
        {
            // cannot start with a digit
            if (i == 0)
                text[i] = '_';
        }
        else
            text[i] = '_';
    }
}

static inline long CCONST(int a, int b, int c, int d)
{
    return (a << 24) | (b << 16) | (c << 8) | (d << 0);
}

// ---------------------------------------------------------------------------------------------

class AudioEffectX : public DistrhoPluginBase
{
public:
    AudioEffectX(audioMasterCallback, uint32_t programCount, uint32_t parameterCount) :
        DistrhoPluginBase(parameterCount, programCount),
        curProgram(0)
    {
        m_name     = nullptr;
        m_label    = nullptr;
        m_maker    = nullptr;
        m_license  = nullptr;
        m_uniqueId = 0;

        vst_hints  = 0;
        vst_events.numEvents = 0;

        for (uint32_t i=0; i < MAX_VST_EVENTS; i++)
            vst_events.events[i] = &events[i];
    }

    virtual ~AudioEffectX()
    {
    }

    // -------------------------------------------------
    // Information

    const char* d_name()
    {
        return m_name;
    }

    const char* d_label()
    {
        return m_label;
    }

    const char* d_maker()
    {
        return m_maker;
    }

    const char* d_license()
    {
        return m_license;
    }

    uint32_t d_version()
    {
        return getVendorVersion();
    }

    long d_uniqueId()
    {
        return m_uniqueId;
    }

    // -------------------------------------------------
    // Internal data

    float d_parameterValue(uint32_t index)
    {
        if (index < d_parameterCount())
            return getParameter(index);
        return 0.0f;
    }

    void d_setParameterValue(uint32_t index, float value)
    {
        if (index < d_parameterCount())
            setParameter(index, value);
    }

    void d_setProgram(uint32_t index)
    {
        if (index < d_programCount())
            setProgram(index);
    }

    // -------------------------------------------------
    // Init

    void d_init()
    {
        char buf_str[256] = { 0 };

        getEffectName(buf_str);
        m_name = strdup(buf_str);

        name_to_symbol(buf_str);
        m_label = strdup(buf_str);

        getVendorString(buf_str);
        m_maker = strdup(buf_str);

        for (uint32_t i = 0; i < d_parameterCount(); i++)
        {
            // TODO
            p_paramsInfo[i].hints |= PARAMETER_IS_AUTOMABLE;

            getParameterName(i, buf_str);
            p_paramsInfo[i].name = strdup(buf_str);

            char* symbol = strdup(p_paramsInfo[i].name);
            name_to_symbol(symbol);
            p_paramsInfo[i].symbol = symbol;

            getParameterLabel(i, buf_str);
            p_paramsInfo[i].unit = strdup(buf_str);

            p_paramsInfo[i].range.def  = getParameter(i);
            p_paramsInfo[i].range.max  = 1.0f;
            p_paramsInfo[i].range.step = 0.001f;
            p_paramsInfo[i].range.stepSmall = 0.00001f;
            p_paramsInfo[i].range.stepLarge = 0.01f;
        }

        for (uint32_t i = 0; i < d_programCount(); i++)
        {
            //buf_str[0] = 0;
            //getProgramName_(i, buf_str);
            //if (buf_str[0] != 0)
            //    p_programs[i] = strdup(buf_str);
        }
    }

    void d_cleanup()
    {
        if (m_name)
            free((void*)m_name);

        if (m_maker)
            free((void*)m_maker);

        if (m_license)
            free((void*)m_license);

        m_name    = nullptr;
        m_maker   = nullptr;
        m_license = nullptr;
    }

    // -------------------------------------------------
    // Process stuff

    void d_activate()
    {
        resume();
    }

    void d_deactivate()
    {
        suspend();
    }

    void d_run(float** inputs, float** outputs, uint32_t frames, uint32_t midiEventCount, MidiEvent* midiEvents)
    {
        vst_events.numEvents = 0;

        for (uint32_t i=0; i < midiEventCount && i < MAX_VST_EVENTS; i++, vst_events.numEvents++)
        {
            VstMidiEvent* const event = vst_events.events[i];
            event->deltaFrames = midiEvents[i].frame;
            event->midiData[0] = midiEvents[i].buffer[0];
            event->midiData[1] = midiEvents[i].buffer[1];
            event->midiData[2] = midiEvents[i].buffer[2];
        }

        if (vst_events.numEvents > 0)
            processEvents(&vst_events);

        if (vst_hints & PLUGIN_CAN_REPLACE)
        {
            processReplacing(inputs, outputs, frames);
        }
        else
        {
            for (int32_t i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++)
                memset(outputs[i], 0, sizeof(float) * frames);

            process(inputs, outputs, frames);
        }
    }

    // -------------------------------------------------
    // VST side compatibility calls

#ifdef DISTRHO_PLUGIN_BASE_VST_COMPAT
    void canMono() {}
    void wantEvents() {}
#endif

    void canProcessReplacing(bool yesno = true)
    {
        if (yesno)
            vst_hints |= PLUGIN_CAN_REPLACE;
        else
            vst_hints &= ~PLUGIN_CAN_REPLACE;
    }

    void canDoubleReplacing(bool yesno = true)
    {
        if (yesno)
            vst_hints |= PLUGIN_CAN_DOUBLE_REPLACE;
        else
            vst_hints &= ~PLUGIN_CAN_DOUBLE_REPLACE;
    }

    void programsAreChunks()
    {
        vst_hints |= PLUGIN_USES_CHUNKS;
    }

    int32_t canHostDo(const char* /*feature*/)
    {
        return 1;
    }

    void isSynth()
    {
        // already set with macro DISTRHO_PLUGIN_IS_SYNTH
    }

    void updateDisplay()
    {
        // todo - send some update msg
    }

    void setInitialDelay(int32_t samples)
    {
        d_setLatency(samples);
    }

    void setNumInputs(uint32_t /*numInputs*/)
    {
        // already set with macro DISTRHO_PLUGIN_NUM_INPUTS
    }

    void setNumOutputs(uint32_t /*numOutputs*/)
    {
        // already set with macro DISTRHO_PLUGIN_NUM_OUTPUTS
    }

    void setUniqueID(long uniqueId)
    {
        m_uniqueId = uniqueId;
    }

    double getSampleRate()
    {
        return d_sampleRate();
    }

    uint32_t getBufferSize()
    {
        return d_bufferSize();
    }

    int32_t getProgram()
    {
        return curProgram;
    }

    // unused conversion methods
#if DISTRHO_PLUGIN_BASE_VST_COMPAT
    virtual void dB2string(float, char*) {}
    virtual void Hz2string(float, char*) {}
    virtual void ms2string(float, char*) {}
    virtual void float2string(float, char*) {}
    virtual void long2string(long, char*) {}
#else
    virtual void dB2string(float, char*, int32_t) {}
    virtual void Hz2string(float, char*, int32_t) {}
    virtual void ms2string(float, char*, int32_t) {}
    virtual void float2string(float, char*, int32_t) {}
    virtual void int2string(int32_t, char*, int32_t) {}
#endif

    // optionally implemented in plugin
    virtual void resume() {}
    virtual void suspend() {}

    // required
    virtual bool getEffectName(char* name) = 0;
    virtual bool getProductString(char* text) = 0;
    virtual bool getVendorString(char* text) = 0;

#if DISTRHO_PLUGIN_BASE_VST_COMPAT
    virtual long  getVendorVersion() = 0;
    virtual void  setParameter(long index, float value) = 0;
    virtual void  setProgram(long index) { curProgram = index; }
    virtual float getParameter(long index) = 0;
    virtual void  getParameterName(long index, char* text) = 0;
    virtual void  getParameterLabel(long index, char* label) = 0;
    virtual void  process(float** inputs, float** outputs, long sampleFrames) = 0;
    virtual void  processReplacing(float** inputs, float** outputs, long sampleFrames) = 0;
    virtual long  processEvents(VstEvents* /*events*/) { return 0; }
#else
    virtual int32_t getVendorVersion() = 0;
    virtual void    setParameter(int32_t index, float value) = 0;
    virtual float   getParameter(int32_t index) = 0;
    virtual void    getParameterName(int32_t index, char* text) = 0;
    virtual void    getParameterLabel(int32_t index, char* label) = 0;
    virtual void    process(float** /*inputs*/, float** /*outputs*/, int32_t /*sampleFrames*/) {} // optional
    virtual void    processReplacing(float** inputs, float** outputs, int32_t sampleFrames) = 0;
    virtual int32_t processEvents(VstEvents* /*events*/) { return 0; }
#endif

protected:
    int32_t curProgram;

private:
    const char* m_name;
    const char* m_label;
    const char* m_maker;
    const char* m_license;
    long        m_uniqueId;

    uint32_t  vst_hints;
    VstEvents vst_events;
    VstMidiEvent events[MAX_VST_EVENTS];
};

#endif // __DISTRHO_PORT_VST__
