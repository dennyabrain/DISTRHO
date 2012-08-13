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

#include <cassert>

#include "DistrhoUIInternal.h"

//START_NAMESPACE_DISTRHO
namespace DISTRHO {

// -------------------------------------------------

UI::UI(uint32_t parameterCount)
{
    data = new UIPrivateData;
    assert(data);

    if (! data)
        return;

    data->parameterCount = parameterCount;
}

UI::~UI()
{
    if (data)
        delete data;
}

// -------------------------------------------------
// Host DSP State

double UI::d_sampleRate() const
{
    if (data)
        return data->sampleRate;
    return 44100;
}

void UI::d_setParameterValue(uint32_t index, float value)
{
    if (data)
        data->setParameterValueCallback(DISTRHO_PLUGIN_NUM_INPUTS + DISTRHO_PLUGIN_NUM_OUTPUTS + index, value);
}

#if DISTRHO_PLUGIN_WANT_STATE
void UI::d_changeState(const char* key, const char* value)
{
    if (data)
        data->changeStateCallback(key, value);
}
#endif

// -------------------------------------------------
// Host UI State

int UI::d_getModifiers()
{
    if (data && data->view)
        return puglGetModifiers(data->view);
    return 0;
}

void UI::d_ignoreKeyRepeat(bool ignore)
{
    if (data && data->view)
        puglIgnoreKeyRepeat(data->view, ignore);
}

void UI::d_postRedisplay()
{
    if (data && data->view)
        puglPostRedisplay(data->view);
}

void UI::d_resize(unsigned int width, unsigned int height)
{
    if (data)
        data->uiResizeCallback(width, height);
}

// -------------------------------------------------

END_NAMESPACE_DISTRHO
