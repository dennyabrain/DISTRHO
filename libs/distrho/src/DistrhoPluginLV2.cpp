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

#ifdef DISTRHO_PLUGIN_TARGET_LV2

#include "DistrhoPluginInternal.h"

#include "lv2-sdk/lv2.h"
#include "lv2-sdk/atom.h"
#include "lv2-sdk/atom-util.h"
#include "lv2-sdk/midi.h"
#include "lv2-sdk/patch.h"
#include "lv2-sdk/programs.h"
#include "lv2-sdk/state.h"
#include "lv2-sdk/urid.h"

#include <cassert>
#include <map>
#include <vector>

#ifndef DISTRHO_PLUGIN_URI
# error DISTRHO_PLUGIN_URI undefined!
#endif

#define DISTRHO_LV2_STATE_URI "urn:distrho:lv2State"

#define DISTRHO_LV2_USE_EVENTS         (DISTRHO_PLUGIN_IS_SYNTH || DISTRHO_PLUGIN_WANT_STATE)
#define DISTRHO_LV2_USE_EXTENSION_DATA (DISTRHO_PLUGIN_WANT_PROGRAMS || DISTRHO_PLUGIN_WANT_STATE)

typedef float*                floatptr;
typedef std::vector<float>    floatVector;
typedef std::vector<floatptr> floatptrVector;

typedef std::map<char*,char*> charMap;

// -------------------------------------------------

START_NAMESPACE_DISTRHO

class PluginLv2
{
public:
    PluginLv2(double sampleRate, const LV2_Feature* const* features)
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
#if DISTRHO_PLUGIN_HAS_UI
        portSampleRate = nullptr;
#endif

        // xxx
#if DISTRHO_LV2_USE_EVENTS
        portEventsIn   = nullptr;
#endif

#if DISTRHO_LV2_USE_EVENTS
        // URIDs
        uridMap        = nullptr;
# if DISTRHO_PLUGIN_IS_SYNTH
        uridIdMidiEvent    = 0;
# endif
# if DISTRHO_PLUGIN_WANT_STATE
        uridIdPatchMessage = 0;
# endif

        for (uint32_t i=0; features[i]; i++)
        {
            if (strcmp(features[i]->URI, LV2_URID_MAP_URI) == 0)
            {
                uridMap = (LV2_URID_Map*)features[i]->data;
# if DISTRHO_PLUGIN_IS_SYNTH
                uridIdMidiEvent    = uridMap->map(uridMap->handle, LV2_MIDI__MidiEvent);
# endif
# if DISTRHO_PLUGIN_WANT_STATE
                uridIdPatchMessage = uridMap->map(uridMap->handle, LV2_PATCH__Message);
# endif
                break;
            }
        }
#else
        (void)features;
#endif
    }

    ~PluginLv2()
    {
        portAudioIns.clear();
        portAudioOuts.clear();
        portControls.clear();
        lastControlValues.clear();

        // xxx
#if DISTRHO_PLUGIN_WANT_STATE
        // TODO - free values
        stateMap.clear();
#endif
    }

    void lv2_activate()
    {
        plugin.activate();
        updateParameterOutputs();
    }

    void lv2_deactivate()
    {
        plugin.deactivate();
    }

    void lv2_connect_port(uint32_t port, void* dataLocation)
    {
        uint32_t i, index = 0;

        for (i=0; i < DISTRHO_PLUGIN_NUM_INPUTS; i++)
        {
            if (port == index++)
            {
                portAudioIns[i] = (floatptr)dataLocation;
                return;
            }
        }

        for (i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++)
        {
            if (port == index++)
            {
                portAudioOuts[i] = (floatptr)dataLocation;
                return;
            }
        }

        for (i=0; i < plugin.parameterCount(); i++)
        {
            if (port == index++)
            {
                portControls[i] = (floatptr)dataLocation;
                return;
            }
        }

        // xxx
#if DISTRHO_LV2_USE_EVENTS
        if (port == index++)
        {
            portEventsIn = (LV2_Atom_Sequence*)dataLocation;
            return;
        }
#endif

        if (port == index++)
        {
            portLatency = (floatptr)dataLocation;
            return;
        }

#if DISTRHO_PLUGIN_HAS_UI
        if (port == index++)
        {
            portSampleRate = (floatptr)dataLocation;
            return;
        }
#endif
    }

    void lv2_run(uint32_t bufferSize)
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

        // Get Events, xxx
        uint32_t midiEventCount = 0;

