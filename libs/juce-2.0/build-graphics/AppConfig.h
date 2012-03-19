/*
  ==============================================================================

   Build options for juce-graphics static library

  ==============================================================================
*/

#ifndef __DISTRHO_JUCE_GRAPHICS_APPCONFIG_H__
#define __DISTRHO_JUCE_GRAPHICS_APPCONFIG_H__

#include "../build-events/AppConfig.h"

//=============================================================================
/** Config: JUCE_USE_COREIMAGE_LOADER

    On OSX, enabling this flag means that the CoreImage codecs will be used to load
    PNG/JPEG/GIF files. It is enabled by default, but you may want to disable it if
    you'd rather use libpng, libjpeg, etc.
*/
#if MAC
 #define JUCE_USE_COREIMAGE_LOADER 1
#else
 #define JUCE_USE_COREIMAGE_LOADER 0
#endif

/** Config: JUCE_USE_DIRECTWRITE

    Enabling this flag means that DirectWrite will be used when available for font
    management and layout.
*/
#if WINDOWS
 #define JUCE_USE_DIRECTWRITE 1
#else
 #define JUCE_USE_DIRECTWRITE 0
#endif

#define JUCE_INCLUDE_PNGLIB_CODE 1

#define JUCE_INCLUDE_JPEGLIB_CODE 1

#if MAC
 #define USE_COREGRAPHICS_RENDERING 1
#else
 #define USE_COREGRAPHICS_RENDERING 0
#endif

#endif // __DISTRHO_JUCE_GRAPHICS_APPCONFIG_H__
