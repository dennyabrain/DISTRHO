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

#include "DistrhoUI.h"

#ifdef DISTRHO_UI_OPENGL
# include "DistrhoUIOpenGL.h"
# include "pugl/pugl.h"
#else
# include "DistrhoUIQt4.h"
# include <QtGui/QMouseEvent>
# include <QtGui/QSizeGrip>
# include <QtGui/QVBoxLayout>
# ifdef Q_WS_X11
#  include <QtGui/QX11EmbedWidget>
# endif
#endif

#include <cassert>

START_NAMESPACE_DISTRHO

// -------------------------------------------------

#ifdef DISTRHO_UI_OPENGL
typedef PuglView* NativeWidget;
#else
typedef QWidget*  NativeWidget;
# ifdef Q_WS_X11
class QEmbedWidget : public QX11EmbedWidget
#else
class QEmbedWidget : public QWidget
#endif
{
public:
    QEmbedWidget() {}
    ~QEmbedWidget() {}

# ifndef Q_WS_X11
    // TODO for Windows and Mac OS support
    void embedInto(WId id);
    WId containerWinId() const;
# endif
};
#endif

typedef void (*setParamFunc)    (void* ptr, uint32_t index, float value);
typedef void (*setStateFunc)    (void* ptr, const char* key, const char* value);
typedef void (*uiEditParamFunc) (void* ptr, uint32_t index, bool started);
typedef void (*uiSendNoteFunc)  (void* ptr, bool onOff, uint8_t channel, uint8_t note, uint8_t velo);
typedef void (*uiResizeFunc)    (void* ptr, unsigned int width, unsigned int height);

static double d_lastUiSampleRate = 0.0;

// -------------------------------------------------

struct UIPrivateData {
    // DSP
    double   sampleRate;
    uint32_t parameterOffset;

    // UI
    void*        ptr;
    NativeWidget widget;

    // Callbacks
    setParamFunc    setParamCallbackFunc;
    setStateFunc    setStateCallbackFunc;
    uiEditParamFunc uiEditParamCallbackFunc;
    uiSendNoteFunc  uiSendNoteCallbackFunc;
    uiResizeFunc    uiResizeCallbackFunc;

    UIPrivateData()
        : sampleRate(d_lastUiSampleRate),
          parameterOffset(0),
          ptr(nullptr),
          widget(nullptr),
          setParamCallbackFunc(nullptr),
          setStateCallbackFunc(nullptr),
          uiEditParamCallbackFunc(nullptr),
          uiSendNoteCallbackFunc(nullptr),
          uiResizeCallbackFunc(nullptr)
    {
        assert(d_lastUiSampleRate != 0.0);
    }

    ~UIPrivateData()
    {
    }

    void setParamCallback(uint32_t rindex, float value)
    {
        if (setParamCallbackFunc)
            setParamCallbackFunc(ptr, rindex, value);
    }

    void setStateCallback(const char* key, const char* value)
    {
        if (setStateCallbackFunc)
            setStateCallbackFunc(ptr, key, value);
    }

    void uiEditParamCallback(uint32_t index, bool started)
    {
        if (uiEditParamCallbackFunc)
            uiEditParamCallbackFunc(ptr, index, started);
    }

    void uiSendNoteCallback(bool onOff, uint8_t channel, uint8_t note, uint8_t velocity)
    {
        if (uiSendNoteCallbackFunc)
            uiSendNoteCallbackFunc(ptr, onOff, channel, note, velocity);
    }

    void uiResizeCallback(unsigned int width, unsigned int height)
    {
        if (uiResizeCallbackFunc)
            uiResizeCallbackFunc(ptr, width, height);
    }
};

// -------------------------------------------------

