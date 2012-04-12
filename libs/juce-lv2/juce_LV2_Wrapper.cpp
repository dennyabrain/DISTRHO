/*
  ==============================================================================

   Juce LV2 Wrapper, based on VST Wrapper code

  ==============================================================================
*/

// Your project must contain an AppConfig.h file with your project-specific settings in it,
// and your header search path must make it accessible to the module's files.
#include "AppConfig.h"

#if 1 // TODO - remove me
#include "JucePluginMain.h"
//#include "JucePluginCharacteristics.h"
#endif

#include "utility/juce_CheckSettingMacros.h"

#if JucePlugin_Build_LV2

//==============================================================================
/** Enable LV2 development features
* This macro enables currently development/unstable features of LV2, use with care.
* Features are:
* - atom based MIDI and Time-Pos
*/
#define JUCE_LV2_ENABLE_DEV_FEATURES 1

/*
 * Available macros:
 * - JucePlugin_WantsLV2Presets
 * - JucePlugin_WantsLV2State
 * - JucePlugin_WantsLV2StateString
 * - JucePlugin_WantsLV2TimePos
 * - JucePlugin_WantsLV2InstanceAccess (UI)
 */

#if JUCE_LINUX
 #include <X11/Xlib.h>
 #include <X11/Xutil.h>
 #include <X11/Xatom.h>
 #undef KeyPress
#endif

#include <fstream>
#include <iostream>

// LV2 includes
#include "includes/lv2.h"
#include "includes/instance-access.h"
#include "includes/midi.h"
#include "includes/state.h"
#include "includes/urid.h"
#include "includes/ui.h"

#include "includes/lv2_external_ui.h"

#if JUCE_LV2_ENABLE_DEV_FEATURES
 #include "includes/atom.h"
 #include "includes/atom-util.h"
 #include "includes/time.h"
#else
 #define LV2_ATOM__String "http://lv2plug.in/ns/ext/atom#String"
 #include "includes/event.h"
 #include "includes/event-helpers.h"
#endif

#include "modules/juce_audio_plugin_client/utility/juce_IncludeModuleHeaders.h"

// FIXME - juce base64 algorithm is broken
#include "base64/Base64.cpp"

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
#define JUCE_LV2_STATE_BINARY_URI "urn:juce:stateBinary"

//==============================================================================
/** Somewhere in the codebase of your plugin, you need to implement this function
    and make it create an instance of the filter subclass that you're building.
*/
extern AudioProcessor* JUCE_CALLTYPE createPluginFilter();

//==============================================================================
// Various helper functions for creating the ttl files

#if JUCE_MAC
 #define PLUGIN_EXT ".dylib"
#elif JUCE_LINUX
 #define PLUGIN_EXT ".so"
#elif JUCE_WINDOWS
 #define PLUGIN_EXT ".dll"
#endif

/** Returns the name of the plugin binary file */
String getBinaryName()
{
    return String(JucePlugin_Name).replace(" ", "_");
}

/** Returns plugin type, defined in AppConfig.h or JucePluginCharacteristics.h */
const String getPluginType()
{
    String pluginType;
#ifdef JucePlugin_LV2Category
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
            if (i == 0 && std::isdigit(c))
                symbol += "_";
            else if (std::isalpha(c) || std::isdigit(c))
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
#if JucePlugin_WantsLV2Presets
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
        manifest += "    a <" LV2_EXTERNAL_UI_URI "> ;\n";
        manifest += "    ui:binary <" + binary + PLUGIN_EXT "> ";
#if JucePlugin_WantsLV2InstanceAccess
        manifest += ";\n";
        manifest += "    ui:requiredFeature <" LV2_INSTANCE_ACCESS_URI "> .\n";
#else
        manifest += ".\n";
#endif
        manifest += "\n";

        manifest += "<" JucePlugin_LV2URI "#ExternalOldUI>\n";
        manifest += "    a ui:external ;\n";
        manifest += "    ui:binary <" + binary + PLUGIN_EXT "> ";
#if JucePlugin_WantsLV2InstanceAccess
        manifest += ";\n";
        manifest += "    ui:requiredFeature <" LV2_INSTANCE_ACCESS_URI "> .\n";
#else
        manifest += ".\n";
#endif
        manifest += "\n";

#if JUCE_LINUX
        manifest += "<" JucePlugin_LV2URI "#X11UI>\n";
        manifest += "    a ui:X11UI ;\n";
        manifest += "    ui:binary <" + binary + PLUGIN_EXT "> ;\n";
 #if JucePlugin_WantsLV2InstanceAccess
        manifest += "    ui:requiredFeature <" LV2_INSTANCE_ACCESS_URI "> ;\n";
 #endif
        manifest += "    ui:optionalFeature ui:noUserResize .\n";
        manifest += "\n";
#endif
    }

#if JucePlugin_WantsLV2Presets
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
String makePluginTtl(AudioProcessor* const filter)
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
    plugin += "    lv2:requiredFeature <" LV2_URID__map "> ;\n";
#elif (JucePlugin_WantsMidiInput || JucePlugin_ProducesMidiOutput || JucePlugin_WantsLV2State || (JUCE_LV2_ENABLE_DEV_FEATURES && JucePlugin_WantsLV2TimePos))
    plugin += "    lv2:optionalFeature <" LV2_URID__map "> ;\n";
#endif
#if JucePlugin_WantsLV2State
    plugin += "    lv2:extensionData <" LV2_STATE__interface "> ;\n";
#endif
    plugin += "\n";

    if (filter->hasEditor())
    {
        plugin += "    ui:ui <" JucePlugin_LV2URI "#ExternalUI> ,\n";
        plugin += "          <" JucePlugin_LV2URI "#ExternalOldUI> ";
#if JUCE_LINUX
        plugin += ",\n";
        plugin += "          <" JucePlugin_LV2URI "#X11UI> ;\n";
#else
        plugin += ";\n";
#endif
        plugin += "\n";
    }

    uint32 portIndex = 0;

    // Event input (old MIDI or MIDI + TimePos)
