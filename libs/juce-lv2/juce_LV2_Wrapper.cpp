/*
  ==============================================================================

   Juce LV2 Wrapper, based on VST Wrapper code

  ==============================================================================
*/

// Your project must contain an AppConfig.h file with your project-specific settings in it,
// and your header search path must make it accessible to the module's files.
#include "AppConfig.h"

#include "utility/juce_CheckSettingMacros.h"

#if JucePlugin_Build_LV2

//==============================================================================
/** Enable LV2 development features
* This macro enables currently development/unstable features of LV2, use with care.
* Features are:
* - atom based MIDI and Time-Pos
* - X11 UI
*/
#define JUCE_LV2_ENABLE_DEV_FEATURES 0

/*
 * Available macros:
 * - JucePlugin_WantsLV2Presets
 * - JucePlugin_WantsLV2State
 * - JucePlugin_WantsLV2TimePos
 * - JucePlugin_WantsLV2InstanceAccess (UI)
 */

#if (JUCE_LINUX && JUCE_LV2_ENABLE_DEV_FEATURES)
 #define JucePlugin_WantsLV2X11UI 1
#endif

#ifdef _WIN32
 #include <windows.h>
#elif defined (LINUX)
 #include <X11/Xlib.h>
 #include <X11/Xutil.h>
 #include <X11/Xatom.h>
 #undef KeyPress
#else
 #include <Carbon/Carbon.h>
#endif

#include <fstream>
#include <iostream>

// LV2 includes
#include "includes/lv2.h"
#include "includes/instance-access.h"
#include "includes/state.h"
#include "includes/urid.h"
#include "includes/ui.h"
#include "includes/lv2_external_ui.h"

#if JUCE_LV2_ENABLE_DEV_FEATURES
 #include "includes/atom.h"
 #include "includes/time.h"
 #include "includes/ui-resize.h"
#else
 #include "lv2/event.h"
 #include "lv2/event-helpers.h"
#endif

#include "modules/juce_audio_plugin_client/utility/juce_IncludeModuleHeaders.h"

namespace juce
{
 #if JUCE_MAC
  extern void initialiseMac();
 #endif

 #if JUCE_LINUX
  extern Display* display;
 #endif
}

#define JUCE_LV2_STATE_STRING_URI "urn:juce:stateString"

//==============================================================================
/** Somewhere in the codebase of your plugin, you need to implement this function
    and make it create an instance of the filter subclass that you're building.
*/
extern AudioProcessor* JUCE_CALLTYPE createPluginFilter();

//==============================================================================
// Various helper functions for creating the ttl files

#ifdef JUCE_WINDOWS
 #define PLUGIN_EXT ".dll"
#else
 #define PLUGIN_EXT ".so"
#endif

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

/** Converts a parameter name to an LV2 compatible symbol. */
String nameToSymbol(const String& name, const uint32 portIndex)
{
    String symbol, trimmedName = name.trimStart().trimEnd().toLowerCase();

    if (trimmedName.isEmpty())
    {
        symbol += "lv2_port_";
        symbol += String(portIndex+1);
    }
    else
    {
        for (int i=0; i < trimmedName.length(); i++)
        {
            const juce_wchar c = trimmedName[i];
            if (std::isalpha(c) || std::isdigit(c))
                symbol += c;
            else
                symbol += "_";
        }
    }
    return symbol;
}

/** Create the manifest.ttl contents */
String makeManifestTtl(AudioProcessor* const filter, const String& binary)
{
    String manifest;
    manifest += "@prefix lv2:  <http://lv2plug.in/ns/lv2core#> .\n";
#ifdef JucePlugin_WantsLV2Presets
    manifest += "@prefix pset: <http://lv2plug.in/ns/ext/presets#> .\n";
#endif
    manifest += "@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .\n";
    if (filter->hasEditor())
        manifest += "@prefix ui:   <http://lv2plug.in/ns/extensions/ui#> .\n";
    manifest += "\n";

    manifest += "<" JucePlugin_LV2URI ">\n";
    manifest += "    a lv2:Plugin ;\n";
    manifest += "    lv2:binary <" + binary + PLUGIN_EXT "> ;\n";
    manifest += "    rdfs:seeAlso <" + binary + ".ttl> .\n";
    manifest += "\n";

    if (filter->hasEditor())
    {
        manifest += "<" JucePlugin_LV2URI "#ExternalUI>\n";
        manifest += "    a <http://nedko.arnaudov.name/lv2/external_ui/> ;\n";
        manifest += "    ui:binary <" + binary + PLUGIN_EXT "> ";
#ifdef JucePlugin_WantsLV2InstanceAccess
        manifest += ";\n";
        manifest += "    ui:requiredFeature <http://lv2plug.in/ns/ext/instance-access> .\n";
#else
        manifest += ".\n";
#endif
        manifest += "\n";

        manifest += "<" JucePlugin_LV2URI "#ExternalOldUI>\n";
        manifest += "    a ui:external ;\n";
        manifest += "    ui:binary <" + binary + PLUGIN_EXT "> ";
#ifdef JucePlugin_WantsLV2InstanceAccess
        manifest += ";\n";
        manifest += "    ui:requiredFeature <http://lv2plug.in/ns/ext/instance-access> .\n";
#else
        manifest += ".\n";
#endif
        manifest += "\n";

#if JucePlugin_WantsLV2X11UI
        manifest += "<" JucePlugin_LV2URI "#X11UI>\n";
        manifest += "    a ui:X11UI ;\n";
        manifest += "    ui:binary <" + binary + PLUGIN_EXT "> ;\n";
 #ifdef JucePlugin_WantsLV2InstanceAccess
        manifest += "    ui:requiredFeature <http://lv2plug.in/ns/ext/instance-access> ;\n";
 #endif
        manifest += "    ui:optionalFeature ui:noUserResize .\n";
        manifest += "\n";
#endif
    }

#ifdef JucePlugin_WantsLV2Presets
    for (int i = 0; i < filter->getNumPrograms(); i++)
    {
        manifest += "<" JucePlugin_LV2URI "#preset" + String(i+1) + ">\n";
        manifest += "    a pset:Preset ;\n";
        manifest += "    lv2:appliesTo <" JucePlugin_LV2URI "> ;\n";
        manifest += "    rdfs:seeAlso <presets.ttl> .\n";
        manifest += "\n";
    }
#endif

    return manifest;
}

