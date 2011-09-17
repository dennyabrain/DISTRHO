/*
 *  JUCE LV2 wrapper
 */

#include "juce_IncludeCharacteristics.h"

#if JucePlugin_Build_LV2

#include <fstream>
#include <iostream>
#include <stdint.h>

#include "juce.h"

// LV2 includes
#include "lv2/lv2.h"
#include "lv2/event.h"
#include "lv2/event_helpers.h"
#include "lv2/instance_access.h"
#include "lv2/uri_map.h"
#include "lv2/ui.h"
#include "lv2/lv2_external_ui.h"

// These are dummy values!
enum FakePlugCategory
{
    kPlugCategUnknown,
    kPlugCategEffect,
    kPlugCategSynth,
    kPlugCategAnalysis,
    kPlugCategMastering,
    kPlugCategSpacializer,
    kPlugCategRoomFx,
    kPlugSurroundFx,
    kPlugCategRestoration,
    kPlugCategOfflineProcess,
    kPlugCategGenerator
};

extern AudioProcessor* JUCE_CALLTYPE createPluginFilter();

String name_to_symbol(String Name, uint32_t port_index)
{
    String Symbol = Name.trimStart().trimEnd().replace(" ", "_").toLowerCase();

    if (Symbol.isEmpty())
    {
        Symbol += String(port_index);
    }
    else
    {
        for (int i=0; i < Symbol.length(); i++)
        {
            if (std::isalpha(Symbol[i]) || std::isdigit(Symbol[i]) || Symbol[i] == '_') {
                // nothing
            } else {
                Symbol[i] == '_';
            }
        }
    }

    return Symbol;
}

String float_to_string(float value)
{
    if (value < 0.0f || value > 1.0f) {
        std::cerr << "WARNING - Parameter uses out-of-bounds value -> " << value << std::endl;
    }
    String string(value);
    if (!string.contains(".")) {
        string += ".0";
    }
    return string;
}

String get_uri()
{
    return String("urn:" JucePlugin_Manufacturer ":" JucePlugin_Name ":" JucePlugin_VersionString).replace(" ", "_");
}

String get_juce_ui_uri()
{
    return String("urn:" JucePlugin_Manufacturer ":" JucePlugin_Name ":JUCE-Native-UI").replace(" ", "_");
}

String get_external_ui_uri()
{
    return String("urn:" JucePlugin_Manufacturer ":" JucePlugin_Name ":JUCE-External-UI").replace(" ", "_");
}

String get_binary_name()
{
    return String(JucePlugin_Name).replace(" ", "_");
}

String get_plugin_type()
{
    String ptype;

    switch (JucePlugin_VSTCategory) {
    case kPlugCategSynth:
        ptype += "lv2:InstrumentPlugin";
        break;
    case kPlugCategAnalysis:
        ptype += "lv2:AnalyserPlugin";
        break;
    case kPlugCategMastering:
        ptype += "lv2:DynamicsPlugin";
        break;
    case kPlugCategSpacializer:
        ptype += "lv2:SpatialPlugin";
        break;
    case kPlugCategRoomFx:
        ptype += "lv2:ModulatorPlugin";
        break;
    case kPlugCategRestoration:
        ptype += "lv2:UtilityPlugin";
        break;
    case kPlugCategGenerator:
        ptype += "lv2:GeneratorPlugin";
        break;
    }

    if (ptype.isNotEmpty()) {
        ptype += ", ";
    }

    ptype += "lv2:Plugin";
    return ptype;
}

String get_manifest_ttl(String URI, String Binary)
{
    String manifest;
    manifest += "@prefix lv2:  <http://lv2plug.in/ns/lv2core#> .\n";
    manifest += "@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .\n";
    manifest += "\n";
    manifest += "<" + URI + ">\n";
    manifest += "    a lv2:Plugin ;\n";
    manifest += "    lv2:binary <" + Binary + ".so> ;\n";
    manifest += "    rdfs:seeAlso <" + Binary +".ttl> .\n";
    return manifest;
}

