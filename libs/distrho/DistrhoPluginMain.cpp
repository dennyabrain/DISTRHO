/*
 * DISTHRO Plugin Toolkit (DPT)
 * Copyright (C) 2012 Filipe Coelho <falktx@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * A copy of the license is included with this software, or can be
 * found online at www.gnu.org/licenses.
 */

#include "src/DistrhoPlugin.cpp"

#if defined(DISTRHO_PLUGIN_TARGET_LADSPA) || defined(DISTRHO_PLUGIN_TARGET_DSSI)
# include "src/DistrhoPluginLADSPA+DSSI.cpp"
#elif defined(DISTRHO_PLUGIN_TARGET_LV2)
# include "src/DistrhoPluginLV2.cpp"
# include "src/DistrhoPluginLV2export.cpp"
#elif defined(DISTRHO_PLUGIN_TARGET_VST)
# include "src/DistrhoPluginVST.cpp"
#endif
