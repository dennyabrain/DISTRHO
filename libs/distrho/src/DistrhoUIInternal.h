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

#ifndef __DISTRHO_UI_INTERNAL_H__
#define __DISTRHO_UI_INTERNAL_H__

#include "DistrhoDefines.h"

#ifdef DISTRHO_UI_OPENGL
# include "DistrhoUIOpenGLExt.h"
# include "pugl/pugl.h"
#else
# include "DistrhoUIQt4.h"
#endif

#include <cassert>

START_NAMESPACE_DISTRHO

// -------------------------------------------------

#ifdef DISTRHO_UI_OPENGL
typedef PuglView* NativeWidget;
#else
typedef QWidget*  NativeWidget;
#endif

typedef void (*changeStateFunc)(void* ptr, const char* key, const char* value);
typedef void (*setParameterValueFunc)(void* ptr, uint32_t index, float value);
typedef void (*uiResizeFunc)(void* ptr, unsigned int width, unsigned int height);

// -------------------------------------------------

struct UIPrivateData {
    // DSP
    uint32_t parameterCount;
    double   sampleRate;

    // UI
    void*        ptr;
    NativeWidget widget;

    // Callbacks
    changeStateFunc       changeStateCallbackFunc;
    setParameterValueFunc setParameterValueCallbackFunc;
    uiResizeFunc          uiResizeCallbackFunc;

    UIPrivateData()
        : parameterCount(0),
          sampleRate(44100.0),
          ptr(nullptr),
          widget(nullptr),
          changeStateCallbackFunc(nullptr),
          setParameterValueCallbackFunc(nullptr),
          uiResizeCallbackFunc(nullptr) {}

    ~UIPrivateData()
    {
    }

    void changeStateCallback(const char* key, const char* value)
    {
        if (changeStateCallbackFunc)
            changeStateCallbackFunc(ptr, key, value);
    }

    void setParameterValueCallback(uint32_t index, float value)
    {
        if (setParameterValueCallbackFunc)
            setParameterValueCallbackFunc(ptr, index, value);
    }

    void uiResizeCallback(unsigned int width, unsigned int height)
    {
        if (uiResizeCallbackFunc)
            uiResizeCallbackFunc(ptr, width, height);
    }
};

// -------------------------------------------------

class UIInternal
{
public:
    UIInternal(void* ptr, intptr_t winId, changeStateFunc changeStateCall, setParameterValueFunc setParameterValueCall, uiResizeFunc uiResizeCall)
        : ui(createUI()),
          data(nullptr)
    {
        assert(ui);

        if (! ui)
            return;

        data = ui->data;
        assert(data);

        if (! data)
            return;

        data->ptr = ptr;
        data->changeStateCallbackFunc       = changeStateCall;
        data->setParameterValueCallbackFunc = setParameterValueCall;
        data->uiResizeCallbackFunc          = uiResizeCall;

#ifdef DISTRHO_UI_OPENGL
        gl_initiated = false;
        gl_createWindow(winId);
#else
        data->widget = (Qt4UI*)ui;
        Q_UNUSED(winId);
#endif
    }

    ~UIInternal()
    {
    }

    // ---------------------------------------------

    void idle()
    {
        if (ui)
            ui->d_uiIdle();
    }

    unsigned int getWidth()
    {
        return ui ? ui->d_width() : 0;
    }

    unsigned int getHeight()
    {
        return ui ? ui->d_height() : 0;
    }

    NativeWidget getNativeWidget()
    {
        return data ? data->widget : nullptr;
    }

    // ---------------------------------------------

    void parameterChanged(uint32_t index, float value)
    {
        if (ui)
            ui->d_parameterChanged(index, value);
    }

#if DISTRHO_PLUGIN_WANT_PROGRAMS
    void programChanged(uint32_t index)
    {
        if (ui)
            ui->d_programChanged(index);
    }
#endif

#if DISTRHO_PLUGIN_WANT_STATE
    void stateChanged(const char* key, const char* value)
    {
        if (ui)
            ui->d_stateChanged(key, value);
    }
#endif

    // ---------------------------------------------

#ifdef DISTRHO_UI_OPENGL
    void gl_createWindow(PuglNativeWindow parent)
    {
        if ((data && data->widget) || ! ui)
            return;

        data->widget = puglCreate(parent, ui->d_title(), ui->d_width(), ui->d_height(), false);

        assert(data->widget);

        if (! data->widget)
            return;

        puglSetHandle(data->widget, this);
        puglSetDisplayFunc(data->widget, gl_onDisplayCallback);
        puglSetKeyboardFunc(data->widget, gl_onKeyboardCallback);
        puglSetMotionFunc(data->widget, gl_onMotionCallback);
        puglSetMouseFunc(data->widget, gl_onMouseCallback);
        puglSetScrollFunc(data->widget, gl_onScrollCallback);
        puglSetSpecialFunc(data->widget, gl_onSpecialCallback);
        puglSetReshapeFunc(data->widget, gl_onReshapeCallback);
        puglSetCloseFunc(data->widget, gl_onCloseCallback);
    }

