// distrho lv2 plugin

#include "PluginBase.h"

#include "lv2-sdk/lv2.h"
#include "lv2-sdk/event.h"
#include "lv2-sdk/event-helpers.h"
#include "lv2-sdk/midi.h"
#include "lv2-sdk/urid.h"
#include "lv2-sdk/ui.h"

#include <fstream>
#include <iostream>
#include <vector>

#ifndef DISTRHO_PLUGIN_URI
#error DISTRHO_PLUGIN_URI undefined!
#endif

// ---------------------------------------------------------------------------------------------

class DistrhoPluginLv2
{
public:
    DistrhoPluginLv2(double sampleRate)
    {
        m_plugin = createDistrhoPlugin();
        m_plugin->d_init();

        lastBufferSize = 512;
        m_plugin->__setSampleRate(sampleRate);
        m_plugin->__setBufferSize(lastBufferSize);

        portMidiIn = nullptr;

        for (int32_t i=0; i < DISTRHO_PLUGIN_NUM_INPUTS; i++)
            portAudioIns.push_back(nullptr);

        for (int32_t i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++)
            portAudioOuts.push_back(nullptr);

        for (uint32_t i=0; i < m_plugin->d_parameterCount(); i++)
        {
            portControls.push_back(nullptr);
            lastControlValues.push_back(m_plugin->d_parameterValue(i));
        }
    }

    virtual ~DistrhoPluginLv2()
    {
        m_plugin->d_cleanup();
        delete m_plugin;

        lastControlValues.clear();
        portAudioIns.clear();
        portAudioOuts.clear();
        portControls.clear();
    }

    void lv2_activate()
    {
        m_plugin->d_activate();
    }

    void lv2_deactivate()
    {
        m_plugin->d_deactivate();
    }

    void lv2_connect_port(uint32_t portId, void* data)
    {
        uint32_t index = 0;

#if DISTRHO_PLUGIN_IS_SYNTH
        if (portId == index++)
        {
            portMidiIn = (LV2_Event_Buffer*)data;
            return;
        }
#endif

        for (int32_t i=0; i < DISTRHO_PLUGIN_NUM_INPUTS; i++)
        {
            if (portId == index++)
            {
                portAudioIns[i] = (float*)data;
                return;
            }
        }

        for (int32_t i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++)
        {
            if (portId == index++)
            {
                portAudioOuts[i] = (float*)data;
                return;
            }
        }

        for (uint32_t i=0; i < m_plugin->d_parameterCount(); i++)
        {
            if (portId == index++)
            {
                portControls[i] = (float*)data;
                return;
            }
        }

        if (portId == index++)
        {
            portLatency = (float*)data;
            *portLatency = m_plugin->__latency();
            return;
        }
    }

    void lv2_run(uint32_t samples)
    {
        if (samples == 0)
            return;

        // Check for updated bufferSize
        if (samples >= 2 && samples != lastBufferSize)
        {
            lastBufferSize = samples;
            m_plugin->__setBufferSize(lastBufferSize);

            m_plugin->d_deactivate();
            m_plugin->d_activate();
        }

        // Check for updated parameters
        float curValue;
        const ParameterInfo* pinfo;

        for (uint32_t i=0; i < m_plugin->d_parameterCount(); i++)
        {
            if (portControls[i] != nullptr)
            {
                curValue = *(float*)portControls[i];
                pinfo    = m_plugin->d_parameterInfo(i);

                if (lastControlValues[i] != curValue && (pinfo->hints & PARAMETER_IS_OUTPUT) == 0)
                {
                    m_plugin->d_setParameterValue(i, curValue);
                    lastControlValues[i] = curValue;
                }
            }
        }

        // Get MIDI Events
        uint32_t midiEventCount = 0;

        if (portMidiIn)
        {
            LV2_Event* ev;
            LV2_Event_Iterator iter;

            uint8_t* data;
            lv2_event_begin(&iter, portMidiIn);

            for (uint32_t i=0; i < iter.buf->event_count; i++)
            {
                ev = lv2_event_get(&iter, &data);
                if (ev && data)
                {
                    midiEvents[midiEventCount].frame = ev->frames;
                    midiEvents[midiEventCount].buffer[0] = data[0];
                    midiEvents[midiEventCount].buffer[1] = data[1];
                    midiEvents[midiEventCount].buffer[2] = data[2];
                    midiEventCount++;
                }

                lv2_event_increment(&iter);
            }
        }

        // Run plugin for this cycle
        float* inputs[DISTRHO_PLUGIN_NUM_INPUTS];
        float* outputs[DISTRHO_PLUGIN_NUM_OUTPUTS];

        for (int32_t i=0; i < DISTRHO_PLUGIN_NUM_INPUTS; i++)
            inputs[i] = portAudioIns[i];

        for (int32_t i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++)
            outputs[i] = portAudioOuts[i];

        m_plugin->d_run(inputs, outputs, samples, midiEventCount, midiEvents);

        // Update parameter outputs
        for (uint32_t i=0; i < m_plugin->d_parameterCount(); i++)
        {
            pinfo = m_plugin->d_parameterInfo(i);
            if (pinfo->hints & PARAMETER_IS_OUTPUT)
                lastControlValues[i] = *portControls[i] = m_plugin->d_parameterValue(i);
        }

        *portLatency = m_plugin->__latency();
    }

private:
    // The plugin
    DistrhoPluginBase* m_plugin;