String get_plugin_ttl(String URI, String Binary)
{
    uint32_t i, port_index = 0;
    AudioProcessor* filter = createPluginFilter();

    String plugin;
    plugin += "@prefix doap:  <http://usefulinc.com/ns/doap#> .\n";
    //plugin += "@prefix rdf:  <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n";
    //plugin += "@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .\n";
    plugin += "@prefix lv2:   <http://lv2plug.in/ns/lv2core#> .\n";
    plugin += "@prefix lv2ev: <http://lv2plug.in/ns/ext/event#> .\n";
    plugin += "@prefix lv2ui: <http://lv2plug.in/ns/extensions/ui#> .\n";
    plugin += "\n";

    if (filter->hasEditor()) {
        plugin += "<" + get_juce_ui_uri() + ">\n";
        plugin += "    a lv2ui:JUCEUI ;\n";
        plugin += "    lv2ui:binary <" + Binary + ".so> .\n";
        plugin += "<" + get_external_ui_uri() + ">\n";
        plugin += "    a lv2ui:external ;\n";
        plugin += "    lv2ui:binary <" + Binary + ".so> .\n";
        plugin += "\n";
    }

    plugin += "<" + URI + ">\n";
    plugin += "    a " + get_plugin_type() + " ;\n";

    if (filter->hasEditor()) {
        plugin += "    lv2ui:ui <" + get_juce_ui_uri() + ">,\n";
        plugin += "             <" + get_external_ui_uri() + ">;\n";
    }

    plugin += "\n";

#if JucePlugin_WantsMidiInput
    plugin += "    lv2:port [\n";
    plugin += "      a lv2:InputPort, lv2ev:EventPort;\n";
    plugin += "      lv2ev:supportsEvent <http://lv2plug.in/ns/ext/midi#MidiEvent>;\n";
    plugin += "      lv2:index " + String(port_index++) + ";\n";
    plugin += "      lv2:symbol \"midi_in\";\n";
    plugin += "      lv2:name \"MIDI Input\";\n";
    plugin += "    ] ;\n\n";
#endif

#if JucePlugin_ProducesMidiOutput
    plugin += "    lv2:port [\n";
    plugin += "      a lv2:OutputPort, lv2ev:EventPort;\n";
    plugin += "      lv2ev:supportsEvent <http://lv2plug.in/ns/ext/midi#MidiEvent>;\n";
    plugin += "      lv2:index " + String(port_index++) + ";\n";
    plugin += "      lv2:symbol \"midi_out\";\n";
    plugin += "      lv2:name \"MIDI Output\";\n";
    plugin += "    ] ;\n\n";
#endif

    for (i=0; i<JucePlugin_MaxNumInputChannels; i++) {
        if (i == 0) {
            plugin += "    lv2:port [\n";
        } else {
            plugin += "    [\n";
        }

        plugin += "      a lv2:InputPort, lv2:AudioPort;\n";
        //plugin += "      lv2:datatype lv2:float;\n";
        plugin += "      lv2:index " + String(port_index++) + ";\n";
        plugin += "      lv2:symbol \"audio_in_" + String(i+1) + "\";\n";
        plugin += "      lv2:name \"Audio Input " + String(i+1) + "\";\n";

        if (i+1 == JucePlugin_MaxNumInputChannels) {
            plugin += "    ] ;\n\n";
        } else {
            plugin += "    ],\n";
        }
    }

    for (i=0; i<JucePlugin_MaxNumOutputChannels; i++) {
        if (i == 0) {
            plugin += "    lv2:port [\n";
        } else {
            plugin += "    [\n";
        }

        plugin += "      a lv2:OutputPort, lv2:AudioPort;\n";
        //plugin += "      lv2:datatype lv2:float;\n";
        plugin += "      lv2:index " + String(port_index++) + ";\n";
        plugin += "      lv2:symbol \"audio_out_" + String(i+1) + "\";\n";
        plugin += "      lv2:name \"Audio Output " + String(i+1) + "\";\n";

        if (i+1 == JucePlugin_MaxNumOutputChannels) {
            plugin += "    ] ;\n\n";
        } else {
            plugin += "    ],\n";
        }
    }

    for (i=0; i < filter->getNumParameters(); i++) {
        if (i == 0) {
            plugin += "    lv2:port [\n";
        } else {
            plugin += "    [\n";
        }

        plugin += "      a lv2:InputPort;\n";
        plugin += "      a lv2:ControlPort;\n";
        //plugin += "      lv2:datatype lv2:float;\n";
        plugin += "      lv2:index " + String(port_index++) + ";\n";
        plugin += "      lv2:symbol \"" + name_to_symbol(filter->getParameterName(i), i) + "\";\n";
        plugin += "      lv2:name \"" + filter->getParameterName(i) + "\";\n";
        plugin += "      lv2:default " + float_to_string(filter->getParameter(i)) + ";\n";
        plugin += "      lv2:minimum 0.0;\n";
        plugin += "      lv2:maximum 1.0;\n";

        if (i+1 == filter->getNumParameters()) {
            plugin += "    ] ;\n\n";
        } else {
            plugin += "    ],\n";
        }
    }

    plugin += "    doap:name \"" JucePlugin_Name "\" ;\n";
    plugin += "    doap:creator \"" JucePlugin_Manufacturer "\" .\n";

    delete filter;
    return plugin;
}