/** Create the plugin.ttl contents */
String makePluginTtl(AudioProcessor* const filter, const String& binary)
{
    String plugin;
#if (JUCE_LV2_ENABLE_DEV_FEATURES && (JucePlugin_WantsMidiInput || JucePlugin_ProducesMidiOutput || JucePlugin_WantsLV2TimePos))
    plugin += "@prefix atom: <http://lv2plug.in/ns/ext/atom#> .\n";
#endif
    plugin += "@prefix doap: <http://usefulinc.com/ns/doap#> .\n";
#if ((! JUCE_LV2_ENABLE_DEV_FEATURES) && (JucePlugin_WantsMidiInput || JucePlugin_ProducesMidiOutput))
    plugin += "@prefix ev:   <http://lv2plug.in/ns/ext/event#> .\n";
#endif
    plugin += "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n";
    plugin += "@prefix lv2:  <http://lv2plug.in/ns/lv2core#> .\n";
#if JucePlugin_WantsLV2TimePos
    plugin += "@prefix ue:   <http://lv2plug.in/ns/extensions/units#> .\n";
#endif
    if (filter->hasEditor())
        plugin += "@prefix ui:   <http://lv2plug.in/ns/extensions/ui#> .\n";
    plugin += "\n";

    plugin += "<" JucePlugin_LV2URI ">\n";
    plugin += "    a " + getPluginType() + " ;\n";
#if JucePlugin_IsSynth
    plugin += "    lv2:requiredFeature <http://lv2plug.in/ns/ext/urid#map> ;\n";
#elif (JucePlugin_WantsMidiInput || JucePlugin_ProducesMidiOutput || JucePlugin_WantsLV2State || JucePlugin_WantsLV2TimePos)
    plugin += "    lv2:optionalFeature <http://lv2plug.in/ns/ext/urid#map> ;\n";
#endif
#if JucePlugin_WantsLV2State
    plugin += "    lv2:extensionData <http://lv2plug.in/ns/ext/state#Interface> ;\n";
#endif
    plugin += "\n";

    if (filter->hasEditor())
    {
        plugin += "    ui:ui <" JucePlugin_LV2URI "#ExternalUI> ,\n";
        plugin += "          <" JucePlugin_LV2URI "#ExternalOldUI> ";
#if JucePlugin_WantsLV2X11UI
        plugin += ",\n";
        plugin += "          <" JucePlugin_LV2URI "#X11UI> ;\n";
#else
        plugin += ";\n";
#endif
        plugin += "\n";
    }

    uint32 portIndex = 0;

#if (JucePlugin_WantsMidiInput || (JUCE_LV2_ENABLE_DEV_FEATURES && JucePlugin_WantsLV2TimePos))
    plugin += "    lv2:port [\n";
 #if JUCE_LV2_ENABLE_DEV_FEATURES
    plugin += "      a lv2:InputPort, atom:MessagePort ;\n";
    plugin += "      atom:bufferType atom:Sequence ;\n";
  #if JucePlugin_WantsLV2TimePos
    plugin += "      atom:supports <http://lv2plug.in/ns/ext/midi#MidiEvent> ,\n";
    plugin += "                    <http://lv2plug.in/ns/ext/time#Position> ;\n";
  #else
    plugin += "      atom:supports <http://lv2plug.in/ns/ext/midi#MidiEvent> ;\n";
  #endif
 #else
    plugin += "      a lv2:InputPort, ev:EventPort ;\n";
    plugin += "      ev:supportsEvent <http://lv2plug.in/ns/ext/midi#MidiEvent> ;\n";
 #endif
    plugin += "      lv2:index " + String(portIndex++) + " ;\n";
    plugin += "      lv2:symbol \"lv2_events_in\" ;\n";
    plugin += "      lv2:name \"Events Input\" ;\n";
 #if ! JucePlugin_IsSynth
    plugin += "      lv2:portProperty lv2:connectionOptional ;\n";
 #endif
    plugin += "    ] ;\n\n";
#endif

#if JucePlugin_ProducesMidiOutput
    plugin += "    lv2:port [\n";
 #if JUCE_LV2_ENABLE_DEV_FEATURES
    plugin += "      a lv2:OutputPort, atom:MessagePort ;\n";
    plugin += "      atom:bufferType atom:Sequence ;\n";
    plugin += "      atom:supports <http://lv2plug.in/ns/ext/midi#MidiEvent> ;\n";
 #else
    plugin += "      a lv2:OutputPort, ev:EventPort ;\n";
    plugin += "      ev:supportsEvent <http://lv2plug.in/ns/ext/midi#MidiEvent> ;\n";
 #endif
    plugin += "      lv2:index " + String(portIndex++) + " ;\n";
    plugin += "      lv2:symbol \"lv2_events_out\" ;\n";
    plugin += "      lv2:name \"Events Output\" ;\n";
    plugin += "      lv2:portProperty lv2:connectionOptional ;\n";
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
        plugin += "      lv2:symbol \"lv2_audio_in_" + String(i+1) + "\" ;\n";
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
        plugin += "      lv2:symbol \"lv2_audio_out_" + String(i+1) + "\" ;\n";
        plugin += "      lv2:name \"Audio Output " + String(i+1) + "\" ;\n";

        if (i+1 == JucePlugin_MaxNumOutputChannels)
            plugin += "    ] ;\n\n";
        else
            plugin += "    ],\n";
    }

#if JucePlugin_WantsLV2TimePos
    plugin += "    lv2:port [\n";
    plugin += "      a lv2:InputPort, lv2:ControlPort ;\n";
    plugin += "      lv2:index " + String(portIndex++) + " ;\n";
    plugin += "      lv2:symbol \"lv2_time_bpm\" ;\n";
    plugin += "      lv2:name \"LV2 BPM\" ;\n";
    plugin += "      lv2:default 120.0 ;\n";
    plugin += "      lv2:minimum 10.0 ;\n";
    plugin += "      lv2:maximum 400.0 ;\n";
    plugin += "      lv2:portProperty <http://lv2plug.in/ns/ext/port-props#reportsBpm> ;\n";
    plugin += "      ue:unit ue:bpm ;\n";
    plugin += "    ] ;\n\n";
