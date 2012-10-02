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

// TODO - don't use sample-rate port if not (UI or DSSI)

#if defined(DISTRHO_PLUGIN_TARGET_LADSPA) || defined(DISTRHO_PLUGIN_TARGET_DSSI)

#include "DistrhoPluginInternal.h"

#ifdef DISTRHO_PLUGIN_TARGET_DSSI
# include "dssi/dssi.h"
# define DISTRHO_DSSI_USE_PROGRAMS (DISTRHO_PLUGIN_WANT_PROGRAMS && ! DISTRHO_PLUGIN_WANT_STATE)
#else
# include "ladspa/ladspa.h"
# if DISTRHO_PLUGIN_IS_SYNTH
#  error Cannot build synth plugin with LADSPA
# endif
#endif

#include <cstdio>
#include <vector>

typedef LADSPA_Data*                LADSPA_DataPtr;
typedef std::vector<LADSPA_Data>    LADSPA_DataVector;
typedef std::vector<LADSPA_DataPtr> LADSPA_DataPtrVector;

// -------------------------------------------------

START_NAMESPACE_DISTRHO

class PluginLadspaDssi
{
public:
    PluginLadspaDssi(double sampleRate)
        : lastBufferSize(512),
          lastSampleRate(sampleRate)
    {
        plugin.setBufferSize(lastBufferSize);
        plugin.setSampleRate(lastSampleRate);

        for (uint32_t i=0; i < DISTRHO_PLUGIN_NUM_INPUTS; i++)
            portAudioIns.push_back(nullptr);

        for (uint32_t i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++)
            portAudioOuts.push_back(nullptr);

        for (uint32_t i=0; i < plugin.parameterCount(); i++)
        {
            portControls.push_back(nullptr);
            lastControlValues.push_back(plugin.parameterValue(i));
        }

        portLatency    = nullptr;
        portSampleRate = nullptr;
    }

    ~PluginLadspaDssi()
    {
        portAudioIns.clear();
        portAudioOuts.clear();
        portControls.clear();
        lastControlValues.clear();
    }

    void ladspa_activate()
    {
        plugin.activate();
        updateParameterOutputs();
    }

    void ladspa_deactivate()
    {
        plugin.deactivate();
    }

    void ladspa_connect_port(unsigned long port, LADSPA_DataPtr dataLocation)
    {
        unsigned long i, index = 0;

        for (i=0; i < DISTRHO_PLUGIN_NUM_INPUTS; i++)
        {
            if (port == index++)
            {
                portAudioIns[i] = dataLocation;
                return;
            }
        }

        for (i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++)
        {
            if (port == index++)
            {
                portAudioOuts[i] = dataLocation;
                return;
            }
        }

        for (i=0; i < plugin.parameterCount(); i++)
        {
            if (port == index++)
            {
                portControls[i] = dataLocation;
                return;
            }
        }

        if (port == index++)
        {
            portLatency = dataLocation;
            return;
        }

        if (port == index++)
        {
            portSampleRate = dataLocation;
            return;
        }
    }

#ifdef DISTRHO_PLUGIN_TARGET_DSSI
# if DISTRHO_PLUGIN_WANT_STATE
    char* dssi_configure(const char* key, const char* value)
    {
        if (strncmp(key, DSSI_RESERVED_CONFIGURE_PREFIX, strlen(DSSI_RESERVED_CONFIGURE_PREFIX) == 0))
            return nullptr;

        plugin.changeState(key, value);
        return nullptr;
    }
# endif

# if DISTRHO_DSSI_USE_PROGRAMS
    const DSSI_Program_Descriptor* dssi_get_program(unsigned long index)
    {
        if (index >= plugin.programCount())
            return nullptr;

        static DSSI_Program_Descriptor desc;
        desc.Bank    = index / 128;
        desc.Program = index % 128;
        desc.Name    = plugin.programName(index);
        return &desc;
    }