void generate_ttl()
{
    String URI = get_uri();
    String Binary = get_binary_name();
    String BinaryTTL = Binary + ".ttl";

    std::cout << "Writing manifest.ttl...";
    std::fstream manifest("manifest.ttl", std::ios::out);
    manifest << get_manifest_ttl(URI, Binary) << std::endl;
    manifest.close();
    std::cout << " done!" << std::endl;

    std::cout << "Writing " << BinaryTTL << "...";
    std::fstream plugin(BinaryTTL.toUTF8(), std::ios::out);
    plugin << get_plugin_ttl(URI, Binary) << std::endl;
    plugin.close();
    std::cout << " done!" << std::endl;
}

//==============================================================================
BEGIN_JUCE_NAMESPACE
 //extern void juce_callAnyTimersSynchronously();

 #if JUCE_MAC
  extern void initialiseMac();
 #endif
END_JUCE_NAMESPACE

//==============================================================================
#if JUCE_LINUX

class SharedMessageThread : public Thread
{
public:
    SharedMessageThread()
      : Thread ("Lv2MessageThread"),
        initialised (false)
    {
        startThread (7);

        while (! initialised)
            sleep (1);
    }

    ~SharedMessageThread()
    {
        signalThreadShouldExit();
        JUCEApplication::quit();
        waitForThreadToExit (5000);
        clearSingletonInstance();
    }

    void run()
    {
        initialiseJuce_GUI();
        initialised = true;

        MessageManager::getInstance()->setCurrentThreadAsMessageThread();

        while ((! threadShouldExit()) && MessageManager::getInstance()->runDispatchLoopUntil (250))
        {}
    }

    juce_DeclareSingleton (SharedMessageThread, false);

private:
    bool initialised;
};

juce_ImplementSingleton (SharedMessageThread)

#endif

static Array<void*> activePlugins;

//==============================================================================
// Create a new JUCE LV2 Plugin
class JuceLV2Wrapper : private Timer
{
public:
    JuceLV2Wrapper(const LV2_Descriptor* descriptor_, double sample_rate_, const LV2_Feature* const* features) :
            chunkMemoryTime (0),
            numInChans (JucePlugin_MaxNumInputChannels),
            numOutChans (JucePlugin_MaxNumOutputChannels),
            isProcessing (false),
            firstProcessCallback (true),
            descriptor (descriptor_),
            sample_rate (sample_rate_),
            buffer_size (512),
            midi_uri_id (0),
            port_count (0)
    {
        printf("JuceLV2Wrapper()\n");

        JUCE_AUTORELEASEPOOL;
        initialiseJuce_GUI();

#if JUCE_LINUX
        MessageManagerLock mmLock;
#endif

        filter = createPluginFilter();
        jassert(filter != nullptr);

        filter->setPlayConfigDetails(numInChans, numOutChans, 0, 0);

        // Port count
#if JucePlugin_WantsMidiInput
        port_count += 1;
#endif
#if JucePlugin_ProducesMidiOutput
        port_count += 1;
#endif
        port_count += numInChans;
        port_count += numOutChans;
        port_count += filter->getNumParameters();

        // Set Port data
        port_min = nullptr;
        port_mout = nullptr;
        ports_ctrl.insertMultiple(0, nullptr, filter->getNumParameters());
        ports_ctrl_last.insertMultiple(0, 0.0f, filter->getNumParameters());

        for (int i=0; i < numInChans; i++) {
            ports_ain[i] = nullptr;
        }

        for (int i=0; i < numOutChans; i++) {
            ports_aout[i] = nullptr;
        }

        for (int i=0; i < filter->getNumParameters(); i++) {
            ports_ctrl_last.set(i, filter->getParameter(i));
        }

        // Get MIDI URI Id
        for (uint16_t j = 0; features[j]; j++)
        {
            if (strcmp(features[j]->URI, LV2_URI_MAP_URI) == 0)
            {
                LV2_URI_Map_Feature* uri_feature = (LV2_URI_Map_Feature*)features[j]->data;
                midi_uri_id = uri_feature->uri_to_id(uri_feature->callback_data, LV2_EVENT_URI, "http://lv2plug.in/ns/ext/midi#MidiEvent");
                break;
            }
        }

        activePlugins.add (this);

        startTimer(1000);
    }