#endif

    for (int i=0; i < filter->getNumParameters(); i++)
    {
        if (i == 0)
            plugin += "    lv2:port [\n";
        else
            plugin += "    [\n";

        plugin += "      a lv2:InputPort, lv2:ControlPort ;\n";
        plugin += "      lv2:index " + String(portIndex++) + " ;\n";
        plugin += "      lv2:symbol \"" + nameToSymbol(filter->getParameterName(i), i) + "\" ;\n";
        if (filter->getParameterName(i).isNotEmpty())
          plugin += "      lv2:name \"" + filter->getParameterName(i) + "\" ;\n";
        else
          plugin += "      lv2:name \"Port " + String(i+1) + "\" ;\n";
        plugin += "      lv2:default " + String(filter->getParameter(i)) + " ;\n";
        plugin += "      lv2:minimum 0.0 ;\n";
        plugin += "      lv2:maximum 1.0 ;\n";

        if (i+1 == filter->getNumParameters())
            plugin += "    ] ;\n\n";
        else
            plugin += "    ],\n";
    }

    plugin += "    lv2:port [\n";
    plugin += "      a lv2:OutputPort, lv2:ControlPort ;\n";
    plugin += "      lv2:index " + String(portIndex++) + " ;\n";
    plugin += "      lv2:symbol \"lv2_latency\" ;\n";
    plugin += "      lv2:name \"Latency\" ;\n";
    plugin += "      lv2:portProperty lv2:reportsLatency ;\n";
    plugin += "    ] ;\n\n";

    plugin += "    doap:name \"" JucePlugin_Name "\" ;\n";
    plugin += "    doap:maintainer [ foaf:name \"" JucePlugin_Manufacturer "\" ] .\n";

    return plugin;
}

/** Create the presets.ttl contents */
String makePresetsTtl(AudioProcessor* const filter)
{
    uint32 portIndex = 0;

    String presets;
    presets += "@prefix lv2:   <http://lv2plug.in/ns/lv2core#> .\n";
    presets += "@prefix pset:  <http://lv2plug.in/ns/ext/presets#> .\n";
    presets += "@prefix rdfs:  <http://www.w3.org/2000/01/rdf-schema#> .\n";
#if JucePlugin_WantsLV2State
    presets += "@prefix state: <http://lv2plug.in/ns/ext/state#> .\n";
#endif
    presets += "\n";

    for (int i = 0; i < filter->getNumPrograms(); i++)
    {
        std::cout << "\nSaving preset #" << i+1 << "...";
        std::cout.flush();

        filter->setCurrentProgram(i);
        presets += "<" JucePlugin_LV2URI "#preset" + String(i+1) + "> a pset:Preset ;\n";
        presets += "    rdfs:label \"" + filter->getProgramName(i) + "\" ;\n";

#if JucePlugin_WantsLV2State
        presets += "    state:state [\n";
        presets += "        <" JUCE_LV2_STATE_STRING_URI ">\n";
        presets += "\"\"\"\n";
        presets += filter->getStateInformationString().replace("\r\n","\n");
        presets += "\"\"\"\n";
        if (filter->getNumParameters() > 0)
          presets += "    ] ;\n\n";
        else
          presets += "    ] .\n\n";
#endif

        for (int j=0; j < filter->getNumParameters(); j++)
        {
            presets += "    lv2:port [\n";

            presets += "        lv2:symbol \"" + nameToSymbol(filter->getParameterName(j), j) + "\" ;\n";
            presets += "        pset:value " + String(filter->getParameter(j)) + " ;\n";

            if (j+1 == filter->getNumParameters())
                presets += "    ] ";
            else
                presets += "    ] ;\n";
        }
        presets += ".\n\n";
    }

    return presets;
}

/** Creates manifest.ttl, plugin.ttl and presets.ttl files */
void createTtlFiles()
{
    ScopedJuceInitialiser_GUI juceInitialiser;
    ScopedPointer<AudioProcessor> filter (createPluginFilter());

    String binary = getBinaryName();
    String binaryTTL = binary + ".ttl";

     std::cout << "Writing manifest.ttl..."; std::cout.flush();
     std::fstream manifest("manifest.ttl", std::ios::out);
     manifest << makeManifestTtl(filter, binary) << std::endl;
     manifest.close();
     std::cout << " done!" << std::endl;

    std::cout << "Writing " << binaryTTL << "..."; std::cout.flush();
    std::fstream plugin(binaryTTL.toUTF8(), std::ios::out);
    plugin << makePluginTtl(filter, binary) << std::endl;
    plugin.close();
    std::cout << " done!" << std::endl;

#ifdef JucePlugin_WantsLV2Presets
    std::cout << "Writing presets.ttl..."; std::cout.flush();
    std::fstream presets("presets.ttl", std::ios::out);
    presets << makePresetsTtl(filter) << std::endl;
    presets.close();
    std::cout << " done!" << std::endl;
#endif
}

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
static Array<void*> activeUIs;

//==============================================================================
/**
    Lightweight DocumentWindow subclass for external ui
*/
class JuceLV2ExternalUIWindow : public DocumentWindow
{
public:
    /** Creates a Document Window wrapper */
    JuceLV2ExternalUIWindow (const String& title) :
            DocumentWindow (title, Colours::white, DocumentWindow::minimiseButton | DocumentWindow::closeButton, true),
            closed (false),
            lastPos (100, 100)
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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLV2ExternalUIWindow);
};

//==============================================================================
/**
    Juce LV2 External UI handle
*/
class JuceLV2ExternalUIWrapper : public lv2_external_ui
{
public:
    JuceLV2ExternalUIWrapper (AudioProcessorEditor* const editor_, const String& title) :
            editor(editor_),
            window(nullptr)
    {
        const MessageManagerLock mmLock;
        window = new JuceLV2ExternalUIWindow (title);
        window->setOpaque (true);
        //window->setAlwaysOnTop(true); // FIXME - does not work properly on Linux
        window->setUsingNativeTitleBar (true);
        window->setContentNonOwned (editor, true);

        // external UI calls
        run  = doRun;
        show = doShow;
        hide = doHide;

    }

    ~JuceLV2ExternalUIWrapper()
    {
        if (window)
            delete window;
    }

    bool isClosed()
    {
        if (window)
            return window->isClosed();
        else
            return true;
    }

    void resetWindow()
    {
        if (window)
            window->reset();
    }

    //==============================================================================
    static void doRun(lv2_external_ui* _this_)
    {
        const MessageManagerLock mmLock;
        JuceLV2ExternalUIWrapper* externalUI = (JuceLV2ExternalUIWrapper*)_this_;
        if (externalUI->window && ! externalUI->window->isClosed())
            externalUI->window->repaint();
    }

