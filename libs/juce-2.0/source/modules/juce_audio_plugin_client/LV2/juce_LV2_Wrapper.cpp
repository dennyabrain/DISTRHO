/*
  ==============================================================================

   Juce LV2 Wrapper

  ==============================================================================
*/

// Your project must contain an AppConfig.h file with your project-specific settings in it,
// and your header search path must make it accessible to the module's files.
#include "AppConfig.h"

#include "../utility/juce_CheckSettingMacros.h"

#if 1//JucePlugin_Build_LV2

/*
 * Available macros:
 * - JucePlugin_LV2Category
 * - JucePlugin_WantsLV2State
 * - JucePlugin_WantsLV2StateString
 * - JucePlugin_WantsLV2Presets
 * - JucePlugin_WantsLV2TimePos
 */

#if JucePlugin_WantsLV2StateString && ! JucePlugin_WantsLV2State
 #undef JucePlugin_WantsLV2State
 #define JucePlugin_WantsLV2State 1
#endif

#if JUCE_LINUX
 #include <X11/Xlib.h>
 #undef KeyPress
#endif

#include <fstream>
#include <iostream>

// LV2 includes..
#include "includes/lv2.h"
#include "includes/atom.h"
#include "includes/atom-util.h"
#include "includes/buf-size.h"
#include "includes/instance-access.h"
#include "includes/midi.h"
#include "includes/options.h"
#include "includes/port-props.h"
#include "includes/presets.h"
#include "includes/state.h"
#include "includes/time.h"
#include "includes/ui.h"
#include "includes/units.h"
#include "includes/urid.h"
#include "includes/lv2_external_ui.h"
#include "includes/lv2_programs.h"

#include "../utility/juce_IncludeModuleHeaders.h"

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

#if JucePlugin_WantsLV2State && ! JucePlugin_WantsLV2StateString
 // FIXME - juce base64 algorithm is broken
 #include "base64/Base64.cpp"
#endif

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
const String getBinaryName()
{
    return String(JucePlugin_Name).replace(" ", "_");
}

/** Returns plugin type, defined in AppConfig.h or JucePluginCharacteristics.h */
const String getPluginType()
{
    String pluginType;
#ifdef JucePlugin_LV2Category
    pluginType  = "lv2:" JucePlugin_LV2Category;
    pluginType += ", ";
#elif JucePlugin_IsSynth
    pluginType  = "lv2:InstrumentPlugin, ";
#endif
    pluginType += "lv2:Plugin";
    return pluginType;
}

static Array<String> usedSymbols;

/** Converts a parameter name to an LV2 compatible symbol. */
const String nameToSymbol(const String& name, const uint32 portIndex)
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

    // Do not allow identical symbols
    if (usedSymbols.contains(symbol))
    {
        int offset = 2;
        String offsetStr = "_2";
        symbol += offsetStr;

        while (usedSymbols.contains(symbol))
        {
            offset += 1;
            String newOffsetStr = "_" + String(offset);
            symbol = symbol.replace(offsetStr, newOffsetStr);
            offsetStr = newOffsetStr;
        }
    }
    usedSymbols.add(symbol);

    return symbol;
}

/** Prevents NaN or out of 0.0<->1.0 bounds parameter values. */
float safeParamValue(float value)
{
    if (std::isnan(value))
        value = 0.0f;
    else if (value < 0.0f)
        value = 0.0f;
    else if (value > 1.0f)
        value = 1.0f;
    return value;
}

/** Create the manifest.ttl file contents */
const String makeManifestFile(AudioProcessor* const filter, const String& binary)
{
    String text;

    // Header
    text += "@prefix lv2:  <" LV2_CORE_PREFIX "> .\n";
    text += "@prefix pset: <" LV2_PRESETS_PREFIX "> .\n";
    text += "@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .\n";
    text += "@prefix ui:   <" LV2_UI_PREFIX "> .\n";
    text += "\n";

    // Plugin
    text += "<" JucePlugin_LV2URI ">\n";
    text += "    a lv2:Plugin ;\n";
    text += "    lv2:binary <" + binary + PLUGIN_EXT "> ;\n";
    text += "    rdfs:seeAlso <" + binary + ".ttl> .\n";
    text += "\n";

    // UIs
    if (filter->hasEditor())
    {
        text += "<" JucePlugin_LV2URI "#ExternalUI>\n";
        text += "    a <" LV2_EXTERNAL_UI_URI "> ;\n";
        text += "    ui:binary <" + binary + PLUGIN_EXT "> ;\n";
        text += "    lv2:requiredFeature <" LV2_INSTANCE_ACCESS_URI "> ;\n";
        text += "    lv2:extensionData <" LV2_PROGRAMS__UIInterface "> .\n";
        text += "\n";

        text += "<" JucePlugin_LV2URI "#ParentUI>\n";
#if JUCE_MAC
        text += "    a ui:CocoaUI ;\n";
#elif JUCE_LINUX
        text += "    a ui:X11UI ;\n";
#elif JUCE_WINDOWS
        text += "    a ui:WindowsUI ;\n";
#endif
        text += "    ui:binary <" + binary + PLUGIN_EXT "> ;\n";
        text += "    lv2:requiredFeature <" LV2_INSTANCE_ACCESS_URI "> ;\n";
        text += "    lv2:optionalFeature ui:noUserResize ;\n";
        text += "    lv2:extensionData <" LV2_PROGRAMS__UIInterface "> .\n";
        text += "\n";
    }

#if JucePlugin_WantsLV2Presets
    // Presets
    for (int i = 0; i < filter->getNumPrograms(); i++)
    {
        text += "<" JucePlugin_LV2URI "#preset" + String::formatted("%03i", i+1) + ">\n";
        text += "    a pset:Preset ;\n";
        text += "    lv2:appliesTo <" JucePlugin_LV2URI "> ;\n";
        text += "    rdfs:seeAlso <presets.ttl> .\n";
        text += "\n";
    }
#endif

    return text;
}