#if (JucePlugin_WantsMidiInput || (JUCE_LV2_ENABLE_DEV_FEATURES && JucePlugin_WantsLV2TimePos))
    plugin += "    lv2:port [\n";
 #if JUCE_LV2_ENABLE_DEV_FEATURES
    plugin += "        a lv2:InputPort, atom:AtomPort ;\n";
    plugin += "        atom:bufferType atom:Sequence ;\n";
  #if JucePlugin_WantsLV2TimePos
    plugin += "        atom:supports <" LV2_MIDI__MidiEvent "> ,\n";
    plugin += "                    <" LV2_TIME__Position "> ;\n";
  #else
    plugin += "        atom:supports <" LV2_MIDI__MidiEvent "> ;\n";
  #endif
 #else
    plugin += "        a lv2:InputPort, ev:EventPort ;\n";
    plugin += "        ev:supportsEvent <" LV2_MIDI__MidiEvent "> ;\n";
 #endif
    plugin += "        lv2:index " + String(portIndex++) + " ;\n";
    plugin += "        lv2:symbol \"lv2_events_in\" ;\n";
    plugin += "        lv2:name \"Events Input\" ;\n";
 #if ! JucePlugin_IsSynth
    plugin += "        lv2:portProperty lv2:connectionOptional ;\n";
 #endif
    plugin += "    ] ;\n\n";
#endif

    // Event output (MIDI only)
#if JucePlugin_ProducesMidiOutput
    plugin += "    lv2:port [\n";
 #if JUCE_LV2_ENABLE_DEV_FEATURES
    plugin += "        a lv2:OutputPort, atom:AtomPort ;\n";
    plugin += "        atom:bufferType atom:Sequence ;\n";
    plugin += "        atom:supports <" LV2_MIDI__MidiEvent "> ;\n";
 #else
    plugin += "        a lv2:OutputPort, ev:EventPort ;\n";
    plugin += "        ev:supportsEvent <" LV2_MIDI__MidiEvent "> ;\n";
 #endif
    plugin += "        lv2:index " + String(portIndex++) + " ;\n";
    plugin += "        lv2:symbol \"lv2_events_out\" ;\n";
    plugin += "        lv2:name \"Events Output\" ;\n";
    plugin += "        lv2:portProperty lv2:connectionOptional ;\n";
    plugin += "    ] ;\n\n";
#endif

    for (int i=0; i<JucePlugin_MaxNumInputChannels; i++)
    {
        if (i == 0)
            plugin += "    lv2:port [\n";
        else
            plugin += "    [\n";

        plugin += "        a lv2:InputPort, lv2:AudioPort ;\n";
        plugin += "        lv2:index " + String(portIndex++) + " ;\n";
        plugin += "        lv2:symbol \"lv2_audio_in_" + String(i+1) + "\" ;\n";
        plugin += "        lv2:name \"Audio Input " + String(i+1) + "\" ;\n";

        if (i+1 == JucePlugin_MaxNumInputChannels)
            plugin += "    ] ;\n\n";
        else
            plugin += "    ] ,\n";
    }

    for (int i=0; i<JucePlugin_MaxNumOutputChannels; i++)
    {
        if (i == 0)
            plugin += "    lv2:port [\n";
        else
            plugin += "    [\n";

        plugin += "        a lv2:OutputPort, lv2:AudioPort ;\n";
        plugin += "        lv2:index " + String(portIndex++) + " ;\n";
        plugin += "        lv2:symbol \"lv2_audio_out_" + String(i+1) + "\" ;\n";
        plugin += "        lv2:name \"Audio Output " + String(i+1) + "\" ;\n";

        if (i+1 == JucePlugin_MaxNumOutputChannels)
            plugin += "    ] ;\n\n";
        else
            plugin += "    ] ,\n";
    }

#if JucePlugin_WantsLV2TimePos
    plugin += "    lv2:port [\n";
    plugin += "        a lv2:InputPort, lv2:ControlPort ;\n";
    plugin += "        lv2:index " + String(portIndex++) + " ;\n";
    plugin += "        lv2:symbol \"lv2_time_bpm\" ;\n";
    plugin += "        lv2:name \"LV2 BPM\" ;\n";
    plugin += "        lv2:default 120.0 ;\n";
    plugin += "        lv2:minimum 10.0 ;\n";
    plugin += "        lv2:maximum 400.0 ;\n";
    plugin += "        lv2:designation <http://lv2plug.in/ns/ext/time#beatsPerMinute> ;\n";
    plugin += "        ue:unit ue:bpm ;\n";
    plugin += "    ] ;\n\n";
#endif

    for (int i=0; i < filter->getNumParameters(); i++)
    {
        if (i == 0)
            plugin += "    lv2:port [\n";
        else
            plugin += "    [\n";

        plugin += "        a lv2:InputPort, lv2:ControlPort ;\n";
        plugin += "        lv2:index " + String(portIndex++) + " ;\n";
        plugin += "        lv2:symbol \"" + nameToSymbol(filter->getParameterName(i), i) + "\" ;\n";
        if (filter->getParameterName(i).isNotEmpty())
          plugin += "        lv2:name \"" + filter->getParameterName(i) + "\" ;\n";
        else
          plugin += "        lv2:name \"Port " + String(i+1) + "\" ;\n";
        plugin += "        lv2:default " + String(filter->getParameter(i), 8) + " ;\n";
        plugin += "        lv2:minimum 0.0 ;\n";
        plugin += "        lv2:maximum 1.0 ;\n";

        if (i+1 == filter->getNumParameters())
            plugin += "    ] ;\n\n";
        else
            plugin += "    ] ,\n";
    }

    plugin += "    lv2:port [\n";
    plugin += "        a lv2:OutputPort, lv2:ControlPort ;\n";
    plugin += "        lv2:index " + String(portIndex++) + " ;\n";
    plugin += "        lv2:symbol \"lv2_latency\" ;\n";
    plugin += "        lv2:name \"Latency\" ;\n";
    plugin += "        lv2:portProperty lv2:reportsLatency ;\n";
    plugin += "    ] ;\n\n";

    plugin += "    doap:name \"" JucePlugin_Name "\" ;\n";
    plugin += "    doap:maintainer [ foaf:name \"" JucePlugin_Manufacturer "\" ] .\n";

    return plugin;
}

