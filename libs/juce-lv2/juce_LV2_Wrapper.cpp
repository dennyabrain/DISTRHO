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
#include "lv2/event-helpers.h"
#include "lv2/instance-access.h"
#include "lv2/state.h"
#include "lv2/uri-map.h"
#include "lv2/time.h"
#include "lv2/ui.h"
#include "lv2/ui-resize.h"
#include "lv2/lv2_external_ui.h"

extern AudioProcessor* JUCE_CALLTYPE createPluginFilter();

//==============================================================================
// Various helper functions for creating the ttl files

/** Converts a parameter name to an LV2 compatible symbol. */
String nameToSymbol(const String& name, const uint32 portIndex)
{
    String trimmedName = name.trimStart().trimEnd().toLowerCase();

    if (trimmedName.isEmpty())
        return String(portIndex);

    String symbol;
    for (int i=0; i < trimmedName.length(); i++)
    {
        const juce_wchar c = trimmedName[i];
        if (std::isalpha(c) || std::isdigit(c))
            symbol += c;
        else
            symbol += '_';
    }
    return symbol;
}

/** Returns the URI of the plugin */
String getURI()
{
    return String("urn:" JucePlugin_Manufacturer ":" JucePlugin_Name).replace(" ", "_");
}

/** Returns the URI of the X11 UI */
String getX11UIURI()
{
    return String("urn:" JucePlugin_Manufacturer ":" JucePlugin_Name ":X11-UI").replace(" ", "_");
}

/** Returns the URI of the External UI */
String getExternalUIURI(bool isNew)
{
    if (isNew)
      return String("urn:" JucePlugin_Manufacturer ":" JucePlugin_Name ":JUCE-External-UI").replace(" ", "_");
    else
      return String("urn:" JucePlugin_Manufacturer ":" JucePlugin_Name ":JUCE-OldExternal-UI").replace(" ", "_");
}

/** Returns the name of the plugin binary file */
String getBinaryName()
{
    return String(JucePlugin_Name).replace(" ", "_");
}

/** Returns plugin type, defined in JucePluginCharacteristics.h */
const String getPluginType()
{
    String pluginType;
#if defined(JucePlugin_LV2Category)
    pluginType = "lv2:" JucePlugin_LV2Category;
#endif
    if (pluginType.isNotEmpty())
        pluginType += ", ";

    pluginType += "lv2:Plugin";
    return pluginType;
}

/** Create the manifest.ttl contents */
String makeManifestTtl(const String& uri, const String& binary)
{
    String manifest;
    manifest += "@prefix lv2:  <http://lv2plug.in/ns/lv2core#> .\n";
    manifest += "@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .\n";
    manifest += "\n";
    manifest += "<" + uri + ">\n";
    manifest += "    a lv2:Plugin ;\n";
    manifest += "    lv2:binary <" + binary + ".so> ;\n";
    manifest += "    rdfs:seeAlso <" + binary +".ttl> .\n";
    return manifest;
}

