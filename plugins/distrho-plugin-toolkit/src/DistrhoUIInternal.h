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

#include <cassert>

#include "DistrhoUI.h"
#include "pugl/pugl.h"

//START_NAMESPACE_DISTRHO
namespace DISTRHO {

// -------------------------------------------------

typedef void (*changeStateFunc)(void* ptr, const char* key, const char* value);
typedef void (*setParameterValueFunc)(void* ptr, uint32_t index, float value);
typedef void (*uiResizeFunc)(void* ptr, unsigned int width, unsigned int height);

#if 0
class DistrhoPuGL : public puGL
{
    DistrhoPuGL(UI* ui_, PuglNativeWindow parent, const char* title, int width, int height)
        : puGL(parent, title, width, height, false),
          ui(ui_)
    {
        assert(ui);

        ui->d_title(), ui->d_width(), ui->d_height();
    }

    // ------------------------------------------

protected:

private:
    UI* const ui;
};
#endif

struct UIPrivateData {
    // DSP
    uint32_t parameterCount;
    double   sampleRate;

    // UI
    PuglView* view;
    void*     ptr;

    // Callbacks
    changeStateFunc       changeStateCallbackFunc;
    setParameterValueFunc setParameterValueCallbackFunc;
    uiResizeFunc          uiResizeCallbackFunc;

    UIPrivateData()
        : parameterCount(0),
          sampleRate(44100),
          view(nullptr),
          ptr(nullptr),
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
    UIInternal(void* ptr, changeStateFunc changeStateCallback, setParameterValueFunc setParameterValueCallback, uiResizeFunc uiResizeCallback) :
        ui(createUI()),
        data(nullptr),
        initiated(false)
    {
        assert(ui);

        if (! ui)
            return;

        data = ui->data;
        assert(data);

        if (! data)
            return;

        data->ptr = ptr;
        data->changeStateCallbackFunc       = changeStateCallback;
        data->setParameterValueCallbackFunc = setParameterValueCallback;
        data->uiResizeCallbackFunc          = uiResizeCallback;
    }

    // ---------------------------------------------

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

    PuglNativeWindow getNativeWindow()
    {
        return (data && data->view) ? puglGetNativeWindow(data->view) : 0;
    }

    PuglStatus processEvents()
    {
        return (data && data->view) ? puglProcessEvents(data->view) : PUGL_SUCCESS;
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

protected:
    UI* const ui;
    UIPrivateData* data;

private:
    bool initiated;

    void onClose()
    {
        if (ui)
            ui->d_onClose();
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
};

// -------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // __DISTRHO_UI_INTERNAL_H__
