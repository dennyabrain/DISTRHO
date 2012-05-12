// distrho dssi plugin

#include "PluginBase.h"

#ifdef DISTRHO_PLUGIN_TARGET_DSSI
#include "dssi-sdk/dssi.h"
#else
#include "ladspa-sdk/ladspa.h"
typedef void* snd_seq_event_t;
#if DISTRHO_PLUGIN_IS_SYNTH
#error Cannot build synth plugin with LADSPA
#endif
#endif

#include <cstdio>
#include <vector>

// ---------------------------------------------------------------------------------------------

class DistrhoPluginDssiLadspa
{
public:
    DistrhoPluginDssiLadspa(double sampleRate)
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

    ~DistrhoPluginDssiLadspa()
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
            if (port == index)
            {
                portAudioIns[i] = dataLocation;
                return;
            }
        }

        for (uint32_t i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++, index++)
        {
            if (port == index)
            {
                portAudioOuts[i] = dataLocation;
                return;
            }
        }

        for (uint32_t i=0; i < m_plugin->d_parameterCount(); i++, index++)
        {
            if (port == index)
            {
                portControls[i] = dataLocation;

                if (m_plugin->d_parameterInfo(i)->hints & PARAMETER_IS_OUTPUT)
                    *portControls[i] = m_plugin->d_parameterValue(i);

                return;
            }
        }

        if (port == index)
        {
            portLatency = dataLocation;
            *portLatency = m_plugin->__latency();
            return;
        }
    }

    void ladspa_run(unsigned long bufferSize)
    {
        dssi_run_synth(bufferSize, nullptr, 0);
    }

#ifdef DISTRHO_PLUGIN_TARGET_DSSI
    char* dssi_configure(const char* key, const char* value)
    {
        (void)key;
        (void)value;
        return nullptr;
    }

    const DSSI_Program_Descriptor* dssi_get_program(unsigned long index)
    {
        if (index < m_plugin->d_programCount())
        {
            static DSSI_Program_Descriptor desc;
            desc.Bank    = index / 128;
            desc.Program = index % 128;
            desc.Name    = m_plugin->d_programName(index);
            return &desc;
        }
        return nullptr;
    }

    void dssi_select_program(unsigned long bank, unsigned long program)
    {
        uint32_t realProgram = bank * 128 + program;
        if (realProgram < m_plugin->d_programCount())
            m_plugin->d_setCurrentProgram(realProgram);
    }
#endif

    void dssi_run_synth(unsigned long bufferSize, snd_seq_event_t* events, unsigned long eventCount)
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

        // Get MIDI Events
        uint32_t midiEventCount = 0;
#if DISTRHO_PLUGIN_IS_SYNTH
        for (unsigned long i=0, j; i < eventCount && midiEventCount < 512; i++)
        {
            if (events[i].type == SND_SEQ_EVENT_NOTEON)
            {
                j = midiEventCount++;
                midiEvents[j].frame = events[i].time.tick;
                midiEvents[j].buffer[0] = 0x80 + events[i].data.note.channel;
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
        }
#else
        (void)events;
        (void)eventCount;
#endif

        // Run plugin for this cycle
        float* inputs[DISTRHO_PLUGIN_NUM_INPUTS];
        float* outputs[DISTRHO_PLUGIN_NUM_OUTPUTS];

        for (uint32_t i=0; i < DISTRHO_PLUGIN_NUM_INPUTS; i++)
            inputs[i] = portAudioIns[i];

        for (uint32_t i=0; i < DISTRHO_PLUGIN_NUM_OUTPUTS; i++)
            outputs[i] = portAudioOuts[i];

        m_plugin->d_run(inputs, outputs, bufferSize, midiEventCount, midiEvents);

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
#if DISTRHO_PLUGIN_IS_SYNTH
    MidiEvent midiEvents[512];
#else
    MidiEvent midiEvents[0];
#endif

    // LADSPA ports
    std::vector<float*> portAudioIns;
    std::vector<float*> portAudioOuts;
    std::vector<float*> portControls;
    float* portLatency;
};

// ---------------------------------------------------------------------------------------------

static LADSPA_Handle ladspa_instantiate(const LADSPA_Descriptor*, unsigned long sampleRate)
{
    return new DistrhoPluginDssiLadspa(sampleRate);
}

static void ladspa_connect_port(LADSPA_Handle instance, unsigned long port, LADSPA_Data* dataLocation)
{
    DistrhoPluginDssiLadspa* plugin = (DistrhoPluginDssiLadspa*)instance;
    plugin->ladspa_connect_port(port, dataLocation);
}