/** Create the plugin.ttl contents */
String makePluginTtl(const String& uri, const String& binary)
{
    uint32 portIndex = 0;
    ScopedPointer<AudioProcessor> filter (createPluginFilter());

    String plugin;
    plugin += "@prefix doap:  <http://usefulinc.com/ns/doap#> .\n";
    plugin += "@prefix foaf:  <http://xmlns.com/foaf/0.1/> .\n";
    plugin += "@prefix lv2:   <http://lv2plug.in/ns/lv2core#> .\n";
    plugin += "@prefix lv2ev: <http://lv2plug.in/ns/ext/event#> .\n";
    plugin += "@prefix lv2ui: <http://lv2plug.in/ns/extensions/ui#> .\n";
    plugin += "@prefix lv2st: <http://lv2plug.in/ns/ext/state#> .\n";
    plugin += "\n";

    if (filter->hasEditor())
    {
        plugin += "<" + getX11UIURI() + ">\n";
        plugin += "    a lv2ui:X11UI ;\n";
        plugin += "    lv2ui:binary <" + binary + ".so> .\n";
        plugin += "<" + getExternalUIURI(true) + ">\n";
        plugin += "    a <http://nedko.arnaudov.name/lv2/external_ui/> ;\n";
        plugin += "    lv2ui:binary <" + binary + ".so> .\n";
        plugin += "<" + getExternalUIURI(false) + ">\n";
        plugin += "    a lv2ui:external ;\n";
        plugin += "    lv2ui:binary <" + binary + ".so> .\n";
        plugin += "\n";
    }

    plugin += "<" + uri + ">\n";
    plugin += "    a " + getPluginType() + " ;\n";
    plugin += "    lv2:extensionData lv2st:Interface ;\n";

    if (filter->hasEditor())
    {
        plugin += "    lv2ui:ui <" + getX11UIURI() + "> ,\n";
        plugin += "             <" + getExternalUIURI(true) + "> ,\n";
        plugin += "             <" + getExternalUIURI(false) + "> ;\n";
    }
    plugin += "\n";

#if JucePlugin_WantsLV2TimePos
    plugin += "    lv2:port [\n";
    plugin += "      a lv2:InputPort, lv2ev:EventPort ;\n";
    plugin += "      lv2ev:supportsEvent <http://lv2plug.in/ns/ext/time#Position> ;\n";
    plugin += "      lv2:index " + String(portIndex++) + " ;\n";
    plugin += "      lv2:symbol \"lv2_time_pos\" ;\n";
    plugin += "      lv2:name \"LV2 Position\" ;\n";
    plugin += "      lv2:portProperty lv2:connectionOptional ;\n";
    plugin += "    ] ;\n\n";
#endif

#if JucePlugin_WantsMidiInput
    plugin += "    lv2:port [\n";
    plugin += "      a lv2:InputPort, lv2ev:EventPort ;\n";
    plugin += "      lv2ev:supportsEvent <http://lv2plug.in/ns/ext/midi#MidiEvent> ;\n";
    plugin += "      lv2:index " + String(portIndex++) + " ;\n";
    plugin += "      lv2:symbol \"midi_in\" ;\n";
    plugin += "      lv2:name \"MIDI Input\" ;\n";
    plugin += "    ] ;\n\n";
#endif

#if JucePlugin_ProducesMidiOutput
    plugin += "    lv2:port [\n";
    plugin += "      a lv2:OutputPort, lv2ev:EventPort ;\n";
    plugin += "      lv2ev:supportsEvent <http://lv2plug.in/ns/ext/midi#MidiEvent> ;\n";
    plugin += "      lv2:index " + String(portIndex++) + " ;\n";
    plugin += "      lv2:symbol \"midi_out\" ;\n";
    plugin += "      lv2:name \"MIDI Output\" ;\n";
    plugin += "    ] ;\n\n";
#endif

    for (int i=0; i<JucePlugin_MaxNumInputChannels; i++)
    {
        if (i == 0)
            plugin += "    lv2:port [\n";
        else
            plugin += "    [\n";

        plugin += "      a lv2:InputPort, lv2:AudioPort ;\n";
        plugin += "      lv2:index " + String(portIndex++) + " ;\n";
        plugin += "      lv2:symbol \"audio_in_" + String(i+1) + "\" ;\n";
        plugin += "      lv2:name \"Audio Input " + String(i+1) + "\" ;\n";

        if (i+1 == JucePlugin_MaxNumInputChannels)
            plugin += "    ] ;\n\n";
        else
            plugin += "    ],\n";
    }

    for (int i=0; i<JucePlugin_MaxNumOutputChannels; i++)
    {
        if (i == 0)
            plugin += "    lv2:port [\n";
        else
            plugin += "    [\n";

        plugin += "      a lv2:OutputPort, lv2:AudioPort ;\n";
        plugin += "      lv2:index " + String(portIndex++) + " ;\n";
        plugin += "      lv2:symbol \"audio_out_" + String(i+1) + "\" ;\n";
        plugin += "      lv2:name \"Audio Output " + String(i+1) + "\" ;\n";

        if (i+1 == JucePlugin_MaxNumOutputChannels)
            plugin += "    ] ;\n\n";
        else
            plugin += "    ],\n";
    }

    for (int i=0; i < filter->getNumParameters(); i++)
    {
        if (i == 0)
            plugin += "    lv2:port [\n";
        else
            plugin += "    [\n";

        plugin += "      a lv2:InputPort ;\n";
        plugin += "      a lv2:ControlPort ;\n";
        plugin += "      lv2:index " + String(portIndex++) + " ;\n";
        plugin += "      lv2:symbol \"" + nameToSymbol(filter->getParameterName(i), i) + "\" ;\n";
        plugin += "      lv2:name \"" + filter->getParameterName(i) + "\" ;\n";
        plugin += "      lv2:default " + String(filter->getParameter(i)) + " ;\n";
        plugin += "      lv2:minimum 0.0 ;\n";
        plugin += "      lv2:maximum 1.0 ;\n";

        if (i+1 == filter->getNumParameters())
            plugin += "    ] ;\n\n";
        else
            plugin += "    ],\n";
    }

    plugin += "    doap:name \"" JucePlugin_Name "\" ;\n";
    plugin += "    doap:maintainer [ foaf:name \"" JucePlugin_Manufacturer "\" ] .\n";

    return plugin;
}

/** Creates the manifest.ttl and plugin.ttl files */
void createTtlFiles()
{
    ScopedJuceInitialiser_GUI juceInitialiser;
    String URI = getURI();
    String Binary = getBinaryName();
    String BinaryTtl = Binary + ".ttl";

    std::cout << "Writing manifest.ttl...";
    std::fstream manifest("manifest.ttl", std::ios::out);
    manifest << makeManifestTtl(URI, Binary) << std::endl;
    manifest.close();
    std::cout << " done!" << std::endl;

    std::cout << "Writing " << BinaryTtl << "...";
    std::fstream plugin(BinaryTtl.toUTF8(), std::ios::out);
    plugin << makePluginTtl(URI, Binary) << std::endl;
    plugin.close();
    std::cout << " done!" << std::endl;
}

//==============================================================================
BEGIN_JUCE_NAMESPACE
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

enum Lv2UiType {
  LV2_UI_X11 = 1,
  LV2_UI_EXTERNAL
};

