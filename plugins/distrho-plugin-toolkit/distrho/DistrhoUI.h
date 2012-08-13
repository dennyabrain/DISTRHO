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

#include <cstdint>

#ifdef DISTRHO_OS_MAC
# include <OpenGL/glu.h>
#else
# include <GL/glu.h>
#endif

#include "DistrhoIncludes.h"

//START_NAMESPACE_DISTRHO
namespace DISTRHO {

// -------------------------------------------------

enum Char {
    CHAR_BACKSPACE = 0x08,
    CHAR_ESCAPE    = 0x1B,
    CHAR_DELETE    = 0x7F
};

enum Key {
    KEY_F1 = 1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_LEFT,
    KEY_UP,
    KEY_RIGHT,
    KEY_DOWN,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,
    KEY_HOME,
    KEY_END,
    KEY_INSERT,
    KEY_SHIFT,
    KEY_CTRL,
    KEY_ALT,
    KEY_SUPER
};

enum Mod {
    MOD_SHIFT = 1 << 0, /**< Shift key */
    MOD_CTRL  = 1 << 1, /**< Control key */
    MOD_ALT   = 1 << 2, /**< Alt/Option key */
    MOD_SUPER = 1 << 3  /**< Mod4/Command/Windows key */
};

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
    int  d_getModifiers();
    void d_ignoreKeyRepeat(bool ignore);
    void d_postRedisplay();
    void d_resize(unsigned int width, unsigned int height);

    // Helper functions
    void setBackgroundImage(const char* data, size_t size);

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
    virtual void d_onInit() = 0;
    virtual void d_onDisplay() = 0;
    virtual void d_onKeyboard(bool press, uint32_t key) = 0;
    virtual void d_onMotion(int x, int y) = 0;
    virtual void d_onMouse(int button, bool press, int x, int y) = 0;
    virtual void d_onReshape(int width, int height) = 0;
    virtual void d_onScroll(float dx, float dy) = 0;
    virtual void d_onSpecial(bool press, Key key) = 0;
    virtual void d_onClose() = 0;

    // ---------------------------------------------

private:
    UIPrivateData* data;
    friend class UIInternal;
};

extern UI* createUI();

// -------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // __DISTRHO_UI_H__
