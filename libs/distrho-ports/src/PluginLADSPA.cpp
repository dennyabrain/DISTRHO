// distrho ladspa plugin

#include "PluginBase.h"

#include "ladspa-sdk/ladspa.h"

#include <fstream>
#include <iostream>
#include <vector>

#if DISTRHO_PLUGIN_IS_SYNTH
#error Cannot use synths with LADPSA
#endif

// ---------------------------------------------------------------------------------------------

class DistrhoPluginLadspa
{
public:
    DistrhoPluginLadspa(double sampleRate)
    {
        m_plugin = createDistrhoPlugin();
        m_plugin->d_init();

        lastBufferSize = 512;
        m_plugin->__setSampleRate(sampleRate);
        m_plugin->__setBufferSize(lastBufferSize);

        for (uint32_t i=0; i < DISTRHO_PLUGIN_NUM_INPUTS; i++)
            portAudioIns.push_back(nullptr);

        for (uint32_t i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++)
            portAudioOuts.push_back(nullptr);

        for (uint32_t i=0; i < m_plugin->d_parameterCount(); i++)
        {
            portControls.push_back(nullptr);
            lastControlValues.push_back(m_plugin->d_parameterValue(i));
        }
    }

    virtual ~DistrhoPluginLadspa()
    {
        m_plugin->d_cleanup();
        delete m_plugin;

        lastControlValues.clear();
        portAudioIns.clear();
        portAudioOuts.clear();
        portControls.clear();
    }

    void ladspa_activate()
    {
        m_plugin->d_activate();
    }

    void ladspa_deactivate()
    {
        m_plugin->d_deactivate();
    }

    void ladspa_connect_port(unsigned long port, LADSPA_Data* dataLocation)
    {
        uint32_t index = 0;

        for (uint32_t i=0; i < DISTRHO_PLUGIN_NUM_INPUTS; i++, index++)
        {
            if (index == port)
            {
                portAudioIns[i] = dataLocation;
                return;
            }
        }

        for (uint32_t i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++, index++)
        {
            if (index == port)
            {
                portAudioOuts[i] = dataLocation;
                return;
            }
        }

        for (uint32_t i=0; i < m_plugin->d_parameterCount(); i++, index++)
        {
            if (index == port)
            {
                portControls[i] = dataLocation;

                if (m_plugin->d_parameterInfo(i)->hints & PARAMETER_IS_OUTPUT)
                    *portControls[i] = m_plugin->d_parameterValue(i);

                return;
            }
        }

        if (index == port)
        {
            portLatency = dataLocation;
            *portLatency = 0.0f;
            return;
        }
    }

    void ladspa_run(unsigned long bufferSize)
    {
        if (bufferSize == 0)
            return;

        // Check for updated bufferSize
        if (bufferSize >= 2 && bufferSize != lastBufferSize)
        {
            lastBufferSize = bufferSize;
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
                curValue = *portControls[i];
                pinfo    = m_plugin->d_parameterInfo(i);

                if (lastControlValues[i] != curValue && (pinfo->hints & PARAMETER_IS_OUTPUT) == 0)
                {
                    m_plugin->d_setParameterValue(i, curValue);
                    lastControlValues[i] = curValue;
                }
            }
        }

        // Run plugin for this cycle
        float* inputs[DISTRHO_PLUGIN_NUM_INPUTS];
        float* outputs[DISTRHO_PLUGIN_NUM_OUTPUTS];

        for (uint32_t i=0; i < DISTRHO_PLUGIN_NUM_INPUTS; i++)
            inputs[i] = portAudioIns[i];

        for (uint32_t i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++)
            outputs[i] = portAudioOuts[i];

        m_plugin->d_run(inputs, outputs, bufferSize, 0, nullptr);

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
    unsigned long lastBufferSize;
    std::vector<float> lastControlValues;

    // LADSPA ports
    std::vector<float*> portAudioIns;
    std::vector<float*> portAudioOuts;
    std::vector<float*> portControls;
    float* portLatency;
};

// ---------------------------------------------------------------------------------------------

static LADSPA_Handle instantiate(const LADSPA_Descriptor*, unsigned long sampleRate)
{
    return new DistrhoPluginLadspa(sampleRate);
}

static void connect_port(LADSPA_Handle instance, unsigned long port, LADSPA_Data* dataLocation)
{
    DistrhoPluginLadspa* plugin = (DistrhoPluginLadspa*)instance;
    plugin->ladspa_connect_port(port, dataLocation);
}

static void activate(LADSPA_Handle instance)
{
    DistrhoPluginLadspa* plugin = (DistrhoPluginLadspa*)instance;
    plugin->ladspa_activate();
}

static void run(LADSPA_Handle instance, unsigned long sampleCount)
{
    DistrhoPluginLadspa* plugin = (DistrhoPluginLadspa*)instance;
    plugin->ladspa_run(sampleCount);
}

static void deactivate(LADSPA_Handle instance)
{
    DistrhoPluginLadspa* plugin = (DistrhoPluginLadspa*)instance;
    plugin->ladspa_deactivate();
}