/** Create the -plugin-.ttl file contents */
const String makePluginFile(AudioProcessor* const filter)
{
    String text;

    // Header
    text += "@prefix atom: <" LV2_ATOM_PREFIX "> .\n";
    text += "@prefix doap: <http://usefulinc.com/ns/doap#> .\n";
    text += "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n";
    text += "@prefix lv2:  <" LV2_CORE_PREFIX "> .\n";
    text += "@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .\n";
    text += "@prefix ui:   <" LV2_UI_PREFIX "> .\n";
    text += "@prefix unit: <" LV2_UNITS_PREFIX "> .\n";
    text += "\n";

    // Plugin
    text += "<" JucePlugin_LV2URI ">\n";
    text += "    a " + getPluginType() + " ;\n";
    text += "    lv2:requiredFeature <" LV2_BUF_SIZE__boundedBlockLength "> ,\n";
    text += "                        <" LV2_URID__map "> ;\n";
    text += "    lv2:extensionData <" LV2_OPTIONS__interface "> ,\n";
    text += "                      <" LV2_STATE__interface "> ,\n";
    text += "                      <" LV2_PROGRAMS__Interface "> ;\n";
    text += "\n";

    // UIs
    if (filter->hasEditor())
    {
        text += "    ui:ui <" JucePlugin_LV2URI "#ExternalUI> ,\n";
        text += "          <" JucePlugin_LV2URI "#ParentUI> ;\n";
        text += "\n";
    }

    uint32 portIndex = 0;

#if (JucePlugin_WantsMidiInput || JucePlugin_WantsLV2TimePos)
    // MIDI input
    text += "    lv2:port [\n";
    text += "        a lv2:InputPort, atom:AtomPort ;\n";
    text += "        atom:bufferType atom:Sequence ;\n";
 #if JucePlugin_WantsMidiInput
    text += "        atom:supports <" LV2_MIDI__MidiEvent "> ;\n";
 #endif
 #if JucePlugin_WantsLV2TimePos
    text += "        atom:supports <" LV2_TIME__Position "> ;\n";
 #endif
    text += "        lv2:index " + String(portIndex++) + " ;\n";
    text += "        lv2:symbol \"lv2_events_in\" ;\n";
    text += "        lv2:name \"Events Input\" ;\n";
    text += "        lv2:designation lv2:control ;\n";
 #if ! JucePlugin_IsSynth
    text += "        lv2:portProperty lv2:connectionOptional ;\n";
 #endif
    text += "    ] ;\n";
    text += "\n";
#endif

#if JucePlugin_ProducesMidiOutput
    // MIDI output
    text += "    lv2:port [\n";
    text += "        a lv2:OutputPort, atom:AtomPort ;\n";
    text += "        atom:bufferType atom:Sequence ;\n";
    text += "        atom:supports <" LV2_MIDI__MidiEvent "> ;\n";
    text += "        lv2:index " + String(portIndex++) + " ;\n";
    text += "        lv2:symbol \"lv2_midi_out\" ;\n";
    text += "        lv2:name \"MIDI Output\" ;\n";
    text += "    ] ;\n";
    text += "\n";
#endif

    // Freewheel and latency ports
    text += "    lv2:port [\n";
    text += "        a lv2:InputPort, lv2:ControlPort ;\n";
    text += "        lv2:index " + String(portIndex++) + " ;\n";
    text += "        lv2:symbol \"lv2_freewheel\" ;\n";
    text += "        lv2:name \"Freewheel\" ;\n";
    text += "        lv2:default 0.0 ;\n";
    text += "        lv2:minimum 0.0 ;\n";
    text += "        lv2:maximum 1.0 ;\n";
    text += "        lv2:designation <" LV2_CORE__freeWheeling "> ;\n";
    text += "        lv2:portProperty lv2:toggled ;\n";
    text += "    ] ,\n";
    text += "    [\n";
    text += "        a lv2:OutputPort, lv2:ControlPort ;\n";
    text += "        lv2:index " + String(portIndex++) + " ;\n";
    text += "        lv2:symbol \"lv2_latency\" ;\n";
    text += "        lv2:name \"Latency\" ;\n";
    text += "        lv2:designation <" LV2_CORE__latency "> ;\n";
    text += "    ] ;\n";
    text += "\n";

    // Audio inputs
    for (int i=0; i < JucePlugin_MaxNumInputChannels; ++i)
    {
        if (i == 0)
            text += "    lv2:port [\n";
        else
            text += "    [\n";

        text += "        a lv2:InputPort, lv2:AudioPort ;\n";
        text += "        lv2:index " + String(portIndex++) + " ;\n";
        text += "        lv2:symbol \"lv2_audio_in_" + String(i+1) + "\" ;\n";
        text += "        lv2:name \"Audio Input " + String(i+1) + "\" ;\n";

        if (i+1 == JucePlugin_MaxNumInputChannels)
            text += "    ] ;\n\n";
        else
            text += "    ] ,\n";
    }

    // Audio outputs
    for (int i=0; i < JucePlugin_MaxNumOutputChannels; ++i)
    {
        if (i == 0)
            text += "    lv2:port [\n";
        else
            text += "    [\n";

        text += "        a lv2:OutputPort, lv2:AudioPort ;\n";
        text += "        lv2:index " + String(portIndex++) + " ;\n";
        text += "        lv2:symbol \"lv2_audio_out_" + String(i+1) + "\" ;\n";
        text += "        lv2:name \"Audio Output " + String(i+1) + "\" ;\n";

        if (i+1 == JucePlugin_MaxNumOutputChannels)
            text += "    ] ;\n\n";
        else
            text += "    ] ,\n";
    }

    // Parameters
    for (int i=0; i < filter->getNumParameters(); ++i)
    {
        if (i == 0)
            text += "    lv2:port [\n";
        else
            text += "    [\n";

        text += "        a lv2:InputPort, lv2:ControlPort ;\n";
        text += "        lv2:index " + String(portIndex++) + " ;\n";
        text += "        lv2:symbol \"" + nameToSymbol(filter->getParameterName(i), i) + "\" ;\n";

        if (filter->getParameterName(i).isNotEmpty())
            text += "        lv2:name \"" + filter->getParameterName(i) + "\" ;\n";
        else
            text += "        lv2:name \"Port " + String(i+1) + "\" ;\n";

        text += "        lv2:default " + String::formatted("%f", safeParamValue(filter->getParameter(i))) + " ;\n";
        text += "        lv2:minimum 0.0 ;\n";
        text += "        lv2:maximum 1.0 ;\n";

        String label(filter->getParameterLabel(i));

        if (label.isNotEmpty())
        {
            text += "        units:unit [\n";
            text += "            a units:Unit ;\n";
            text += "            rdfs:label   \"" + label + "\" ;\n";
            text += "            units:symbol \"" + label + "\" ;\n";
            text += "            units:render \"%f " + label + "\" ;\n";
            text += "        ] ;\n";
        }

        if (! filter->isParameterAutomatable(i))
            text += "        lv2:portProperty <" LV2_PORT_PROPS__expensive "> ;\n";

        if (i+1 == filter->getNumParameters())
            text += "    ] ;\n\n";
        else
            text += "    ] ,\n";
    }

    text += "    doap:name \"" JucePlugin_Name "\" ;\n";
    text += "    doap:maintainer [ foaf:name \"" JucePlugin_Manufacturer "\" ] .\n";

    return text;
}