    void dssi_select_program(unsigned long bank, unsigned long program)
    {
        const unsigned long realProgram = bank * 128 + program;

        if (realProgram >= plugin.programCount())
            return;

        plugin.setProgram(realProgram);
    }
# endif

    void ladspa_run(unsigned long bufferSize)
    {
        dssi_run_synth(bufferSize, nullptr, 0);
    }

    void dssi_run_synth(unsigned long bufferSize, snd_seq_event_t* events, unsigned long eventCount)
#else
    void ladspa_run(unsigned long bufferSize)
#endif
    {
        if (bufferSize <= 1)
            return;

        // Check for updated bufferSize
        if (bufferSize != lastBufferSize)
        {
            lastBufferSize = bufferSize;
            plugin.setBufferSize(lastBufferSize, true);
        }

        // Check for updated parameters
        float curValue;

        for (uint32_t i=0; i < plugin.parameterCount(); i++)
        {
            if (! portControls[i])
                continue;

            curValue = *portControls[i];

            if (lastControlValues[i] != curValue && ! plugin.parameterIsOutput(i))
            {
                lastControlValues[i] = curValue;
                plugin.setParameterValue(i, curValue);
            }
        }

        // Get MIDI Events
        uint32_t midiEventCount = 0;

#ifdef DISTRHO_PLUGIN_TARGET_DSSI
# if DISTRHO_PLUGIN_IS_SYNTH
        for (uint32_t i=0, j; i < eventCount && midiEventCount < MAX_MIDI_EVENTS; i++)
        {
            if (events[i].type == SND_SEQ_EVENT_NOTEON)
            {
                j = midiEventCount++;
                midiEvents[j].frame = events[i].time.tick;
                midiEvents[j].buffer[0] = 0x90 + events[i].data.note.channel;
                midiEvents[j].buffer[1] = events[i].data.note.note;
                midiEvents[j].buffer[2] = events[i].data.note.velocity;
            }
            else if (events[i].type == SND_SEQ_EVENT_NOTEOFF)
            {
                j = midiEventCount++;
                midiEvents[j].frame = events[i].time.tick;
                midiEvents[j].buffer[0] = 0x80 + events[i].data.note.channel;
                midiEvents[j].buffer[1] = events[i].data.note.note;
                midiEvents[j].buffer[2] = 0;
                midiEventCount++;
            }
            // TODO - sound/notes off, other types
        }
# else
        // unused
        (void)events;
        (void)eventCount;
# endif
#endif

        // Run plugin for this cycle
        const float* inputs[DISTRHO_PLUGIN_NUM_INPUTS];
        float*       outputs[DISTRHO_PLUGIN_NUM_OUTPUTS];

        for (uint32_t i=0; i < DISTRHO_PLUGIN_NUM_INPUTS; i++)
            inputs[i] = portAudioIns[i];

        for (uint32_t i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++)
            outputs[i] = portAudioOuts[i];

        plugin.run(inputs, outputs, bufferSize, midiEventCount, midiEvents);

        updateParameterOutputs();
    }

private:
    PluginInternal plugin;

    // LADSPA ports
    LADSPA_DataPtrVector portAudioIns;
    LADSPA_DataPtrVector portAudioOuts;
    LADSPA_DataPtrVector portControls;
    LADSPA_DataPtr       portLatency;
    LADSPA_DataPtr       portSampleRate;

    // Temporary data
    unsigned long     lastBufferSize;
    const double      lastSampleRate;
    LADSPA_DataVector lastControlValues;

#if DISTRHO_PLUGIN_IS_SYNTH
    MidiEvent midiEvents[MAX_MIDI_EVENTS];
#else
    MidiEvent midiEvents[0];
#endif

    void updateParameterOutputs()
    {
        for (uint32_t i=0; i < plugin.parameterCount(); i++)
        {
            if (plugin.parameterIsOutput(i))
                lastControlValues[i] = *portControls[i] = plugin.parameterValue(i);
        }

        if (portLatency)
            *portLatency = plugin.latency();

        if (portSampleRate)
            *portSampleRate = lastSampleRate;
    }
};