    ~JuceLV2Wrapper()
    {
        JUCE_AUTORELEASEPOOL

        {
#if JUCE_LINUX
            MessageManagerLock mmLock;
#endif
            stopTimer();

            delete filter;
            filter = nullptr;

            channels.free();
            deleteTempChannels();

            ports_ctrl.clear();
            ports_ctrl_last.clear();

            jassert (activePlugins.contains (this));
            activePlugins.removeValue (this);
        }

        if (activePlugins.size() == 0)
        {
#if JUCE_LINUX
            SharedMessageThread::deleteInstance();
#endif
            shutdownJuce_GUI();
        }
    }

    //==============================================================================
    // LV2 Descriptor Calls
    void do_connect_port(uint32_t port, void* data_location)
    {
        if (port < port_count)
        {
            int i;
            uint32_t index = 0;

#if JucePlugin_WantsMidiInput
            if (port == index) {
                port_min = (LV2_Event_Buffer*)data_location;
                return;
            }
            index += 1;
#endif

#if JucePlugin_ProducesMidiOutput
            if (port == index) {
                port_mout = (LV2_Event_Buffer*)data_location;
                return;
            }
            index += 1;
#endif

            for (i=0; i < numInChans; i++) {
                if (port == index) {
                    ports_ain[i] = (float*)data_location;
                    return;
                }
                index += 1;
            }

            for (i=0; i < numOutChans; i++) {
                if (port == index) {
                    ports_aout[i] = (float*)data_location;
                    return;
                }
                index += 1;
            }

            for (i=0; i < filter->getNumParameters(); i++) {
                if (port == index) {
                    ports_ctrl.set(i, (float*)data_location);
                    return;
                }
                index += 1;
            }
        }
    }

    void do_activate()
    {
        if (filter != nullptr)
        {
            isProcessing = true;
            channels.calloc (numInChans + numOutChans);

            jassert (sample_rate > 0);
            if (sample_rate <= 0.0)
                sample_rate = 44100.0;

            jassert (buffer_size > 0);

            firstProcessCallback = true;

            filter->setNonRealtime (false);
            filter->setPlayConfigDetails (numInChans, numOutChans, sample_rate, buffer_size);

            deleteTempChannels();

            filter->prepareToPlay (sample_rate, buffer_size);

            midiEvents.ensureSize (2048);
            midiEvents.clear();
        }
    }

    void do_deactivate()
    {
        if (filter != nullptr)
        {
            filter->releaseResources();

            isProcessing = false;
            channels.free();

            deleteTempChannels();
        }
    }