    static void doShow(lv2_external_ui* _this_)
    {
        const MessageManagerLock mmLock;
        JuceLV2ExternalUIWrapper* externalUI = (JuceLV2ExternalUIWrapper*)_this_;
        if (externalUI->window && ! externalUI->window->isClosed())
        {
            if (! externalUI->window->isOnDesktop())
            {
                Point<int> lastPos = externalUI->window->getLastPos();
                externalUI->window->setTopLeftPosition(lastPos.getX(), lastPos.getY());
                externalUI->window->addToDesktop();
            }
            externalUI->window->setVisible(true);
        }
    }

    static void doHide(lv2_external_ui* _this_)
    {
        const MessageManagerLock mmLock;
        JuceLV2ExternalUIWrapper* externalUI = (JuceLV2ExternalUIWrapper*)_this_;
        if (externalUI->window && ! externalUI->window->isClosed())
            externalUI->window->setVisible(false);
    }

private:
    AudioProcessorEditor* editor;
    JuceLV2ExternalUIWindow* window;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLV2ExternalUIWrapper);
};

//==============================================================================
/**
    Juce LV2 X11 UI container, listens for resize events and passes them to ui-resize
*/
#if JucePlugin_WantsLV2X11UI
class JuceLV2X11Editor : public Component
{
public:
    JuceLV2X11Editor (AudioProcessorEditor* const editor, LV2_UI_Resize_Feature* uiResizeFeature_)
        : uiResizeFeature(uiResizeFeature_)
    {
        setOpaque (true);
        editor->setOpaque (true);
        setBounds (editor->getBounds());

        editor->setTopLeftPosition (0, 0);
        addAndMakeVisible (editor);
    }

    JuceLV2X11Editor()
    {
    }

    void childBoundsChanged (Component* child)
    {
        const int cw = child->getWidth();
        const int ch = child->getHeight();

        XResizeWindow (display, (Window) getWindowHandle(), cw, ch);

        if (uiResizeFeature)
            uiResizeFeature->ui_resize (uiResizeFeature->data, cw, ch);
    }

    void reset (LV2_UI_Resize_Feature* uiResizeFeature_)
    {
        uiResizeFeature = uiResizeFeature_;

        if (uiResizeFeature)
            uiResizeFeature->ui_resize (uiResizeFeature->data, getWidth(), getHeight());
    }

private:
    //==============================================================================
    LV2_UI_Resize_Feature* uiResizeFeature;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLV2X11Editor);
};
#endif