//==============================================================================
/** Lightweight DocumentWindow subclass that captures close button presses, and responds by closing the external ui. */
class JuceLV2DocumentWindow : public DocumentWindow
{
public:
    /** Creates a Document Window wrapper */
    JuceLV2DocumentWindow (const String& title) :
            DocumentWindow (title, Colours::white, DocumentWindow::minimiseButton | DocumentWindow::closeButton, true),
            closed(false),
            lastPos(100, 100)
    {
    }

    /** Close button handler */
    void closeButtonPressed()
    {
        lastPos = getScreenPosition();
        removeFromDesktop();
        closed = true;
    }

    Point<int> getLastPos()
    {
      return lastPos;
    }

    bool isClosed()
    {
        return closed;
    }

    void reset()
    {
        closed = false;
    }

private:
    bool closed;
    Point<int> lastPos;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLV2DocumentWindow);
};

//==============================================================================
/** Create a new JUCE External UI */
class JuceLv2ExternalUI : public lv2_external_ui
{
public:
    JuceLv2ExternalUI (AudioProcessor* filter_, AudioProcessorEditor* const editor_, const String& title) :
            editor(editor_),
            window(nullptr)
    {
        run  = do_ui_run;
        show = do_ui_show;
        hide = do_ui_hide;

        const MessageManagerLock mmLock;
        window = new JuceLV2DocumentWindow(title);
        window->setOpaque(true);
        //window->setAlwaysOnTop(true); // FIXME - does not work properly on Linux
        window->setUsingNativeTitleBar(true);
        window->setContentNonOwned(editor, true);
    }

    ~JuceLv2ExternalUI()
    {
        if (window)
            delete window;
    }

    static void do_ui_run(lv2_external_ui * _this_)
    {
        const MessageManagerLock mmLock;
        JuceLv2ExternalUI* externalUI = (JuceLv2ExternalUI*)_this_;
        if (externalUI->window && !externalUI->window->isClosed())
            externalUI->window->repaint();
    }

    static void do_ui_show(lv2_external_ui * _this_)
    {
        const MessageManagerLock mmLock;
        JuceLv2ExternalUI* externalUI = (JuceLv2ExternalUI*)_this_;
        if (externalUI->window && !externalUI->window->isClosed())
        {
            if (!externalUI->window->isOnDesktop())
            {
                Point<int> lastPos = externalUI->window->getLastPos();
                externalUI->window->setTopLeftPosition(lastPos.getX(), lastPos.getY());
                externalUI->window->addToDesktop();
                //externalUI->window->addToDesktop(externalUI->window->getDesktopWindowStyleFlags());
            }
            externalUI->window->setVisible(true);
        }
    }

    static void do_ui_hide(lv2_external_ui * _this_)
    {
        const MessageManagerLock mmLock;
        JuceLv2ExternalUI* externalUI = (JuceLv2ExternalUI*)_this_;
        if (externalUI->window && !externalUI->window->isClosed())
          externalUI->window->setVisible(false);
    }

    bool isClosed()
    {
        if (window)
            return window->isClosed();
        else
            return false;
    }

    void resetWindow()
    {
        if (window)
            window->reset();
    }

private:
    AudioProcessorEditor* editor;
    JuceLV2DocumentWindow* window;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLv2ExternalUI);
};