/** Create the presets.ttl file contents */
const String makePresetsFile(AudioProcessor* const filter)
{
    String text;

    // Header
    text += "@prefix atom:  <" LV2_ATOM_PREFIX "> .\n";
    text += "@prefix lv2:   <" LV2_CORE_PREFIX "> .\n";
    text += "@prefix pset:  <" LV2_PRESETS_PREFIX "> .\n";
    text += "@prefix rdf:   <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n";
    text += "@prefix rdfs:  <http://www.w3.org/2000/01/rdf-schema#> .\n";
    text += "@prefix state: <" LV2_STATE_PREFIX "> .\n";
    text += "@prefix xsd:   <http://www.w3.org/2001/XMLSchema#> .\n";
    text += "\n";

    // Presets
    const int numPrograms = filter->getNumPrograms();

    for (int i = 0; i < numPrograms; ++i)
    {
        std::cout << "\nSaving preset " << i+1 << "/" << numPrograms+1 << "...";
        std::cout.flush();

        String preset;

        // Label
        filter->setCurrentProgram(i);
        preset += "<" JucePlugin_LV2URI "#preset" + String::formatted("%03i", i+1) + "> a pset:Preset ;\n";
        preset += "    rdfs:label \"" + filter->getProgramName(i) + "\" ;\n";

        // State
#if JucePlugin_WantsLV2State
        preset += "    state:state [\n";
 #if JucePlugin_WantsLV2StateString
        preset += "        <" JUCE_LV2_STATE_STRING_URI ">\n";
        preset += "\"\"\"\n";
        preset += filter->getStateInformationString().replace("\r\n","\n");
        preset += "\"\"\"\n";
 #else
        MemoryBlock chunkMemory;
        filter->getCurrentProgramStateInformation(chunkMemory);
        const String chunkString(Base64Encode(chunkMemory));

        preset += "        <" JUCE_LV2_STATE_BINARY_URI "> [\n";
        preset += "            a atom:Chunk ;\n";
        preset += "            rdf:value \"" + chunkString + "\"^^xsd:base64Binary ;\n";
        preset += "        ] ;\n";
 #endif
        if (filter->getNumParameters() > 0)
            preset += "    ] ;\n\n";
        else
            preset += "    ] .\n\n";
#endif

        // Port values
        usedSymbols.clear();

        for (int j=0; j < filter->getNumParameters(); j++)
        {
              if (j == 0)
                preset += "    lv2:port [\n";
            else
                preset += "    [\n";

            preset += "        lv2:symbol \"" + nameToSymbol(filter->getParameterName(j), j) + "\" ;\n";
            preset += "        pset:value " + String::formatted("%f", safeParamValue(filter->getParameter(j))) + " ;\n";

            if (j+1 == filter->getNumParameters())
                preset += "    ] ";
            else
                preset += "    ] ,\n";
        }
        preset += ".\n\n";

        text += preset;
    }

    return text;
}

/** Creates manifest.ttl, plugin.ttl and presets.ttl files */
void createLv2Files()
{
    ScopedJuceInitialiser_GUI juceInitialiser;
    ScopedPointer<AudioProcessor> filter (createPluginFilterOfType (AudioProcessor::wrapperType_VST)); // FIXME

    String binary(getBinaryName());
    String binaryTTL(binary + ".ttl");

    std::cout << "Writing manifest.ttl..."; std::cout.flush();
    std::fstream manifest("manifest.ttl", std::ios::out);
    manifest << makeManifestFile(filter, binary) << std::endl;
    manifest.close();
    std::cout << " done!" << std::endl;

    std::cout << "Writing " << binary << ".ttl..."; std::cout.flush();
    std::fstream plugin(binaryTTL.toUTF8(), std::ios::out);
    plugin << makePluginFile(filter) << std::endl;
    plugin.close();
    std::cout << " done!" << std::endl;

#if JucePlugin_WantsLV2Presets
    std::cout << "Writing presets.ttl..."; std::cout.flush();
    std::fstream presets("presets.ttl", std::ios::out);
    presets << makePresetsFile(filter) << std::endl;
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

//==============================================================================
/**
    Lightweight DocumentWindow subclass for external ui
*/
class JuceLv2ExternalUIWindow : public DocumentWindow
{
public:
    /** Creates a Document Window wrapper */
    JuceLv2ExternalUIWindow (AudioProcessorEditor* editor, const String& title) :
            DocumentWindow (title, Colours::white, DocumentWindow::minimiseButton | DocumentWindow::closeButton, false),
            closed (false),
            lastPos (0, 0)
    {
        setOpaque (true);
        setContentNonOwned (editor, true);
        setSize (editor->getWidth(), editor->getHeight());
        setUsingNativeTitleBar (true);

#if ! JUCE_LINUX
        // FIXME - does not work properly on Linux
        setAlwaysOnTop( true);
#endif
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
        setTopLeftPosition (lastPos.getX(), lastPos.getY());
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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLv2ExternalUIWindow);
};

//==============================================================================
/**
    Juce LV2 External UI handle
*/
class JuceLv2ExternalUIWrapper : public LV2_External_UI_Widget
{
public:
    JuceLv2ExternalUIWrapper (AudioProcessorEditor* editor, const String& title)
        : window (editor, title)
    {
        // external UI calls
        run  = doRun;
        show = doShow;
        hide = doHide;
    }

    ~JuceLv2ExternalUIWrapper()
    {
        if (window.isOnDesktop())
            window.removeFromDesktop();
    }

    void close()
    {
        window.closeButtonPressed();
    }

    bool isClosed()
    {
        return window.isClosed();
    }

    void reset(const String& title)
    {
        window.reset();
        window.setName(title);
    }

    void repaint()
    {
        window.repaint();
    }

    Point<int> getScreenPosition()
    {
        if (window.isClosed())
            return window.getLastPos();
        else
            return window.getScreenPosition();
    }

    void setScreenPos(int x, int y)
    {
        if (! window.isClosed())
            window.setTopLeftPosition(x, y);
    }

    //==============================================================================
    static void doRun (LV2_External_UI_Widget* _this_)
    {
        const MessageManagerLock mmLock;
        JuceLv2ExternalUIWrapper* self = (JuceLv2ExternalUIWrapper*) _this_;

        if (! self->isClosed())
            self->window.repaint();
    }

    static void doShow (LV2_External_UI_Widget* _this_)
    {
        const MessageManagerLock mmLock;
        JuceLv2ExternalUIWrapper* self = (JuceLv2ExternalUIWrapper*) _this_;

        if (! self->isClosed())
        {
            if (! self->window.isOnDesktop())
                self->window.addToDesktop();

            self->window.restoreLastPos();
            self->window.setVisible(true);
        }
    }

    static void doHide (LV2_External_UI_Widget* _this_)
    {
        const MessageManagerLock mmLock;
        JuceLv2ExternalUIWrapper* self = (JuceLv2ExternalUIWrapper*) _this_;

        if (! self->isClosed())
        {
            self->window.saveLastPos();
            self->window.setVisible(false);
        }
    }

private:
    JuceLv2ExternalUIWindow window;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLv2ExternalUIWrapper);
};