static void ladspa_activate(LADSPA_Handle instance)
{
    DistrhoPluginDssiLadspa* plugin = (DistrhoPluginDssiLadspa*)instance;
    plugin->ladspa_activate();
}

static void ladspa_run(LADSPA_Handle instance, unsigned long sampleCount)
{
    DistrhoPluginDssiLadspa* plugin = (DistrhoPluginDssiLadspa*)instance;
    plugin->ladspa_run(sampleCount);
}

static void ladspa_deactivate(LADSPA_Handle instance)
{
    DistrhoPluginDssiLadspa* plugin = (DistrhoPluginDssiLadspa*)instance;
    plugin->ladspa_deactivate();
}

static void ladspa_cleanup(LADSPA_Handle instance)
{
    delete (DistrhoPluginDssiLadspa*)instance;
}

#ifdef DISTRHO_PLUGIN_TARGET_DSSI
static char* dssi_configure(LADSPA_Handle instance, const char* key, const char* value)
{
    DistrhoPluginDssiLadspa* plugin = (DistrhoPluginDssiLadspa*)instance;
    return plugin->dssi_configure(key, value);
}

static const DSSI_Program_Descriptor* dssi_get_program(LADSPA_Handle instance, unsigned long index)
{
    DistrhoPluginDssiLadspa* plugin = (DistrhoPluginDssiLadspa*)instance;
    return plugin->dssi_get_program(index);
}

static void dssi_select_program(LADSPA_Handle instance, unsigned long bank, unsigned long program)
{
    DistrhoPluginDssiLadspa* plugin = (DistrhoPluginDssiLadspa*)instance;
    plugin->dssi_select_program(bank, program);
}

#if DISTRHO_PLUGIN_IS_SYNTH
static void dssi_run_synth(LADSPA_Handle instance, unsigned long sampleCount, snd_seq_event_t* events, unsigned long eventCount)
{
    DistrhoPluginDssi* plugin = (DistrhoPluginDssi*)instance;
    plugin->dssi_run_synth(sampleCount, events, eventCount);
}
#endif
#endif

// ---------------------------------------------------------------------------------------------

static LADSPA_Descriptor ldescriptor = {
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
    ladspa_instantiate,
    ladspa_connect_port,
    ladspa_activate,
    ladspa_run,
    nullptr,
    nullptr,
    ladspa_deactivate,
    ladspa_cleanup
};

#ifdef DISTRHO_PLUGIN_TARGET_DSSI
static DSSI_Descriptor descriptor = {
    1,
    &ldescriptor,
    dssi_configure,
    dssi_get_program,
    dssi_select_program,
    nullptr,
#if DISTRHO_PLUGIN_IS_SYNTH
    dssi_run_synth,
#else
    nullptr,
#endif
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr
};
#endif

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
    ldescriptor.UniqueID  = UniqueID;
    ldescriptor.Label     = strdup(DummyInfoPlugin->d_label());
    ldescriptor.Name      = strdup(DummyInfoPlugin->d_name());
    ldescriptor.Maker     = strdup(DummyInfoPlugin->d_maker());
    ldescriptor.Copyright = strdup(DummyInfoPlugin->d_license());
    ldescriptor.PortCount = PortCount;
    ldescriptor.PortNames = PortNames;
    ldescriptor.PortDescriptors = PortDescriptors;
    ldescriptor.PortRangeHints  = PortRangeHints;

    // Delete dummy plugin
    DummyInfoPlugin->d_cleanup();
    delete DummyInfoPlugin;
}

__attribute__((destructor))
static void descriptor_fini()
{
    free((void*)ldescriptor.Label);
    free((void*)ldescriptor.Name);
    free((void*)ldescriptor.Maker);
    free((void*)ldescriptor.Copyright);

    for (unsigned long i=0; i < ldescriptor.PortCount; i++)
        free((void*)ldescriptor.PortNames[i]);

    delete[] ldescriptor.PortNames;
    delete[] ldescriptor.PortDescriptors;
    delete[] ldescriptor.PortRangeHints;
}

// ---------------------------------------------------------------------------------------------

DISTRHO_PLUGIN_EXPORT
const LADSPA_Descriptor* ladspa_descriptor(unsigned long index)
{
    return (index == 0) ? &ldescriptor : nullptr;
}

#ifdef DISTRHO_PLUGIN_TARGET_DSSI
DISTRHO_PLUGIN_EXPORT
const DSSI_Descriptor* dssi_descriptor(unsigned long index)
{
    return (index == 0) ? &descriptor : nullptr;
}
#endif