//==============================================================================
/** Create a new JUCE Editor */
class JuceLV2Editor : public AudioProcessorListener,
                      public Timer
{
public:
    JuceLV2Editor (AudioProcessor* filter_, const LV2UI_Descriptor* uiDescriptor_, LV2UI_Write_Function writeFunction_, LV2UI_Controller controller_, LV2UI_Widget* widget, const LV2_Feature* const* features, Lv2UiType uiType_) :
            filter(filter_),
            editor(nullptr),
            externalUI(nullptr),
            externalUIHost(nullptr),
            uiResizeFeature(nullptr),
            uiDescriptor(uiDescriptor_),
            writeFunction(writeFunction_),
            controller(controller_),
            uiType(uiType_)
    {
        filter->addListener(this);

        if (filter->hasEditor())
        {
            editor = filter->createEditorIfNeeded();
        }

        if (editor)
        {
            switch(uiType)
            {
            case LV2_UI_X11:
                editor->setOpaque (true);
                editor->addToDesktop (0);
                *widget = editor->getWindowHandle();
                for (uint16 j = 0; features[j]; j++)
                {
                    if (strcmp(features[j]->URI, LV2_UI_RESIZE_URI "#UIResize") == 0 && features[j]->data)
                    {
                        uiResizeFeature = (LV2_UI_Resize_Feature*)features[j]->data;
                        uiResizeFeature->ui_resize(uiResizeFeature->data, editor->getWidth(), editor->getHeight());
                        break;
                    }
                }
                break;

            case LV2_UI_EXTERNAL:
                for (uint16 j = 0; features[j]; j++)
                {
                    if ((strcmp(features[j]->URI, LV2_EXTERNAL_UI_URI) == 0 || strcmp(features[j]->URI, LV2_EXTERNAL_UI_DEPRECATED_URI) == 0) && features[j]->data)
                    {
                        externalUIHost = (lv2_external_ui_host*)features[j]->data;
                        break;
                    }
                }

                if (externalUIHost)
                {
                    String title = (externalUIHost->plugin_human_id && externalUIHost->plugin_human_id[0] != 0) ? String(externalUIHost->plugin_human_id) : filter->getName();
                    externalUI = new JuceLv2ExternalUI(filter, editor, title);
                    *widget = externalUI;
                }
                else
                {
                    *widget = nullptr;
                    std::cerr << "Failed to init external UI host" << std::endl;
                }
                break;

            default:
                *widget = nullptr;
                std::cerr << "Unknown UI Type" << std::endl;
            }
        }
        else
        {
            *widget = nullptr;
            std::cerr << "Plugin has no UI" << std::endl;
        }

        // Offset for control ports
        parameterPortOffset = 0;
#if JucePlugin_WantsLV2TimePos
        parameterPortOffset += 1;
#endif
#if JucePlugin_WantsMidiInput
        parameterPortOffset += 1;
#endif
#if JucePlugin_ProducesMidiOutput
        parameterPortOffset += 1;
#endif
        parameterPortOffset += JucePlugin_MaxNumInputChannels;
        parameterPortOffset += JucePlugin_MaxNumOutputChannels;
    }

    ~JuceLV2Editor()
    {
        JUCE_AUTORELEASEPOOL
        PopupMenu::dismissAllActiveMenus();

        stopTimer();

        filter->removeListener(this);

        if (externalUI)
            delete externalUI;

        if (editor)
        {
          filter->editorBeingDeleted(editor);
          delete editor;
        }
    }

    void doPortEvent(const uint32 portIndex, const float value)
    {
        filter->setParameter(portIndex-parameterPortOffset, value);
    }

    void doCleanup()
    {
    }

    //==============================================================================
    void audioProcessorParameterChanged (AudioProcessor*, int index, float newValue)
    {
        if (controller && writeFunction)
            writeFunction(controller, index+parameterPortOffset, sizeof(float), 0, &newValue);
    }

    void audioProcessorChanged (AudioProcessor*) {}

    //==============================================================================
    void resetExternalUIIfNeeded(LV2UI_Write_Function writeFunction_, LV2UI_Controller controller_, LV2UI_Widget* widget)
    {
        writeFunction = writeFunction_;
        controller = controller_;

        if (uiType == LV2_UI_EXTERNAL)
        {
            *widget = externalUI;

            if (externalUI)
            {
                externalUI->resetWindow();
                startTimer(100);
            }
        }
    }

    void timerCallback()
    {
        if (externalUI->isClosed())
        {
            if (externalUIHost)
               externalUIHost->ui_closed(controller);

            stopTimer();
        }
    }

private:
    AudioProcessor* filter;
    AudioProcessorEditor* editor;
    JuceLv2ExternalUI* externalUI;
    lv2_external_ui_host* externalUIHost;
    LV2_UI_Resize_Feature* uiResizeFeature;

    const LV2UI_Descriptor* uiDescriptor;
    LV2UI_Write_Function writeFunction;
    LV2UI_Controller controller;
    Lv2UiType uiType;

    int32 parameterPortOffset;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLV2Editor);
};

//==============================================================================
// Create a new JUCE LV2 Plugin
class JuceLV2Wrapper : public AudioPlayHead
{
public:
    JuceLV2Wrapper(const LV2_Descriptor* descriptor_, double sampleRate_, const LV2_Feature* const* features) :
            lv2Editor (nullptr),
            numInChans (JucePlugin_MaxNumInputChannels),
            numOutChans (JucePlugin_MaxNumOutputChannels),
            isProcessing (false),
            firstProcessCallback (true),
            descriptor (descriptor_),
            sampleRate (sampleRate_),
            bufferSize (512),
            uriMap (nullptr),
            midiURIId (0),
            portCount (0)
    {
        JUCE_AUTORELEASEPOOL;
        initialiseJuce_GUI();

#if JUCE_LINUX
        MessageManagerLock mmLock;
#endif

        filter = createPluginFilter();
        jassert(filter != nullptr);

        filter->setPlayConfigDetails(numInChans, numOutChans, 0, 0);
        filter->setPlayHead (this);

        // Port count
        portCount  = 0;
#if JucePlugin_WantsLV2TimePos
        portCount += 1;
#endif
#if JucePlugin_WantsMidiInput
        portCount += 1;
#endif
#if JucePlugin_ProducesMidiOutput
        portCount += 1;
#endif
        portCount += numInChans;
        portCount += numOutChans;
        portCount += filter->getNumParameters();

        memset(&timePos, 0, sizeof(LV2_Time_Position));

        // Set Port data
        timePosPort = nullptr;
        midiInPort  = nullptr;
        midiOutPort = nullptr;
        parameterInPorts.insertMultiple(0, nullptr, filter->getNumParameters());
        parameterInPortsValues.insertMultiple(0, 0.0f, filter->getNumParameters());

        for (int i=0; i < numInChans; i++)
            audioInPorts[i] = nullptr;

        for (int i=0; i < numOutChans; i++)
            audioOutPorts[i] = nullptr;

        for (int i=0; i < filter->getNumParameters(); i++)
            parameterInPortsValues.set(i, filter->getParameter(i));

        // Get MIDI URI Id
        for (uint16 j = 0; features[j]; j++)
        {
            if (strcmp(features[j]->URI, LV2_URI_MAP_URI) == 0)
            {
                uriMap = (LV2_URI_Map_Feature*)features[j]->data;
                midiURIId = uriMap->uri_to_id(uriMap->callback_data, LV2_EVENT_URI, "http://lv2plug.in/ns/ext/midi#MidiEvent");
                break;
            }
        }

        activePlugins.add (this);
    }

