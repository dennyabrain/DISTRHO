/*
 *  JUCE LV2 wrapper
 */

#include "AppConfig.h"

#include "../utility/juce_CheckSettingMacros.h"

#if JucePlugin_Build_LV2

#ifdef _MSC_VER
 #pragma warning (disable : 4996 4100)
#endif

#ifdef _WIN32
 #undef _WIN32_WINNT
 #define _WIN32_WINNT 0x500
 #undef STRICT
 #define STRICT 1
 #include <windows.h>
#elif defined (LINUX)
 #include <X11/Xlib.h>
 #include <X11/Xutil.h>
 #include <X11/Xatom.h>
 #undef KeyPress
#else
 #include <Carbon/Carbon.h>
#endif

#ifdef PRAGMA_ALIGN_SUPPORTED
 #undef PRAGMA_ALIGN_SUPPORTED
 #define PRAGMA_ALIGN_SUPPORTED 1
#endif

#include "juce.h"

// LV2 includes
#include "lv2/lv2.h"
#include "lv2/event.h"
#include "lv2/event-helpers.h"
#include "lv2/instance-access.h"
#include "lv2/state.h"
#include "lv2/uri-map.h"
#include "lv2/time.h"
#include "lv2/ui.h"
#include "lv2/ui-resize.h"

//==============================================================================
// Various helper functions for creating the ttl files

enum Lv2UiType {
  LV2_UI_X11 = 1,
  LV2_UI_EXTERNAL
};

#endif