static void cleanup(LADSPA_Handle instance)
{
    delete (DistrhoPluginLadspa*)instance;
}

static LADSPA_Descriptor descriptor = {
    /* UniqueID        */ 0,
    /* Label           */ nullptr,
    /* Properties      */ 0x0,
    /* Name            */ nullptr,
    /* Maker           */ nullptr,
    /* Copyright       */ nullptr,
    /* PortCount       */ 0,
    /* PortDescriptors */ nullptr,
    /* PortNames       */ nullptr,
    /* PortRangeHints  */ nullptr,
    nullptr,
    instantiate,
    connect_port,
    activate,
    run,
    nullptr,
    nullptr,
    deactivate,
    cleanup
};

// ---------------------------------------------------------------------------------------------

__attribute__((constructor))
static void descriptor_init()
{
    // Create Dummy plugin to get data from
    DistrhoPluginBase* DummyInfoPlugin = createDistrhoPlugin();
    DummyInfoPlugin->d_init();

    // Get data
    unsigned long i, port = 0;
    unsigned long PortCount = DummyInfoPlugin->d_parameterCount() + DISTRHO_PLUGIN_NUM_INPUTS + DISTRHO_PLUGIN_NUM_OUTPUTS + 1;
    unsigned long UniqueID  = DummyInfoPlugin->d_uniqueId();
    const char** PortNames  = new const char* [PortCount];
    LADSPA_PortDescriptor* PortDescriptors = new LADSPA_PortDescriptor [PortCount];
    LADSPA_PortRangeHint*  PortRangeHints  = new LADSPA_PortRangeHint  [PortCount];

    for (i=0; i < DISTRHO_PLUGIN_NUM_INPUTS; i++, port++)
    {
        char portName[16] = { 0 };
        sprintf(portName, "audio_in_%lu", i+1);

        PortNames[port]       = strdup(portName);
        PortDescriptors[port] = LADSPA_PORT_AUDIO | LADSPA_PORT_INPUT;

        PortRangeHints[port].HintDescriptor = 0;
        PortRangeHints[port].LowerBound = 0.0f;
        PortRangeHints[port].UpperBound = 1.0f;
    }

    for (i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++, port++)
    {
        char portName[16] = { 0 };
        sprintf(portName, "audio_out_%lu", i+1);

        PortNames[port]       = strdup(portName);
        PortDescriptors[port] = LADSPA_PORT_AUDIO | LADSPA_PORT_OUTPUT;

        PortRangeHints[port].HintDescriptor = 0;
        PortRangeHints[port].LowerBound = 0.0f;
        PortRangeHints[port].UpperBound = 1.0f;
    }

    for (i=0; i < DummyInfoPlugin->d_parameterCount(); i++, port++)
    {
        const ParameterInfo* ParamInfo = DummyInfoPlugin->d_parameterInfo(i);

        PortNames[port]       = strdup(ParamInfo->name);
        PortDescriptors[port] = LADSPA_PORT_CONTROL;

        if (ParamInfo->hints & PARAMETER_IS_OUTPUT)
            PortDescriptors[port] |= LADSPA_PORT_OUTPUT;
        else
            PortDescriptors[port] |= LADSPA_PORT_INPUT;

        PortRangeHints[port].HintDescriptor = LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE;
        PortRangeHints[port].LowerBound = ParamInfo->range.min;
        PortRangeHints[port].UpperBound = ParamInfo->range.max;
    }

    PortNames[port]       = strdup("_latency");
    PortDescriptors[port] = LADSPA_PORT_CONTROL | LADSPA_PORT_OUTPUT;
    PortRangeHints[port].HintDescriptor = 0;
    PortRangeHints[port].LowerBound = 0.0f;
    PortRangeHints[port].UpperBound = 1.0f;

    // Set data
    descriptor.UniqueID  = UniqueID;
    descriptor.Label     = strdup(DummyInfoPlugin->d_label());
    descriptor.Name      = strdup(DummyInfoPlugin->d_name());
    descriptor.Maker     = strdup(DummyInfoPlugin->d_maker());
    descriptor.Copyright = strdup(DummyInfoPlugin->d_license());
    descriptor.PortCount = PortCount;
    descriptor.PortNames = PortNames;
    descriptor.PortDescriptors = PortDescriptors;
    descriptor.PortRangeHints  = PortRangeHints;

    // Delete dummy plugin
    DummyInfoPlugin->d_cleanup();
    delete DummyInfoPlugin;
}

__attribute__((destructor))
static void descriptor_fini()
{
    free((void*)descriptor.Label);
    free((void*)descriptor.Name);
    free((void*)descriptor.Maker);
    free((void*)descriptor.Copyright);

    for (unsigned long i=0; i < descriptor.PortCount; i++)
        free((void*)descriptor.PortNames[i]);

    delete[] descriptor.PortNames;
    delete[] descriptor.PortDescriptors;
    delete[] descriptor.PortRangeHints;
}

// ---------------------------------------------------------------------------------------------

DISTRHO_PLUGIN_EXPORT
const LADSPA_Descriptor* ladspa_descriptor(unsigned long index)
{
    return (index == 0) ? &descriptor : nullptr;
}