// -------------------------------------------------

static LADSPA_Handle ladspa_instantiate(const LADSPA_Descriptor*, unsigned long sampleRate)
{
    return new PluginLadspaDssi(sampleRate);
}

static void ladspa_connect_port(LADSPA_Handle instance, unsigned long port, LADSPA_Data* dataLocation)
{
    PluginLadspaDssi* plugin = (PluginLadspaDssi*)instance;
    assert(plugin);

    plugin->ladspa_connect_port(port, dataLocation);
}

static void ladspa_activate(LADSPA_Handle instance)
{
    PluginLadspaDssi* plugin = (PluginLadspaDssi*)instance;
    assert(plugin);

    plugin->ladspa_activate();
}

static void ladspa_run(LADSPA_Handle instance, unsigned long sampleCount)
{
    PluginLadspaDssi* plugin = (PluginLadspaDssi*)instance;
    assert(plugin);

    plugin->ladspa_run(sampleCount);
}

static void ladspa_deactivate(LADSPA_Handle instance)
{
    PluginLadspaDssi* plugin = (PluginLadspaDssi*)instance;
    assert(plugin);

    plugin->ladspa_deactivate();
}

static void ladspa_cleanup(LADSPA_Handle instance)
{
    PluginLadspaDssi* plugin = (PluginLadspaDssi*)instance;
    assert(plugin);

    delete plugin;
}

#ifdef DISTRHO_PLUGIN_TARGET_DSSI
# if DISTRHO_PLUGIN_WANT_STATE
static char* dssi_configure(LADSPA_Handle instance, const char* key, const char* value)
{
    PluginLadspaDssi* plugin = (PluginLadspaDssi*)instance;
    assert(plugin);

    return plugin->dssi_configure(key, value);
}
#endif

# if DISTRHO_DSSI_USE_PROGRAMS
static const DSSI_Program_Descriptor* dssi_get_program(LADSPA_Handle instance, unsigned long index)
{
    PluginLadspaDssi* plugin = (PluginLadspaDssi*)instance;
    assert(plugin);

    return plugin->dssi_get_program(index);
}

static void dssi_select_program(LADSPA_Handle instance, unsigned long bank, unsigned long program)
{
    PluginLadspaDssi* plugin = (PluginLadspaDssi*)instance;
    assert(plugin);

    plugin->dssi_select_program(bank, program);
}
# endif

# if DISTRHO_PLUGIN_IS_SYNTH
static void dssi_run_synth(LADSPA_Handle instance, unsigned long sampleCount, snd_seq_event_t* events, unsigned long eventCount)
{
    PluginLadspaDssi* plugin = (PluginLadspaDssi*)instance;
    assert(plugin);

    plugin->dssi_run_synth(sampleCount, events, eventCount);
}
# endif
#endif

// -------------------------------------------------

static LADSPA_Descriptor ldescriptor = {
    /* UniqueID   */ 0,
    /* Label      */ nullptr,
    /* Properties */ LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
    /* Name       */ nullptr,
    /* Maker      */ nullptr,
    /* Copyright  */ nullptr,
    /* PortCount  */ 0,
    /* PortDescriptors    */ nullptr,
    /* PortNames          */ nullptr,
    /* PortRangeHints     */ nullptr,
    /* ImplementationData */ nullptr,
    ladspa_instantiate,
    ladspa_connect_port,
    ladspa_activate,
    ladspa_run,
    /* run_adding */          nullptr,
    /* set_run_adding_gain */ nullptr,
    ladspa_deactivate,
    ladspa_cleanup
};

