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

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "DistrhoPluginInternal.h"
#include "DistrhoPluginUtils.h"

#ifdef DISTRHO_PLUGIN_TARGET_LV2

#include "lv2-sdk/lv2.h"
#include "lv2-sdk/atom.h"
#include "lv2-sdk/atom-util.h"
#include "lv2-sdk/midi.h"
#include "lv2-sdk/patch.h"
#include "lv2-sdk/programs.h"
#include "lv2-sdk/state.h"
#include "lv2-sdk/urid.h"
#include "lv2-sdk/ui.h"

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

        // LV2 ports
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

    void lv2_connect_port(unsigned long port, void* dataLocation)
    {
        unsigned long i, index = 0;

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

        if (port == index++)
        {
            portSampleRate = (floatptr)dataLocation;
            return;
        }
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

        // Get Events
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
        float* inputs[DISTRHO_PLUGIN_NUM_INPUTS];
        float* outputs[DISTRHO_PLUGIN_NUM_OUTPUTS];

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
        const uint32_t index = bank * 128 + program;

        if (index >= plugin.programCount())
            return;

        plugin.setProgram(index);
    }
#endif

#if DISTRHO_PLUGIN_WANT_STATE
    LV2_State_Status lv2_save(LV2_State_Store_Function store, LV2_State_Handle handle, uint32_t /*flags*/, const LV2_Feature* const* /*features*/)
    {
        for (charMap::iterator i = stateMap.begin(); i != stateMap.end(); i++)
        {
            const char* key   = i->first;
            const char* value = i->second;

            store(handle, uridMap->map(uridMap->handle, DISTRHO_LV2_STATE_URI), value, strlen(key), uridMap->map(uridMap->handle, LV2_ATOM__String), LV2_STATE_IS_POD|LV2_STATE_IS_PORTABLE);
        }

        return LV2_STATE_SUCCESS;
    }

    LV2_State_Status lv2_restore(LV2_State_Retrieve_Function retrieve, LV2_State_Handle handle, uint32_t flags, const LV2_Feature* const* /*features*/)
    {
        size_t   size;
        uint32_t type;
        const void* data = retrieve(handle, uridMap->map(uridMap->handle, DISTRHO_LV2_STATE_URI), &size, &type, &flags);

        if (! data)
            return LV2_STATE_ERR_NO_PROPERTY;

        if (type != uridMap->map(uridMap->handle, LV2_ATOM__String))
            return LV2_STATE_ERR_BAD_TYPE;

        const char* keyValue = (const char*)data;
        const char*  value   = strstr(keyValue, " \u00b7 ") + 4;
        const size_t keyLen  = strlen(keyValue) - strlen(value) - 4;

        char key[keyLen];
        strncpy(key, keyValue, keyLen);

        setStateChange(key, value);

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
    floatptr       portSampleRate;
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

        if (portSampleRate)
            *portSampleRate = lastSampleRate;
    }
};

// -------------------------------------------------

