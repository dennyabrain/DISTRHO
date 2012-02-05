/*
  ==============================================================================

   Build options for juce-video static library

  ==============================================================================
*/

#ifndef __DISTRHO_JUCE_VIDEO_APPCONFIG_H__
#define __DISTRHO_JUCE_VIDEO_APPCONFIG_H__

#include "../build-core/AppConfig.h"
#include "../build-gui-extra/AppConfig.h"

//=============================================================================
/** Config: JUCE_DIRECTSHOW
    Enables DirectShow media-streaming architecture (MS Windows only).
*/
#if WINDOWS
 #define JUCE_DIRECTSHOW 0
#endif

/** Config: JUCE_MEDIAFOUNDATION
    Enables Media Foundation multimedia platform (Windows Vista and above).
*/
#if WINDOWS
 #define JUCE_MEDIAFOUNDATION 0
#endif

/** Config: JUCE_QUICKTIME
    Enables the QuickTimeMovieComponent class (Mac and Windows).
    If you're building on Windows, you'll need to have the Apple QuickTime SDK
    installed, and its header files will need to be on your include path.
*/
#define JUCE_QUICKTIME 0

/** Config: JUCE_USE_CAMERA
    Enables web-cam support using the CameraDevice class (Mac and Windows).
*/
#define JUCE_USE_CAMERA 0

#endif // __DISTRHO_JUCE_VIDEO_APPCONFIG_H__