//==============================================================================
/**
    Juce LV2 Parent UI container, listens for resize events and passes them to ui-resize
*/
class JuceLv2ParentContainer : public Component
{
public:
    JuceLv2ParentContainer (AudioProcessorEditor* editor, const LV2UI_Resize* uiResize_)
        : uiResize(uiResize_)
    {
        setOpaque (true);
        editor->setOpaque (true);
        setBounds (editor->getBounds());

        editor->setTopLeftPosition (0, 0);
        addAndMakeVisible (editor);
    }

    ~JuceLv2ParentContainer()
    {
    }

    void paint (Graphics&) {}
    void paintOverChildren (Graphics&) {}

    void childBoundsChanged (Component* child)
    {
        const int cw = child->getWidth();
        const int ch = child->getHeight();

#if JUCE_LINUX
        XResizeWindow (display, (Window) getWindowHandle(), cw, ch);
#else
        setSize (cw, ch);
#endif

        if (uiResize != nullptr)
            uiResize->ui_resize (uiResize->handle, cw, ch);
    }

    void reset (const LV2UI_Resize* uiResize_)
    {
        uiResize = uiResize_;

        if (uiResize != nullptr)
            uiResize->ui_resize (uiResize->handle, getWidth(), getHeight());
    }

private:
    //==============================================================================
    const LV2UI_Resize* uiResize;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLv2ParentContainer);
};

