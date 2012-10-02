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

#include "DistrhoUINotes.h"

#include <QtGui/QResizeEvent>

// -------------------------------------------------

DistrhoUINotes::DistrhoUINotes()
    : DISTRHO::Qt4UI(1), // 1 parameter
      textEdit(this),
      button(this),
      progressBar(this),
      spacer(this),
      gridLayout(this)
{
    curPage = 1;

    saveSizeNowChecker = -1;
    saveTextNowChecker = -1;

    button.setCheckable(true);
    button.setChecked(true);
    button.setText("Edit");
    button.setFixedSize(button.minimumSizeHint());

    progressBar.set_minimum(1);
    progressBar.set_maximum(100);
    progressBar.set_value(1);

    spacer.setText("");
    spacer.setFixedSize(5, 5);

    textEdit.setReadOnly(false);

    setLayout(&gridLayout);
    gridLayout.addWidget(&textEdit, 0, 0, 1, 3);
    gridLayout.addWidget(&button, 1, 0, 1, 1);
    gridLayout.addWidget(&progressBar, 1, 1, 1, 1);
    gridLayout.addWidget(&spacer, 1, 2, 1, 1);
    gridLayout.setContentsMargins(0, 0, 0, 0);

    connect(&button, SIGNAL(clicked(bool)), SLOT(buttonClicked(bool)));
    connect(&progressBar, SIGNAL(valueChangedFromBar(float)), SLOT(progressBarValueChanged(float)));
    connect(&textEdit, SIGNAL(textChanged()), SLOT(textChanged()));

    setFixedSize(300, 200);
}

DistrhoUINotes::~DistrhoUINotes()
{
}

// -------------------------------------------------
// DSP Callbacks

void DistrhoUINotes::d_parameterChanged(uint32_t index, float value)
{
    if (index != 0)
        return;

    int nextCurPage = value;

    if (nextCurPage != curPage && nextCurPage >= 1 && nextCurPage <= 100)
    {
        curPage = nextCurPage;

        textEdit.setPlainText(notes[curPage-1]);
        progressBar.set_value(curPage);
        progressBar.update();
    }
}

void DistrhoUINotes::d_stateChanged(const char* key, const char* value)
{
    if (strcmp(key, "guiWidth") == 0)
    {
        bool ok;
        int width = QString(value).toInt(&ok);

        if (ok && width > 0)
            setFixedWidth(width);
    }

    else if (strcmp(key, "guiHeight") == 0)
    {
        bool ok;
        int height = QString(value).toInt(&ok);

        if (ok && height > 0)
            setFixedHeight(height);
    }

    else if (strncmp(key, "pageText #", 10) == 0)
    {
        bool ok;
        int pageIndex = QString(key+10).toInt(&ok);

        if (ok && pageIndex >= 1 && pageIndex <= 100)
        {
            notes[pageIndex-1] = QString(value);

            if (pageIndex == curPage)
                textEdit.setPlainText(notes[pageIndex-1]);
        }
    }

    else if (strcmp(key, "readOnly") == 0)
    {
        bool readOnly = !strcmp(value, "yes");
        button.setChecked(!readOnly);
        textEdit.setReadOnly(readOnly);
    }
}

// -------------------------------------------------
// UI Callbacks

void DistrhoUINotes::d_uiIdle()
{
    if (saveSizeNowChecker == 11)
    {
        d_changeState("guiWidth", QString::number(width()).toUtf8().constData());
        d_changeState("guiHeight", QString::number(height()).toUtf8().constData());

        saveSizeNowChecker = -1;
    }

    if (saveTextNowChecker == 11)
    {
        QString pageKey   = QString("pageText #%1").arg(curPage);
        QString pageValue = textEdit.toPlainText();
        d_changeState(pageKey.toUtf8().constData(), pageValue.toUtf8().constData());

        saveTextNowChecker = -1;
    }

    if (saveSizeNowChecker >= 0)
        saveSizeNowChecker++;

    if (saveTextNowChecker >= 0)
        saveTextNowChecker++;

    DISTRHO::Qt4UI::d_uiIdle();
}

void DistrhoUINotes::resizeEvent(QResizeEvent* event)
{
    saveSizeNowChecker = 0;
    DISTRHO::Qt4UI::resizeEvent(event);
}

// -------------------------------------------------

void DistrhoUINotes::buttonClicked(bool click)
{
    bool readOnly = !click;
    textEdit.setReadOnly(readOnly);

    d_changeState("readOnly", readOnly ? "yes" : "no");
}

void DistrhoUINotes::progressBarValueChanged(float value)
{
    value = rint(value);

    // maybe save current text before changing page
    if (saveTextNowChecker >= 0 && value >= 1.0f && value <= 100.0f)
    {
        QString pageKey   = QString("pageText #%1").arg(curPage);
        QString pageValue = textEdit.toPlainText();

        if (pageValue != notes[curPage-1])
        {
            notes[curPage-1] = pageValue;
            d_changeState(pageKey.toUtf8().constData(), pageValue.toUtf8().constData());
        }

        saveTextNowChecker = -1;
    }

    // change current page
    d_parameterChanged(0, value);

    // tell host about this change
    d_setParameterValue(0, value);
}

void DistrhoUINotes::textChanged()
{
    saveTextNowChecker = 0;
}

// -------------------------------------------------

START_NAMESPACE_DISTRHO

UI* createUI()
{
    return new DistrhoUINotes;
}

END_NAMESPACE_DISTRHO
