/*
  ==============================================================================

   Build options for juce-gui-basics static library

  ==============================================================================
*/

#ifndef __DISTRHO_JUCE_GUI_BASICS_APPCONFIG_H__
#define __DISTRHO_JUCE_GUI_BASICS_APPCONFIG_H__

#include "../build-graphics/AppConfig.h"
#include "../build-data-structures/AppConfig.h"

//=============================================================================
/** Config: JUCE_ENABLE_REPAINT_DEBUGGING
    If this option is turned on, each area of the screen that gets repainted will
    flash in a random colour, so that you can see exactly which bits of your
    components are being drawn.
*/
#define JUCE_ENABLE_REPAINT_DEBUGGING 0

/** JUCE_USE_XINERAMA: Enables Xinerama multi-monitor support (Linux only).
    Unless you specifically want to disable this, it's best to leave this option turned on.
*/
#if LINUX
 #define JUCE_USE_XINERAMA 1
#else
 #define JUCE_USE_XINERAMA 0
#endif

/** Config: JUCE_USE_XSHM
    Enables X shared memory for faster rendering on Linux. This is best left turned on
    unless you have a good reason to disable it.
*/
#if LINUX
 #define JUCE_USE_XSHM 1
#else
 #define JUCE_USE_XSHM 0
#endif

/** Config: JUCE_USE_XRENDER
    Enables XRender to allow semi-transparent windowing on Linux.
*/
#if LINUX
 #define JUCE_USE_XRENDER 1
#else
 #define JUCE_USE_XRENDER 0
#endif

/** Config: JUCE_USE_XCURSOR
    Uses XCursor to allow ARGB cursor on Linux. This is best left turned on unless you have
    a good reason to disable it.
*/
#if LINUX
 #define JUCE_USE_XCURSOR 1
#else
 #define JUCE_USE_XCURSOR 0
#endif

#endif // __DISTRHO_JUCE_GUI_BASICS_APPCONFIG_H__