    ~JuceLV2Wrapper()
    {
        JUCE_AUTORELEASEPOOL

        {
#if JUCE_LINUX
            MessageManagerLock mmLock;
#endif
            if (lv2Editor)
              delete lv2Editor;

            delete filter;
            filter = nullptr;

            channels.free();
            deleteTempChannels();

            parameterInPorts.clear();
            parameterInPortsValues.clear();

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
    void doConnectPort(const uint32 port, void* dataLocation)
    {
        if (port < portCount)
        {
            uint32 index = 0;

#if JucePlugin_WantsLV2TimePos
            if (port == 0)
            {
                timePosPort = (LV2_Event_Buffer*)dataLocation;
                return;
            }
            ++index;
#endif

#if JucePlugin_WantsMidiInput
            if (port == index)
            {
                midiInPort = (LV2_Event_Buffer*)dataLocation;
                return;
            }
            ++index;
#endif

#if JucePlugin_ProducesMidiOutput
            if (port == index)
            {
                midiOutPort = (LV2_Event_Buffer*)dataLocation;
                return;
            }
            ++index;
#endif

            for (int i=0; i < numInChans; ++i, ++index)
            {
                if (port == index)
                {
                    audioInPorts[i] = (float*)dataLocation;
                    return;
                }
            }

            for (int i=0; i < numOutChans; ++i, ++index)
            {
                if (port == index)
                {
                    audioOutPorts[i] = (float*)dataLocation;
                    return;
                }
            }

            for (int i=0; i < filter->getNumParameters(); ++i, ++index)
            {
                if (port == index)
                {
                    parameterInPorts.set(i, (float*)dataLocation);
                    return;
                }
            }
        }
    }

    void doActivate()
    {
        if (filter != nullptr)
        {
            isProcessing = true;
            channels.calloc (numInChans + numOutChans);

            jassert (sampleRate > 0);
            if (sampleRate <= 0.0)
                sampleRate = 44100.0;

            jassert (bufferSize > 0);

            firstProcessCallback = true;

            filter->setNonRealtime (false);
            filter->setPlayConfigDetails (numInChans, numOutChans, sampleRate, bufferSize);

            deleteTempChannels();

            filter->prepareToPlay (sampleRate, bufferSize);

            midiEvents.ensureSize (2048);
            midiEvents.clear();
        }
    }

    void doDeactivate()
    {
        if (filter != nullptr)
        {
            filter->releaseResources();

            isProcessing = false;
            channels.free();

            deleteTempChannels();
        }
    }

    void doRun(uint32 numSamples)
    {
        if (firstProcessCallback)
        {
            firstProcessCallback = false;

            // if this fails, the host hasn't called resume() before processing
            jassert (isProcessing);

            // (tragically, some hosts actually need this, although it's stupid to have
            //  to do it here..)
            if (! isProcessing)
                doActivate();

            filter->setNonRealtime (false);

           #if JUCE_WINDOWS
            if (GetThreadPriority (GetCurrentThread()) <= THREAD_PRIORITY_NORMAL
                  && GetThreadPriority (GetCurrentThread()) >= THREAD_PRIORITY_LOWEST)
                filter->setNonRealtime (true);
           #endif
        }

        // Check if buffer size changed
        if (bufferSize != numSamples)
        {
            bufferSize = numSamples;
            filter->setPlayConfigDetails(numInChans, numOutChans, sampleRate, bufferSize);
            filter->prepareToPlay(sampleRate, bufferSize);
        }

#if JucePlugin_WantsLV2TimePos
        if (timePosPort != nullptr)
        {
            LV2_Event* event = nullptr;
            LV2_Event_Iterator iter;
            lv2_event_begin(&iter, timePosPort);
            uint8* data = nullptr;

            while (lv2_event_is_valid(&iter))
            {
                event = lv2_event_get(&iter, &data);
                lv2_event_increment(&iter);
            }

            if (event != nullptr && event->size == sizeof(LV2_Time_Position))
              memcpy(&timePos, data, sizeof(LV2_Time_Position));
            else
              memset(&timePos, 0, sizeof(LV2_Time_Position));
        }
        else
          memset(&timePos, 0, sizeof(LV2_Time_Position));
#endif

        // Check for updated parameters
        float cur_value;
        for (int i = 0; i < parameterInPorts.size(); i++)
        {
            if (parameterInPorts[i] != nullptr)
            {
                cur_value = *(float*)parameterInPorts[i];
                if (parameterInPortsValues[i] != cur_value)
                {
                    filter->setParameter(i, cur_value);
                    parameterInPortsValues.setUnchecked(i, cur_value);
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
                    zeromem (audioOutPorts[i], sizeof (float) * numSamples);
            }
            else
            {
                int i;
                for (i = 0; i < numOut; ++i)
                {
                    float* chan = tempChannels.getUnchecked(i);

                    if (chan == 0)
                    {
                        chan = audioOutPorts[i];

                        // if some output channels are disabled, some hosts supply the same buffer
                        // for multiple channels - this buggers up our method of copying the
                        // inputs over the outputs, so we need to create unique temp buffers in this case..
                        for (int j = i; --j >= 0;)
                        {
                            if (audioOutPorts[j] == chan)
                            {
                                chan = new float [bufferSize * 2];
                                tempChannels.set (i, chan);
                                break;
                            }
                        }
                    }

                    if (i < numIn && chan != audioInPorts[i])
                        memcpy (chan, audioInPorts[i], sizeof (float) * numSamples);

                    channels[i] = chan;
                }

                // LV2 MIDI Input
                if (midiInPort != nullptr)
                {
                    midiEvents.clear();

                    LV2_Event_Iterator iter;
                    lv2_event_begin(&iter, midiInPort);
                    uint32 sampleFrame = 0;
                    uint8* data = 0;

                    while (sampleFrame < numSamples && lv2_event_is_valid(&iter))
                    {
                        const LV2_Event* event = lv2_event_get(&iter, &data);
                        sampleFrame = event->frames;
                        midiEvents.addEvent(data, event->size, event->frames);
                        lv2_event_increment(&iter);
                    }
                }

                for (; i < numIn; ++i)
                    channels[i] = audioInPorts[i];

                AudioSampleBuffer chans (channels, jmax (numIn, numOut), numSamples);

                filter->processBlock (chans, midiEvents);
            }
        }

        if (! midiEvents.isEmpty() && midiOutPort != nullptr)
        {
#if JucePlugin_ProducesMidiOutput
            const int numEvents = midiEvents.getNumEvents();

            LV2_Event_Iterator iter;
            lv2_event_buffer_reset(midiOutPort, LV2_EVENT_AUDIO_STAMP, (uint8*)(midiOutPort + 1));
            lv2_event_begin(&iter, midiOutPort);

            const JUCE_NAMESPACE::uint8* midiEventData;
            int midiEventSize, midiEventPosition;
            MidiBuffer::Iterator i (midiEvents);

            while (i.getNextEvent (midiEventData, midiEventSize, midiEventPosition))
            {
                jassert (midiEventPosition >= 0 && midiEventPosition < sample_count);

                lv2_event_write(&iter, midiEventPosition, 0, midiURIId, midiEventSize, midiEventData);
            }
#endif
            midiEvents.clear();
        }
    }

    void doCleanup()
    {
        if (lv2Editor)
            lv2Editor->doCleanup();
    }

    //==============================================================================
    // JUCE Stuff

    bool getCurrentPosition (AudioPlayHead::CurrentPositionInfo& info)
    {
#if JucePlugin_WantsLV2TimePos
        if (timePosPort == nullptr || sampleRate <= 0)
            return false;

        if (timePos.flags & LV2_TIME_HAS_BBT)
        {
            info.bpm = timePos.beats_per_minute;
            info.timeSigNumerator   = timePos.beats_per_bar;
            info.timeSigDenominator = timePos.beat_type;
            info.ppqPosition = (timePos.frame / sampleRate) * timePos.beats_per_minute / 60.0;
            info.ppqPositionOfLastBarStart = 0;
        }
        else
        {
            info.bpm = 130.0;
            info.timeSigNumerator = 4;
            info.timeSigDenominator = 4;
            info.ppqPosition = 0;
            info.ppqPositionOfLastBarStart = 0;
        }

        info.timeInSeconds  = timePos.frame / sampleRate;
        info.editOriginTime = 0;
        info.frameRate = AudioPlayHead::fpsUnknown;
        info.isPlaying   = (timePos.state == LV2_TIME_ROLLING);
        info.isRecording = false;

        return true;
#else
        return false;
#endif
    }

    AudioProcessor* getFilter() { return filter; }

    //==============================================================================
    void getChunk (MemoryBlock& data)
    {
        if (filter == nullptr)
            return;
        data.setSize (0);
        if (filter)
            filter->getStateInformation(data);
    }

    void setChunk (const MemoryBlock& data)
    {
        if (filter == nullptr)
            return;
        filter->setStateInformation(data.getData(), data.getSize());
    }

    LV2_URI_Map_Feature* getURIMap()
    {
        return uriMap;
    }

    bool hasLV2Editor()
    {
        return lv2Editor != nullptr;
    }

    JuceLV2Editor* getLV2Editor(LV2UI_Write_Function writeFunction, LV2UI_Controller controller, LV2UI_Widget* widget)
    {
        if (lv2Editor)
        {
            lv2Editor->resetExternalUIIfNeeded(writeFunction, controller, widget);
        }
        return lv2Editor;
    }

    void createLV2Editor(const LV2UI_Descriptor* uiDescriptor, LV2UI_Write_Function writeFunction, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features, Lv2UiType uiType)
    {
        lv2Editor = new JuceLV2Editor(filter, uiDescriptor, writeFunction, controller, widget, features, uiType);
    }

    //==============================================================================
private:
    AudioProcessor* filter;
    JuceLV2Editor* lv2Editor;
    MidiBuffer midiEvents;
    int numInChans, numOutChans;
    bool isProcessing, firstProcessCallback;
    HeapBlock<float*> channels;
    Array<float*> tempChannels;  // see note in doRun()

    const LV2_Descriptor* descriptor;

    double sampleRate;
    uint32 bufferSize;
    LV2_Time_Position timePos;
    LV2_URI_Map_Feature* uriMap;
    uint16 midiURIId;
    uint32 portCount;

    LV2_Event_Buffer* timePosPort;
    LV2_Event_Buffer* midiInPort;
    LV2_Event_Buffer* midiOutPort;
    float* audioInPorts[JucePlugin_MaxNumInputChannels];
    float* audioOutPorts[JucePlugin_MaxNumOutputChannels];
    Array<float*> parameterInPorts;
    Array<float> parameterInPortsValues;

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
// LV2 descriptor functions
LV2_Handle juceLV2Instantiate(const LV2_Descriptor* descriptor, double sampleRate, const char* bundlePath, const LV2_Feature* const* features)
{
    JuceLV2Wrapper* wrapper = new JuceLV2Wrapper(descriptor, sampleRate, features);
    return wrapper;
}

void juceLV2ConnectPort(LV2_Handle instance, uint32 port, void* dataLocation)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    wrapper->doConnectPort(port, dataLocation);
}

void juceLV2Activate(LV2_Handle instance)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    wrapper->doActivate();
}

void juceLV2Run(LV2_Handle instance, uint32 sampleCount)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    wrapper->doRun(sampleCount);
}

void juceLV2Deactivate(LV2_Handle instance)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    wrapper->doDeactivate();
}