//==============================================================================
/**
    Juce LV2 UI handle
*/
class JuceLv2UIWrapper : public AudioProcessorListener,
                         public Timer
{
public:
    JuceLv2UIWrapper (AudioProcessor* filter_, LV2UI_Write_Function writeFunction_, LV2UI_Controller controller_,
                      LV2UI_Widget* widget, const LV2_Feature* const* features, bool isExternal_)
        : filter (filter_),
          writeFunction (writeFunction_),
          controller (controller_),
          isExternal (isExternal_),
          controlPortOffset (0),
          lastProgramCount (0),
          uiTouch (nullptr),
          programsHost (nullptr),
          externalUIHost (nullptr),
          lastExternalUIPos (-1, -1),
          uiResize (nullptr)
    {
        jassert (filter != nullptr);

        filter->addListener(this);

        if (filter->hasEditor())
        {
            editor = filter->createEditorIfNeeded();

            if (editor == nullptr)
            {
                *widget = nullptr;
                return;
            }
        }

        for (int i = 0; features[i] != nullptr; ++i)
        {
            if (strcmp(features[i]->URI, LV2_UI__touch) == 0)
                uiTouch = (const LV2UI_Touch*)features[i]->data;

            else if (strcmp(features[i]->URI, LV2_PROGRAMS__Host) == 0)
                programsHost = (const LV2_Programs_Host*)features[i]->data;
        }

        if (isExternal)
        {
            resetExternalUI (features);

            if (externalUIHost != nullptr)
            {
                String title(filter->getName());

                if (externalUIHost->plugin_human_id != nullptr)
                    title = externalUIHost->plugin_human_id;

                externalUI = new JuceLv2ExternalUIWrapper(editor, title);
                *widget = externalUI;
                startTimer (100);
            }
            else
            {
                *widget = nullptr;
            }
        }
        else
        {
            resetParentUI (features);

            if (parentContainer != nullptr)
               *widget = parentContainer->getWindowHandle();
            else
               *widget = nullptr;
        }

#if (JucePlugin_WantsMidiInput || JucePlugin_WantsLV2TimePos)
        controlPortOffset += 1;
#endif
#if JucePlugin_ProducesMidiOutput
        controlPortOffset += 1;
#endif
        controlPortOffset += 2; // freewheel and sampleRate
        controlPortOffset += JucePlugin_MaxNumInputChannels;
        controlPortOffset += JucePlugin_MaxNumOutputChannels;

        lastProgramCount = filter->getNumPrograms();
    }

    ~JuceLv2UIWrapper()
    {
        PopupMenu::dismissAllActiveMenus();

        filter->removeListener(this);

        parentContainer = nullptr;
        externalUI = nullptr;
        externalUIHost = nullptr;

        if (editor != nullptr)
        {
            filter->editorBeingDeleted (editor);
            editor = nullptr;
        }
    }

    //==============================================================================
    // LV2 core calls

    void lv2Cleanup()
    {
        if (isExternal)
        {
            if (isTimerRunning())
                stopTimer();

            externalUIHost = nullptr;

            if (externalUI != nullptr)
            {
                lastExternalUIPos = externalUI->getScreenPosition();
                externalUI->close();
            }
        }
        else
        {
            if (parentContainer != nullptr && parentContainer->isOnDesktop())
                parentContainer->removeFromDesktop();
        }
    }

    //==============================================================================
    // Juce calls

    void audioProcessorParameterChanged (AudioProcessor*, int index, float newValue)
    {
        if (writeFunction != nullptr && controller != nullptr)
            writeFunction (controller, index + controlPortOffset, sizeof (float), 0, &newValue);
    }

    void audioProcessorChanged (AudioProcessor*)
    {
        if (filter != nullptr && programsHost != nullptr)
        {
            if (filter->getNumPrograms() != lastProgramCount)
                programsHost->program_changed (programsHost->handle, -1);
            else
                programsHost->program_changed (programsHost->handle, filter->getCurrentProgram());

            lastProgramCount = filter->getNumPrograms();
        }
    }

    void audioProcessorParameterChangeGestureBegin (AudioProcessor*, int parameterIndex)
    {
        if (uiTouch != nullptr)
            uiTouch->touch (uiTouch->handle, parameterIndex + controlPortOffset, true);
    }

    void audioProcessorParameterChangeGestureEnd (AudioProcessor*, int parameterIndex)
    {
        if (uiTouch != nullptr)
            uiTouch->touch (uiTouch->handle, parameterIndex + controlPortOffset, false);
    }

    void timerCallback()
    {
        if (externalUI != nullptr && externalUI->isClosed())
        {
            if (externalUIHost != nullptr)
                externalUIHost->ui_closed (controller);

            if (isTimerRunning())
                stopTimer();
        }
    }

    //==============================================================================
    void resetIfNeeded (LV2UI_Write_Function writeFunction_, LV2UI_Controller controller_, LV2UI_Widget* widget,
                        const LV2_Feature* const* features)
    {
        writeFunction = writeFunction_;
        controller = controller_;
        uiTouch = nullptr;
        programsHost = nullptr;

        for (int i = 0; features[i] != nullptr; ++i)
        {
            if (strcmp(features[i]->URI, LV2_UI__touch) == 0)
                uiTouch = (const LV2UI_Touch*)features[i]->data;

            else if (strcmp(features[i]->URI, LV2_PROGRAMS__Host) == 0)
                programsHost = (const LV2_Programs_Host*)features[i]->data;
        }

        if (isExternal)
        {
            resetExternalUI (features);
            *widget = externalUI;
        }
        else
        {
            resetParentUI (features);
            *widget = parentContainer->getWindowHandle();
        }
    }

    void repaint()
    {
        const MessageManagerLock mmLock;

        if (editor != nullptr)
            editor->repaint();

        if (parentContainer != nullptr)
            parentContainer->repaint();

        if (externalUI != nullptr)
            externalUI->repaint();
    }

private:
    AudioProcessor* const filter;
    ScopedPointer<AudioProcessorEditor> editor;

    LV2UI_Write_Function writeFunction;
    LV2UI_Controller controller;
    const bool isExternal;

    uint32 controlPortOffset;
    int lastProgramCount;

    const LV2UI_Touch* uiTouch;
    const LV2_Programs_Host* programsHost;

    ScopedPointer<JuceLv2ExternalUIWrapper> externalUI;
    const LV2_External_UI_Host* externalUIHost;
    Point<int> lastExternalUIPos;

    ScopedPointer<JuceLv2ParentContainer> parentContainer;
    const LV2UI_Resize* uiResize;

    //==============================================================================
    void resetExternalUI (const LV2_Feature* const* features)
    {
        externalUIHost = nullptr;

        for (int i = 0; features[i] != nullptr; ++i)
        {
            if (strcmp(features[i]->URI, LV2_EXTERNAL_UI__Host) == 0)
            {
                externalUIHost = (const LV2_External_UI_Host*)features[i]->data;
                break;
            }
        }

        if (externalUI != nullptr)
        {
            String title(filter->getName());

            if (externalUIHost->plugin_human_id != nullptr)
                title = externalUIHost->plugin_human_id;

            if (lastExternalUIPos.getX() != -1 && lastExternalUIPos.getY() != -1)
                externalUI->setScreenPos(lastExternalUIPos.getX(), lastExternalUIPos.getY());

            externalUI->reset(title);
            startTimer (100);
        }
    }

    void resetParentUI (const LV2_Feature* const* features)
    {
        void* parent = nullptr;
        uiResize = nullptr;

        for (int i = 0; features[i] != nullptr; ++i)
        {
            if (strcmp(features[i]->URI, LV2_UI__parent) == 0)
                parent = features[i]->data;

            else if (strcmp(features[i]->URI, LV2_UI__resize) == 0)
                uiResize = (const LV2UI_Resize*)features[i]->data;
        }

        if (parent != nullptr)
        {
            if (parentContainer == nullptr)
                parentContainer = new JuceLv2ParentContainer (editor, uiResize);

            parentContainer->setVisible (false);

            if (parentContainer->isOnDesktop())
                parentContainer->removeFromDesktop();

#if (JUCE_MAC || JUCE_WINDOWS)
            parentContainer->addToDesktop (0, parent);
#elif JUCE_LINUX
            parentContainer->addToDesktop (0);

            Window hostWindow = (Window) parent;
            Window editorWnd  = (Window) parentContainer->getWindowHandle();
            XReparentWindow (display, editorWnd, hostWindow, 0, 0);
#endif

            parentContainer->reset (uiResize);
            parentContainer->setVisible (true);
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLv2UIWrapper)
};

//==============================================================================
/**
    Juce LV2 handle
*/
class JuceLv2Wrapper : public AudioPlayHead
{
public:
    //==============================================================================
    JuceLv2Wrapper (double sampleRate_, const LV2_Feature* const* features)
        : numInChans (JucePlugin_MaxNumInputChannels),
          numOutChans (JucePlugin_MaxNumOutputChannels),
          bufferSize (2048),
          sampleRate (sampleRate_),
          uridMap (nullptr),
          uridAtomSequence (0),
          uridMidiEvent (0),
          uridTimePos (0)
    {
        filter = createPluginFilterOfType (AudioProcessor::wrapperType_VST); // FIXME
        jassert (filter != nullptr);

        filter->setPlayConfigDetails (numInChans, numOutChans, 0, 0);
        filter->setPlayHead (this);

#if (JucePlugin_WantsMidiInput || JucePlugin_WantsLV2TimePos)
        portEventsIn = nullptr;
#endif
#if JucePlugin_ProducesMidiOutput
        portMidiOut = nullptr;
#endif

        portFreewheel = nullptr;
        portLatency   = nullptr;

        for (int i=0; i < numInChans; i++)
            portAudioIns[i] = nullptr;
        for (int i=0; i < numOutChans; i++)
            portAudioOuts[i] = nullptr;

        portControls.insertMultiple (0, nullptr, filter->getNumParameters());

        for (int i=0; i < filter->getNumParameters(); i++)
            lastControlValues.add (filter->getParameter(i));

        curPosInfo.resetToDefault();

        // we need URID_Map first
        for (int i=0; features[i] != nullptr; ++i)
        {
            if (strcmp(features[i]->URI, LV2_URID__map) == 0)
            {
                uridMap = (const LV2_URID_Map*)features[i]->data;
                break;
            }
        }

        // we require uridMap to work properly (it's set as required feature)
        jassert (uridMap != nullptr);

        if (uridMap != nullptr)
        {
            for (int i=0; features[i] != nullptr; ++i)
            {
                if (strcmp(features[i]->URI, LV2_OPTIONS__options) == 0)
                {
                    const LV2_Options_Option* options = (const LV2_Options_Option*)features[i]->data;

                    for (int j=0; options[j].key != 0; ++j)
                    {
                        if (options[j].key == uridMap->map(uridMap->handle, LV2_BUF_SIZE__maxBlockLength))
                        {
                            if (options[j].type == uridMap->map(uridMap->handle, LV2_ATOM__Int))
                                bufferSize = *(int*)options[j].value;
                            else
                                std::cerr << "Host provides maxBlockLength but has wrong value type" << std::endl;

                            break;
                        }
                    }
                    break;
                }
            }

            uridAtomSequence = uridMap->map(uridMap->handle, LV2_ATOM__Sequence);
            uridTimePos = uridMap->map(uridMap->handle, LV2_TIME__Position);
            uridMidiEvent = uridMap->map(uridMap->handle, LV2_MIDI__MidiEvent);
        }

        progDesc.bank = 0;
        progDesc.program = 0;
        progDesc.name = nullptr;

        activePlugins.add (this);
    }

    ~JuceLv2Wrapper ()
    {
        ui = nullptr;
        filter = nullptr;

        if (progDesc.name != nullptr)
            free((void*)progDesc.name);

        portControls.clear();
        lastControlValues.clear();

        jassert (activePlugins.contains (this));
        activePlugins.removeFirstMatchingValue (this);
    }

    //==============================================================================
    // LV2 core calls

    void lv2ConnectPort (uint32 portId, void* dataLocation)
    {
        uint32 index = 0;

#if (JucePlugin_WantsMidiInput || JucePlugin_WantsLV2TimePos)
        if (portId == index++)
        {
            portEventsIn = (LV2_Atom_Sequence*)dataLocation;
            return;
        }
#endif

#if JucePlugin_ProducesMidiOutput
        if (portId == index++)
        {
            portMidiOut = (LV2_Atom_Sequence*)dataLocation;
            return;
        }
#endif

        if (portId == index++)
        {
            portFreewheel = (float*)dataLocation;
            return;
        }

        if (portId == index++)
        {
            portLatency = (float*)dataLocation;
            return;
        }

        for (int i=0; i < numInChans; ++i)
        {
            if (portId == index++)
            {
                portAudioIns[i] = (float*)dataLocation;
                return;
            }
        }

        for (int i=0; i < numOutChans; ++i)
        {
            if (portId == index++)
            {
                portAudioOuts[i] = (float*)dataLocation;
                return;
            }
        }

        for (int i=0; i < filter->getNumParameters(); ++i)
        {
            if (portId == index++)
            {
                portControls.set(i, (float*)dataLocation);
                return;
            }
        }
    }

    void lv2Activate()
    {
        jassert (filter != nullptr);

        filter->prepareToPlay (sampleRate, bufferSize);

        channels.calloc (numInChans + numOutChans);

#if (JucePlugin_WantsMidiInput || JucePlugin_ProducesMidiOutput)
        midiEvents.ensureSize (2048);
        midiEvents.clear();
#endif
    }

    void lv2Deactivate()
    {
        jassert (filter != nullptr);

        filter->releaseResources();

        channels.free();
    }

    void lv2Run (uint32 sampleCount)
    {
        jassert (filter != nullptr);

        if (portLatency != nullptr)
            *portLatency = filter->getLatencySamples();

        if (portFreewheel != nullptr)
            filter->setNonRealtime (*portFreewheel > 0.5f);

        if (sampleCount == 0)
        {
            /**
               LV2 pre-roll
               Hosts might use this to force plugins to update its output control ports.
               (plugins can only access port locations during run) */
            return;
        }

        // Check for updated parameters
        {
            float curValue;

            for (int i = 0; i < portControls.size(); ++i)
            {
                if (portControls[i] != nullptr)
                {
                    curValue = *portControls[i];

                    if (lastControlValues[i] != curValue)
                    {
                        filter->setParameter(i, curValue);
                        lastControlValues.setUnchecked(i, curValue);
                    }
                }
            }
        }

        {
            const ScopedLock sl (filter->getCallbackLock());

            if (filter->isSuspended() && false)
            {
                for (int i = 0; i < numOutChans; ++i)
                    zeromem (portAudioOuts[i], sizeof (float) * sampleCount);
            }
            else
            {
                int i;
                for (i = 0; i < numOutChans; ++i)
                {
                    channels[i] = portAudioOuts[i];

                    if (i < numInChans && portAudioIns[i] != portAudioOuts[i])
                        FloatVectorOperations::copy (portAudioOuts [i], portAudioIns[i], sampleCount);
                }

                for (; i < numInChans; ++i)
                    channels [i] = portAudioIns[i];

#if (JucePlugin_WantsMidiInput || JucePlugin_WantsLV2TimePos)
                if (portEventsIn != nullptr)
                {
                    midiEvents.clear();

                    LV2_ATOM_SEQUENCE_FOREACH(portEventsIn, iter)
                    {
                        const LV2_Atom_Event* event = (const LV2_Atom_Event*)iter;

                        if (event == nullptr)
                            continue;

 #if JucePlugin_WantsMidiInput
                        if (event->body.type == uridMidiEvent)
                        {
                            if (event->time.frames >= sampleCount)
                               break;

                            const uint8* data = (const uint8*)(event + 1);
                            midiEvents.addEvent(data, event->body.size, event->time.frames);
                            continue;
                        }
 #endif
 #if JucePlugin_WantsLV2TimePos
                        if (event->body.type == uridTimePos)
                        {
                            // TODO
                        }
 #endif
                    }
                }
#endif
                {
                    AudioSampleBuffer chans (channels, jmax (numInChans, numOutChans), sampleCount);
                    filter->processBlock (chans, midiEvents);
                }
            }
        }

        if (! midiEvents.isEmpty())
        {
#if JucePlugin_ProducesMidiOutput
            if (portMidiOut != nullptr)
            {
                const uint8* midiEventData;
                int midiEventSize, midiEventPosition;
                MidiBuffer::Iterator i (midiEvents);

                uint32_t size, offset = 0;
                LV2_Atom_Event* aev;

                portMidiOut->atom.size = 0;
                portMidiOut->atom.type = uridAtomSequence;
                portMidiOut->body.unit = 0;
                portMidiOut->body.pad  = 0;

                while (i.getNextEvent (midiEventData, midiEventSize, midiEventPosition))
                {
                    jassert (midiEventPosition >= 0 && midiEventPosition < sampleCount);

                    aev = (LV2_Atom_Event*)((char*)LV2_ATOM_CONTENTS(LV2_Atom_Sequence, portMidiOut) + offset);
                    aev->time.frames = midiEventPosition;
                    aev->body.type   = uridMidiEvent;
                    aev->body.size   = midiEventSize;
                    memcpy(LV2_ATOM_BODY(&aev->body), midiEventData, midiEventSize);

                    size    = lv2_atom_pad_size(sizeof(LV2_Atom_Event) + midiEventSize);
                    offset += size;
                    portMidiOut->atom.size += size;
                }
            }
#endif
            midiEvents.clear();
        }
    }

    //==============================================================================
    // LV2 extended calls

    uint32_t lv2GetOptions (LV2_Options_Option* options)
    {
        // currently unused
        return LV2_OPTIONS_SUCCESS;
    }

    uint32_t lv2SetOptions (const LV2_Options_Option* options)
    {
        for (int j=0; options[j].key != 0; ++j)
        {
            if (options[j].key == uridMap->map(uridMap->handle, LV2_BUF_SIZE__maxBlockLength))
            {
                if (options[j].type == uridMap->map(uridMap->handle, LV2_ATOM__Int))
                    bufferSize = *(int*)options[j].value;
                else
                    std::cerr << "Host changed maxBlockLength but with wrong value type" << std::endl;
            }
            else if (options[j].key == uridMap->map(uridMap->handle, LV2_CORE__sampleRate))
            {
                if (options[j].type == uridMap->map(uridMap->handle, LV2_ATOM__Double))
                    sampleRate = *(double*)options[j].value;
                else
                    std::cerr << "Host changed sampleRate but with wrong value type" << std::endl;
            }
        }

        return LV2_OPTIONS_SUCCESS;
    }

    const LV2_Program_Descriptor* lv2GetProgram (uint32_t index)
    {
        jassert (filter != nullptr);

        if (progDesc.name != nullptr)
        {
            free((void*)progDesc.name);
            progDesc.name = nullptr;
        }

        if ((int)index < filter->getNumPrograms())
        {
            progDesc.bank    = index / 128;
            progDesc.program = index % 128;
            progDesc.name    = strdup(filter->getProgramName(index).toUTF8());
            return &progDesc;
        }

        return nullptr;
    }

    void lv2SelectProgram (uint32_t bank, uint32_t program)
    {
        jassert (filter != nullptr);

        int realProgram = bank * 128 + program;

        if (realProgram < filter->getNumPrograms())
        {
            filter->setCurrentProgram(realProgram);

            // update input control ports now
            for (int i = 0; i < portControls.size(); ++i)
            {
                float value = filter->getParameter(i);

                if (portControls[i] != nullptr)
                    *portControls[i] = value;

                lastControlValues.set(i, value);
            }
        }
    }

    LV2_State_Status lv2SaveState (LV2_State_Store_Function store, LV2_State_Handle stateHandle)
    {
        jassert (filter != nullptr);

#if JucePlugin_WantsLV2StateString
        String stateData(filter->getStateInformationString().replace("\r\n","\n"));
        CharPointer_UTF8 charData(stateData.toUTF8());

        store (stateHandle,
               uridMap->map(uridMap->handle, JUCE_LV2_STATE_STRING_URI),
               charData.getAddress(),
               charData.sizeInBytes(),
               uridMap->map(uridMap->handle, LV2_ATOM__String),
               LV2_STATE_IS_POD|LV2_STATE_IS_PORTABLE);
#else
        MemoryBlock chunkMemory;
        filter->getCurrentProgramStateInformation (chunkMemory);

        store (stateHandle,
               uridMap->map(uridMap->handle, JUCE_LV2_STATE_BINARY_URI),
               chunkMemory.getData(),
               chunkMemory.getSize(),
               uridMap->map(uridMap->handle, LV2_ATOM__Chunk),
               LV2_STATE_IS_POD|LV2_STATE_IS_PORTABLE);
#endif

        return LV2_STATE_SUCCESS;
    }

    LV2_State_Status lv2RestoreState (LV2_State_Retrieve_Function retrieve, LV2_State_Handle stateHandle, uint32_t flags)
    {
        jassert (filter != nullptr);

        size_t size;
        uint32 type;
        const void* data = retrieve (stateHandle,
#if JucePlugin_WantsLV2StateString
                                     uridMap->map(uridMap->handle, JUCE_LV2_STATE_STRING_URI),
#else
                                     uridMap->map(uridMap->handle, JUCE_LV2_STATE_BINARY_URI),
#endif
                                     &size, &type, &flags);

#if JucePlugin_WantsLV2StateString
        if (type == uridMap->map (uridMap->handle, LV2_ATOM__String))
        {
            String stateData (CharPointer_UTF8(static_cast<const char*>(data)));
            filter->setStateInformationString (stateData);

            if (ui != nullptr)
                ui->repaint();

            return LV2_STATE_SUCCESS;
        }
#else
        if (type == uridMap->map (uridMap->handle, LV2_ATOM__Chunk))
        {
            filter->setCurrentProgramStateInformation (data, size);

            if (ui != nullptr)
                ui->repaint();

            return LV2_STATE_SUCCESS;
        }
#endif

        return LV2_STATE_ERR_BAD_TYPE;
    }

    //==============================================================================
    // Juce calls

    bool getCurrentPosition (AudioPlayHead::CurrentPositionInfo& info)
    {
        return false;
    }

    //==============================================================================
    JuceLv2UIWrapper* getUI (LV2UI_Write_Function writeFunction, LV2UI_Controller controller, LV2UI_Widget* widget,
                             const LV2_Feature* const* features, bool isExternal)
    {
        if (ui != nullptr)
            ui->resetIfNeeded (writeFunction, controller, widget, features);
        else
            ui = new JuceLv2UIWrapper (filter, writeFunction, controller, widget, features, isExternal);

        return ui;
    }

private:
    ScopedPointer<AudioProcessor> filter;
    ScopedPointer<JuceLv2UIWrapper> ui;
    HeapBlock<float*> channels;
    MidiBuffer midiEvents;
    int numInChans, numOutChans;

#if (JucePlugin_WantsMidiInput || JucePlugin_WantsLV2TimePos)
    LV2_Atom_Sequence* portEventsIn;
#endif
#if JucePlugin_ProducesMidiOutput
    LV2_Atom_Sequence* portMidiOut;
#endif
    float* portFreewheel;
    float* portLatency;
    float* portAudioIns[JucePlugin_MaxNumInputChannels];
    float* portAudioOuts[JucePlugin_MaxNumOutputChannels];
    Array<float*> portControls;

    uint32 bufferSize;
    double sampleRate;
    Array<float> lastControlValues;
    AudioPlayHead::CurrentPositionInfo curPosInfo;

    const LV2_URID_Map* uridMap;
    LV2_URID uridAtomSequence;
    LV2_URID uridMidiEvent;
    LV2_URID uridTimePos;

    LV2_Program_Descriptor progDesc;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLv2Wrapper)
};