    void do_run(uint32_t sample_count)
    {
        if (firstProcessCallback)
        {
            firstProcessCallback = false;

            // if this fails, the host hasn't called resume() before processing
            jassert (isProcessing);

            // (tragically, some hosts actually need this, although it's stupid to have
            //  to do it here..)
            if (! isProcessing)
                do_activate();

            filter->setNonRealtime (false);

           #if JUCE_WINDOWS
            if (GetThreadPriority (GetCurrentThread()) <= THREAD_PRIORITY_NORMAL
                  && GetThreadPriority (GetCurrentThread()) >= THREAD_PRIORITY_LOWEST)
                filter->setNonRealtime (true);
           #endif
        }

        // Check if buffer size changed
        if (buffer_size != sample_count)
        {
            buffer_size = sample_count;
            filter->setPlayConfigDetails(numInChans, numOutChans, sample_rate, buffer_size);
            filter->prepareToPlay(sample_rate, buffer_size);
        }

        // Check for updated parameters
        float cur_value;
        for (int i = 0; i < ports_ctrl.size(); i++)
        {
            if (ports_ctrl[i] != nullptr)
            {
                cur_value = *(float*)ports_ctrl[i];
                if (ports_ctrl_last[i] != cur_value) {
                    filter->setParameter(i, cur_value);
                    ports_ctrl_last.setUnchecked(i, cur_value);
                }
            }
        }

        jassert (activePlugins.contains (this));

        {
            const ScopedLock sl (filter->getCallbackLock());

            const int numIn = numInChans;
            const int numOut = numOutChans;

            if (filter->isSuspended())
            {
                for (int i = 0; i < numOut; ++i)
                    zeromem (ports_aout[i], sizeof (float) * sample_count);
            }
            else
            {
                int i;
                for (i = 0; i < numOut; ++i)
                {
                    float* chan = tempChannels.getUnchecked(i);

                    if (chan == 0)
                    {
                        chan = ports_aout[i];

                        // if some output channels are disabled, some hosts supply the same buffer
                        // for multiple channels - this buggers up our method of copying the
                        // inputs over the outputs, so we need to create unique temp buffers in this case..
                        for (int j = i; --j >= 0;)
                        {
                            if (ports_aout[j] == chan)
                            {
                                chan = new float [buffer_size * 2];
                                tempChannels.set (i, chan);
                                break;
                            }
                        }
                    }

                    if (i < numIn && chan != ports_ain[i])
                        memcpy (chan, ports_ain[i], sizeof (float) * sample_count);

                    channels[i] = chan;
                }

                // LV2 MIDI Input
                if (port_min != nullptr)
                {
                    LV2_Event_Iterator iter;
                    lv2_event_begin(&iter, port_min);

                    lv2_event_buffer_reset(port_min, LV2_EVENT_AUDIO_STAMP, (uint8_t*)(port_min + 1));

                    for (uint32_t i=0; i < iter.buf->event_count; ++i) {
                        uint8_t* data;
                        LV2_Event* ev = lv2_event_get(&iter, &data);
                        midiEvents.addEvent(data, ev->size, ev->frames);
                        lv2_event_increment(&iter);
                    }
                }

                for (; i < numIn; ++i)
                    channels[i] = ports_ain[i];

                AudioSampleBuffer chans (channels, jmax (numIn, numOut), sample_count);

                filter->processBlock (chans, midiEvents);
            }
        }

        if (! midiEvents.isEmpty() && port_mout != nullptr)
        {
#if JucePlugin_ProducesMidiOutput
            const int numEvents = midiEvents.getNumEvents();

            LV2_Event_Iterator iter;
            lv2_event_buffer_reset(port_mout, LV2_EVENT_AUDIO_STAMP, (uint8_t*)(port_mout + 1));
            lv2_event_begin(&iter, port_mout);

            const JUCE_NAMESPACE::uint8* midiEventData;
            int midiEventSize, midiEventPosition;
            MidiBuffer::Iterator i (midiEvents);

            while (i.getNextEvent (midiEventData, midiEventSize, midiEventPosition))
            {
                jassert (midiEventPosition >= 0 && midiEventPosition < sample_count);

                lv2_event_write(&iter, midiEventPosition, 0, midi_uri_id, midiEventSize, midiEventData);
            }
#endif
            midiEvents.clear();
        }
    }

    void do_cleanup()
    {
        stopTimer();

#if 0
        if (descriptor)
        {
            free((void*)descriptor->URI);
            delete descriptor;
        }
#endif
    }

    //==============================================================================
    // JUCE Stuff

    AudioProcessor* getFilter() { return filter; }

    //==============================================================================
    int32_t getChunk (void** data)
    {
        if (filter == nullptr)
            return 0;

        chunkMemory.setSize (0);
        filter->getCurrentProgramStateInformation (chunkMemory);

        *data = (void*) chunkMemory.getData();

        // because the chunk is only needed temporarily by the host (or at least you'd
        // hope so) we'll give it a while and then free it in the timer callback.
        chunkMemoryTime = JUCE_NAMESPACE::Time::getApproximateMillisecondCounter();

        return (int32_t) chunkMemory.getSize();
    }

    void setChunk (void* data, int32_t byteSize)
    {
        if (filter == nullptr)
            return;

        chunkMemory.setSize (0);
        chunkMemoryTime = 0;

        if (byteSize > 0 && data != nullptr)
        {
            filter->setCurrentProgramStateInformation (data, byteSize);
        }
    }

    void timerCallback()
    {
        if (chunkMemoryTime > 0 && chunkMemoryTime < JUCE_NAMESPACE::Time::getApproximateMillisecondCounter() - 2000)
        {
            chunkMemoryTime = 0;
            chunkMemory.setSize (0);
        }
    }

    //==============================================================================
private:
    AudioProcessor* filter;
    JUCE_NAMESPACE::MemoryBlock chunkMemory;
    JUCE_NAMESPACE::uint32 chunkMemoryTime;
    MidiBuffer midiEvents;
    int numInChans, numOutChans;
    bool isProcessing, firstProcessCallback;
    HeapBlock<float*> channels;
    Array<float*> tempChannels;  // see note in do_run()

    const LV2_Descriptor* descriptor;

    double sample_rate;
    int buffer_size;
    uint16_t midi_uri_id;
    uint32_t port_count;

