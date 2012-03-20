/*
  ==============================================================================

   Build options for juce-audio-utils static library

  ==============================================================================
*/

#ifndef __DISTRHO_JUCE_AUDIO_UTILS_APPCONFIG_H__
#define __DISTRHO_JUCE_AUDIO_UTILS_APPCONFIG_H__

#include "../build-gui-basics/AppConfig.h"
#if JucePlugin_Build_Standalone
 #include "../build-audio-devices_full/AppConfig.h"
#else
 #include "../build-audio-devices/AppConfig.h"
#endif
#include "../build-audio-formats/AppConfig.h"
#include "../build-audio-processors/AppConfig.h"

#endif // __DISTRHO_JUCE_AUDIO_UTILS_APPCONFIG_H__
