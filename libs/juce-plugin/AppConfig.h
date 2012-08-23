/*
  ==============================================================================

   Build options for juce based plugins

  ==============================================================================
*/

#ifndef __DISTRHO_PLUGIN_APPCONFIG_H__
#define __DISTRHO_PLUGIN_APPCONFIG_H__

#include "../build-core/AppConfig.h"
#include "../build-audio-basics/AppConfig.h"
#include "../build-audio-formats/AppConfig.h"
#include "../build-audio-processors/AppConfig.h"
#include "../build-audio-utils/AppConfig.h"
//#include "../build-cryptography/AppConfig.h"
#include "../build-data-structures/AppConfig.h"
#include "../build-events/AppConfig.h"
#include "../build-graphics/AppConfig.h"
#include "../build-gui-basics/AppConfig.h"
//#include "../build-gui-extra/AppConfig.h"
//#include "../build-opengl/AppConfig.h"
//#include "../build-video/AppConfig.h"

#if JucePlugin_Build_Standalone
# include "../build-audio-devices_full/AppConfig.h"
#else
# include "../build-audio-devices/AppConfig.h"
#endif

#endif // __DISTRHO_PLUGIN_APPCONFIG_H__