/** Create the presets.ttl contents */
String makePresetsTtl(AudioProcessor* const filter)
{
    String presets;
#if JucePlugin_WantsLV2State
    presets += "@prefix atom:  <http://lv2plug.in/ns/ext/atom#> .\n";
#endif
    presets += "@prefix lv2:   <http://lv2plug.in/ns/lv2core#> .\n";
    presets += "@prefix pset:  <http://lv2plug.in/ns/ext/presets#> .\n";
#if JucePlugin_WantsLV2State
    presets += "@prefix rdf:   <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n";
#endif
    presets += "@prefix rdfs:  <http://www.w3.org/2000/01/rdf-schema#> .\n";
#if JucePlugin_WantsLV2StateString
    presets += "@prefix state: <http://lv2plug.in/ns/ext/state#> .\n";
#elif JucePlugin_WantsLV2State
    presets += "@prefix state: <http://lv2plug.in/ns/ext/state#> .\n";
    presets += "@prefix xsd:   <http://www.w3.org/2001/XMLSchema#> .\n";
#endif
    presets += "\n";

    const int numPrograms = filter->getNumPrograms();

    for (int i = 0; i < numPrograms; i++)
    {
        std::cout << "\nSaving preset " << i+1 << "/" << numPrograms+1 << "...";
        std::cout.flush();

        filter->setCurrentProgram(i);
        presets += "<" JucePlugin_LV2URI "#preset" + String(i+1) + "> a pset:Preset ;\n";
        presets += "    rdfs:label \"" + filter->getProgramName(i) + "\" ;\n";

#if JucePlugin_WantsLV2State
        presets += "    state:state [\n";
 #if JucePlugin_WantsLV2StateString
        presets += "        <" JUCE_LV2_STATE_STRING_URI ">\n";
        presets += "\"\"\"\n";
        presets += filter->getStateInformationString().replace("\r\n","\n");
        presets += "\"\"\"\n";
 #else
        MemoryBlock chunkMemory;
        filter->getCurrentProgramStateInformation(chunkMemory);
        const String chunkString = Base64Encode(chunkMemory);

        presets += "        <" JUCE_LV2_STATE_BINARY_URI "> [\n";
        presets += "            a atom:Chunk ;\n";
        presets += "            rdf:value\"\"\"" + chunkString + "\"\"\"^^xsd:base64Binary\n";
        presets += "        ]\n";
 #endif
        if (filter->getNumParameters() > 0)
            presets += "    ] ;\n\n";
        else
            presets += "    ] .\n\n";
#endif

        for (int j=0; j < filter->getNumParameters(); j++)
        {
              if (j == 0)
                presets += "    lv2:port [\n";
            else
                presets += "    [\n";

            presets += "        lv2:symbol \"" + nameToSymbol(filter->getParameterName(j), j) + "\" ;\n";
            presets += "        pset:value " + String(filter->getParameter(j), 8) + " ;\n";

            if (j+1 == filter->getNumParameters())
                presets += "    ] ";
            else
                presets += "    ] ,\n";
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
    plugin << makePluginTtl(filter) << std::endl;
    plugin.close();
    std::cout << " done!" << std::endl;

#if JucePlugin_WantsLV2Presets
    std::cout << "Writing presets.ttl..."; std::cout.flush();
    std::fstream presets("presets.ttl", std::ios::out);
    presets << makePresetsTtl(filter) << std::endl;
    presets.close();
    std::cout << " done!" << std::endl;
#endif
}

static bool needsGUIShutdown = false;
static Array<void*> activePlugins;
static Array<void*> activeUIs;

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
        needsGUIShutdown = true;

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

//==============================================================================
/**
    Lightweight DocumentWindow subclass for external ui
*/
class JuceLV2ExternalUIWindow : public DocumentWindow
{
public:
    /** Creates a Document Window wrapper */
    JuceLV2ExternalUIWindow (const String& title) :
            DocumentWindow (title, Colours::white, DocumentWindow::minimiseButton | DocumentWindow::closeButton, false),
            closed (false),
            lastPos (100, 100)
    {
        setSize(50, 50);
        setOpaque (true);
        setUsingNativeTitleBar (true);

        // FIXME - does not work properly on Linux
        //window->setAlwaysOnTop(true);
    }

    /** Close button handler */
    void closeButtonPressed()
    {
        saveLastPos();
        removeFromDesktop();
        closed = true;
    }

    void saveLastPos()
    {
        lastPos = getScreenPosition();
    }

    void restoreLastPos()
    {
        setTopLeftPosition(lastPos.getX(), lastPos.getY());
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
    JuceLV2ExternalUIWrapper (AudioProcessorEditor* const editor, const String& title)
    {
        window = new JuceLV2ExternalUIWindow (title);
        window->setContentNonOwned (editor, true);

        // native titlebar currently broken
        window->setSize(editor->getWidth(), editor->getHeight());

        // external UI calls
        run  = doRun;
        show = doShow;
        hide = doHide;
    }

    ~JuceLV2ExternalUIWrapper()
    {
        if (window->isOnDesktop())
            window->removeFromDesktop();

        window = nullptr;
    }

    bool isClosed()
    {
        return window->isClosed();
    }

    void resetWindow()
    {
        window->reset();
    }

    Point<int> getScreenPosition()
    {
        if (window->isClosed())
            return window->getLastPos();
        else
            return window->getScreenPosition();
    }

    void setScreenPos(int x, int y)
    {
        if (! window->isClosed())
        {
            window->setTopLeftPosition(x, y);
        }
    }

    //==============================================================================
    static void doRun (lv2_external_ui* _that_)
    {
        const MessageManagerLock mmLock;
        JuceLV2ExternalUIWrapper* _this_ = (JuceLV2ExternalUIWrapper*) _that_;

        if (! _this_->isClosed())
            _this_->window->repaint();
    }

    static void doShow (lv2_external_ui* _that_)
    {
        const MessageManagerLock mmLock;
        JuceLV2ExternalUIWrapper* _this_ = (JuceLV2ExternalUIWrapper*) _that_;

        if (! _this_->isClosed())
        {
            if (! _this_->window->isOnDesktop())
                _this_->window->addToDesktop();

            _this_->window->restoreLastPos();
            _this_->window->setVisible(true);
        }
    }

    static void doHide (lv2_external_ui* _that_)
    {
        const MessageManagerLock mmLock;
        JuceLV2ExternalUIWrapper* _this_ = (JuceLV2ExternalUIWrapper*) _that_;

        if (! _this_->isClosed())
        {
            _this_->window->saveLastPos();
            _this_->window->setVisible(false);
        }
    }

private:
    ScopedPointer<JuceLV2ExternalUIWindow> window;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLV2ExternalUIWrapper);
};

//==============================================================================
/**
    Juce LV2 X11 UI container, listens for resize events and passes them to ui-resize
*/
#if JUCE_LINUX
class JuceLV2X11Container : public Component
{
public:
    JuceLV2X11Container (AudioProcessorEditor* const editor, LV2UI_Resize* uiResizeFeature_)
        : uiResizeFeature(uiResizeFeature_)
    {
        setOpaque (true);
        editor->setOpaque (true);
        setBounds (editor->getBounds());

        editor->setTopLeftPosition (0, 0);
        addAndMakeVisible (editor);
    }

    ~JuceLV2X11Container()
    {
    }

    void paint (Graphics&) {}
    void paintOverChildren (Graphics&) {}

    void childBoundsChanged (Component* child)
    {
        const int cw = child->getWidth();
        const int ch = child->getHeight();

        XResizeWindow (display, (Window) getWindowHandle(), cw, ch);

        if (uiResizeFeature)
            uiResizeFeature->ui_resize (uiResizeFeature->handle, cw, ch);
    }

    void reset (LV2UI_Resize* uiResizeFeature_)
    {
        uiResizeFeature = uiResizeFeature_;

        if (uiResizeFeature)
            uiResizeFeature->ui_resize (uiResizeFeature->handle, getWidth(), getHeight());
    }

private:
    //==============================================================================
    LV2UI_Resize* uiResizeFeature;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLV2X11Container);
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
#if JUCE_LINUX
            x11Container (nullptr),
            uiResizeFeature (nullptr),
#endif
            externalUI (nullptr),
            externalUIHost (nullptr),
            externalUIPos (100, 100),
            uiTouch (nullptr)
    {
        filter->addListener(this);

        if (filter->hasEditor())
            editor = filter->createEditorIfNeeded();

        if (editor)
        {
            // Get UI Touch feature
            for (uint32 i = 0; features[i]; i++)
            {
                if (strcmp(features[i]->URI, LV2_UI__touch) == 0 && features[i]->data)
                {
                    uiTouch = (LV2UI_Touch*)features[i]->data;
                    break;
                }
            }

            switch (uiType)
            {
#if JUCE_LINUX
            case UI_X11:
                resetX11UI (features);

                if (x11Container)
                    *widget = x11Container->getWindowHandle();
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
#if (JucePlugin_WantsMidiInput || (JUCE_LV2_ENABLE_DEV_FEATURES && JucePlugin_WantsLV2TimePos))
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
        PopupMenu::dismissAllActiveMenus();

        filter->removeListener(this);

#if JUCE_LINUX
        x11Container = nullptr;
#endif
        externalUI = nullptr;
        externalUIHost = nullptr;

        if (editor)
        {
            filter->editorBeingDeleted(editor);
            editor = nullptr;
        }

#if ! JucePlugin_WantsLV2InstanceAccess
        // fake filter created for UI
        delete filter;
        //filter = nullptr;
#endif

        jassert (activeUIs.contains (this));
        activeUIs.removeValue (this);
    }

    void doPortEvent(const uint32 portIndex, const float value)
    {
#if ! JucePlugin_WantsLV2InstanceAccess
        if (filter && (int32)portIndex - (int32)controlPortOffset >= 0) // FIXME?
            filter->setParameter(portIndex-controlPortOffset, value);
#else
        // With instance access, plugin has already been updated
        (void)portIndex;
        (void)value;
#endif
    }

    void doCleanup()
    {
#if JucePlugin_WantsLV2InstanceAccess
        if (uiType == UI_X11)
        {
 #if JUCE_LINUX
            if (x11Container && x11Container->isOnDesktop())
                x11Container->removeFromDesktop();
 #endif
        }
        else if (uiType == UI_EXTERNAL)
        {
            if (externalUI)
                externalUIPos = externalUI->getScreenPosition();
        }
#endif

        if (isTimerRunning())
            stopTimer();
    }

    //==============================================================================
    void audioProcessorParameterChanged (AudioProcessor*, int index, float newValue)
    {
        if (writeFunction && controller)
            writeFunction(controller, index+controlPortOffset, sizeof (float), 0, &newValue);
    }

    void audioProcessorChanged (AudioProcessor*) {}

    void audioProcessorParameterChangeGestureBegin (AudioProcessor*, int parameterIndex)
    {
        if (uiTouch)
            uiTouch->touch(uiTouch->handle, parameterIndex + controlPortOffset, true);
    }

    void audioProcessorParameterChangeGestureEnd (AudioProcessor*, int parameterIndex)
    {
        if (uiTouch)
            uiTouch->touch(uiTouch->handle, parameterIndex + controlPortOffset, false);
    }

    void timerCallback()
    {
        if (externalUI && externalUI->isClosed())
        {
            if (externalUIHost)
                externalUIHost->ui_closed (controller);

            if (isTimerRunning()) // prevents assertion failure
                stopTimer();
        }
    }

    //==============================================================================
    void resetIfNeeded(LV2UI_Write_Function writeFunction_, LV2UI_Controller controller_, LV2UI_Widget* widget, const LV2_Feature* const* features)
    {
        writeFunction = writeFunction_;
        controller    = controller_;

        if (uiType == UI_X11)
        {
#if JUCE_LINUX
            resetX11UI (features);
            *widget = x11Container->getWindowHandle();
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
    AudioProcessor* const filter;
    ScopedPointer<AudioProcessorEditor> editor;

    LV2UI_Write_Function writeFunction;
    LV2UI_Controller controller;
    const UIType uiType;

#if JUCE_LINUX
    ScopedPointer<JuceLV2X11Container> x11Container;
    LV2UI_Resize* uiResizeFeature;
#endif
    ScopedPointer<JuceLV2ExternalUIWrapper> externalUI;
    lv2_external_ui_host* externalUIHost;
    Point<int> externalUIPos;

    LV2UI_Touch* uiTouch;

    uint32 controlPortOffset;

    //==============================================================================
#if JUCE_LINUX
    void resetX11UI(const LV2_Feature* const* features)
    {
        void* parent = nullptr;
        uiResizeFeature = nullptr;

        for (uint32 i = 0; features[i]; i++)
        {
            if (strcmp(features[i]->URI, LV2_UI__parent) == 0)
                parent = features[i]->data;

            else if (strcmp(features[i]->URI, LV2_UI__resize) == 0)
                uiResizeFeature = (LV2UI_Resize*)features[i]->data;
        }

        if (parent)
        {
            if (x11Container == nullptr)
                x11Container = new JuceLV2X11Container(editor, uiResizeFeature);

            if (x11Container->isOnDesktop())
                x11Container->removeFromDesktop ();

            x11Container->setVisible (false);
            x11Container->addToDesktop (0);

            Window hostWindow = (Window) parent;
            Window editorWnd  = (Window) x11Container->getWindowHandle();
            XReparentWindow (display, editorWnd, hostWindow, 0, 0);

            x11Container->setVisible (true);
            x11Container->reset (uiResizeFeature);
        }
    }
#endif

    void resetExternalUI(const LV2_Feature* const* features)
    {
        externalUIHost = nullptr;

        for (uint32 i = 0; features[i]; i++)
        {
            if (strcmp(features[i]->URI, LV2_EXTERNAL_UI_URI) == 0 || strcmp(features[i]->URI, LV2_EXTERNAL_UI_DEPRECATED_URI) == 0)
            {
                externalUIHost = (lv2_external_ui_host*)features[i]->data;
                break;
            }
        }

#if JucePlugin_WantsLV2InstanceAccess
        if (externalUI)
            externalUI->setScreenPos(externalUIPos.getX(), externalUIPos.getY());
#endif
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
 #if JUCE_LV2_ENABLE_DEV_FEATURES
            uridIdAtomSequence (0),
 #endif
#endif
            uridMap (nullptr)
    {
        filter = createPluginFilter();
        jassert(filter != nullptr);

        filter->setPlayConfigDetails(numInChans, numOutChans, 0, 0);
        filter->setPlayHead (this);

        // Set Port data
#if (JucePlugin_WantsMidiInput || (JUCE_LV2_ENABLE_DEV_FEATURES && JucePlugin_WantsLV2TimePos))
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

#if (JucePlugin_WantsMidiInput || JucePlugin_ProducesMidiOutput || JucePlugin_WantsLV2State || (JUCE_LV2_ENABLE_DEV_FEATURES && JucePlugin_WantsLV2TimePos))
        for (uint32 i = 0; features[i]; i++)
        {
            if (strcmp(features[i]->URI, LV2_URID_MAP_URI) == 0)
            {
                uridMap = (LV2_URID_Map*)features[i]->data;
 #if (JucePlugin_WantsMidiInput || JucePlugin_ProducesMidiOutput)
                uridIdMidi = uridMap->map(uridMap->handle, LV2_MIDI__MidiEvent);
  #if JUCE_LV2_ENABLE_DEV_FEATURES
                uridIdAtomSequence = uridMap->map(uridMap->handle, LV2_ATOM__Sequence);
  #endif
 #endif
                break;
            }
        }
#else
        (void)features;
#endif

        lastControlValues.insertMultiple(0, 0.0f, filter->getNumParameters());

        for (int i=0; i < filter->getNumParameters(); i++)
            lastControlValues.set(i, filter->getParameter(i));

        activePlugins.add (this);
    }

    ~JuceLV2Wrapper()
    {
        filter = nullptr;

        channels.free();
        deleteTempChannels();

        portControls.clear();
        lastControlValues.clear();

        jassert (activePlugins.contains (this));
        activePlugins.removeValue (this);
    }

    //==============================================================================
    // LV2 Descriptor Calls
    void doConnectPort(const uint32 portId, void* dataLocation)
    {
        uint32 index = 0;

#if (JucePlugin_WantsMidiInput || (JUCE_LV2_ENABLE_DEV_FEATURES && JucePlugin_WantsLV2TimePos))
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

            // if this fails, the host hasn't called activate() before processing
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
        if (bufferSize >= 2 && bufferSize != numSamples)
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

                    if (chan == nullptr)
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

                for (; i < numIn; ++i)
                    channels[i] = portAudioIns[i];

#if JucePlugin_WantsMidiInput
                // LV2 MIDI Input
                if (portEventIn != nullptr)
                {
                    midiEvents.clear();

 #if JUCE_LV2_ENABLE_DEV_FEATURES
                    LV2_SEQUENCE_FOREACH(portEventIn, j)
                    {
                        LV2_Atom_Event* const event = lv2_sequence_iter_get(j);

                        if (event && event->body.type == uridIdMidi)
                        {
                            if (event->time.frames >= numSamples)
                               break;

                            uint8* const data = (uint8* const)(event + 1);
                            midiEvents.addEvent(data, event->body.size, event->time.frames);
                        }
                    }
 #else
                    LV2_Event_Iterator iter;
                    lv2_event_begin(&iter, portEventIn);
                    uint32 sampleFrame = 0;
                    uint8* data = 0;

                    while (sampleFrame < numSamples && lv2_event_is_valid(&iter))
                    {
                        LV2_Event* const event = lv2_event_get(&iter, &data);

                        if (event && event->type == uridIdMidi)
                        {
                            sampleFrame = event->frames;
                            midiEvents.addEvent(data, event->size, event->frames);
                        }

                        lv2_event_increment(&iter);
                    }
 #endif
                }
#endif

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
            if (portEventOut != nullptr)
            {
                const uint8* midiEventData;
                int midiEventSize, midiEventPosition;
                MidiBuffer::Iterator i (midiEvents);

 #if JUCE_LV2_ENABLE_DEV_FEATURES
                uint32_t size, offset = 0;
                LV2_Atom_Event* aev;

                portEventOut->atom.size = 0;
                portEventOut->atom.type = uridIdAtomSequence;
                portEventOut->body.unit = 0;
                portEventOut->body.pad  = 0;

                while (i.getNextEvent (midiEventData, midiEventSize, midiEventPosition))
                {
                    jassert (midiEventPosition >= 0 && midiEventPosition < numSamples);

                    aev = (LV2_Atom_Event*)((char*)LV2_ATOM_CONTENTS(LV2_Atom_Sequence, portEventOut) + offset);
                    aev->time.frames = midiEventPosition;
                    aev->body.type   = uridIdMidi;
                    aev->body.size   = midiEventSize;
                    memcpy(LV2_ATOM_BODY(&aev->body), midiEventData, midiEventSize);

                    size    = lv2_atom_pad_size(sizeof(LV2_Atom_Event) + midiEventSize);
                    offset += size;
                    portEventOut->atom.size += size;
                }
 #else
                LV2_Event_Iterator iter;
                lv2_event_buffer_reset(portEventOut, LV2_EVENT_AUDIO_STAMP, (uint8*)(portEventOut + 1));
                lv2_event_begin(&iter, portEventOut);

                while (i.getNextEvent (midiEventData, midiEventSize, midiEventPosition))
                {
                    jassert (midiEventPosition >= 0 && midiEventPosition < numSamples);

                    lv2_event_write(&iter, midiEventPosition, 0, uridIdMidi, midiEventSize, midiEventData);
                }
 #endif
            }
#endif
            midiEvents.clear();
        }
    }

    void doCleanup()
    {
#if JucePlugin_WantsLV2InstanceAccess
        ui = nullptr;
#endif
    }

    //==============================================================================
    // JUCE Stuff

    bool getCurrentPosition (AudioPlayHead::CurrentPositionInfo& info)
    {
#if JucePlugin_WantsLV2TimePos
        if (sampleRate <= 0)
            return false;

 #if JUCE_LV2_ENABLE_DEV_FEATURES
        if (portTimeBPM)
            info.bpm = *portTimeBPM;
        else
            info.bpm = 120.0;

        info.timeSigNumerator   = 4;
        info.timeSigDenominator = 4;
        info.timeInSeconds  = 0;
        info.editOriginTime = 0;
        info.ppqPosition = 0;
        info.ppqPositionOfLastBarStart = 0;
        info.frameRate   = AudioPlayHead::fpsUnknown;
        info.isPlaying   = false;
        info.isRecording = false;
 #else
        if (portTimeBPM)
            info.bpm = *portTimeBPM;
        else
            info.bpm = 120.0;

        info.timeSigNumerator   = 4;
        info.timeSigDenominator = 4;
        info.timeInSeconds  = 0;
        info.editOriginTime = 0;
        info.ppqPosition = 0;
        info.ppqPositionOfLastBarStart = 0;
        info.frameRate   = AudioPlayHead::fpsUnknown;
        info.isPlaying   = false;
        info.isRecording = false;
 #endif
        return true;
#else
        (void)info;
        return false;
#endif
    }

    AudioProcessor* getFilter() { return filter; }

    //==============================================================================
    void getStateBinary (MemoryBlock& destData)
    {
        if (filter)
            filter->getCurrentProgramStateInformation (destData);

    }

    void setStateBinary (const void* data, int sizeInBytes)
    {
        if (filter)
            filter->setCurrentProgramStateInformation (data, sizeInBytes);
    }

#if JucePlugin_WantsLV2StateString
    String getStateString ()
    {
        if (filter == nullptr)
            return String::empty;

        return filter->getStateInformationString().replace("\r\n","\n");
    }

    void setStateString (const String& data)
    {
        if (filter == nullptr)
            return;

        filter->setStateInformationString(data);
    }
#endif

    const LV2_URID_Map* getURIDMap()
    {
        return uridMap;
    }

#if JucePlugin_WantsLV2InstanceAccess
    JuceLV2UIWrapper* getUI(LV2UI_Write_Function writeFunction, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features, JuceLV2UIWrapper::UIType uiType)
    {
        if (ui)
            ui->resetIfNeeded(writeFunction, controller, widget, features);
        else
            ui = new JuceLV2UIWrapper(filter, writeFunction, controller, widget, features, uiType);
        return ui;
    }
#endif

    //==============================================================================
private:
    ScopedPointer<AudioProcessor> filter;
    ScopedPointer<JuceLV2UIWrapper> ui;
    MidiBuffer midiEvents;
    int numInChans, numOutChans;
    bool isProcessing, firstProcessCallback;
    HeapBlock<float*> channels;
    Array<float*> tempChannels;  // see note in doRun()

    double sampleRate;
    uint32 bufferSize;
#if (JucePlugin_WantsMidiInput || JucePlugin_ProducesMidiOutput)
    LV2_URID uridIdMidi;
 #if JUCE_LV2_ENABLE_DEV_FEATURES
    LV2_URID uridIdAtomSequence;
 #endif
#endif
    LV2_URID_Map* uridMap;
    Array<float> lastControlValues;

    // LV2 Port data
#if (JucePlugin_WantsMidiInput || (JUCE_LV2_ENABLE_DEV_FEATURES && JucePlugin_WantsLV2TimePos))
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
LV2_Handle juceLV2_Instantiate(const LV2_Descriptor* /*descriptor*/, double sampleRate, const char* /*bundlePath*/, const LV2_Feature* const* features)
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
    JUCE_AUTORELEASEPOOL
    {
        const MessageManagerLock mmLock;
        JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
        wrapper->doCleanup();
        delete wrapper;
    }

    if (activePlugins.size() == 0 && activeUIs.size() == 0)
    {
       #if JUCE_LINUX
        SharedMessageThread::deleteInstance();
       #endif

        if (needsGUIShutdown)
        {
            shutdownJuce_GUI();
            needsGUIShutdown = false;
        }
    }
}

//==============================================================================
#if JucePlugin_WantsLV2State
LV2_State_Status juceLV2_Save(LV2_Handle instance, LV2_State_Store_Function store, LV2_State_Handle handle, uint32_t /*flags*/, const LV2_Feature* const* /*features*/)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    jassert(wrapper);

    const LV2_URID_Map* uridMap = wrapper->getURIDMap();

 #if JucePlugin_WantsLV2StateString
    String stateData = wrapper->getStateString();

    store (handle,
           uridMap->map(uridMap->handle, JUCE_LV2_STATE_STRING_URI),
           stateData.toUTF8().getAddress(),
           stateData.toUTF8().sizeInBytes(),
           uridMap->map(uridMap->handle, LV2_ATOM__String),
           LV2_STATE_IS_POD|LV2_STATE_IS_PORTABLE);
 #else
    MemoryBlock chunkMemory;
    chunkMemory.setSize (0);
    wrapper->getStateBinary(chunkMemory);

    store (handle,
           uridMap->map(uridMap->handle, JUCE_LV2_STATE_BINARY_URI),
           chunkMemory.getData(),
           chunkMemory.getSize(),
           uridMap->map(uridMap->handle, LV2_ATOM__Chunk),
           LV2_STATE_IS_POD|LV2_STATE_IS_PORTABLE);
 #endif

    return LV2_STATE_SUCCESS;
}

LV2_State_Status juceLV2_Restore(LV2_Handle instance, LV2_State_Retrieve_Function retrieve, LV2_State_Handle handle, uint32_t flags, const LV2_Feature* const* /*features*/)
{
    JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)instance;
    jassert(wrapper);

    const LV2_URID_Map* uridMap = wrapper->getURIDMap();

    size_t size;
    uint32 type;
    const void* data = retrieve (handle,
                             #if JucePlugin_WantsLV2StateString
                                 uridMap->map(uridMap->handle, JUCE_LV2_STATE_STRING_URI),
                             #else
                                 uridMap->map(uridMap->handle, JUCE_LV2_STATE_BINARY_URI),
                             #endif
                                 &size, &type, &flags);

 #if JucePlugin_WantsLV2StateString
    if (type == uridMap->map(uridMap->handle, LV2_ATOM__String))
    {
        String stateData = String(CharPointer_UTF8(static_cast<const char*>(data)));
        wrapper->setStateString(stateData);
 #else
    if (type == uridMap->map(uridMap->handle, LV2_ATOM__Chunk))
    {
        wrapper->setStateBinary(data, size);
 #endif
        return LV2_STATE_SUCCESS;
    }

    return LV2_STATE_ERR_BAD_TYPE;
}
#endif

const void* juceLV2_ExtensionData(const char* uri)
{
#if JucePlugin_WantsLV2State
    static const LV2_State_Interface state = { juceLV2_Save, juceLV2_Restore };
    if (strcmp(uri, LV2_STATE__interface) == 0)
        return &state;
#else
    (void)uri;
#endif
    return nullptr;
}

//==============================================================================
// LV2 UI descriptor functions
LV2UI_Handle juceLV2UI_Instantiate(LV2UI_Write_Function writeFunction, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features, JuceLV2UIWrapper::UIType uiType)
{
    if (activeUIs.size() == 0)
        initialiseJuce_GUI();

    const MessageManagerLock mmLock;
    needsGUIShutdown = true;

#if JucePlugin_WantsLV2InstanceAccess
    for (uint32 i = 0; features[i]; i++)
    {
        if (strcmp(features[i]->URI, LV2_INSTANCE_ACCESS_URI) == 0 && features[i]->data)
        {
            JuceLV2Wrapper* wrapper = (JuceLV2Wrapper*)features[i]->data;
            return wrapper->getUI(writeFunction, controller, widget, features, uiType);
        }
    }
    std::cerr << "Host does not support instance-access, cannot use UI" << std::endl;
    return nullptr;
#else
    // this is a fake filter!
    AudioProcessor* const filter = createPluginFilter();
    JuceLV2UIWrapper* uiWrapper = new JuceLV2UIWrapper(filter, writeFunction, controller, widget, features, uiType);
    return uiWrapper;
#endif
}

LV2UI_Handle juceLV2UI_InstantiateExternal(const LV2UI_Descriptor* /*descriptor*/, const char* /*plugin_uri*/, const char* /*bundle_path*/, LV2UI_Write_Function writeFunction, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features)
{
    return juceLV2UI_Instantiate(writeFunction, controller, widget, features, JuceLV2UIWrapper::UI_EXTERNAL);
}

LV2UI_Handle juceLV2UI_InstantiateX11(const LV2UI_Descriptor* /*descriptor*/, const char* /*plugin_uri*/, const char* /*bundle_path*/, LV2UI_Write_Function writeFunction, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features)
{
    return juceLV2UI_Instantiate(writeFunction, controller, widget, features, JuceLV2UIWrapper::UI_X11);
}

void juceLV2UI_Cleanup(LV2UI_Handle instance)
{
    JUCE_AUTORELEASEPOOL
    {
        const MessageManagerLock mmLock;
        JuceLV2UIWrapper* uiWrapper = (JuceLV2UIWrapper*)instance;
        uiWrapper->doCleanup();

#if ! JucePlugin_WantsLV2InstanceAccess
        delete uiWrapper;
#endif
    }

    if (activePlugins.size() == 0 && activeUIs.size() == 0)
    {
       #if JUCE_LINUX
        SharedMessageThread::deleteInstance();
       #endif

        if (needsGUIShutdown)
        {
            shutdownJuce_GUI();
            needsGUIShutdown = false;
        }
    }
}

void juceLV2UI_PortEvent(LV2UI_Handle instance, uint32 portIndex, uint32 bufferSize, uint32 format, const void* buffer)
{
    const MessageManagerLock mmLock;
    JuceLV2UIWrapper* uiWrapper = (JuceLV2UIWrapper*)instance;

    if (uiWrapper && format == 0 && bufferSize == sizeof (float))
    {
        const float value = *(const float*)buffer;
        uiWrapper->doPortEvent(portIndex, value);
    }
}

const void* juceLV2UI_ExtensionData(const char* /*uri*/)
{
    return nullptr;
}

//==============================================================================
// static LV2 Descriptor objects
static const LV2_Descriptor JuceLv2Plugin = {
    JucePlugin_LV2URI,
    juceLV2_Instantiate,
    juceLV2_ConnectPort,
    juceLV2_Activate,
    juceLV2_Run,
    juceLV2_Deactivate,
    juceLV2_Cleanup,
    juceLV2_ExtensionData
};

static const LV2UI_Descriptor JuceLv2UI_External = {
    JucePlugin_LV2URI "#ExternalUI",
    juceLV2UI_InstantiateExternal,
    juceLV2UI_Cleanup,
    juceLV2UI_PortEvent,
    juceLV2UI_ExtensionData
};

static const LV2UI_Descriptor JuceLv2UI_ExternalOld = {
    JucePlugin_LV2URI "#ExternalOldUI",
    juceLV2UI_InstantiateExternal,
    juceLV2UI_Cleanup,
    juceLV2UI_PortEvent,
    juceLV2UI_ExtensionData
};

static const LV2UI_Descriptor JuceLv2UI_X11 = {
    JucePlugin_LV2URI "#X11UI",
    juceLV2UI_InstantiateX11,
    juceLV2UI_Cleanup,
    juceLV2UI_PortEvent,
    juceLV2UI_ExtensionData
};

//==============================================================================
// Mac startup code..
#if JUCE_MAC

    extern "C" __attribute__ ((visibility("default"))) void lv2_generate_ttl()
    {
        createTtlFiles();
    }

    extern "C" __attribute__ ((visibility("default"))) const LV2_Descriptor* lv2_descriptor(uint32 index)
    {
        initialiseMac();
        return (index == 0) ? &JuceLv2Plugin : nullptr;
    }

    extern "C" __attribute__ ((visibility("default"))) const LV2UI_Descriptor* lv2ui_descriptor(uint32 index)
    {
        initialiseMac();
        switch (index)
        {
          case 0:
            return &JuceLv2UI_External;
          case 1:
            return &JuceLv2UI_ExternalOld;
          default:
            return nullptr;
        }
    }

//==============================================================================
// Linux startup code..
#elif JUCE_LINUX

    extern "C" __attribute__ ((visibility("default"))) void lv2_generate_ttl()
    {
        createTtlFiles();
    }

    extern "C" __attribute__ ((visibility("default"))) const LV2_Descriptor* lv2_descriptor(uint32 index)
    {
        SharedMessageThread::getInstance();
        return (index == 0) ? &JuceLv2Plugin : nullptr;
    }

    extern "C" __attribute__ ((visibility("default"))) const LV2UI_Descriptor* lv2ui_descriptor(uint32 index)
    {
        SharedMessageThread::getInstance();
        switch (index)
        {
          case 0:
            return &JuceLv2UI_External;
          case 1:
            return &JuceLv2UI_ExternalOld;
#if JUCE_LINUX
          case 2:
            return &JuceLv2UI_X11;
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

    extern "C" __declspec (dllexport) void lv2_generate_ttl()
    {
        createTtlFiles();
    }

    extern "C" __declspec (dllexport) const LV2_Descriptor* lv2_descriptor(uint32 index)
    {
        return (index == 0) ? &JuceLv2Plugin : nullptr;
    }

    extern "C" __declspec (dllexport) const LV2UI_Descriptor* lv2ui_descriptor(uint32 index)
    {
        switch (index)
        {
          case 0:
            return &JuceLv2UI_External;
          case 1:
            return &JuceLv2UI_ExternalOld;
          default:
            return nullptr;
        }
    }

#endif

#endif