void juceLV2Cleanup(LV2_Handle instance)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    wrapper->doCleanup();
    delete wrapper;
}

//==============================================================================
void juceLV2Save(LV2_Handle instance, LV2_State_Store_Function store, LV2_State_Handle handle, uint32_t flags, const LV2_Feature* const* features)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    jassert(wrapper);

    const String juceChunkURI = getURI() + "#chunk";
    MemoryBlock chunkMemory;
    wrapper->getChunk(chunkMemory);

    LV2_URI_Map_Feature* uriMap = wrapper->getURIMap();
    store(handle,
          uriMap->uri_to_id(uriMap->callback_data, 0, juceChunkURI.toUTF8().getAddress()),
          chunkMemory.getData(),
          chunkMemory.getSize(),
          uriMap->uri_to_id(uriMap->callback_data, 0, "juce_binary_chunk"),
          LV2_STATE_IS_POD | LV2_STATE_IS_PORTABLE);
}

void juceLV2Restore(LV2_Handle instance, LV2_State_Retrieve_Function retrieve, LV2_State_Handle handle, uint32_t flags, const LV2_Feature* const* features)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    jassert(wrapper);

    const String juceChunkURI = getURI() + "#chunk";
    LV2_URI_Map_Feature* uriMap = wrapper->getURIMap();

    size_t size;
    uint32 type;
    const void *data = retrieve(handle,
                                uriMap->uri_to_id(uriMap->callback_data, 0, juceChunkURI.toUTF8().getAddress()),
                                &size, &type, &flags);

    MemoryBlock chunkMemory(data, size);
    wrapper->setChunk(chunkMemory);
}

