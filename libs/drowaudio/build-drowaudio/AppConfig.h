/*
  ==============================================================================

   Build options for juced static library

  ==============================================================================
*/

#ifndef __DISTRHO_DROWAUDIO_APPCONFIG_H__
#define __DISTRHO_DROWAUDIO_APPCONFIG_H__

#include "../build-audio-basics/AppConfig.h"
#include "../build-audio-devices/AppConfig.h"
#include "../build-audio-formats/AppConfig.h"
#include "../build-audio-utils/AppConfig.h"
#include "../build-core/AppConfig.h"
#include "../build-data-structures/AppConfig.h"
#include "../build-events/AppConfig.h"
#include "../build-graphics/AppConfig.h"
#include "../build-gui-basics/AppConfig.h"

//=============================================================================
/** Config: DROWAUDIO_USE_FFTREAL
    Enables the FFTReal library. By default this is enabled except on the Mac
    where the Accelerate framework is preferred. However, if you do explicity 
    enable this setting fftreal can be used for testing purposes.
 */
#if JUCE_MAC
 #define DROWAUDIO_USE_FFTREAL 0
#else
 #define DROWAUDIO_USE_FFTREAL 1
#endif

/** Config: DROWAUDIO_USE_SOUNDTOUCH
    Enables the SoundTouch library and the associated SoundTouch classes for
    independant pitch and tempo scaling. By default this is enabled.
 */
#define DROWAUDIO_USE_SOUNDTOUCH 1

/** Config: DROWAUDIO_USE_CURL
    Enables the cURL library and the associated network classes. By default
    this is enabled.
 */
#define DROWAUDIO_USE_CURL 0

#endif // __DISTRHO_DROWAUDIO_APPCONFIG_H__