#ifdef DISTRHO_PLUGIN_TARGET_DSSI
static DSSI_Descriptor descriptor = {
    1,
    &ldescriptor,
# if DISTRHO_PLUGIN_WANT_STATE
    dssi_configure,
# else
    /* configure                    */ nullptr,
# endif
# if DISTRHO_DSSI_USE_PROGRAMS
    dssi_get_program,
    dssi_select_program,
# else
    /* get_program                  */ nullptr,
    /* select_program               */ nullptr,
# endif
    /* get_midi_controller_for_port */ nullptr,
# if DISTRHO_PLUGIN_IS_SYNTH
    dssi_run_synth,
# else
    /* run_synth                    */ nullptr,
# endif
    /* run_synth_adding             */ nullptr,
    /* run_multiple_synths          */ nullptr,
    /* run_multiple_synths_adding   */ nullptr
};
#endif

// -------------------------------------------------

class DescriptorInitializer
{
public:
    DescriptorInitializer()
    {
        // Create dummy plugin to get data from
        PluginInternal plugin;

        // Get port count, init
        unsigned long i, port = 0;
        unsigned long portCount = DISTRHO_PLUGIN_NUM_INPUTS + DISTRHO_PLUGIN_NUM_OUTPUTS + plugin.parameterCount() + 2;
        const char** portNames  = new const char* [portCount];
        LADSPA_PortDescriptor* portDescriptors = new LADSPA_PortDescriptor [portCount];
        LADSPA_PortRangeHint*  portRangeHints  = new LADSPA_PortRangeHint  [portCount];

        // Set ports
        for (i=0; i < DISTRHO_PLUGIN_NUM_INPUTS; i++, port++)
        {
            char portName[16] = { 0 };
            sprintf(portName, "audio_in_%lu", i+1);

            portNames[port]       = strdup(portName);
            portDescriptors[port] = LADSPA_PORT_AUDIO | LADSPA_PORT_INPUT;

            portRangeHints[port].HintDescriptor = 0;
            portRangeHints[port].LowerBound = 0.0f;
            portRangeHints[port].UpperBound = 1.0f;
        }

        for (i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++, port++)
        {
            char portName[16] = { 0 };
            sprintf(portName, "audio_out_%lu", i+1);

            portNames[port]       = strdup(portName);
            portDescriptors[port] = LADSPA_PORT_AUDIO | LADSPA_PORT_OUTPUT;

            portRangeHints[port].HintDescriptor = 0;
            portRangeHints[port].LowerBound = 0.0f;
            portRangeHints[port].UpperBound = 1.0f;
        }

        for (i=0; i < plugin.parameterCount(); i++, port++)
        {
            portNames[port]       = plugin.parameterName(i);
            portDescriptors[port] = LADSPA_PORT_CONTROL;

            if (plugin.parameterIsOutput(i))
                portDescriptors[port] |= LADSPA_PORT_OUTPUT;
            else
                portDescriptors[port] |= LADSPA_PORT_INPUT;

            {
                const ParameterRanges* ranges = plugin.parameterRanges(i);
                const float defValue = ranges->def;

                portRangeHints[port].HintDescriptor = LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE;
                portRangeHints[port].LowerBound     = ranges->min;
                portRangeHints[port].UpperBound     = ranges->max;

                if (defValue == 0.0f)
                    portRangeHints[port].HintDescriptor |= LADSPA_HINT_DEFAULT_0;
                else if (defValue == 1.0f)
                    portRangeHints[port].HintDescriptor |= LADSPA_HINT_DEFAULT_1;
                else if (defValue == 100.0f)
                    portRangeHints[port].HintDescriptor |= LADSPA_HINT_DEFAULT_100;
                else if (defValue == 440.0f)
                    portRangeHints[port].HintDescriptor |= LADSPA_HINT_DEFAULT_440;
                else if (ranges->min == defValue)
                    portRangeHints[port].HintDescriptor |= LADSPA_HINT_DEFAULT_MINIMUM;
                else if (ranges->max == defValue)
                    portRangeHints[port].HintDescriptor |= LADSPA_HINT_DEFAULT_MAXIMUM;
                else
                {
                    const float middleValue = ranges->min/2 + ranges->max/2;
                    const float middleLow   = (ranges->min/2 + middleValue/2)/2 + middleValue/2;
                    const float middleHigh  = (ranges->max/2 + middleValue/2)/2 + middleValue/2;

                    if (defValue < middleLow)
                        portRangeHints[port].HintDescriptor |= LADSPA_HINT_DEFAULT_LOW;
                    else if (defValue > middleHigh)
                        portRangeHints[port].HintDescriptor |= LADSPA_HINT_DEFAULT_HIGH;
                    else
                        portRangeHints[port].HintDescriptor |= LADSPA_HINT_DEFAULT_MIDDLE;
                }
            }

            {
                uint32_t hints = plugin.parameterHints(i);

                if (hints & PARAMETER_IS_BOOLEAN)
                    portRangeHints[port].HintDescriptor |= LADSPA_HINT_TOGGLED;
                if (hints & PARAMETER_IS_INTEGER)
                    portRangeHints[port].HintDescriptor |= LADSPA_HINT_INTEGER;
            }
        }

        // Set latency port
        portNames[port]       = strdup("_latency");
        portDescriptors[port] = LADSPA_PORT_CONTROL | LADSPA_PORT_OUTPUT;
        portRangeHints[port].HintDescriptor = LADSPA_HINT_SAMPLE_RATE;
        portRangeHints[port].LowerBound     = 0.0f;
        portRangeHints[port].UpperBound     = 1.0f;
        port++;

        // Set sample-rate port
        portNames[port]       = strdup("_sample-rate");
        portDescriptors[port] = LADSPA_PORT_CONTROL | LADSPA_PORT_OUTPUT;
        portRangeHints[port].HintDescriptor = LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE;
        portRangeHints[port].LowerBound     = 0.0f;
        portRangeHints[port].UpperBound     = 256000.0f;
        port++;

        // Set data
        ldescriptor.UniqueID  = plugin.uniqueId();
        ldescriptor.Label     = strdup(plugin.label());
        ldescriptor.Name      = strdup(plugin.name());
        ldescriptor.Maker     = strdup(plugin.maker());
        ldescriptor.Copyright = strdup(plugin.license());
        ldescriptor.PortCount = portCount;
        ldescriptor.PortNames = portNames;
        ldescriptor.PortDescriptors = portDescriptors;
        ldescriptor.PortRangeHints  = portRangeHints;
    }