const void* juceLV2ExtensionData(const char* uri)
{
    static const LV2_State_Interface state = { juceLV2Save, juceLV2Restore };
    if (strcmp(uri, LV2_STATE_INTERFACE_URI) == 0)
        return &state;
    return nullptr;
}

//==============================================================================
LV2UI_Handle juceLV2UIInstantiate(const LV2UI_Descriptor* uiDescriptor, LV2UI_Write_Function writeFunction, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features, Lv2UiType uiType)
{
    const MessageManagerLock mmLock;

    for (uint16 i = 0; features[i]; i++)
    {
        if (strcmp(features[i]->URI, LV2_INSTANCE_ACCESS_URI) == 0 && features[i]->data)
        {
            JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)features[i]->data;

            if (!wrapper->hasLV2Editor())
            {
                wrapper->createLV2Editor(uiDescriptor, writeFunction, controller, widget, features, uiType);
            }

            return wrapper->getLV2Editor(writeFunction, controller, widget);
        }
    }

    std::cerr << "Host does not support instance-access, cannot use UI" << std::endl;
    return nullptr;
}

LV2UI_Handle juceLV2UIInstantiateX11(const LV2UI_Descriptor* descriptor, const char* plugin_uri, const char* bundle_path, LV2UI_Write_Function writeFunction, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features)
{
    return juceLV2UIInstantiate(descriptor, writeFunction, controller, widget, features, LV2_UI_X11);
}

LV2UI_Handle juceLV2UIInstantiateExternal(const LV2UI_Descriptor* descriptor, const char* plugin_uri, const char* bundle_path, LV2UI_Write_Function writeFunction, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features)
{
    return juceLV2UIInstantiate(descriptor, writeFunction, controller, widget, features, LV2_UI_EXTERNAL);
}

