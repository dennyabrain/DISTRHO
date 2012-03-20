/*
  ==============================================================================

   Main symbol/entry for juce plugins

  ==============================================================================
*/

#include "JucePluginMain.h"

#if JucePlugin_Build_AU
#include "modules/juce_audio_plugin_client/AU/juce_AU_Wrapper.mm"

#elif JucePlugin_Build_LV2
#include "juce_LV2_Wrapper.cpp"

#elif JucePlugin_Build_RTAS
#include "modules/juce_audio_plugin_client/RTAS/juce_RTAS_Wrapper.cpp"

#elif JucePlugin_Build_VST
#define JUCE_USE_VSTSDK_2_4 1
#include "modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp"

#elif JucePlugin_Build_Standalone
#include "juce_StandaloneFilterApplication.cpp"

#else
#error Invalid configuration

#endif
