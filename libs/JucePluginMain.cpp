/*
  ==============================================================================

   Main symbol/entry for juce plugins

  ==============================================================================
*/

#if JucePlugin_Build_AU
// TODO

#elif JucePlugin_Build_LV2
// TODO

#elif JucePlugin_Build_RTAS
// TODO

#elif JucePlugin_Build_VST
#define JUCE_USE_VSTSDK_2_4 1
#include "juce-modules/source/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp"

#elif JucePlugin_Build_Standalone
#include "juce-custom/Standalone/juce_StandaloneFilterApplication.cpp"

#else
#error Invalid configuration

#endif
