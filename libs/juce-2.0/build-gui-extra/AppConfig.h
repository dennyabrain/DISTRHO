/*
  ==============================================================================

   Build options for juce-gui-extra static library

  ==============================================================================
*/

#ifndef __DISTRHO_JUCE_GUI_EXTRA_APPCONFIG_H__
#define __DISTRHO_JUCE_GUI_EXTRA_APPCONFIG_H__

#include "../build-gui-basics/AppConfig.h"

//=============================================================================
/** Config: JUCE_WEB_BROWSER
    This lets you disable the WebBrowserComponent class (Mac and Windows).
    If you're not using any embedded web-pages, turning this off may reduce your code size.
*/
#define JUCE_WEB_BROWSER 1

#endif // __DISTRHO_JUCE_GUI_EXTRA_APPCONFIG_H__
