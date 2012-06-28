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
 * A copy of the license is included with this software, or can be
 * found online at www.gnu.org/licenses.
 */

#ifndef __DISTRHO_UI_BASE__
#define __DISTRHO_UI_BASE__

#include "DistrhoPlugin.h"

#if DISTRHO_PLUGIN_WANTS_UI

#include <QtGui/QWidget>

class DistrhoUiBase : public QWidget
{
    Q_OBJECT

public:
    DistrhoUiBase(QWidget* parent = nullptr) : QWidget(parent)
    {
    }

    virtual ~DistrhoUiBase()
    {
    }

    virtual bool d_isUiResizable() = 0;
    virtual void d_setParameterValue(quint32 index, float value) = 0;
    virtual void d_setProgram(quint32 index) = 0;

signals:
    void d_parameterChanged(quint32 index, float value);
};

// ---------------------------------------------------------------------------------------------

extern DistrhoUiBase* createDistrhoUI();

#endif // DISTRHO_PLUGIN_WANTS_UI
#endif // __DISTRHO_UI_BASE__