//==============================================================================
/**
    Juce LV2 UI handle
*/
class JuceLV2UIWrapper : public AudioProcessorListener,
                         public Timer
{
public:
    enum UIType {
        UI_X11,
        UI_EXTERNAL
    };

    JuceLV2UIWrapper (AudioProcessor* const filter_, LV2UI_Write_Function writeFunction_, LV2UI_Controller controller_, LV2UI_Widget* widget, const LV2_Feature* const* features, UIType uiType_) :
            filter (filter_),
            editor (nullptr),
            writeFunction (writeFunction_),
            controller (controller_),
            uiType (uiType_),
#if JucePlugin_WantsLV2X11UI
            x11Editor (nullptr),
            uiResizeFeature (nullptr),
#endif
            externalUI (nullptr),
            externalUIHost (nullptr)
    {
        if (activeUIs.size() == 0)
            initialiseJuce_GUI();

#if JUCE_LINUX
        MessageManagerLock mmLock;
#endif

        filter->addListener(this);

        if (filter->hasEditor())
        {
            editor = filter->createEditorIfNeeded();
        }

        if (editor)
        {
            switch(uiType)
            {
#if JucePlugin_WantsLV2X11UI
            case UI_X11:
                resetX11UI (features);

                if (x11Editor)
                    *widget = x11Editor->getWindowHandle();
                else
                    *widget = nullptr;

                break;
#endif

            case UI_EXTERNAL:
                resetExternalUI (features);

                if (externalUIHost)
                {
                    String title = (externalUIHost->plugin_human_id && externalUIHost->plugin_human_id[0] != 0) ? String(externalUIHost->plugin_human_id) : filter->getName();
                    externalUI = new JuceLV2ExternalUIWrapper(editor, title);
                    *widget = externalUI;
                    startTimer (100);
                }
                else
                {
                    *widget = nullptr;
                    std::cerr << "Failed to init external UI" << std::endl;
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

        controlPortOffset = 0;
#if JucePlugin_WantsMidiInput
        controlPortOffset += 1;
#endif
#if JucePlugin_ProducesMidiOutput
        controlPortOffset += 1;
#endif
#if JucePlugin_WantsLV2TimePos
        controlPortOffset += 1;
#endif
        controlPortOffset += JucePlugin_MaxNumInputChannels;
        controlPortOffset += JucePlugin_MaxNumOutputChannels;

        activeUIs.add (this);
    }

    ~JuceLV2UIWrapper()
    {
        JUCE_AUTORELEASEPOOL

        {
#if JUCE_LINUX
            MessageManagerLock mmLock;
#endif
            PopupMenu::dismissAllActiveMenus();

            stopTimer();

            filter->removeListener(this);

#if JucePlugin_WantsLV2X11UI
            if (x11Editor)
              delete x11Editor;
#endif

            if (externalUI)
                delete externalUI;

            if (editor)
            {
                filter->editorBeingDeleted(editor);
                delete editor;
            }

#ifndef JucePlugin_WantsLV2InstanceAccess
            // fake filter created for UI
            delete filter;
            filter = nullptr;
#endif

            jassert (activeUIs.contains (this));
            activeUIs.removeValue (this);
        }

        if (activePlugins.size() == 0 && activeUIs.size() == 0)
        {
#if JUCE_LINUX
            SharedMessageThread::deleteInstance();
#endif
            shutdownJuce_GUI();
        }
    }

    void doPortEvent(const uint32 portIndex, const float value)
    {
#ifndef JucePlugin_WantsLV2InstanceAccess
        // With instance access, plugin has already been updated
        if (filter && portIndex-controlPortOffset >= 0) // FIXME?
            filter->setParameter(portIndex-controlPortOffset, value);
#endif
    }

    void doCleanup()
    {
#if JucePlugin_WantsLV2X11UI
        if (x11Editor)
            x11Editor->removeFromDesktop();
#endif
    }

    //==============================================================================
    void audioProcessorParameterChanged (AudioProcessor*, int index, float newValue)
    {
        if (controller && writeFunction)
           writeFunction(controller, index+controlPortOffset, sizeof (float), 0, &newValue);
    }

    void audioProcessorChanged (AudioProcessor*)
    {
    }

    void timerCallback()
    {
        if (externalUI && externalUI->isClosed())
        {
            if (externalUIHost)
                externalUIHost->ui_closed (controller);

            stopTimer();
        }
    }

    //==============================================================================
    void resetIfNeeded(LV2UI_Write_Function writeFunction_, LV2UI_Controller controller_, LV2UI_Widget* widget, const LV2_Feature* const* features)
    {
        writeFunction = writeFunction_;
        controller = controller_;

        if (uiType == UI_X11)
        {
#if JucePlugin_WantsLV2X11UI
            resetX11UI (features);
            *widget = x11Editor->getWindowHandle();
#endif
        }
        else if (uiType == UI_EXTERNAL)
        {
            resetExternalUI (features);
            *widget = externalUI;

            if (externalUI)
            {
                externalUI->resetWindow();
                startTimer (100);
            }
        }
        else
            *widget = nullptr;
    }

private:
    AudioProcessor* filter;
    AudioProcessorEditor* editor;

    LV2UI_Write_Function writeFunction;
    LV2UI_Controller controller;
    UIType uiType;

#if JucePlugin_WantsLV2X11UI
    JuceLV2X11Editor* x11Editor;
    LV2_UI_Resize_Feature* uiResizeFeature;
#endif
    JuceLV2ExternalUIWrapper* externalUI;
    lv2_external_ui_host* externalUIHost;

    uint32 controlPortOffset;

    //==============================================================================
#if JucePlugin_WantsLV2X11UI
    void resetX11UI(const LV2_Feature* const* features)
    {
        void* parent = nullptr;
        uiResizeFeature = nullptr;

        for (uint16 i = 0; features[i]; i++)
        {
            if (strcmp(features[i]->URI, LV2_UI_URI "#parent") == 0)
                parent = features[i]->data;

            else if (strcmp(features[i]->URI, LV2_UI_RESIZE_URI "#UIResize") == 0)
                uiResizeFeature = (LV2_UI_Resize_Feature*)features[i]->data;
        }

        if (parent != nullptr)
        {
            if (x11Editor == nullptr)
                x11Editor = new JuceLV2X11Editor(editor, uiResizeFeature);

            if (x11Editor->isOnDesktop())
                x11Editor->removeFromDesktop ();

            x11Editor->setVisible (false);
            x11Editor->addToDesktop (0);

            Window hostWindow = (Window) parent;
            Window editorWnd  = (Window) x11Editor->getWindowHandle();
            XReparentWindow (display, editorWnd, hostWindow, 0, 0);

            x11Editor->setVisible (true);
            x11Editor->reset (uiResizeFeature);
        }
    }
#endif

    void resetExternalUI(const LV2_Feature* const* features)
    {
        externalUIHost = nullptr;

        for (uint16 i = 0; features[i]; i++)
        {
            if (strcmp(features[i]->URI, LV2_EXTERNAL_UI_URI) == 0 || strcmp(features[i]->URI, LV2_EXTERNAL_UI_DEPRECATED_URI) == 0)
            {
                externalUIHost = (lv2_external_ui_host*)features[i]->data;
                break;
            }
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLV2UIWrapper);
};

//==============================================================================
/**
    Juce LV2 handle
*/
class JuceLV2Wrapper : public AudioPlayHead
{
public:
    JuceLV2Wrapper(double sampleRate_, const LV2_Feature* const* features) :
            ui (nullptr),
            numInChans (JucePlugin_MaxNumInputChannels),
            numOutChans (JucePlugin_MaxNumOutputChannels),
            isProcessing (false),
            firstProcessCallback (true),
            sampleRate (sampleRate_),
            bufferSize (512),
#if (JucePlugin_WantsMidiInput || JucePlugin_ProducesMidiOutput)
            uridIdMidi (0),
#endif
            uridMap (nullptr)
    {
        filter = createPluginFilter();
        jassert(filter != nullptr);

        filter->setPlayConfigDetails(numInChans, numOutChans, 0, 0);
        filter->setPlayHead (this);

        // Set Port data
#if JucePlugin_WantsMidiInput
        portEventIn = nullptr;
#endif
#if JucePlugin_ProducesMidiOutput
        portEventOut = nullptr;
#endif
        for (int i=0; i < numInChans; i++)
            portAudioIns[i] = nullptr;
        for (int i=0; i < numOutChans; i++)
            portAudioOuts[i] = nullptr;
        portControls.insertMultiple(0, nullptr, filter->getNumParameters());
        portLatency = nullptr;

#if (JucePlugin_WantsMidiInput || JucePlugin_ProducesMidiOutput || JucePlugin_WantsLV2State)
        for (uint16 i = 0; features[i]; i++)
        {
            if (strcmp(features[i]->URI, LV2_URID_MAP_URI) == 0)
            {
                uridMap = (LV2_URID_Map*)features[i]->data;
#if (JucePlugin_WantsMidiInput || JucePlugin_ProducesMidiOutput)
                uridIdMidi = uridMap->map(uridMap->handle, "http://lv2plug.in/ns/ext/midi#MidiEvent");
#endif
                break;
            }
        }
#endif

        lastControlValues.insertMultiple(0, 0.0f, filter->getNumParameters());

        for (int i=0; i < filter->getNumParameters(); i++)
            lastControlValues.set(i, filter->getParameter(i));

        activePlugins.add (this);
    }

    ~JuceLV2Wrapper()
    {
        JUCE_AUTORELEASEPOOL

        {
#if JUCE_LINUX
            MessageManagerLock mmLock;
#endif
            if (ui)
                delete ui;

            delete filter;
            filter = nullptr;

            channels.free();
            deleteTempChannels();

            portControls.clear();
            lastControlValues.clear();

            jassert (activePlugins.contains (this));
            activePlugins.removeValue (this);
        }

        if (activePlugins.size() == 0 && activeUIs.size() == 0)
        {
#if JUCE_LINUX
            SharedMessageThread::deleteInstance();
#endif
            shutdownJuce_GUI();
        }
    }

    //==============================================================================
    // LV2 Descriptor Calls
    void doConnectPort(const uint32 portId, void* dataLocation)
    {
        uint32 index = 0;

#if JucePlugin_WantsMidiInput
        if (portId == index)
        {
#if JUCE_LV2_ENABLE_DEV_FEATURES
            portEventIn = (LV2_Atom_Sequence*)dataLocation;
#else
            portEventIn = (LV2_Event_Buffer*)dataLocation;
#endif
            return;
        }
        index++;
#endif

#if JucePlugin_ProducesMidiOutput
        if (portId == index)
        {
#if JUCE_LV2_ENABLE_DEV_FEATURES
            portEventOut = (LV2_Atom_Sequence*)dataLocation;
#else
            portEventOut = (LV2_Event_Buffer*)dataLocation;
#endif
            return;
        }
        index++;
#endif

        for (int i=0; i < numInChans; i++, index++)
        {
            if (portId == index)
            {
                portAudioIns[i] = (float*)dataLocation;
                return;
            }
        }

        for (int i=0; i < numOutChans; i++, index++)
        {
            if (portId == index)
            {
                portAudioOuts[i] = (float*)dataLocation;
                return;
            }
        }

#if JucePlugin_WantsLV2TimePos
        if (portId == index)
        {
            portTimeBPM = (float*)dataLocation;
            return;
        }
        index++;
#endif

        for (int i=0; i < filter->getNumParameters(); i++, index++)
        {
            if (portId == index)
            {
                portControls.set(i, (float*)dataLocation);
                return;
            }
        }

        if (portId == index)
        {
            portLatency = (float*)dataLocation;
            return;
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

            if (portLatency)
                *portLatency = filter->getLatencySamples();
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
        if (bufferSize >= 16 && bufferSize != numSamples)
        {
            bufferSize = numSamples;
            filter->setPlayConfigDetails (numInChans, numOutChans, sampleRate, bufferSize);
            filter->prepareToPlay (sampleRate, bufferSize);
        }

        // Check for updated parameters
        float curValue;
        for (int i = 0; i < portControls.size(); i++)
        {
            if (portControls[i] != nullptr)
            {
                curValue = *(float*)portControls[i];
                if (lastControlValues[i] != curValue)
                {
                    filter->setParameter(i, curValue);
                    lastControlValues.setUnchecked(i, curValue);
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
                    zeromem (portAudioOuts[i], sizeof (float) * numSamples);
            }
            else
            {
                int i;
                for (i = 0; i < numOut; ++i)
                {
                    float* chan = tempChannels.getUnchecked(i);

                    if (chan == 0)
                    {
                        chan = portAudioOuts[i];

                        // if some output channels are disabled, some hosts supply the same buffer
                        // for multiple channels - this buggers up our method of copying the
                        // inputs over the outputs, so we need to create unique temp buffers in this case..
                        for (int j = i; --j >= 0;)
                        {
                            if (portAudioOuts[j] == chan)
                            {
                                chan = new float [bufferSize * 2];
                                tempChannels.set (i, chan);
                                break;
                            }
                        }
                    }

                    if (i < numIn && chan != portAudioIns[i])
                        memcpy (chan, portAudioIns[i], sizeof (float) * numSamples);

                    channels[i] = chan;
                }

#if JucePlugin_WantsMidiInput
                // LV2 MIDI Input
                if (portEventIn != nullptr)
                {
                    midiEvents.clear();

#if JUCE_LV2_ENABLE_DEV_FEATURES
#else
#endif

//                     LV2_Event_Iterator iter;
//                     lv2_event_begin(&iter, midiInPort);
//                     uint32 sampleFrame = 0;
//                     uint8* data = 0;
// 
//                     while (sampleFrame < numSamples && lv2_event_is_valid(&iter))
//                     {
//                         const LV2_Event* event = lv2_event_get(&iter, &data);
// 
//                         if (event != nullptr && event->type == midiURIId)
//                         {
//                             sampleFrame = event->frames;
//                             midiEvents.addEvent(data, event->size, event->frames);
//                         }
// 
//                         lv2_event_increment(&iter);
//                     }
                }
#endif

                for (; i < numIn; ++i)
                    channels[i] = portAudioIns[i];

                {
                    AudioSampleBuffer chans (channels, jmax (numIn, numOut), numSamples);
                    filter->processBlock (chans, midiEvents);
                }

                // copy back any temp channels that may have been used..
                for (i = 0; i < numOut; ++i)
                {
                    const float* const chan = tempChannels.getUnchecked(i);

                    if (chan != nullptr)
                        memcpy (portAudioOuts[i], chan, sizeof (float) * numSamples);
                }
            }
        }

        if (! midiEvents.isEmpty())
        {
#if JucePlugin_ProducesMidiOutput
            const int numEvents = midiEvents.getNumEvents();

#if JUCE_LV2_ENABLE_DEV_FEATURES
#else
#endif

//             LV2_Event_Iterator iter;
//             lv2_event_buffer_reset(midiOutPort, LV2_EVENT_AUDIO_STAMP, (uint8*)(midiOutPort + 1));
//             lv2_event_begin(&iter, midiOutPort);
// 
//             const JUCE_NAMESPACE::uint8* midiEventData;
//             int midiEventSize, midiEventPosition;
//             MidiBuffer::Iterator i (midiEvents);
// 
//             while (i.getNextEvent (midiEventData, midiEventSize, midiEventPosition))
//             {
//                 jassert (midiEventPosition >= 0 && midiEventPosition < numSamples);
// 
//                 lv2_event_write(&iter, midiEventPosition, 0, midiURIId, midiEventSize, midiEventData);
//             }
#endif
            midiEvents.clear();
        }
    }

    void doCleanup()
    {
    }

    //==============================================================================
    // JUCE Stuff

    bool getCurrentPosition (AudioPlayHead::CurrentPositionInfo& info)
    {
#if JucePlugin_WantsLV2TimePos
        if (sampleRate <= 0)
            return false;

        if (portTimeBPM)
            info.bpm = *portTimeBPM;
        else
            info.bpm = 120.0;

        info.timeSigNumerator   = 4;
        info.timeSigDenominator = 4;
        info.ppqPosition = 0;
        info.ppqPositionOfLastBarStart = 0;
        info.timeInSeconds  = 0;
        info.editOriginTime = 0;
        info.frameRate   = AudioPlayHead::fpsUnknown;
        info.isPlaying   = true;
        info.isRecording = false;

        return true;
#endif
    }

    AudioProcessor* getFilter() { return filter; }

    //==============================================================================
    String getState ()
    {
        if (filter == nullptr)
            return String::empty;

        return filter->getStateInformationString().replace("\r\n","\n");
    }

    void setState (const String& data)
    {
        if (filter == nullptr)
            return;

        filter->setStateInformationString(data);
    }

    LV2_URID_Map* const getURIDMap()
    {
        return uridMap;
    }

    bool hasUI()
    {
        return ui != nullptr;
    }

    JuceLV2UIWrapper* getUI(LV2UI_Write_Function writeFunction, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features)
    {
        if (ui)
           ui->resetIfNeeded(writeFunction, controller, widget, features);
        return ui;
    }

    void createUI(LV2UI_Write_Function writeFunction, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features, JuceLV2UIWrapper::UIType uiType)
    {
        ui = new JuceLV2UIWrapper(filter, writeFunction, controller, widget, features, uiType);
    }

    //==============================================================================
private:
    AudioProcessor* filter;
    JuceLV2UIWrapper* ui;
    MidiBuffer midiEvents;
    int numInChans, numOutChans;
    bool isProcessing, firstProcessCallback;
    HeapBlock<float*> channels;
    Array<float*> tempChannels;  // see note in doRun()

    double sampleRate;
    uint32 bufferSize;
#if (JucePlugin_WantsMidiInput || JucePlugin_ProducesMidiOutput)
    LV2_URID uridIdMidi;
#endif
    LV2_URID_Map* uridMap;
    Array<float> lastControlValues; 

    // LV2 Port data
#if JucePlugin_WantsMidiInput
#if JUCE_LV2_ENABLE_DEV_FEATURES
    LV2_Atom_Sequence* portEventIn;
#else
    LV2_Event_Buffer* portEventIn;
#endif
#endif
#if JucePlugin_ProducesMidiOutput
#if JUCE_LV2_ENABLE_DEV_FEATURES
    LV2_Atom_Sequence* portEventOut;
#else
    LV2_Event_Buffer* portEventOut;
#endif
#endif
    float* portAudioIns[JucePlugin_MaxNumInputChannels];
    float* portAudioOuts[JucePlugin_MaxNumOutputChannels];
#if JucePlugin_WantsLV2TimePos
    float* portTimeBPM;
#endif
    Array<float*> portControls;
    float* portLatency;

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
LV2_Handle juceLV2_Instantiate(const LV2_Descriptor* descriptor, double sampleRate, const char* bundlePath, const LV2_Feature* const* features)
{
    JuceLV2Wrapper* wrapper = new JuceLV2Wrapper(sampleRate, features);
    return wrapper;
}

void juceLV2_ConnectPort(LV2_Handle instance, uint32 port, void* dataLocation)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    wrapper->doConnectPort(port, dataLocation);
}

void juceLV2_Activate(LV2_Handle instance)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    wrapper->doActivate();
}

void juceLV2_Run(LV2_Handle instance, uint32 sampleCount)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    wrapper->doRun(sampleCount);
}

void juceLV2_Deactivate(LV2_Handle instance)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    wrapper->doDeactivate();
}

void juceLV2_Cleanup(LV2_Handle instance)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    wrapper->doCleanup();
    delete wrapper;
}

//==============================================================================
#ifdef JucePlugin_WantsLV2State
void juceLV2_Save(LV2_Handle instance, LV2_State_Store_Function store, LV2_State_Handle handle, uint32_t flags, const LV2_Feature* const* features)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    jassert(wrapper);

    String stateData = wrapper->getState();
    LV2_URID_Map* uridMap = wrapper->getURIDMap();

    store (handle,
           uridMap->map(uridMap->handle, JUCE_LV2_STATE_STRING_URI),
           stateData.toUTF8().getAddress(),
           stateData.toUTF8().sizeInBytes(),
           uridMap->map(uridMap->handle, LV2_ATOM__String),
           LV2_STATE_IS_POD|LV2_STATE_IS_PORTABLE);
}

void juceLV2_Restore(LV2_Handle instance, LV2_State_Retrieve_Function retrieve, LV2_State_Handle handle, uint32_t flags, const LV2_Feature* const* features)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    jassert(wrapper);

    LV2_URID_Map* uridMap = wrapper->getURIDMap();

    size_t size;
    uint32 type;
    const void* data = retrieve (handle,
                                 uridMap->map(uridMap->handle, JUCE_LV2_STATE_STRING_URI),
                                 &size, &type, &flags);

    if (type == uridMap->map(uridMap->handle, LV2_ATOM__String))
    {
        String stateData = String(CharPointer_UTF8(static_cast<const char*>(data)));
        wrapper->setState(stateData);
    }
}
#endif