    LV2_Event_Buffer* port_min;
    LV2_Event_Buffer* port_mout;
    float* ports_ain[JucePlugin_MaxNumInputChannels];
    float* ports_aout[JucePlugin_MaxNumOutputChannels];
    Array<float*> ports_ctrl;
    Array<float> ports_ctrl_last;

    //==============================================================================
    void deleteTempChannels()
    {
        for (int i = tempChannels.size(); --i >= 0;)
            delete[] (tempChannels.getUnchecked(i));

        tempChannels.clear();

        if (filter != nullptr)
            tempChannels.insertMultiple (0, 0, filter->getNumInputChannels() + filter->getNumOutputChannels());
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLV2Wrapper);
};

//==============================================================================
// Create a new JUCE External UI
class JuceLv2ExternalUI  : public lv2_external_ui,
                           public DocumentWindow
{
public:
    JuceLv2ExternalUI (JuceLV2Wrapper* const wrapper_, AudioProcessorEditor* const editor_, lv2_external_ui_host* external_ui_host_, LV2UI_Controller controller_) :
        DocumentWindow(String::empty, Colours::white, DocumentWindow::minimiseButton | DocumentWindow::closeButton, true),
            wrapper(wrapper_),
            editor(editor_),
            external_ui_host(external_ui_host_),
            controller(controller_)
    {
        lv2_external_ui::run = do_run;
        lv2_external_ui::show = do_show;
        lv2_external_ui::hide = do_hide;

        //setOpaque (true);
        //editor->setOpaque (true);

        //String title = external_ui_host->plugin_human_id != nullptr ? String(external_ui_host->plugin_human_id) : wrapper->getFilter()->getName();
        //setName(title);

        //setTitleBarHeight (0);
        //setDropShadowEnabled(false);
        //setUsingNativeTitleBar(true);

        //setContentNonOwned(editor, true);
    }

    ~JuceLv2ExternalUI()
    {
    }

    static void do_run(lv2_external_ui * _this_)
    {
      std::cout << "run" << std::endl;
        //editor->repaint();
        //repaint();
    }

    static void do_show(lv2_external_ui * _this_)
    {
      std::cout << "show" << std::endl;
        //setVisible(true);
    }

    static void do_hide(lv2_external_ui * _this_)
    {
      std::cout << "hide" << std::endl;
        //setVisible(false);
    }

    AudioProcessorEditor* getEditorComp() const
    {
        return dynamic_cast <AudioProcessorEditor*> (getContentComponent());
    }

    void closeButtonPressed()
    {
        //delete this;
        external_ui_host->ui_closed(controller);
    }

    LV2UI_Widget getLv2Widget()
    {
        return nullptr; //&external_ui;
    }

private:
    JuceLV2Wrapper* wrapper;
    AudioProcessorEditor* editor;

    lv2_external_ui external_ui;
    lv2_external_ui_host* external_ui_host;
    LV2UI_Controller controller;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLv2ExternalUI);
};

//==============================================================================
// Create a new JUCE Editor
class JuceLv2Editor : public AudioProcessorListener
{
public:
    JuceLv2Editor (JuceLV2Wrapper* const wrapper_, const LV2UI_Descriptor* ui_descriptor_, LV2UI_Write_Function write_function_, LV2UI_Controller controller_, LV2UI_Widget* widget, const LV2_Feature* const* features, bool isExternalUI) :
            wrapper(wrapper_),
            externalUI(nullptr),
            ui_descriptor(ui_descriptor_),
            write_function(write_function_),
            controller(controller_),
            editor(nullptr)
    {
        filter = wrapper->getFilter();
        filter->addListener(this);

        if (filter->hasEditor() && false)
        {
            printf("TEST - Before\n");
            editor = filter->createEditorIfNeeded();
            printf("TEST - After\n");
        }

        if (editor != nullptr)
        {
            if (isExternalUI)
            {
                // External UI
                lv2_external_ui_host* external_ui_host = nullptr;

                for (uint16_t j = 0; features[j]; j++)
                {
                    if (strcmp(features[j]->URI, LV2_EXTERNAL_UI_URI) == 0 && features[j]->data != nullptr)
                    {
                        external_ui_host = (lv2_external_ui_host*)features[j]->data;
                        break;
                    }
                }

                if (external_ui_host)
                {
                    externalUI = new JuceLv2ExternalUI(wrapper, editor, external_ui_host, controller);
                    *widget = nullptr; //externalUI;
                }
                else
                {
                    *widget = nullptr;
                    std::cerr << "Failed to init external UI" << std::endl;
                }
            }
            else
            {
                // JUCE UI
                editor->setOpaque (true);
                editor->setVisible (true);
                *widget = editor;
            }
        }
        else
        {
            widget = nullptr;
            std::cerr << "Failed to init UI" << std::endl;
        }

        // Padding for control ports
        ctrl_pad = 0;
#if JucePlugin_WantsMidiInput
        ctrl_pad += 1;
#endif
#if JucePlugin_ProducesMidiOutput
        ctrl_pad += 1;
#endif
        ctrl_pad += JucePlugin_MaxNumInputChannels;
        ctrl_pad += JucePlugin_MaxNumOutputChannels;
    }

