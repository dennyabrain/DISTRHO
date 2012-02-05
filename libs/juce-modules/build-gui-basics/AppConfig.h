/*
  ==============================================================================

   Build options for juce-gui-basics static library

  ==============================================================================
*/

#ifndef __DISTRHO_JUCE_GUI_BASICS_APPCONFIG_H__
#define __DISTRHO_JUCE_GUI_BASICS_APPCONFIG_H__

#include "../build-core/AppConfig.h"

//=============================================================================
/** Config: JUCE_ENABLE_REPAINT_DEBUGGING
    If this option is turned on, each area of the screen that gets repainted will
    flash in a random colour, so that you can see exactly which bits of your
    components are being drawn.
*/
#ifdef DEBUG
 #define JUCE_ENABLE_REPAINT_DEBUGGING 1
#else
 #define JUCE_ENABLE_REPAINT_DEBUGGING 0
#endif

/** JUCE_USE_XINERAMA: Enables Xinerama multi-monitor support (Linux only).
    Unless you specifically want to disable this, it's best to leave this option turned on.
*/
#define JUCE_USE_XINERAMA 1

/** Config: JUCE_USE_XSHM
    Enables X shared memory for faster rendering on Linux. This is best left turned on
    unless you have a good reason to disable it.
*/
#define JUCE_USE_XSHM 1

/** Config: JUCE_USE_XRENDER
    Enables XRender to allow semi-transparent windowing on Linux.
*/
#define JUCE_USE_XRENDER 1

/** Config: JUCE_USE_XCURSOR
    Uses XCursor to allow ARGB cursor on Linux. This is best left turned on unless you have
    a good reason to disable it.
*/
#define JUCE_USE_XCURSOR 1

#endif // __DISTRHO_JUCE_GUI_BASICS_APPCONFIG_H__