const void* juceLV2_ExtensionData(const char* uri)
{
#ifdef JucePlugin_WantsLV2State
    static const LV2_State_Interface state = { juceLV2_Save, juceLV2_Restore };
    if (strcmp(uri, LV2_STATE__Interface) == 0)
        return &state;
#endif
    return nullptr;
}

//==============================================================================
// LV2 UI descriptor functions
LV2UI_Handle juceLV2UI_Instantiate(const LV2UI_Descriptor* uiDescriptor, LV2UI_Write_Function writeFunction, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features, JuceLV2UIWrapper::UIType uiType)
{
    const MessageManagerLock mmLock;

#ifdef JucePlugin_WantsLV2InstanceAccess
    for (uint16 i = 0; features[i]; i++)
    {
        if (strcmp(features[i]->URI, LV2_INSTANCE_ACCESS_URI) == 0 && features[i]->data)
        {
            JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)features[i]->data;

            if (! wrapper->hasUI())
            {
                wrapper->createUI (writeFunction, controller, widget, features, uiType);
            }

            return wrapper->getUI (writeFunction, controller, widget, features);
        }
    }
    std::cerr << "Host does not support instance-access, cannot use UI" << std::endl;
    return nullptr;
#else
    // this is a fake filter!
    AudioProcessor* filter = createPluginFilter();
    JuceLV2UIWrapper* uiWrapper = new JuceLV2UIWrapper(filter, writeFunction, controller, widget, features, uiType);
    return uiWrapper;