    void gl_destroyWindowGL()
    {
        OpenGLUI* const uiGL = (OpenGLUI*)ui;
        assert(uiGL);

        if (uiGL)
            uiGL->d_onClose();

        if (data && data->widget)
        {
            puglDestroy(data->widget);
            data->widget = nullptr;
        }
    }

    PuglNativeWindow gl_getNativeWindow()
    {
        return (data && data->widget) ? puglGetNativeWindow(data->widget) : 0;
    }

    // ---------------------------------------------

    void gl_onDisplay()
    {
        OpenGLUI* const uiGL = (OpenGLUI*)ui;
        assert(uiGL);

        if (uiGL)
            uiGL->d_onDisplay();
    }

    void gl_onKeyboard(bool press, uint32_t key)
    {
        OpenGLUI* const uiGL = (OpenGLUI*)ui;
        assert(uiGL);

        if (uiGL)
            uiGL->d_onKeyboard(press, key);
    }

    void gl_onMotion(int x, int y)
    {
        OpenGLUI* const uiGL = (OpenGLUI*)ui;
        assert(uiGL);

        if (uiGL)
            uiGL->d_onMotion(x, y);
    }

    void gl_onMouse(int button, bool press, int x, int y)
    {
        OpenGLUI* const uiGL = (OpenGLUI*)ui;
        assert(uiGL);

        if (uiGL)
            uiGL->d_onMouse(button, press, x, y);
    }

    void gl_onReshape(int width, int height)
    {
        OpenGLUI* const uiGL = (OpenGLUI*)ui;
        assert(uiGL);

        if (uiGL)
        {
            if (! gl_initiated)
            {
                uiGL->d_onInit();
                gl_initiated = true;
            }
            else
                uiGL->d_onReshape(width, height);
        }
    }

    void gl_onScroll(float dx, float dy)
    {
        OpenGLUI* const uiGL = (OpenGLUI*)ui;
        assert(uiGL);

        if (uiGL)
            uiGL->d_onScroll(dx, dy);
    }

    void gl_onSpecial(bool press, Key key)
    {
        OpenGLUI* const uiGL = (OpenGLUI*)ui;
        assert(uiGL);

        if (uiGL)
            uiGL->d_onSpecial(press, key);
    }

    void gl_onClose()
    {
        OpenGLUI* const uiGL = (OpenGLUI*)ui;
        assert(uiGL);

        if (uiGL)
            uiGL->d_onClose();
    }

    // ---------------------------------------------

    static void gl_onDisplayCallback(PuglView* view)
    {
        UIInternal* const _this_ = (UIInternal*)puglGetHandle(view);
        _this_->gl_onDisplay();
    }

    static void gl_onKeyboardCallback(PuglView* view, bool press, uint32_t key)
    {
        UIInternal* const _this_ = (UIInternal*)puglGetHandle(view);
        _this_->gl_onKeyboard(press, key);
    }

    static void gl_onMotionCallback(PuglView* view, int x, int y)
    {
        UIInternal* const _this_ = (UIInternal*)puglGetHandle(view);
        _this_->gl_onMotion(x, y);
    }

    static void gl_onMouseCallback(PuglView* view, int button, bool press, int x, int y)
    {
        UIInternal* const _this_ = (UIInternal*)puglGetHandle(view);
        _this_->gl_onMouse(button, press, x, y);
    }

    static void gl_onReshapeCallback(PuglView* view, int width, int height)
    {
        UIInternal* const _this_ = (UIInternal*)puglGetHandle(view);
        _this_->gl_onReshape(width, height);
    }

    static void gl_onScrollCallback(PuglView* view, float dx, float dy)
    {
        UIInternal* const _this_ = (UIInternal*)puglGetHandle(view);
        _this_->gl_onScroll(dx, dy);
    }

    static void gl_onSpecialCallback(PuglView* view, bool press, PuglKey key)
    {
        UIInternal* const _this_ = (UIInternal*)puglGetHandle(view);
        _this_->gl_onSpecial(press, (Key)key);
    }

    static void gl_onCloseCallback(PuglView* view)
    {
        UIInternal* const _this_ = (UIInternal*)puglGetHandle(view);
        _this_->gl_onClose();
    }
#endif

    // ---------------------------------------------

protected:
    UI* const ui;
    UIPrivateData* data;

#ifdef DISTRHO_UI_OPENGL
private:
    bool gl_initiated;
#endif
};

// -------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // __DISTRHO_UI_INTERNAL_H__
