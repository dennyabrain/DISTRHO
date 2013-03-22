/*
  ==============================================================================

   Juce LV2 Wrapper, based on VST Wrapper code

  ==============================================================================
*/

// TESTING, remove later
#define JucePlugin_Build_LV2 1
#define JucePlugin_LV2URI "http://arcticanaudio.com/plugins/thefunction"
#include "JucePluginMain.h"

// Your project must contain an AppConfig.h file with your project-specific settings in it,
// and your header search path must make it accessible to the module's files.
#include "AppConfig.h"

#include "../utility/juce_CheckSettingMacros.h"

#if JucePlugin_Build_LV2

// LV2 includes..
#include "includes/lv2.h"
#include "includes/ui.h"

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
    Juce LV2 handle
*/
class JuceLv2Wrapper : public AudioPlayHead
{
public:
    //==============================================================================
    JuceLv2Wrapper (double sampleRate_, const LV2_Feature* const* features)
        : numInChans (JucePlugin_MaxNumInputChannels),
          numOutChans (JucePlugin_MaxNumOutputChannels),
          sampleRate (sampleRate_)
    {
       #if JUCE_LINUX
        MessageManagerLock mmLock;
       #endif

        filter = createPluginFilterOfType (AudioProcessor::wrapperType_VST);
        jassert(filter != nullptr);

        filter->setPlayConfigDetails (numInChans, numOutChans, 0, 0);
        filter->setPlayHead (this);

#if JucePlugin_WantsMidiInput
        portMidiIn = nullptr;
#endif
#if JucePlugin_ProducesMidiOutput
        portMidiOut = nullptr;
#endif
        portLatency = nullptr;

        for (int i=0; i < numInChans; i++)
            portAudioIns[i] = nullptr;
        for (int i=0; i < numOutChans; i++)
            portAudioOuts[i] = nullptr;

        portControls.insertMultiple(0, nullptr, filter->getNumParameters());

        activePlugins.add (this);
    }

    ~JuceLv2Wrapper ()
    {
    }

    //==============================================================================
    // LV2 calls
    void lv2ConnectPort (uint32 port, void* dataLocation)
    {
    }

    void lv2Activate()
    {
    }

    void lv2Deactivate()
    {
    }

    void lv2Run (uint32 sampleCount)
    {
    }

    //==============================================================================
    // Juce calls
    bool getCurrentPosition (AudioPlayHead::CurrentPositionInfo& info)
    {
        return false;
    }

private:
    ScopedPointer<AudioProcessor> filter;
    int numInChans, numOutChans;

    uint32 bufferSize;
    double sampleRate;
    //AudioPlayHead::CurrentPositionInfo posInfo;

    // LV2 ports location
#if JucePlugin_WantsMidiInput
    LV2_Atom_Sequence* portMidiIn;
#endif
#if JucePlugin_ProducesMidiOutput
    LV2_Atom_Sequence* portMidiOut;
#endif
    float* portLatency;
    float* portAudioIns[JucePlugin_MaxNumInputChannels];
    float* portAudioOuts[JucePlugin_MaxNumOutputChannels];
    Array<float*> portControls;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLv2Wrapper)
};

//==============================================================================
// LV2 descriptor functions

static LV2_Handle juceLV2_Instantiate(const LV2_Descriptor*, double sampleRate, const char*, const LV2_Feature* const* features)
{
    return new JuceLv2Wrapper(sampleRate, features);
}

#define handlePtr ((JuceLv2Wrapper*)handle)

static void juceLV2_ConnectPort(LV2_Handle handle, uint32 port, void* dataLocation)
{
    handlePtr->lv2ConnectPort(port, dataLocation);
}

static void juceLV2_Activate(LV2_Handle handle)
{
    handlePtr->lv2Activate();
}

static void juceLV2_Run(LV2_Handle handle, uint32 sampleCount)
{
    handlePtr->lv2Run(sampleCount);
}

static void juceLV2_Deactivate(LV2_Handle handle)
{
    handlePtr->lv2Deactivate();
}

static void juceLV2_Cleanup(LV2_Handle handle)
{
    delete handlePtr;
}

#undef handlePtr

static const void* juceLV2_ExtensionData(const char* uri)
{
    return nullptr;
}

//==============================================================================
// LV2 UI descriptor functions

static LV2UI_Handle juceLV2UI_Instantiate(LV2UI_Write_Function writeFunction, LV2UI_Controller controller,
                                          LV2UI_Widget* widget, const LV2_Feature* const* features, bool isExternal)
{
    return nullptr;
}

static LV2UI_Handle juceLV2UI_InstantiateExternal(const LV2UI_Descriptor*, const char*, const char*, LV2UI_Write_Function writeFunction,
                                                  LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features)
{
    return juceLV2UI_Instantiate(writeFunction, controller, widget, features, true);
}

static LV2UI_Handle juceLV2UI_InstantiateParent(const LV2UI_Descriptor*, const char*, const char*, LV2UI_Write_Function writeFunction,
                                                LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features)
{
    return juceLV2UI_Instantiate(writeFunction, controller, widget, features, false);
}

static void juceLV2UI_Cleanup(LV2UI_Handle instance)
{
}

static void juceLV2UI_PortEvent(LV2UI_Handle instance, uint32 portIndex, uint32 bufferSize, uint32 format, const void* buffer)
{
}

static const void* juceLV2UI_ExtensionData(const char* uri)
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

static const LV2UI_Descriptor JuceLv2UI_Parent = {
    JucePlugin_LV2URI "#ParentUI",
    juceLV2UI_InstantiateParent,
    juceLV2UI_Cleanup,
    juceLV2UI_PortEvent,
    juceLV2UI_ExtensionData
};

#if ! JUCE_WINDOWS
 #define JUCE_EXPORTED_FUNCTION extern "C" __attribute__ ((visibility("default")))
#endif

//==============================================================================
// Mac startup code..
#if JUCE_MAC

    JUCE_EXPORTED_FUNCTION const LV2_Descriptor* lv2_descriptor(uint32 index);
    JUCE_EXPORTED_FUNCTION const LV2_Descriptor* lv2_descriptor(uint32 index)
    {
        initialiseMac();
        return (index == 0) ? &JuceLv2Plugin : nullptr;
    }

    JUCE_EXPORTED_FUNCTION const LV2UI_Descriptor* lv2ui_descriptor(uint32 index);
    JUCE_EXPORTED_FUNCTION const LV2UI_Descriptor* lv2ui_descriptor(uint32 index)
    {
        initialiseMac();
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

//==============================================================================
// Linux startup code..
#elif JUCE_LINUX

    JUCE_EXPORTED_FUNCTION const LV2_Descriptor* lv2_descriptor(uint32 index);
    JUCE_EXPORTED_FUNCTION const LV2_Descriptor* lv2_descriptor(uint32 index)
    {
        SharedMessageThread::getInstance();
        return (index == 0) ? &JuceLv2Plugin : nullptr;
    }

    JUCE_EXPORTED_FUNCTION const LV2UI_Descriptor* lv2ui_descriptor(uint32 index);
    JUCE_EXPORTED_FUNCTION const LV2UI_Descriptor* lv2ui_descriptor(uint32 index)
    {
        SharedMessageThread::getInstance();
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

    // don't put initialiseJuce_GUI or shutdownJuce_GUI in these... it will crash!
    __attribute__((constructor)) void myPluginInit() {}
    __attribute__((destructor))  void myPluginFini() {}

//==============================================================================
// Win32 startup code..
#elif JUCE_WINDOWS

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
            return &JuceLv2UI_Parent;
        default:
            return nullptr;
        }
    }
#endif

#endif
