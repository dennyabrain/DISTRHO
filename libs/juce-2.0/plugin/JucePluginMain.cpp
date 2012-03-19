/*
  ==============================================================================

   Main symbol/entry for juce plugins

  ==============================================================================
*/

#include "JucePluginMain.h"

#if JucePlugin_Build_AU
// TODO

#elif JucePlugin_Build_LV2
// TODO

#elif JucePlugin_Build_RTAS
// TODO

#elif JucePlugin_Build_VST
#define JUCE_USE_VSTSDK_2_4 1
#include "../source/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp"

#elif JucePlugin_Build_Standalone
#include "juce_StandaloneFilterApplication.cpp"

#else
#error Invalid configuration

#endif