    ~DescriptorInitializer()
    {
        if (ldescriptor.Label)
            free((void*)ldescriptor.Label);

        if (ldescriptor.Name)
            free((void*)ldescriptor.Name);

        if (ldescriptor.Maker)
            free((void*)ldescriptor.Maker);

        if (ldescriptor.Copyright)
            free((void*)ldescriptor.Copyright);

        if (ldescriptor.PortDescriptors)
            delete[] ldescriptor.PortDescriptors;

        if (ldescriptor.PortNames)
        {
            for (unsigned long i=0; i < ldescriptor.PortCount; i++)
            {
                if (ldescriptor.PortNames[i])
                    free((void*)ldescriptor.PortNames[i]);
            }

            delete[] ldescriptor.PortNames;
        }

        if (ldescriptor.PortRangeHints)
            delete[] ldescriptor.PortRangeHints;
    }
};

static DescriptorInitializer init;

END_NAMESPACE_DISTRHO

// -------------------------------------------------

DISTRHO_PLUGIN_EXPORT
const LADSPA_Descriptor* ladspa_descriptor(unsigned long index)
{
    USE_NAMESPACE_DISTRHO
    return (index == 0) ? &ldescriptor : nullptr;
}

#ifdef DISTRHO_PLUGIN_TARGET_DSSI
DISTRHO_PLUGIN_EXPORT
const DSSI_Descriptor* dssi_descriptor(unsigned long index)
{
    USE_NAMESPACE_DISTRHO
    return (index == 0) ? &descriptor : nullptr;
}
#endif

// -------------------------------------------------

#endif // defined(DISTRHO_PLUGIN_TARGET_LADSPA) || defined(DISTRHO_PLUGIN_TARGET_DSSI)
