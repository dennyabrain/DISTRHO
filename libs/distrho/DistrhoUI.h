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

#ifndef __DISTRHO_UI_H__
#define __DISTRHO_UI_H__

#include "src/DistrhoDefines.h"

#include <cstdint>

START_NAMESPACE_DISTRHO

// -------------------------------------------------

struct UIPrivateData;

class UI
{
public:
    UI(uint32_t parameterCount);
    virtual ~UI();

    // ---------------------------------------------

    // Host DSP State
    double d_sampleRate() const;
    void   d_setParameterValue(uint32_t index, float value);
#if DISTRHO_PLUGIN_WANT_STATE
    void   d_changeState(const char* key, const char* value);
#endif

    // Host UI State
    void d_uiResize(unsigned int width, unsigned int height);
    // TODO - d_touch/edit/automate

    // ---------------------------------------------

protected:
    // Information
    virtual const char*  d_title() = 0;
    virtual unsigned int d_width() = 0;
    virtual unsigned int d_height() = 0;

    // DSP Callbacks
    virtual void d_parameterChanged(uint32_t index, float value) = 0;
#if DISTRHO_PLUGIN_WANT_PROGRAMS
    virtual void d_programChanged(uint32_t index) = 0;
#endif
#if DISTRHO_PLUGIN_WANT_STATE
    virtual void d_stateChanged(const char* key, const char* value) = 0;
#endif

    // UI Callbacks
    virtual void d_uiIdle() = 0;

    // ---------------------------------------------

private:
    UIPrivateData* data;
    friend class UIInternal;
};

UI* createUI();

// -------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // __DISTRHO_UI_H__
