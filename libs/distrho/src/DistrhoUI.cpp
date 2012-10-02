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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * For a full copy of the license see the GPL.txt file
 */

#include <cassert>

#include "DistrhoUIInternal.h"

START_NAMESPACE_DISTRHO

// -------------------------------------------------

UI::UI(uint32_t parameterCount)
{
    data = new UIPrivateData;
    assert(data);

    if (! data)
        return;

    data->parameterCount = parameterCount;

#ifdef DISTRHO_UI_QT4
    data->widget = (Qt4UI*)this;
#endif
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

void UI::d_uiResize(unsigned int width, unsigned int height)
{
    if (data)
        data->uiResizeCallback(width, height);
}

// -------------------------------------------------

END_NAMESPACE_DISTRHO
