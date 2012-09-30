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

#include <fstream>
#include <iostream>

#include "DistrhoPluginInternal.h"

#include "lv2-sdk/lv2.h"
#include "lv2-sdk/atom.h"
#include "lv2-sdk/patch.h"
#include "lv2-sdk/programs.h"
#include "lv2-sdk/state.h"
#include "lv2-sdk/urid.h"
#include "lv2-sdk/ui.h"

#ifndef DISTRHO_PLUGIN_URI
# error DISTRHO_PLUGIN_URI undefined!
#endif

#define DISTRHO_LV2_USE_EVENTS (DISTRHO_PLUGIN_IS_SYNTH || DISTRHO_PLUGIN_WANT_STATE)

// -------------------------------------------------

START_NAMESPACE_DISTRHO

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
#if DISTRHO_OS_HAIKU
        manifestString += "    a ui:BeUI ;\n";
#elif DISTRHO_OS_MACOS
        manifestString += "    a ui:CocoaUI ;\n";
#elif DISTRHO_OS_WINDOWS
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

END_NAMESPACE_DISTRHO

// -------------------------------------------------

DISTRHO_PLUGIN_EXPORT
void lv2_generate_ttl()
{
    USE_NAMESPACE_DISTRHO
    lv2_generate_ttl_func();
}

// -------------------------------------------------