#if DISTRHO_LV2_USE_EVENTS
        LV2_ATOM_SEQUENCE_FOREACH(portEventsIn, iter)
        {
            LV2_Atom_Event* const event = (LV2_Atom_Event* const)iter;

            if (! event)
                continue;

# if DISTRHO_PLUGIN_IS_SYNTH
            if (event->body.type == uridIdMidiEvent)
            {
                if (event->time.frames >= bufferSize || midiEventCount >= MAX_MIDI_EVENTS)
                    break;

                if (event->body.size > 3)
                    continue;

                uint8_t* const data = (uint8_t* const)(event + 1);

                midiEvents[midiEventCount].frame     = event->time.frames;
                memcpy(midiEvents[midiEventCount].buffer, data, event->body.size);

                midiEventCount += 1;
                continue;
            }
# endif
# if DISTRHO_PLUGIN_WANT_STATE
            if (event->body.type == uridIdPatchMessage)
            {
                // TODO
            }
# endif
        }
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

#if DISTRHO_PLUGIN_WANT_PROGRAMS
    const LV2_Program_Descriptor* lv2_get_program(uint32_t index)
    {
        if (index >= plugin.programCount())
            return nullptr;

        static LV2_Program_Descriptor desc;
        desc.bank    = index / 128;
        desc.program = index % 128;
        desc.name    = plugin.programName(index);
        return &desc;
    }

    void lv2_select_program(uint32_t bank, uint32_t program)
    {
        const uint32_t realProgram = bank * 128 + program;

        if (realProgram >= plugin.programCount())
            return;

        plugin.setProgram(realProgram);
    }
#endif

#if DISTRHO_PLUGIN_WANT_STATE
    // xxx - probably needs multiple STATE-URIs, so we're screwed
    LV2_State_Status lv2_save(LV2_State_Store_Function store, LV2_State_Handle handle, uint32_t /*flags*/, const LV2_Feature* const* /*features*/)
    {
        for (auto i = stateMap.begin(); i != stateMap.end(); i++)
        {
            //const char* key   = i->first;
            //const char* value = i->second;

            //size_t keyValueLen = strlen(key) + strlen(value) + 4;
            //char keyValue[keyValueLen+1] = { 0 };

            //strcpy(keyValue, key);
            //strcat(keyValue, " \u00b7 ");
            //strcat(keyValue, value);

            //store(handle, uridMap->map(uridMap->handle, DISTRHO_LV2_STATE_URI), keyValue, keyValueLen, uridMap->map(uridMap->handle, LV2_ATOM__String), LV2_STATE_IS_POD|LV2_STATE_IS_PORTABLE);
        }

        return LV2_STATE_SUCCESS;
    }

    LV2_State_Status lv2_restore(LV2_State_Retrieve_Function retrieve, LV2_State_Handle handle, uint32_t flags, const LV2_Feature* const* /*features*/)
    {
        size_t   size = 0;
        uint32_t type = 0;
        const void* data = retrieve(handle, uridMap->map(uridMap->handle, DISTRHO_LV2_STATE_URI), &size, &type, &flags);

        if (! data)
            return LV2_STATE_ERR_NO_PROPERTY;

        if (type != uridMap->map(uridMap->handle, LV2_ATOM__String))
            return LV2_STATE_ERR_BAD_TYPE;

        // xxx - looks ok, but needs testing
        //const char* keyValue = (const char*)data;
        //const char* value    = strstr(keyValue, " \u00b7 ") + 4;
        //const size_t keyLen  = strlen(keyValue) - strlen(value) - 4;

        //char key[keyLen+1] = { 0 };
        //strncpy(key, keyValue, keyLen);

        //setStateChange(key, value);

        return LV2_STATE_SUCCESS;
    }
#endif

private:
    PluginInternal plugin;

    // LV2 ports
    floatptrVector portAudioIns;
    floatptrVector portAudioOuts;
    floatptrVector portControls;
    floatptr       portLatency;
#if DISTRHO_PLUGIN_HAS_UI
    floatptr       portSampleRate;
#endif

    // xxx
#if DISTRHO_LV2_USE_EVENTS
    LV2_Atom_Sequence* portEventsIn;

    // URIDs
    LV2_URID_Map* uridMap;
# if DISTRHO_PLUGIN_WANT_STATE
    LV2_URID      uridIdPatchMessage;
# endif
# if DISTRHO_PLUGIN_IS_SYNTH
    LV2_URID      uridIdMidiEvent;
# endif
#endif

    // Temporary data
    uint32_t     lastBufferSize;
    const double lastSampleRate;
    floatVector  lastControlValues;

#if DISTRHO_PLUGIN_IS_SYNTH
    MidiEvent midiEvents[MAX_MIDI_EVENTS];
#else
    MidiEvent midiEvents[0];
#endif

    // xxx
