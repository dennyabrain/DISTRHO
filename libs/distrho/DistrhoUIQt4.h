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

#ifndef __DISTRHO_QT4_UI_H__
#define __DISTRHO_QT4_UI_H__

#include "src/DistrhoDefines.h"

#ifdef DISTRHO_UI_QT4

#include "DistrhoUI.h"

#include <QtGui/QWidget>

START_NAMESPACE_DISTRHO

// -------------------------------------------------

struct Qt4UIPrivateData;

class Qt4UI : public UI,
              public QWidget
{
public:
    Qt4UI(uint32_t parameterCount);
    virtual ~Qt4UI();

    // ---------------------------------------------

protected:
    // Information
    virtual const char* d_title() = 0;
    virtual bool d_resizable() { return false; }
    virtual int  d_minimumWidth() { return 100; }
    virtual int  d_minimumHeight() { return 100; }

    // DSP Callbacks
    virtual void d_parameterChanged(uint32_t index, float value) = 0;
#if DISTRHO_PLUGIN_WANT_PROGRAMS
    virtual void d_programChanged(uint32_t index) = 0;
#endif
#if DISTRHO_PLUGIN_WANT_STATE
    virtual void d_stateChanged(const char* key, const char* value) = 0;
#endif

    // UI Callbacks
    virtual void d_uiIdle();

    // Implement resize internally
    virtual void resizeEvent(QResizeEvent*);
    unsigned int d_width() { return width(); }
    unsigned int d_height() { return height(); }

private:
    Qt4UIPrivateData* data;
};

// -------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // DISTRHO_UI_QT4

#endif // __DISTRHO_QT4_UI_H__