void juceLV2UIPortEvent(LV2UI_Handle instance, uint32 portIndex, uint32 bufferSize, uint32 format, const void* buffer)
{
    const MessageManagerLock mmLock;
    JuceLV2Editor* editor = (JuceLV2Editor*)instance;

    if (editor && bufferSize == sizeof(float) && format == 0)
    {
        float value = *(float*)buffer;
        editor->doPortEvent(portIndex, value);
    }
}

void juceLV2UICleanup(LV2UI_Handle instance)
{
     // UI is kept open and only closes on plugin cleanup
}

//==============================================================================
// static LV2 Descriptor objects

class NewLv2Plugin : public LV2_Descriptor
{
public:
    NewLv2Plugin()
    {
        URI            = strdup((const char*) getURI().toUTF8());
        instantiate    = juceLV2Instantiate;
        connect_port   = juceLV2ConnectPort;
        activate       = juceLV2Activate;
        run            = juceLV2Run;
        deactivate     = juceLV2Deactivate;
        cleanup        = juceLV2Cleanup;
        extension_data = juceLV2ExtensionData;
    }
};

class NewLv2UI_X11 : public LV2UI_Descriptor
{
public:
    NewLv2UI_X11()
    {
        URI            = strdup((const char*) getX11UIURI().toUTF8());
        instantiate    = juceLV2UIInstantiateX11;
        cleanup        = juceLV2UICleanup;
        port_event     = juceLV2UIPortEvent;
        extension_data = juceLV2ExtensionData;
    }
};

class NewLv2UI_external : public LV2UI_Descriptor
{
public:
    NewLv2UI_external()
    {
        URI            = strdup((const char*) getExternalUIURI(true).toUTF8());
        instantiate    = juceLV2UIInstantiateExternal;
        cleanup        = juceLV2UICleanup;
        port_event     = juceLV2UIPortEvent;
        extension_data = juceLV2ExtensionData;
    }
};

class NewLv2UI_externalOld : public LV2UI_Descriptor
{
public:
    NewLv2UI_externalOld()
    {
        URI            = strdup((const char*) getExternalUIURI(false).toUTF8());
        instantiate    = juceLV2UIInstantiateExternal;
        cleanup        = juceLV2UICleanup;
        port_event     = juceLV2UIPortEvent;
        extension_data = juceLV2ExtensionData;
    }
};

static NewLv2Plugin  NewLv2Plugin_Obj;
static NewLv2UI_X11  NewLv2UI_X11_Obj;
static NewLv2UI_external    NewLv2UI_external_Obj;
static NewLv2UI_externalOld NewLv2UI_externalOld_Obj;

LV2UI_Descriptor* getNewLv2UI(uint32 index)
{
    switch (index)
    {
      case 0:
        return &NewLv2UI_X11_Obj;
      case 1:
        return &NewLv2UI_external_Obj;
      case 2:
        return &NewLv2UI_externalOld_Obj;
      default:
        return nullptr;
    }
}

//==============================================================================
// Mac startup code..
#if JUCE_MAC

extern "C" __attribute__ ((visibility("default"))) void juce_lv2_ttl_generator()
{
    createTtlFiles();
}

extern "C" __attribute__ ((visibility("default"))) const LV2_Descriptor* lv2_descriptor(uint32 index)
{
    initialiseMac();
    return (index == 0) ? &NewLv2Plugin_Obj : nullptr;
}

extern "C" __attribute__ ((visibility("default"))) const LV2UI_Descriptor* lv2ui_descriptor(uint32 index)
{
    return (index <= 2) ? getNewLv2UI(index) : nullptr;
}

//==============================================================================
// Linux startup code..
#elif JUCE_LINUX

extern "C" __attribute__ ((visibility("default"))) void juce_lv2_ttl_generator()
{
    createTtlFiles();
}

extern "C" __attribute__ ((visibility("default"))) const LV2_Descriptor* lv2_descriptor(uint32 index)
{
    SharedMessageThread::getInstance();
    return (index == 0) ? &NewLv2Plugin_Obj : nullptr;
}

extern "C" __attribute__ ((visibility("default"))) const LV2UI_Descriptor* lv2ui_descriptor(uint32 index)
{
    return (index <= 2) ? getNewLv2UI(index) : nullptr;
}

// don't put initialiseJuce_GUI or shutdownJuce_GUI in these... it will crash!
__attribute__((constructor)) void myPluginInit() {}
__attribute__((destructor))  void myPluginFini() {}

//==============================================================================
// Win32 startup code..
#else

extern "C" __declspec (dllexport) void juce_lv2_ttl_generator()
{
    createTtlFiles();
}

extern "C" __declspec (dllexport) const LV2_Descriptor* lv2_descriptor(uint32 index)
{
    return (index == 0) ? &NewLv2Plugin_Obj : nullptr;
}

extern "C" __declspec (dllexport) const LV2UI_Descriptor* lv2ui_descriptor(uint32 index)
{
    return (index <= 2) ? getNewLv2UI(index) : nullptr;
}

#endif

#endif
