/*
  ==============================================================================

   Main symbol/entry for juce plugins

  ==============================================================================
*/

#ifndef __DISTRHO_PLUGIN_MAIN_H__
#define __DISTRHO_PLUGIN_MAIN_H__

#include "AppConfig.h"
#include "JucePluginCharacteristics.h"

#include "../source/modules/juce_core/juce_core.h"
#include "../source/modules/juce_audio_basics/juce_audio_basics.h"
#include "../source/modules/juce_audio_processors/juce_audio_processors.h"
//#include "../source/modules/juce_cryptography/juce_cryptography.h"
#include "../source/modules/juce_data_structures/juce_data_structures.h"
#include "../source/modules/juce_events/juce_events.h"
#include "../source/modules/juce_graphics/juce_graphics.h"
#include "../source/modules/juce_gui_basics/juce_gui_basics.h"
//#include "../source/modules/juce_gui_extra/juce_gui_extra.h"
//#include "../source/modules/juce_opengl/juce_opengl.h"
//#include "../source/modules/juce_video/juce_video.h"

#if JucePlugin_Build_Standalone
#include "../source/modules/juce_audio_devices/juce_audio_devices.h"
#include "../source/modules/juce_audio_formats/juce_audio_formats.h"
#include "../source/modules/juce_audio_utils/juce_audio_utils.h"
#endif

#endif // __DISTRHO_PLUGIN_MAIN_H__