//==============================================================================
// LV2 descriptor functions

static LV2_Handle juceLV2_Instantiate (const LV2_Descriptor*, double sampleRate, const char*, const LV2_Feature* const* features)
{
    JUCE_AUTORELEASEPOOL

    if (activePlugins.size() == 0)
    {
        initialiseJuce_GUI();
#if JUCE_LINUX
        SharedMessageThread::getInstance();
#endif
    }

#if JUCE_LINUX
    MessageManagerLock mmLock;
#endif

    return new JuceLv2Wrapper (sampleRate, features);
}

#define handlePtr ((JuceLv2Wrapper*)handle)

static void juceLV2_ConnectPort (LV2_Handle handle, uint32 port, void* dataLocation)
{
    handlePtr->lv2ConnectPort (port, dataLocation);
}

static void juceLV2_Activate (LV2_Handle handle)
{
    handlePtr->lv2Activate();
}

static void juceLV2_Run( LV2_Handle handle, uint32 sampleCount)
{
    handlePtr->lv2Run (sampleCount);
}

static void juceLV2_Deactivate (LV2_Handle handle)
{
    handlePtr->lv2Deactivate();
}

static void juceLV2_Cleanup (LV2_Handle handle)
{
    JUCE_AUTORELEASEPOOL

    {
#if JUCE_LINUX
        MessageManagerLock mmLock;
#endif
        delete handlePtr;
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
// LV2 extended functions

static uint32_t juceLV2_getOptions (LV2_Handle handle, LV2_Options_Option* options)
{
    return handlePtr->lv2GetOptions(options);
}

static uint32_t juceLV2_setOptions (LV2_Handle handle, const LV2_Options_Option* options)
{
    return handlePtr->lv2SetOptions(options);
}

static const LV2_Program_Descriptor* juceLV2_getProgram (LV2_Handle handle, uint32_t index)
{
    return handlePtr->lv2GetProgram(index);
}

static void juceLV2_selectProgram (LV2_Handle handle, uint32_t bank, uint32_t program)
{
    handlePtr->lv2SelectProgram(bank, program);
}

static LV2_State_Status juceLV2_SaveState(LV2_Handle handle, LV2_State_Store_Function store, LV2_State_Handle stateHandle,
                                          uint32_t, const LV2_Feature* const*)
{
    return handlePtr->lv2SaveState(store, stateHandle);
}

static LV2_State_Status juceLV2_RestoreState (LV2_Handle handle, LV2_State_Retrieve_Function retrieve, LV2_State_Handle stateHandle,
                                              uint32_t flags, const LV2_Feature* const*)
{
    return handlePtr->lv2RestoreState(retrieve, stateHandle, flags);
}

#undef handlePtr

static const void* juceLV2_ExtensionData (const char* uri)
{
    static const LV2_Options_Interface options = { juceLV2_getOptions, juceLV2_setOptions };
    static const LV2_Programs_Interface programs = { juceLV2_getProgram, juceLV2_selectProgram };
    static const LV2_State_Interface state = { juceLV2_SaveState, juceLV2_RestoreState };

    if (strcmp(uri, LV2_OPTIONS__interface) == 0)
        return &options;
    if (strcmp(uri, LV2_PROGRAMS__Interface) == 0)
        return &programs;
    if (strcmp(uri, LV2_STATE__interface) == 0)
        return &state;

    return nullptr;
}

//==============================================================================
// LV2 UI descriptor functions

static LV2UI_Handle juceLV2UI_Instantiate (LV2UI_Write_Function writeFunction, LV2UI_Controller controller,
                                           LV2UI_Widget* widget, const LV2_Feature* const* features, bool isExternal)
{
    JUCE_AUTORELEASEPOOL
    const MessageManagerLock mmLock;

    for (int i = 0; features[i] != nullptr; i++)
    {
        if (strcmp(features[i]->URI, LV2_INSTANCE_ACCESS_URI) == 0 && features[i]->data != nullptr)
        {
            JuceLv2Wrapper* wrapper = (JuceLv2Wrapper*)features[i]->data;
            return wrapper->getUI(writeFunction, controller, widget, features, isExternal);
        }
    }

    std::cerr << "Host does not support instance-access, cannot use UI" << std::endl;
    return nullptr;
}

static LV2UI_Handle juceLV2UI_InstantiateExternal (const LV2UI_Descriptor*, const char*, const char*, LV2UI_Write_Function writeFunction,
                                                   LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features)
{
    return juceLV2UI_Instantiate(writeFunction, controller, widget, features, true);
}

static LV2UI_Handle juceLV2UI_InstantiateParent (const LV2UI_Descriptor*, const char*, const char*, LV2UI_Write_Function writeFunction,
                                                 LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features)
{
    return juceLV2UI_Instantiate(writeFunction, controller, widget, features, false);
}

static void juceLV2UI_Cleanup (LV2UI_Handle handle)
{
    const MessageManagerLock mmLock;

    ((JuceLv2UIWrapper*)handle)->lv2Cleanup();
}

static const void* juceLV2UI_ExtensionData (const char*)
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
    nullptr,
    juceLV2UI_ExtensionData
};

static const LV2UI_Descriptor JuceLv2UI_Parent = {
    JucePlugin_LV2URI "#ParentUI",
    juceLV2UI_InstantiateParent,
    juceLV2UI_Cleanup,
    nullptr,
    juceLV2UI_ExtensionData
};

#if JUCE_WINDOWS
 #define JUCE_EXPORTED_FUNCTION extern "C" __declspec (dllexport)
#else
 #define JUCE_EXPORTED_FUNCTION extern "C" __attribute__ ((visibility("default")))
#endif

//==============================================================================
// startup code..

LV2_SYMBOL_EXPORT const LV2_Descriptor* lv2_descriptor(uint32 index)
{
#if JUCE_MAC
    initialiseMac();
#endif
    return (index == 0) ? &JuceLv2Plugin : nullptr;
}

LV2_SYMBOL_EXPORT const LV2UI_Descriptor* lv2ui_descriptor(uint32 index)
{
#if JUCE_MAC
    initialiseMac();
#endif
    switch (index)
    {
    case 0:
        return &JuceLv2UI_External;
    case 1:
        return &JuceLv2UI_Parent;
    default:
        return nullptr;
    }
}

JUCE_EXPORTED_FUNCTION void lv2_generate_ttl();
JUCE_EXPORTED_FUNCTION void lv2_generate_ttl()
{
#if JUCE_MAC
    initialiseMac();
#endif
    createLv2Files();
}

#endif
