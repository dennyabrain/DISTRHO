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

#include "DistrhoDefines.h"

#ifdef DISTRHO_UI_QT4

#include "DistrhoUIInternal.h"

#include <QtGui/QMouseEvent>
#include <QtGui/QResizeEvent>
#include <QtGui/QSizeGrip>

START_NAMESPACE_DISTRHO

// -------------------------------------------------

class Qt4UIEventFilter : public QObject
{
public:
    Qt4UIEventFilter(Qt4UI* ui_, QSizeGrip* grip_)
        : QObject(grip_),
          ui(ui_),
          grip(grip_)
    {
        mouseDown = false;
        minWidth  = 50;
        minHeight = 50;
    }

    void setMinimumSize(int width, int height)
    {
        minWidth  = width;
        minHeight = height;
    }

protected:
    bool eventFilter(QObject* obj, QEvent* event)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mEvent = (QMouseEvent*)event;
            if (mEvent->button() == Qt::LeftButton)
                mouseDown = true;
            return true;
        }

        if (event->type() == QEvent::MouseMove)
        {
            if (mouseDown)
            {
                QMouseEvent* mEvent = (QMouseEvent*)event;
                int width  = ui->width()  + mEvent->x() - grip->width();
                int height = ui->height() + mEvent->y() - grip->height();

                if (width < minWidth)
                    width = minWidth;
                if (height < minHeight)
                    height = minHeight;

                ui->setFixedSize(width, height);
                //ui->d_uiResize(width, height);

                //grip->move(width - grip->width(), height - grip->height());
            }
            return true;
        }

        if (event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent* mEvent = (QMouseEvent*)event;
            if (mEvent->button() == Qt::LeftButton)
                mouseDown = false;
            return true;
        }

        return QObject::eventFilter(obj, event);
    }

private:
    Qt4UI* const ui;
    QSizeGrip* const grip;
    bool mouseDown;
    int minWidth, minHeight;
};

struct Qt4UIPrivateData {
    QSizeGrip* grip;
    Qt4UIEventFilter* filter;
    bool firstInit;
    int lastWidth, lastHeight;

    Qt4UIPrivateData()
        : grip(nullptr),
          filter(nullptr),
          firstInit(true),
          lastWidth(0),
          lastHeight(0) {}
};

// -------------------------------------------------

Qt4UI::Qt4UI(uint32_t parameterCount)
    : UI(parameterCount),
      QWidget(nullptr)
{
    data = new Qt4UIPrivateData;

    data->grip = new QSizeGrip(this);
    data->grip->resize(data->grip->sizeHint());
    data->grip->move(width() - data->grip->width(), height() - data->grip->height());

    data->filter = new Qt4UIEventFilter(this, data->grip);
    data->grip->installEventFilter(data->filter);
    data->grip->hide();

    data->lastWidth  = width();
    data->lastHeight = height();
}

Qt4UI::~Qt4UI()
{
    data->grip->removeEventFilter(data->filter);

    delete data->filter;
    delete data->grip;
    delete data;
}

void Qt4UI::d_uiIdle()
{
    if (data && data->firstInit && data->grip)
    {
        data->firstInit = false;

        if (d_resizable())
        {
            data->grip->show();
            data->grip->raise();
            data->filter->setMinimumSize(d_minimumWidth(), d_minimumHeight());
        }
    }
}

void Qt4UI::resizeEvent(QResizeEvent* event)
{
    if (! (data && data->grip))
        return;

    const QSize size(event->size());

    if (data->lastWidth != size.width() || data->lastHeight != size.height())
    {
        data->grip->move(size.width() - data->grip->width(), size.height() - data->grip->height());

        d_uiResize(size.width(), size.height());

        data->lastWidth  = size.width();
        data->lastHeight = size.height();
    }
}

// -------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // DISTRHO_UI_QT4
