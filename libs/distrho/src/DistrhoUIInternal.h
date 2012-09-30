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

#ifndef __DISTRHO_UI_INTERNAL_H__
#define __DISTRHO_UI_INTERNAL_H__

//#ifdef DISTRHO_UI_OPENGL
# include "DistrhoUIOpenGL.h"
# include "pugl/pugl.h"
//#else
# include "DistrhoUIQt4.h"
//#endif

#include <cassert>

START_NAMESPACE_DISTRHO

// -------------------------------------------------

//#ifdef DISTRHO_UI_OPENGL
//typedef PuglView* NativeWidget;
//#else
typedef QWidget*  NativeWidget;
//#endif

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
          sampleRate(44100),
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
    UIInternal(void* ptr, changeStateFunc changeStateCall, setParameterValueFunc setParameterValueCall, uiResizeFunc uiResizeCall)
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
        initiated = false;
#endif
    }

    // ---------------------------------------------

#if 0
    void createWindow(PuglNativeWindow parent)
    {
        if ((data && data->view) || ! ui)
            return;

        data->view = puglCreate(parent, ui->d_title(), ui->d_width(), ui->d_height(), false);
        assert(data->view);

        if (! data->view)
            return;

        puglSetHandle(data->view, this);
        puglSetCloseFunc(data->view, onCloseCallback);
        puglSetDisplayFunc(data->view, onDisplayCallback);
        puglSetKeyboardFunc(data->view, onKeyboardCallback);
        puglSetMotionFunc(data->view, onMotionCallback);
        puglSetMouseFunc(data->view, onMouseCallback);
        puglSetScrollFunc(data->view, onScrollCallback);
        puglSetSpecialFunc(data->view, onSpecialCallback);
        puglSetReshapeFunc(data->view, onReshapeCallback);
    }

    void destroyWindow()
    {
        if (ui)
            ui->d_onClose();

        if (data && data->view)
        {
            puglDestroy(data->view);
            data->view = nullptr;
        }
    }

    PuglStatus processEvents()
    {
        return (data && data->view) ? puglProcessEvents(data->view) : PUGL_SUCCESS;
    }
#endif

    NativeWidget getNativeWidget()
    {
        return data ? data->widget : nullptr;
        //return (data && data->view) ? puglGetNativeWindow(data->view) : 0;
    }

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
    void onClose()
    {
        if (ui)
            ((OpenGLUI*)ui)->d_onClose();
    }

    void onDisplay()
    {
        if (ui)
            ui->d_onDisplay();
    }

    void onKeyboard(bool press, uint32_t key)
    {
        if (ui)
            ui->d_onKeyboard(press, key);
    }

    void onMotion(int x, int y)
    {
        if (ui)
            ui->d_onMotion(x, y);
    }

    void onMouse(int button, bool press, int x, int y)
    {
        if (ui)
            ui->d_onMouse(button, press, x, y);
    }

    void onReshape(int width, int height)
    {
        if (ui)
        {
            //if (! initiated)
            //{
            //    ui->d_onInit();
            //    initiated = true;
            //}
            //else
            ui->d_onReshape(width, height);
        }
    }

    void onScroll(float dx, float dy)
    {
        if (ui)
            ui->d_onScroll(dx, dy);
    }

    void onSpecial(bool press, Key key)
    {
        if (ui)
            ui->d_onSpecial(press, key);
    }
#endif

protected:
    UI* const ui;
    UIPrivateData* data;

private:
    bool initiated;
};

// -------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // __DISTRHO_UI_INTERNAL_H__