    // Temporary data
    uint32_t lastBufferSize;
    std::vector<float> lastControlValues;
    MidiEvent midiEvents[512];

    // LV2 ports
    LV2_Event_Buffer* portMidiIn;
    std::vector<float*> portAudioIns;
    std::vector<float*> portAudioOuts;
    std::vector<float*> portControls;
    float* portLatency;
};

// ---------------------------------------------------------------------------------------------

static LV2_Handle instantiate(const LV2_Descriptor*, double sampleRate, const char*, const LV2_Feature* const*)
{
    return new DistrhoPluginLv2(sampleRate);
}

static void cleanup(LV2_Handle instance)
{
    delete (DistrhoPluginLv2*)instance;
}

static void activate(LV2_Handle instance)
{
    DistrhoPluginLv2* plugin = (DistrhoPluginLv2*)instance;
    plugin->lv2_activate();
}

static void deactivate(LV2_Handle instance)
{
    DistrhoPluginLv2* plugin = (DistrhoPluginLv2*)instance;
    plugin->lv2_deactivate();
}

static void connect_port(LV2_Handle instance, uint32_t port, void* data)
{
    DistrhoPluginLv2* plugin = (DistrhoPluginLv2*)instance;
    plugin->lv2_connect_port(port, data);
}

static void run(LV2_Handle instance, uint32_t n_samples)
{
    DistrhoPluginLv2* plugin = (DistrhoPluginLv2*)instance;
    plugin->lv2_run(n_samples);
}

static const void* extension_data(const char* /*uri*/)
{
    return nullptr;
}

static const LV2_Descriptor descriptor = {
    DISTRHO_PLUGIN_URI,
    instantiate,
    connect_port,
    activate,
    run,
    deactivate,
    cleanup,
    extension_data
};

// ---------------------------------------------------------------------------------------------