    ~JuceLv2Editor()
    {
        JUCE_AUTORELEASEPOOL
        PopupMenu::dismissAllActiveMenus();

        filter->removeListener(this);
        filter->editorBeingDeleted (editor);

        if (externalUI != nullptr)
            delete externalUI;

        //if (editor != nullptr)
        //    deleteAndZero (editor);
    }

    void do_port_event(uint32_t port_index, float value)
    {
        filter->setParameter(port_index-ctrl_pad, value);
    }

    void do_cleanup()
    {
        // We should only do this after UI gets working
#if 0
        if (ui_descriptor)
        {
            free((void*)ui_descriptor->URI);
            delete ui_descriptor;
        }
#endif
    }

    //==============================================================================
    void audioProcessorParameterChanged (AudioProcessor*, int index, float newValue)
    {
        if (controller && write_function)
            write_function(controller, index+ctrl_pad, 4 /* sizeof(float) */, 0, &newValue);
    }

    void audioProcessorChanged (AudioProcessor*) {}

private:
    JuceLV2Wrapper* wrapper;
    JuceLv2ExternalUI* externalUI;
    AudioProcessor* filter;
    AudioProcessorEditor* editor;

    const LV2UI_Descriptor* ui_descriptor;
    LV2UI_Write_Function write_function;
    LV2UI_Controller controller;

    int32_t ctrl_pad;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLv2Editor);
};

//==============================================================================
// LV2 descriptor functions
LV2_Handle juce_lv2_instantiate(const LV2_Descriptor* descriptor, double sample_rate, const char* bundle_path, const LV2_Feature* const* features)
{
    JuceLV2Wrapper* wrapper = new JuceLV2Wrapper(descriptor, sample_rate, features);
    return wrapper;
}

void juce_lv2_connect_port(LV2_Handle instance, uint32_t port, void* data_location)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    wrapper->do_connect_port(port, data_location);
}

void juce_lv2_activate(LV2_Handle instance)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    wrapper->do_activate();
}

void juce_lv2_run(LV2_Handle instance, uint32_t sample_count)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    wrapper->do_run(sample_count);
}

void juce_lv2_deactivate(LV2_Handle instance)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    wrapper->do_deactivate();
}

void juce_lv2_cleanup(LV2_Handle instance)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    wrapper->do_cleanup();
    delete wrapper;
}

const void* juce_lv2_extension_data(const char* uri)
{
    printf("TODO :: juce_lv2_extension_data()\n");
    return nullptr;
}

//==============================================================================
LV2UI_Handle juce_lv2ui_instantiate(const LV2UI_Descriptor* descriptor, LV2UI_Write_Function write_function, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features, bool isExternalUI)
{
    const MessageManagerLock mmLock;

    for (uint16_t i = 0; features[i]; i++)
    {
        if (strcmp(features[i]->URI, LV2_INSTANCE_ACCESS_URI) == 0 && features[i]->data != nullptr)
        {
            JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)features[i]->data;
            JuceLv2Editor* editor = new JuceLv2Editor(wrapper, descriptor, write_function, controller, widget, features, isExternalUI);
            return editor;
        }
    }

    std::cerr << "Host does not support instance data - cannot use UI" << std::endl;
    return nullptr;
}

LV2UI_Handle juce_lv2ui_instantiate_JUCE(const LV2UI_Descriptor* descriptor, const char* plugin_uri, const char* bundle_path, LV2UI_Write_Function write_function, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features)
{
    return juce_lv2ui_instantiate(descriptor, write_function, controller, widget, features, false);
}

LV2UI_Handle juce_lv2ui_instantiate_external(const LV2UI_Descriptor* descriptor, const char* plugin_uri, const char* bundle_path, LV2UI_Write_Function write_function, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features)
{
    return juce_lv2ui_instantiate(descriptor, write_function, controller, widget, features, true);
}

