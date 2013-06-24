/*
  ==============================================================================

   Build options for juced static library

  ==============================================================================
*/

#ifndef __DISTRHO_JUCED_APPCONFIG_H__
#define __DISTRHO_JUCED_APPCONFIG_H__

#include "../build-audio-basics/AppConfig.h"

#if JucePlugin_Build_Standalone
 #include "../build-audio-devices_full/AppConfig.h"
#else
 #include "../build-audio-devices/AppConfig.h"
#endif

#include "../build-audio-formats/AppConfig.h"
#include "../build-audio-processors/AppConfig.h"
#include "../build-audio-utils/AppConfig.h"
#include "../build-core/AppConfig.h"
#include "../build-data-structures/AppConfig.h"
#include "../build-events/AppConfig.h"
#include "../build-graphics/AppConfig.h"
#include "../build-gui-basics/AppConfig.h"
#include "../build-gui-extra/AppConfig.h"

//=============================================================================
/** Config: JUCE_LASH
        Enables LASH support on Linux.
        Not enabled by default.
*/
#define JUCE_LASH 0

/** Config: JUCE_USE_GLX
        Enable this under Linux to use GLX for fast openGL rendering with alpha
        compositing support over a composite manager (compiz / xcompmgr).
        Not enabled by default.
*/
#define JUCE_USE_GLX 0

/** Config: JUCE_PLUGINHOST_LADSPA
        Enabling this builds support for LADSPA audio plugins.
        Not enabled by default.
*/
#define JUCE_PLUGINHOST_LADSPA 0

/** Config: JUCE_SUPPORT_SQLITE
        Setting this allows the build to use SQLITE libraries for access a self-contained,
        serverless, zero-configuration, transactional SQL database engine.
        Not enabled by default.
*/
#define JUCE_SUPPORT_SQLITE 0

/** Config: JUCE_SUPPORT_SCRIPTING
        Setting this allows the build to use Angelscript library for using scripting
        inside the juce library itself
        Not enabled by default.
*/
#define JUCE_SUPPORT_SCRIPTING 0

/** Config: JUCETICE_INCLUDE_ANGELSCRIPT_CODE
 Enables direct inclusion of the angelscript library.
 Enabled by default.
*/
#define JUCETICE_INCLUDE_ANGELSCRIPT_CODE  0

/** Config: JUCETICE_INCLUDE_CURL_CODE
 Enables direct inclusion of curl.
 
 // Currently not available //
*/
#define JUCETICE_INCLUDE_CURL_CODE 0

#endif // __DISTRHO_JUCED_APPCONFIG_H__