#if DISTRHO_PLUGIN_WANT_STATE
    charMap stateMap;

    void setStateChange(char* newKey, const char* newValue)
    {
        plugin.changeState(newKey, newValue);

        // check if key already exists
        for (charMap::iterator i = stateMap.begin(); i != stateMap.end(); i++)
        {
            char* key   = i->first;
            char* value = i->second;

            if (strcmp(key, newKey) == 0)
            {
                free(value);
                i->second = strdup(newValue);
                return;
            }
        }

        // add a new one then
        stateMap[newKey] = strdup(newValue);
    }
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

#if DISTRHO_PLUGIN_HAS_UI
        if (portSampleRate)
            *portSampleRate = lastSampleRate;
#endif
    }
};

// -------------------------------------------------

static LV2_Handle lv2_instantiate(const LV2_Descriptor*, double sampleRate, const char* uri, const LV2_Feature* const* features)
{
    if (strcmp(uri, DISTRHO_PLUGIN_URI) != 0)
        return nullptr;

    return new PluginLv2(sampleRate, features);
}

static void lv2_connect_port(LV2_Handle instance, uint32_t port, void* dataLocation)
{
    PluginLv2* plugin = (PluginLv2*)instance;
    assert(plugin);

    plugin->lv2_connect_port(port, dataLocation);
}

static void lv2_activate(LV2_Handle instance)
{
    PluginLv2* plugin = (PluginLv2*)instance;
    assert(plugin);

    plugin->lv2_activate();
}

static void lv2_run(LV2_Handle instance, uint32_t sampleCount)
{
    PluginLv2* plugin = (PluginLv2*)instance;
    assert(plugin);

    plugin->lv2_run(sampleCount);
}

static void lv2_deactivate(LV2_Handle instance)
{
    PluginLv2* plugin = (PluginLv2*)instance;
    assert(plugin);

    plugin->lv2_deactivate();
}

static void lv2_cleanup(LV2_Handle instance)
{
    PluginLv2* plugin = (PluginLv2*)instance;
    assert(plugin);

    delete plugin;
}

#if DISTRHO_LV2_USE_EXTENSION_DATA
# if DISTRHO_PLUGIN_WANT_PROGRAMS
static const LV2_Program_Descriptor* lv2_get_program(LV2_Handle instance, uint32_t index)
{
    PluginLv2* plugin = (PluginLv2*)instance;
    assert(plugin);

    return plugin->lv2_get_program(index);
}

static void lv2_select_program(LV2_Handle instance, uint32_t bank, uint32_t program)
{
    PluginLv2* plugin = (PluginLv2*)instance;
    assert(plugin);

    plugin->lv2_select_program(bank, program);
}
# endif

# if DISTRHO_PLUGIN_WANT_STATE
static LV2_State_Status lv2_save(LV2_Handle instance, LV2_State_Store_Function store, LV2_State_Handle handle, uint32_t flags, const LV2_Feature* const* features)
{
    PluginLv2* plugin = (PluginLv2*)instance;
    assert(plugin);

    return plugin->lv2_save(store, handle, flags, features);
}

static LV2_State_Status lv2_restore(LV2_Handle instance, LV2_State_Retrieve_Function retrieve, LV2_State_Handle handle, uint32_t flags, const LV2_Feature* const* features)
{
    PluginLv2* plugin = (PluginLv2*)instance;
    assert(plugin);

    return plugin->lv2_restore(retrieve, handle, flags, features);
}
# endif

static const void* lv2_extension_data(const char* uri)
{
# if DISTRHO_PLUGIN_WANT_PROGRAMS
    static const LV2_Programs_Interface programs = { lv2_get_program, lv2_select_program };
    if (strcmp(uri, LV2_PROGRAMS__Interface) == 0)
        return &programs;
# endif

# if DISTRHO_PLUGIN_WANT_STATE
    static const LV2_State_Interface state = { lv2_save, lv2_restore };
    if (strcmp(uri, LV2_STATE__interface) == 0)
        return &state;
# endif

    return nullptr;
}
#endif

// -------------------------------------------------

static LV2_Descriptor descriptor = {
    DISTRHO_PLUGIN_URI,
    lv2_instantiate,
    lv2_connect_port,
    lv2_activate,
    lv2_run,
    lv2_deactivate,
    lv2_cleanup,
#if DISTRHO_LV2_USE_EXTENSION_DATA
    lv2_extension_data
#else
    /* extension_data */ nullptr
#endif
};

END_NAMESPACE_DISTRHO

// -------------------------------------------------

DISTRHO_PLUGIN_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    USE_NAMESPACE_DISTRHO
    return (index == 0) ? &descriptor : nullptr;
}

// -------------------------------------------------

#endif // DISTRHO_PLUGIN_TARGET_LV2