#endif
}

LV2UI_Handle juceLV2UI_InstantiateExternal(const LV2UI_Descriptor* descriptor, const char* plugin_uri, const char* bundle_path, LV2UI_Write_Function writeFunction, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features)
{
    return juceLV2UI_Instantiate(descriptor, writeFunction, controller, widget, features, JuceLV2UIWrapper::UI_EXTERNAL);
}

LV2UI_Handle juceLV2UI_InstantiateX11(const LV2UI_Descriptor* descriptor, const char* plugin_uri, const char* bundle_path, LV2UI_Write_Function writeFunction, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features)
{
    return juceLV2UI_Instantiate(descriptor, writeFunction, controller, widget, features, JuceLV2UIWrapper::UI_X11);
}

void juceLV2UI_Cleanup(LV2UI_Handle instance)
{
#ifdef JucePlugin_WantsLV2InstanceAccess
    JuceLV2UIWrapper* uiWrapper = (JuceLV2UIWrapper*)instance;
    uiWrapper->doCleanup();
#else
    delete (JuceLV2UIWrapper*)instance;
#endif
}

void juceLV2UI_PortEvent(LV2UI_Handle instance, uint32 portIndex, uint32 bufferSize, uint32 format, const void* buffer)
{
    const MessageManagerLock mmLock;
    JuceLV2UIWrapper* uiWrapper = (JuceLV2UIWrapper*)instance;

    if (uiWrapper && format == 0 && bufferSize == sizeof (float))
    {
        float value = *(float*)buffer;
        uiWrapper->doPortEvent(portIndex, value);
    }
}