void juce_lv2ui_port_event(LV2UI_Handle instance, uint32_t port_index, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    const MessageManagerLock mmLock;
    JuceLv2Editor* editor = (JuceLv2Editor*)instance;

    if (buffer_size == 4 /* sizeof(float) */ && format == 0)
    {
        float value = *(float*)buffer;
        editor->do_port_event(port_index, value);
    }
}

void juce_lv2ui_cleanup(LV2UI_Handle instance)
{
    const MessageManagerLock mmLock;
    JuceLv2Editor* editor = (JuceLv2Editor*)instance;
    editor->do_cleanup();
    delete editor;
}

//==============================================================================
// Create new LV2 objects
LV2_Descriptor* getNewLv2Plugin()
{
    LV2_Descriptor* const Lv2Plugin = new LV2_Descriptor;
    Lv2Plugin->URI = strdup((const char*) get_uri().toUTF8());
    Lv2Plugin->instantiate = juce_lv2_instantiate;
    Lv2Plugin->connect_port = juce_lv2_connect_port;
    Lv2Plugin->activate = juce_lv2_activate;
    Lv2Plugin->run = juce_lv2_run;
    Lv2Plugin->deactivate = juce_lv2_deactivate;
    Lv2Plugin->cleanup = juce_lv2_cleanup;
    Lv2Plugin->extension_data = juce_lv2_extension_data;
    return Lv2Plugin;
}

LV2UI_Descriptor* getNewLv2UI_JUCE()
{
    LV2UI_Descriptor* Lv2UI = new LV2UI_Descriptor;
    Lv2UI->URI = strdup((const char*) get_juce_ui_uri().toUTF8());
    Lv2UI->instantiate = juce_lv2ui_instantiate_JUCE;
    Lv2UI->cleanup = juce_lv2ui_cleanup;
    Lv2UI->port_event = juce_lv2ui_port_event;
    Lv2UI->extension_data = juce_lv2_extension_data;
    return Lv2UI;
}

LV2UI_Descriptor* getNewLv2UI_External()
{
    LV2UI_Descriptor* Lv2UI = new LV2UI_Descriptor;
    Lv2UI->URI = strdup((const char*) get_external_ui_uri().toUTF8());
    Lv2UI->instantiate = juce_lv2ui_instantiate_external;
    Lv2UI->cleanup = juce_lv2ui_cleanup;
    Lv2UI->port_event = juce_lv2ui_port_event;
    Lv2UI->extension_data = juce_lv2_extension_data;
    return Lv2UI;
}

LV2UI_Descriptor* getNewLv2UI(bool external)
{
    return external ? getNewLv2UI_External() : getNewLv2UI_JUCE();
}

//==============================================================================
// Mac startup code..
#if JUCE_MAC

    extern "C" __attribute__ ((visibility("default"))) void juce_lv2_ttl_generator()
    {
        generate_ttl();
    }

    extern "C" __attribute__ ((visibility("default"))) const LV2_Descriptor* lv2_descriptor(uint32_t index)
    {
        initialiseMac();
        return (index == 0) ? getNewLv2Plugin() : nullptr;
    }

    extern "C" __attribute__ ((visibility("default"))) const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index)
    {
        return (index <= 1) ? getNewLv2UI((index == 1)) : nullptr;
    }

//==============================================================================
// Linux startup code..
#elif JUCE_LINUX

    extern "C" __attribute__ ((visibility("default"))) void juce_lv2_ttl_generator()
    {
        generate_ttl();
    }

    extern "C" __attribute__ ((visibility("default"))) const LV2_Descriptor* lv2_descriptor(uint32_t index)
    {
        SharedMessageThread::getInstance();
        return (index == 0) ? getNewLv2Plugin() : nullptr;
    }

    extern "C" __attribute__ ((visibility("default"))) const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index)
    {
        return (index <= 1) ? getNewLv2UI((index == 1)) : nullptr;
    }

    // don't put initialiseJuce_GUI or shutdownJuce_GUI in these... it will crash!
    __attribute__((constructor)) void myPluginInit() {}
    __attribute__((destructor))  void myPluginFini() {}

//==============================================================================
// Win32 startup code..
#else

    extern "C" __declspec (dllexport) void juce_lv2_ttl_generator()
    {
        generate_ttl();
    }

    extern "C" __declspec (dllexport) const LV2_Descriptor* lv2_descriptor(uint32_t index)
    {
        return (index == 0) ? getNewLv2Plugin() : nullptr;
    }

    extern "C" __declspec (dllexport) const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index)
    {
        return (index <= 1) ? getNewLv2UI((index == 1)) : nullptr;
    }

#endif

#endif