DISTRHO_PLUGIN_EXPORT
void lv2_generate_ttl()
{
    DistrhoPluginBase* plugin = createDistrhoPlugin();
    plugin->d_init();

    const char* plugin_name = plugin->d_name();
    char* plugin_binary = strdup(plugin_name);

    size_t len = strlen(plugin_binary);
    for (size_t i = 0; i < len; i++)
    {
        if (plugin_binary[i] == ' ')
            plugin_binary[i] = '_';
    }

    char plugin_ttl[len+5];
    strcpy(plugin_ttl, plugin_binary);
    strcat(plugin_ttl, ".ttl");

    std::cout << "Writing manifest.ttl..."; std::cout.flush();
    std::fstream manifest_file("manifest.ttl", std::ios::out);

    std::string manifest_string;
    manifest_string += "@prefix lv2:  <" LV2_CORE_PREFIX "> .\n";
    manifest_string += "@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .\n";
#if DISTRHO_PLUGIN_WANTS_UI
    manifest_string += "@prefix ui:   <" LV2_UI_PREFIX "> .\n";
#endif
    manifest_string += "\n";

    manifest_string += "<" DISTRHO_PLUGIN_URI ">\n";
    manifest_string += "    a lv2:Plugin ;\n";
    manifest_string += "    lv2:binary <";
    manifest_string += plugin_binary;
    manifest_string += ".so> ;\n";
    manifest_string += "    rdfs:seeAlso <";
    manifest_string += plugin_binary;
    manifest_string += ".ttl> .\n";
    manifest_string += "\n";

#if DISTRHO_PLUGIN_WANTS_UI
    manifest_string += "<" DISTRHO_PLUGIN_URI "#Qt4UI>\n";
    manifest_string += "    a ui:Qt4UI ;\n";
    manifest_string += "    ui:binary <";
    manifest_string += plugin_binary;
    manifest_string += ".so> .\n";
    manifest_string += "\n";

#if defined(Q_OS_LINUX) || defined(__linux__)
    manifest_string += "<" DISTRHO_PLUGIN_URI "#X11UI>\n";
    manifest_string += "    a ui:X11UI ;\n";
    manifest_string += "    ui:binary <";
    manifest_string += plugin_binary;
    manifest_string += ".so> ;\n";
    manifest_string += "    lv2:optionalFeature ui:noUserResize .\n";
    manifest_string += "\n";
#endif
#endif

    manifest_file << manifest_string << std::endl;
    manifest_file.close();
    std::cout << " done!" << std::endl;

    std::cout << "Writing " << plugin_ttl << "..."; std::cout.flush();
    std::fstream plugin_file(plugin_ttl, std::ios::out);

    std::string plugin_string;
    plugin_string += "@prefix doap: <http://usefulinc.com/ns/doap#> .\n";
#if DISTRHO_PLUGIN_IS_SYNTH
    plugin_string += "@prefix ev:   <" LV2_EVENT_PREFIX "> .\n";
#endif
    plugin_string += "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n";
    plugin_string += "@prefix lv2:  <" LV2_CORE_PREFIX "> .\n";
#if DISTRHO_PLUGIN_WANTS_UI
    plugin_string += "@prefix ui:   <" LV2_UI_PREFIX "> .\n";
#endif
    plugin_string += "\n";

    plugin_string += "<" DISTRHO_PLUGIN_URI ">\n";
#if DISTRHO_PLUGIN_IS_SYNTH
    plugin_string += "    a lv2:InstrumentPlugin, lv2:Plugin ;\n";
    plugin_string += "    lv2:requiredFeature <" LV2_URID__map "> ;\n";
#else
    plugin_string += "    a lv2:Plugin ;\n";
#endif
    plugin_string += "\n";

#if DISTRHO_PLUGIN_WANTS_UI
#if defined(Q_OS_LINUX) || defined(__linux__)
    plugin_string += "    ui:ui <" DISTRHO_PLUGIN_URI "#Qt4UI> ,\n";
    plugin_string += "          <" DISTRHO_PLUGIN_URI "#X11UI> ;\n";
#else
    plugin_string += "    ui:ui <" DISTRHO_PLUGIN_URI "#Qt4UI> ;\n";
#endif
    plugin_string += "\n";
#endif

    uint32_t portIndex = 0;
    char portBuf[64] = { 0 };

#if DISTRHO_PLUGIN_IS_SYNTH
    plugin_string += "    lv2:port [\n";
    plugin_string += "      a lv2:InputPort, ev:EventPort ;\n";
    plugin_string += "      ev:supportsEvent <" LV2_MIDI__MidiEvent "> ;\n";
    plugin_string += "      lv2:index 0 ;\n";
    plugin_string += "      lv2:symbol \"lv2_midi_in\" ;\n";
    plugin_string += "      lv2:name \"Midi Input\" ;\n";
    plugin_string += "    ] ;\n\n";
    portIndex++;
#endif

    for (int32_t i=0; i < DISTRHO_PLUGIN_NUM_INPUTS; i++)
    {
        if (i == 0)
            plugin_string += "    lv2:port [\n";
        else
            plugin_string += "    [\n";

        sprintf(portBuf, "%i", portIndex++);
        plugin_string += "      a lv2:InputPort, lv2:AudioPort ;\n";
        plugin_string += "      lv2:index ";
        plugin_string += portBuf;
        plugin_string += " ;\n";

        sprintf(portBuf, "%i", i+1);
        plugin_string += "      lv2:symbol \"lv2_audio_in_";
        plugin_string += portBuf;
        plugin_string += "\" ;\n";
        plugin_string += "      lv2:name \"Audio Input ";
        plugin_string += portBuf;
        plugin_string += "\" ;\n";

        if (i+1 == DISTRHO_PLUGIN_NUM_INPUTS)
            plugin_string += "    ] ;\n\n";
        else
            plugin_string += "    ],\n";
    }

    for (int32_t i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++)
    {
        if (i == 0)
            plugin_string += "    lv2:port [\n";
        else
            plugin_string += "    [\n";

        sprintf(portBuf, "%i", portIndex++);
        plugin_string += "      a lv2:OutputPort, lv2:AudioPort ;\n";
        plugin_string += "      lv2:index ";
        plugin_string += portBuf;
        plugin_string += " ;\n";

        sprintf(portBuf, "%i", i+1);
        plugin_string += "      lv2:symbol \"lv2_audio_out_";
        plugin_string += portBuf;
        plugin_string += "\" ;\n";
        plugin_string += "      lv2:name \"Audio Output ";
        plugin_string += portBuf;
        plugin_string += "\" ;\n";

        if (i+1 == DISTRHO_PLUGIN_NUM_OUTPUTS)
            plugin_string += "    ] ;\n\n";
        else
            plugin_string += "    ],\n";
    }

    for (uint32_t i=0; i < plugin->d_parameterCount(); i++)
    {
        if (i == 0)
            plugin_string += "    lv2:port [\n";
        else
            plugin_string += "    [\n";

        const ParameterInfo* pinfo = plugin->d_parameterInfo(i);

        sprintf(portBuf, "%i", portIndex++);
        if (pinfo->hints & PARAMETER_IS_OUTPUT)
            plugin_string += "      a lv2:OutputPort, lv2:ControlPort ;\n";
        else
            plugin_string += "      a lv2:InputPort, lv2:ControlPort ;\n";
        plugin_string += "      lv2:index ";
        plugin_string += portBuf;
        plugin_string += " ;\n";

        plugin_string += "      lv2:symbol \"";
        plugin_string += pinfo->symbol;
        plugin_string += "\" ;\n";
        plugin_string += "      lv2:name \"";
        plugin_string += pinfo->name;
        plugin_string += "\" ;\n";

        sprintf(portBuf, "%f", plugin->d_parameterValue(i));
        plugin_string += "      lv2:default ";
        plugin_string += portBuf;
        plugin_string += " ;\n";

        sprintf(portBuf, "%f", pinfo->range.min);
        plugin_string += "      lv2:minimum ";
        plugin_string += portBuf;
        plugin_string += " ;\n";

        sprintf(portBuf, "%f", pinfo->range.max);
        plugin_string += "      lv2:maximum ";
        plugin_string += portBuf;
        plugin_string += " ;\n";

        if (pinfo->hints & PARAMETER_IS_BOOLEAN)
            plugin_string += "      lv2:portProperty lv2:toggled ;\n";
        else if (pinfo->hints & PARAMETER_IS_INTEGER)
            plugin_string += "      lv2:portProperty lv2:integer ;\n";

        if (i+1 == plugin->d_parameterCount())
            plugin_string += "    ] ;\n\n";
        else
            plugin_string += "    ],\n";
    }

    sprintf(portBuf, "%i", portIndex++);
    plugin_string += "    lv2:port [\n";
    plugin_string += "      a lv2:OutputPort, lv2:ControlPort ;\n";
    plugin_string += "      lv2:index ";
    plugin_string += portBuf;
    plugin_string += " ;\n";
    plugin_string += "      lv2:symbol \"lv2_latency\" ;\n";
    plugin_string += "      lv2:name \"Latency\" ;\n";
    plugin_string += "      lv2:portProperty lv2:reportsLatency ;\n";
    plugin_string += "    ] ;\n\n";

    plugin_string += "    doap:name \"";
    plugin_string += plugin_name;
    plugin_string += "\" ;\n";
    plugin_string += "    doap:maintainer [ foaf:name \"";
    plugin_string += plugin->d_maker();
    plugin_string += "\" ] .\n";

    plugin_file << plugin_string << std::endl;
    plugin_file.close();
    std::cout << " done!" << std::endl;

    free(plugin_binary);
    plugin->d_cleanup();
    delete plugin;
}

DISTRHO_PLUGIN_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    return (index == 0) ? &descriptor : nullptr;
}
