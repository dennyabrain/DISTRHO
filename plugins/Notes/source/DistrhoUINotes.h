/*
 * DISTRHO Notes Plugin
 * Copyright (C) 2012 Filipe Coelho <falktx@falktx.com>
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
 * For a full copy of the license see the GPL.txt file
 */

#ifndef __DISTRHO_UI_NOTES_H__
#define __DISTRHO_UI_NOTES_H__

#include "DistrhoUIQt4.h"
#include "ParamProgressBar.h"

#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

// -------------------------------------------------

class DistrhoUINotes : public DISTRHO::Qt4UI
{
    Q_OBJECT

public:
    DistrhoUINotes();
    ~DistrhoUINotes();

    // ---------------------------------------------
protected:

    // Information
    const char* d_title()
    {
        return "Notes";
    }

    bool d_resizable()
    {
        return true;
    }

    int d_minimumWidth()
    {
        return 150;
    }

    int d_minimumHeight()
    {
        return 100;
    }

    // DSP Callbacks
    void d_parameterChanged(uint32_t index, float value);
    void d_stateChanged(const char* key, const char* value);

    // UI Callbacks
    void d_uiIdle();

    // listen for resize events
    void resizeEvent(QResizeEvent*);

private slots:
    void buttonClicked(bool click);
    void progressBarValueChanged(float value);
    void textChanged();

private:
    int curPage;

    int saveSizeNowChecker;
    int saveTextNowChecker;

    QString notes[100];

    QTextEdit textEdit;
    QPushButton button;
    ParamProgressBar progressBar;
    QLabel spacer;

    QGridLayout gridLayout;
};

// -------------------------------------------------

#endif // __DISTRHO_UI_NOTES_H__