static LV2_Handle lv2_instantiate(const LV2_Descriptor*, double sampleRate, const char*, const LV2_Feature* const* features)
{
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

static void lv2_generate_ttl_func()
{
    PluginInternal plugin;

    const char* pluginLabel = plugin.label();

    char pluginTTL[strlen(pluginLabel)+5];
    strcpy(pluginTTL, pluginLabel);
    strcat(pluginTTL, ".ttl");

    // ---------------------------------------------

    {
        std::cout << "Writing manifest.ttl..."; std::cout.flush();
        std::fstream manifestFile("manifest.ttl", std::ios::out);

        std::string manifestString;
        manifestString += "@prefix lv2:  <" LV2_CORE_PREFIX "> .\n";
        manifestString += "@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .\n";
#if DISTRHO_PLUGIN_HAS_UI
        manifestString += "@prefix ui:   <" LV2_UI_PREFIX "> .\n";
#endif
        manifestString += "\n";

        manifestString += "<" DISTRHO_PLUGIN_URI ">\n";
        manifestString += "    a lv2:Plugin ;\n";
        manifestString += "    lv2:binary <";
        manifestString += pluginLabel;
        manifestString += "." DISTRHO_DLL_EXT "> ;\n";
        manifestString += "    rdfs:seeAlso <";
        manifestString += pluginTTL;
        manifestString += "> .\n";
        manifestString += "\n";

#if DISTRHO_PLUGIN_HAS_UI
        manifestString += "<" DISTRHO_UI_URI ">\n";
#if DISTRHO_OS_MACOS
        manifestString += "    a ui:CocoaUI ;\n";
#elif DISTRHO_OS_MACOS
        manifestString += "    a ui:WindowsUI ;\n";
#else
        manifestString += "    a ui:X11UI ;\n";
#endif
        manifestString += "    ui:binary <";
        manifestString += pluginLabel;
        manifestString += "." DISTRHO_DLL_EXT "> ;\n";
#if DISTRHO_LV2_USE_EVENTS
        manifestString += "    lv2:optionalFeature <" LV2_URID__map "> ,\n";
        manifestString += "                        ui:noUserResize .\n";
#else
        manifestString += "    lv2:optionalFeature ui:noUserResize .\n";
#endif
        manifestString += "\n";
#endif

        manifestFile << manifestString << std::endl;
        manifestFile.close();
        std::cout << " done!" << std::endl;
    }

    // ---------------------------------------------

    {
        std::cout << "Writing " << pluginTTL << "..."; std::cout.flush();
        std::fstream pluginFile(pluginTTL, std::ios::out);

        std::string pluginString;
#if DISTRHO_LV2_USE_EVENTS
        pluginString += "@prefix atom: <" LV2_ATOM_PREFIX "> .\n";
#endif
        pluginString += "@prefix doap: <http://usefulinc.com/ns/doap#> .\n";
        pluginString += "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n";
        pluginString += "@prefix lv2:  <" LV2_CORE_PREFIX "> .\n";
#if DISTRHO_PLUGIN_HAS_UI
        pluginString += "@prefix ui:   <" LV2_UI_PREFIX "> .\n";
#endif
        pluginString += "\n";

        pluginString += "<" DISTRHO_PLUGIN_URI ">\n";
#if DISTRHO_PLUGIN_IS_SYNTH
        pluginString += "    a lv2:InstrumentPlugin, lv2:Plugin ;\n";
#else
        pluginString += "    a lv2:Plugin ;\n";
#endif
        pluginString += "    lv2:optionalFeature <" LV2_CORE__hardRTCapable "> ;\n";
#if DISTRHO_LV2_USE_EVENTS
        pluginString += "    lv2:requiredFeature <" LV2_URID__map "> ;\n";
#endif
#if (DISTRHO_PLUGIN_WANT_STATE && DISTRHO_PLUGIN_WANT_PROGRAMS)
        pluginString += "    lv2:extensionData <" LV2_STATE__interface "> ,\n";
        pluginString += "                      <" LV2_PROGRAMS__Interface "> ;\n";
#elif DISTRHO_PLUGIN_WANT_STATE
        pluginString += "    lv2:extensionData <" LV2_STATE__interface "> ;\n";
#elif DISTRHO_PLUGIN_WANT_PROGRAMS
        pluginString += "    lv2:extensionData <" LV2_PROGRAMS__Interface "> ;\n";
#endif
        pluginString += "\n";

#if DISTRHO_PLUGIN_HAS_UI
        pluginString += "    ui:ui <" DISTRHO_UI_URI "> ;\n";
        pluginString += "\n";
#endif

        {
            uint32_t i, portIndex = 0;
            char portBuf[64] = { 0 };

            for (i=0; i < DISTRHO_PLUGIN_NUM_INPUTS; i++)
            {
                if (i == 0)
                    pluginString += "    lv2:port [\n";
                else
                    pluginString += "    [\n";

                sprintf(portBuf, "%i", portIndex++);
                pluginString += "      a lv2:InputPort, lv2:AudioPort ;\n";
                pluginString += "      lv2:index ";
                pluginString += portBuf;
                pluginString += " ;\n";

                sprintf(portBuf, "%i", i+1);
                pluginString += "      lv2:symbol \"lv2_audio_in_";
                pluginString += portBuf;
                pluginString += "\" ;\n";
                pluginString += "      lv2:name \"Audio Input ";
                pluginString += portBuf;
                pluginString += "\" ;\n";

                if (i+1 == DISTRHO_PLUGIN_NUM_INPUTS)
                    pluginString += "    ] ;\n\n";
                else
                    pluginString += "    ] ,\n";
            }

            for (i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++)
            {
                if (i == 0)
                    pluginString += "    lv2:port [\n";
                else
                    pluginString += "    [\n";

                sprintf(portBuf, "%i", portIndex++);
                pluginString += "      a lv2:OutputPort, lv2:AudioPort ;\n";
                pluginString += "      lv2:index ";
                pluginString += portBuf;
                pluginString += " ;\n";

                sprintf(portBuf, "%i", i+1);
                pluginString += "      lv2:symbol \"lv2_audio_out_";
                pluginString += portBuf;
                pluginString += "\" ;\n";
                pluginString += "      lv2:name \"Audio Output ";
                pluginString += portBuf;
                pluginString += "\" ;\n";

                if (i+1 == DISTRHO_PLUGIN_NUM_OUTPUTS)
                    pluginString += "    ] ;\n\n";
                else
                    pluginString += "    ] ,\n";
            }

            for (i=0; i < plugin.parameterCount(); i++)
            {
                if (i == 0)
                    pluginString += "    lv2:port [\n";
                else
                    pluginString += "    [\n";

                if (plugin.parameterIsOutput(i))
                    pluginString += "      a lv2:OutputPort, lv2:ControlPort ;\n";
                else
                    pluginString += "      a lv2:InputPort, lv2:ControlPort ;\n";

                sprintf(portBuf, "%i", portIndex++);
                pluginString += "      lv2:index ";
                pluginString += portBuf;
                pluginString += " ;\n";

                pluginString += "      lv2:name \"";
                pluginString += plugin.parameterName(i);
                pluginString += "\" ;\n";

                {
                    const char* symbol = plugin.parameterSymbol(i);

                    sprintf(portBuf, "lv2_port_%i", i+1);
                    pluginString += "      lv2:symbol \"";
                    pluginString += symbol ? symbol : portBuf;
                    pluginString += "\" ;\n";
                }

                sprintf(portBuf, "%f", plugin.parameterValue(i));
                pluginString += "      lv2:default ";
                pluginString += portBuf;
                pluginString += " ;\n";

                {
                    const ParameterRanges* ranges = plugin.parameterRanges(i);

                    sprintf(portBuf, "%f", ranges->min);
                    pluginString += "      lv2:minimum ";
                    pluginString += portBuf;
                    pluginString += " ;\n";

                    sprintf(portBuf, "%f", ranges->max);
                    pluginString += "      lv2:maximum ";
                    pluginString += portBuf;
                    pluginString += " ;\n";
                }

                {
                    uint32_t hints = plugin.parameterHints(i);

                    if (hints & PARAMETER_IS_BOOLEAN)
                        pluginString += "      lv2:portProperty lv2:toggled ;\n";
                    if (hints & PARAMETER_IS_INTEGER)
                        pluginString += "      lv2:portProperty lv2:integer ;\n";
                }

                if (i+1 == plugin.parameterCount())
                    pluginString += "    ] ;\n\n";
                else
                    pluginString += "    ] ,\n";
            }

#if DISTRHO_LV2_USE_EVENTS
            sprintf(portBuf, "%i", portIndex++);
            pluginString += "    lv2:port [\n";
            pluginString += "      a lv2:InputPort, atom:AtomPort ;\n";
            pluginString += "      lv2:index ";
            pluginString += portBuf;
            pluginString += " ;\n";
            pluginString += "      lv2:name \"Events Input\" ;\n";
            pluginString += "      lv2:symbol \"lv2_events_in\" ;\n";
            pluginString += "      atom:bufferType atom:Sequence ;\n";
# if DISTRHO_PLUGIN_IS_SYNTH
            pluginString += "      atom:supports <" LV2_MIDI__MidiEvent "> ,\n";
            pluginString += "                    <" LV2_PATCH__Message "> ;\n";
# else
            pluginString += "      atom:supports <" LV2_PATCH__Message "> ;\n";
# endif
            pluginString += "    ] ,\n";
#endif

            sprintf(portBuf, "%i", portIndex++);
            pluginString += "    [\n";
            pluginString += "      a lv2:OutputPort, lv2:ControlPort ;\n";
            pluginString += "      lv2:index ";
            pluginString += portBuf;
            pluginString += " ;\n";
            pluginString += "      lv2:name \"Latency\" ;\n";
            pluginString += "      lv2:symbol \"lv2_latency\" ;\n";
            pluginString += "      lv2:designation lv2:latency ;\n";
            pluginString += "    ] ,\n";

            sprintf(portBuf, "%i", portIndex++);
            pluginString += "    [\n";
            pluginString += "      a lv2:OutputPort, lv2:ControlPort ;\n";
            pluginString += "      lv2:index ";
            pluginString += portBuf;
            pluginString += " ;\n";
            pluginString += "      lv2:name \"Sample Rate\" ;\n";
            pluginString += "      lv2:symbol \"lv2_sample_rate\" ;\n";
            pluginString += "      lv2:designation lv2:sampleRate ;\n";
            pluginString += "    ] ;\n\n";
        }

        pluginString += "    doap:name \"";
        pluginString += plugin.name();
        pluginString += "\" ;\n";
        pluginString += "    doap:maintainer [ foaf:name \"";
        pluginString += plugin.maker();
        pluginString += "\" ] .\n";

        pluginFile << pluginString << std::endl;
        pluginFile.close();
        std::cout << " done!" << std::endl;
    }
}

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

DISTRHO_PLUGIN_EXPORT
void lv2_generate_ttl()
{
    USE_NAMESPACE_DISTRHO
    lv2_generate_ttl_func();
}

// -------------------------------------------------

#endif // DISTRHO_PLUGIN_TARGET_LV2
