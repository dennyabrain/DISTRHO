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

#include "DistrhoDefines.h"

#ifdef DISTRHO_UI_OPENGL

#include "DistrhoUIInternal.h"

START_NAMESPACE_DISTRHO

// ---------------------------------------------

static void onCloseCallback(PuglView* view)
{
    UIInternal* const _this_ = (UIInternal*)puglGetHandle(view);
    _this_->onClose();
}

static void onDisplayCallback(PuglView* view)
{
    UIInternal* const _this_ = (UIInternal*)puglGetHandle(view);
    _this_->onDisplay();
}

static void onKeyboardCallback(PuglView* view, bool press, uint32_t key)
{
    UIInternal* const _this_ = (UIInternal*)puglGetHandle(view);
    _this_->onKeyboard(press, key);
}

static void onMotionCallback(PuglView* view, int x, int y)
{
    UIInternal* const _this_ = (UIInternal*)puglGetHandle(view);
    _this_->onMotion(x, y);
}

static void onMouseCallback(PuglView* view, int button, bool press, int x, int y)
{
    UIInternal* const _this_ = (UIInternal*)puglGetHandle(view);
    _this_->onMouse(button, press, x, y);
}

static void onReshapeCallback(PuglView* view, int width, int height)
{
    UIInternal* const _this_ = (UIInternal*)puglGetHandle(view);
    _this_->onReshape(width, height);
}

static void onScrollCallback(PuglView* view, float dx, float dy)
{
    UIInternal* const _this_ = (UIInternal*)puglGetHandle(view);
    _this_->onScroll(dx, dy);
}

static void onSpecialCallback(PuglView* view, bool press, PuglKey key)
{
    UIInternal* const _this_ = (UIInternal*)puglGetHandle(view);
    _this_->onSpecial(press, (Key)key);
}

// -------------------------------------------------

OpenGLUI::OpenGLUI(uint32_t parameterCount)
    : UI(parameterCount)
{
}

OpenGLUI::~OpenGLUI()
{
}

// -------------------------------------------------

int OpenGLUI::d_getModifiers()
{
    if (data && data->view)
        return puglGetModifiers(data->view);
    return 0;
}

void OpenGLUI::d_ignoreKeyRepeat(bool ignore)
{
    if (data && data->view)
        puglIgnoreKeyRepeat(data->view, ignore);
}

void OpenGLUI::d_postRedisplay()
{
    if (data && data->view)
        puglPostRedisplay(data->view);
}

// -------------------------------------------------

END_NAMESPACE_DISTRHO

#include "pugl/pugl_x11.c"

#endif // DISTRHO_UI_OPENGL
