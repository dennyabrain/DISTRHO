/*
 * pugl C++ interface
 * Copyright (C) 2012 Filipe Coelho <falktx@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * For a full copy of the GNU General Public License see the COPYING file
 */

#ifndef PUGLMM_H
#define PUGLMM_H

#include <cassert>

#include "pugl.h"

class puGL
{
public:
    puGL(PuglNativeWindow parent, const char* title, int width, int height, bool resizable)
        : view(puglCreate(parent, title, width, height, resizable))
    {
        assert(view);

        if (! view)
            return;

        puglSetHandle(view, this);
        puglSetCloseFunc(view, onCloseCallback);
        puglSetDisplayFunc(view, onDisplayCallback);
        puglSetKeyboardFunc(view, onKeyboardCallback);
        puglSetMotionFunc(view, onMotionCallback);
        puglSetMouseFunc(view, onMouseCallback);
        puglSetScrollFunc(view, onScrollCallback);
        puglSetSpecialFunc(view, onSpecialCallback);
        puglSetReshapeFunc(view, onReshapeCallback);
    }

    virtual ~puGL()
    {
        if (view)
            puglDestroy(view);
    }

    int getModifiers()
    {
        if (! view)
            return 0;

        return puglGetModifiers(view);
    }

    PuglView* getView() const
    {
        if (! view)
            return nullptr;

        return view;
    }

    void ignoreKeyRepeat(bool ignore)
    {
        if (! view)
            return;

        puglIgnoreKeyRepeat(view, ignore);
    }

    PuglNativeWindow getNativeWindow()
    {
        if (! view)
            return 0;

        return puglGetNativeWindow(view);
    }

    PuglStatus processEvents()
    {
        if (! view)
            return PUGL_SUCCESS;

        return puglProcessEvents(view);
    }

    void postRedisplay()
    {
        if (! view)
            return;

        puglPostRedisplay(view);
    }

    // ------------------------------------------

protected:
    virtual void onClose() {}
    virtual void onDisplay() {}
    virtual void onKeyboard(bool /*press*/, uint32_t /*key*/) {}
    virtual void onMotion(int /*x*/, int /*y*/) {}
    virtual void onMouse(int /*button*/, bool /*press*/, int /*x*/, int /*y*/) {}
    virtual void onReshape(int /*width*/, int /*height*/) {}
    virtual void onScroll(float /*dx*/, float /*dy*/) {}
    virtual void onSpecial(bool /*press*/, PuglKey /*key*/) {}

    // ------------------------------------------

private:
    PuglView* const view;

    static void onCloseCallback(PuglView* view)
    {
        puGL* const _this_ = (puGL*)puglGetHandle(view);
        _this_->onClose();
    }

    static void onDisplayCallback(PuglView* view)
    {
        puGL* const _this_ = (puGL*)puglGetHandle(view);
        _this_->onDisplay();
    }

    static void onKeyboardCallback(PuglView* view, bool press, uint32_t key)
    {
        puGL* const _this_ = (puGL*)puglGetHandle(view);
        _this_->onKeyboard(press, key);
    }

    static void onMotionCallback(PuglView* view, int x, int y)
    {
        puGL* const _this_ = (puGL*)puglGetHandle(view);
        _this_->onMotion(x, y);
    }

    static void onMouseCallback(PuglView* view, int button, bool press, int x, int y)
    {
        puGL* const _this_ = (puGL*)puglGetHandle(view);
        _this_->onMouse(button, press, x, y);
    }

    static void onReshapeCallback(PuglView* view, int width, int height)
    {
        puGL* const _this_ = (puGL*)puglGetHandle(view);
        _this_->onReshape(width, height);
    }

    static void onScrollCallback(PuglView* view, float dx, float dy)
    {
        puGL* const _this_ = (puGL*)puglGetHandle(view);
        _this_->onScroll(dx, dy);
    }

    static void onSpecialCallback(PuglView* view, bool press, PuglKey key)
    {
        puGL* const _this_ = (puGL*)puglGetHandle(view);
        _this_->onSpecial(press, key);
    }
};

#endif // PUGLMM_H