#ifdef DISTRHO_UI_QT4
class UIInternal : public QObject
#else
class UIInternal
#endif
{
public:
    UIInternal(void* ptr, intptr_t winId, setParamFunc setParamCall, setStateFunc setStateCall, uiEditParamFunc uiEditParamCall, uiSendNoteFunc uiSendNoteCall, uiResizeFunc uiResizeCall)
        : ui(createUI()),
          data(nullptr)
    {
        assert(ui);

#ifdef DISTRHO_UI_QT4
        qt_grip   = nullptr;
        qt_widget = nullptr;
#else
        gl_initiated = false;
#endif

        if (! ui)
            return;

        data = ui->data;

        data->ptr = ptr;
        data->setParamCallbackFunc    = setParamCall;
        data->setStateCallbackFunc    = setStateCall;
        data->uiEditParamCallbackFunc = uiEditParamCall;
        data->uiSendNoteCallbackFunc  = uiSendNoteCall;
        data->uiResizeCallbackFunc    = uiResizeCall;

        createWindow(winId);
    }

    ~UIInternal()
    {
        if (ui)
        {
            destroyWindow();
            delete ui;
        }
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

    intptr_t getWindowId()
    {
#ifdef DISTRHO_UI_QT4
        return qt_widget ? qt_widget->winId() : 0;
#else
        return (data && data->widget) ? puglGetNativeWindow(data->widget) : 0;
#endif
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

#if DISTRHO_PLUGIN_IS_SYNTH
    void noteReceived(bool onOff, uint8_t channel, uint8_t note, uint8_t velocity)
    {
        if (ui)
            ui->d_uiNoteReceived(onOff, channel, note, velocity);
    }
#endif

    // ---------------------------------------------

    void createWindow(intptr_t parent)
    {
#ifdef DISTRHO_UI_QT4
        // create embedable widget
        qt_widget = new QEmbedWidget;

        // set layout
        qt_widget->setLayout(new QVBoxLayout(qt_widget));
        qt_widget->layout()->addWidget(data->widget);
        qt_widget->layout()->setContentsMargins(0, 0, 0, 0);
        qt_widget->setFixedSize(ui->d_width(), ui->d_height());

        // listen for resize on the plugin widget
        data->widget->installEventFilter(this);

        // set resize grip
        if (((Qt4UI*)ui)->d_resizable())
        {
            qt_grip = new QSizeGrip(qt_widget);
            qt_grip->resize(qt_grip->sizeHint());
            qt_grip->setCursor(Qt::SizeFDiagCursor);
            qt_grip->move(ui->d_width() - qt_grip->width(), ui->d_height() - qt_grip->height());
            qt_grip->show();
            qt_grip->raise();
            qt_grip->installEventFilter(this);
        }

        // reparent widget
        qt_widget->embedInto(parent);

        // show it
        qt_widget->show();

#else
        if ((data && data->widget) || ! ui)
            return;

        data->widget = puglCreate(parent, DISTRHO_PLUGIN_NAME, ui->d_width(), ui->d_height(), false);

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
#endif
    }

    void destroyWindow()
    {
#ifdef DISTRHO_UI_QT4
        if (qt_grip)
            delete qt_grip;

        if (qt_widget)
            delete qt_widget;
#else
        ((OpenGLUI*)ui)->d_onClose();

        if (data && data->widget)
        {
            puglDestroy(data->widget);
            data->widget = nullptr;
        }
#endif
    }

    // ---------------------------------------------

#ifdef DISTRHO_UI_OPENGL
    void gl_onDisplay()
    {
        OpenGLUI* uiGL = (OpenGLUI*)ui;
        assert(uiGL);

        if (uiGL)
            uiGL->d_onDisplay();
    }

    void gl_onKeyboard(bool press, uint32_t key)
    {
        OpenGLUI* uiGL = (OpenGLUI*)ui;
        assert(uiGL);

        if (uiGL)
            uiGL->d_onKeyboard(press, key);
    }

    void gl_onMotion(int x, int y)
    {
        OpenGLUI* uiGL = (OpenGLUI*)ui;
        assert(uiGL);

        if (uiGL)
            uiGL->d_onMotion(x, y);
    }

    void gl_onMouse(int button, bool press, int x, int y)
    {
        OpenGLUI* uiGL = (OpenGLUI*)ui;
        assert(uiGL);

        if (uiGL)
            uiGL->d_onMouse(button, press, x, y);
    }

    void gl_onReshape(int width, int height)
    {
        OpenGLUI* uiGL = (OpenGLUI*)ui;
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
        OpenGLUI* uiGL = (OpenGLUI*)ui;
        assert(uiGL);

        if (uiGL)
            uiGL->d_onScroll(dx, dy);
    }

    void gl_onSpecial(bool press, Key key)
    {
        OpenGLUI* uiGL = (OpenGLUI*)ui;
        assert(uiGL);

        if (uiGL)
            uiGL->d_onSpecial(press, key);
    }

    void gl_onClose()
    {
        OpenGLUI* uiGL = (OpenGLUI*)ui;
        assert(uiGL);

        if (uiGL)
            uiGL->d_onClose();
    }

    // ---------------------------------------------

    static void gl_onDisplayCallback(PuglView* view)
    {
        UIInternal* _this_ = (UIInternal*)puglGetHandle(view);
        _this_->gl_onDisplay();
    }

    static void gl_onKeyboardCallback(PuglView* view, bool press, uint32_t key)
    {
        UIInternal* _this_ = (UIInternal*)puglGetHandle(view);
        _this_->gl_onKeyboard(press, key);
    }

    static void gl_onMotionCallback(PuglView* view, int x, int y)
    {
        UIInternal* _this_ = (UIInternal*)puglGetHandle(view);
        _this_->gl_onMotion(x, y);
    }

    static void gl_onMouseCallback(PuglView* view, int button, bool press, int x, int y)
    {
        UIInternal* _this_ = (UIInternal*)puglGetHandle(view);
        _this_->gl_onMouse(button, press, x, y);
    }

    static void gl_onReshapeCallback(PuglView* view, int width, int height)
    {
        UIInternal* _this_ = (UIInternal*)puglGetHandle(view);
        _this_->gl_onReshape(width, height);
    }

    static void gl_onScrollCallback(PuglView* view, float dx, float dy)
    {
        UIInternal* _this_ = (UIInternal*)puglGetHandle(view);
        _this_->gl_onScroll(dx, dy);
    }

    static void gl_onSpecialCallback(PuglView* view, bool press, PuglKey key)
    {
        UIInternal* _this_ = (UIInternal*)puglGetHandle(view);
        _this_->gl_onSpecial(press, (Key)key);
    }

    static void gl_onCloseCallback(PuglView* view)
    {
        UIInternal* _this_ = (UIInternal*)puglGetHandle(view);
        _this_->gl_onClose();
    }
#endif

    // ---------------------------------------------

protected:
    UI* const ui;
    UIPrivateData* data;

#ifdef DISTRHO_UI_QT4
    bool eventFilter(QObject* obj, QEvent* event)
    {
        if (obj == qt_grip)
        {
            if (event->type() == QEvent::MouseButtonPress)
            {
                QMouseEvent* mEvent = (QMouseEvent*)event;
                if (mEvent->button() == Qt::LeftButton)
                    qt_mouseDown = true;
                return true;
            }

            if (event->type() == QEvent::MouseMove)
            {
                if (qt_mouseDown)
                {
                    Qt4UI* qt_ui = (Qt4UI*)ui;
                    QMouseEvent* mEvent = (QMouseEvent*)event;
                    int width  = ui->d_width()  + mEvent->x() - qt_grip->width();
                    int height = ui->d_height() + mEvent->y() - qt_grip->height();

                    if (width < qt_ui->d_minimumWidth())
                        width = qt_ui->d_minimumWidth();
                    if (height < qt_ui->d_minimumHeight())
                        height = qt_ui->d_minimumHeight();

                    data->widget->setFixedSize(width, height);
                }

                return true;
            }

            if (event->type() == QEvent::MouseButtonRelease)
            {
                QMouseEvent* mEvent = (QMouseEvent*)event;
                if (mEvent->button() == Qt::LeftButton)
                    qt_mouseDown = false;
                return true;
            }
        }
        else if (data && obj == data->widget)
        {
            if (event->type() == QEvent::Resize)
            {
                QResizeEvent* rEvent = (QResizeEvent*)event;
                const QSize&  size   = rEvent->size();

                qt_widget->setFixedSize(size.width(), size.height());
                qt_grip->move(size.width() - qt_grip->width(), size.height() - qt_grip->height());

                ui->d_uiResize(size.width(), size.height());
            }
        }

        return QObject::eventFilter(obj, event);
    }
#endif

private:
#ifdef DISTRHO_UI_QT4
    bool qt_mouseDown;
    QSizeGrip* qt_grip;
# ifdef Q_WS_X11
    QEmbedWidget* qt_widget;
# else
    QWidget* qt_widget;
# endif
#else
    bool gl_initiated;
#endif
};

// -------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // __DISTRHO_UI_INTERNAL_H__