const void* juceLV2UI_ExtensionData(const char* uri)
{
    return nullptr;
}

//==============================================================================
// static LV2 Descriptor objects
class JuceLv2Plugin : public LV2_Descriptor
{
public:
    JuceLv2Plugin()
    {
        URI            = JucePlugin_LV2URI;
        instantiate    = juceLV2_Instantiate;
        connect_port   = juceLV2_ConnectPort;
        activate       = juceLV2_Activate;
        run            = juceLV2_Run;
        deactivate     = juceLV2_Deactivate;
        cleanup        = juceLV2_Cleanup;
        extension_data = juceLV2_ExtensionData;
    }
};

class JuceLv2UI_External : public LV2UI_Descriptor
{
public:
    JuceLv2UI_External()
    {
        URI            = JucePlugin_LV2URI "#ExternalUI";
        instantiate    = juceLV2UI_InstantiateExternal;
        cleanup        = juceLV2UI_Cleanup;
        port_event     = juceLV2UI_PortEvent;
        extension_data = juceLV2UI_ExtensionData;
    }
};

class JuceLv2UI_ExternalOld : public LV2UI_Descriptor
{
public:
    JuceLv2UI_ExternalOld()
    {
        URI            = JucePlugin_LV2URI "#ExternalOldUI";
        instantiate    = juceLV2UI_InstantiateExternal;
        cleanup        = juceLV2UI_Cleanup;
        port_event     = juceLV2UI_PortEvent;
        extension_data = juceLV2UI_ExtensionData;
    }
};

class JuceLv2UI_X11 : public LV2UI_Descriptor
{
public:
    JuceLv2UI_X11()
    {
        URI            = JucePlugin_LV2URI "#X11UI";
        instantiate    = juceLV2UI_InstantiateX11;
        cleanup        = juceLV2UI_Cleanup;
        port_event     = juceLV2UI_PortEvent;
        extension_data = juceLV2UI_ExtensionData;
    }
};

static JuceLv2Plugin         JuceLv2Plugin_Obj;
static JuceLv2UI_External    JuceLv2UI_External_Obj;
static JuceLv2UI_ExternalOld JuceLv2UI_ExternalOld_Obj;
static JuceLv2UI_X11         JuceLv2UI_X11_Obj;

//==============================================================================
// Mac startup code..
#if JUCE_MAC

    extern "C" __attribute__ ((visibility("default"))) void juce_lv2_ttl_generator()
    {
        initialiseMac();
        createTtlFiles();
    }

    extern "C" __attribute__ ((visibility("default"))) const LV2_Descriptor* lv2_descriptor(uint32 index)
    {
        initialiseMac();
        return (index == 0) ? &JuceLv2Plugin_Obj : nullptr;
    }

    extern "C" __attribute__ ((visibility("default"))) const LV2UI_Descriptor* lv2ui_descriptor(uint32 index)
    {
        initialiseMac();
        switch (index)
        {
          case 0:
            return &JuceLv2UI_External_Obj;
          case 1:
            return &JuceLv2UI_ExternalOld_Obj;
          default:
            return nullptr;
        }
    }

//==============================================================================
// Linux startup code..
#elif JUCE_LINUX

    extern "C" __attribute__ ((visibility("default"))) void juce_lv2_ttl_generator()
    {
        SharedMessageThread::getInstance();
        createTtlFiles();
    }

    extern "C" __attribute__ ((visibility("default"))) const LV2_Descriptor* lv2_descriptor(uint32 index)
    {
        SharedMessageThread::getInstance();
        return (index == 0) ? &JuceLv2Plugin_Obj : nullptr;
    }

    extern "C" __attribute__ ((visibility("default"))) const LV2UI_Descriptor* lv2ui_descriptor(uint32 index)
    {
        SharedMessageThread::getInstance();
        switch (index)
        {
          case 0:
            return &JuceLv2UI_External_Obj;
          case 1:
            return &JuceLv2UI_ExternalOld_Obj;
#if JucePlugin_WantsLV2X11UI
          case 2:
            return &JuceLv2UI_X11_Obj;
#endif
          default:
            return nullptr;
        }
    }

    // don't put initialiseJuce_GUI or shutdownJuce_GUI in these... it will crash!
    __attribute__((constructor)) void myPluginInit() {}
    __attribute__((destructor))  void myPluginFini() {}

//==============================================================================
// Windows startup code..
#else

    extern "C" __declspec (dllexport) void juce_lv2_ttl_generator()
    {
        createTtlFiles();
    }

    extern "C" __declspec (dllexport) const LV2_Descriptor* lv2_descriptor(uint32 index)
    {
        return (index == 0) ? &JuceLv2Plugin_Obj : nullptr;
    }

    extern "C" __declspec (dllexport) const LV2UI_Descriptor* lv2ui_descriptor(uint32 index)
    {
        switch (index)
        {
          case 0:
            return &JuceLv2UI_External_Obj;
          case 1:
            return &JuceLv2UI_ExternalOld_Obj;
          default:
            return nullptr;
        }
    }

#endif

#endif
