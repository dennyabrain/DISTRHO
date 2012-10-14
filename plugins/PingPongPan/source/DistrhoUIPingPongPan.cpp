/*
 * DISTRHO PingPongPan Plugin, based on PingPongPan by Michael Gruhn
 * Copyright (C) 2012 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * For a full copy of the license see the LGPL.txt file
 */

#include "DistrhoUIPingPongPan.h"

// -------------------------------------------------

DistrhoUIPingPongPan::DistrhoUIPingPongPan()
    : DISTRHO::OpenGLExtUI()
{
    // background
    DISTRHO::Image bgImage(DistrhoArtwork::backgroundData, DistrhoArtwork::backgroundWidth, DistrhoArtwork::backgroundHeight, GL_BGRA);
    setBackgroundImage(bgImage);

    // knobs
    DISTRHO::Image knobImage(DistrhoArtwork::knobData, DistrhoArtwork::knobWidth, DistrhoArtwork::knobHeight);
    DISTRHO::Point knobPos(136, 30);

    // knob Low-Mid
    knobFreq = new DISTRHO::ImageKnob(knobImage, knobPos);
    knobFreq->setRange(0.0f, 100.0f);
    knobFreq->setValue(50.0f);
    addImageKnob(knobFreq);

    // knob Mid-High
    knobPos.setX(258);
    knobWidth = new DISTRHO::ImageKnob(knobImage, knobPos);
    knobWidth->setRange(0.0f, 100.0f);
    knobWidth->setValue(75.0f);
    addImageKnob(knobWidth);

    // about button
    DISTRHO::Image aboutImageNormal(DistrhoArtwork::aboutButtonNormalData, DistrhoArtwork::aboutButtonNormalWidth, DistrhoArtwork::aboutButtonNormalHeight);
    DISTRHO::Image aboutImageHover(DistrhoArtwork::aboutButtonHoverData, DistrhoArtwork::aboutButtonHoverWidth, DistrhoArtwork::aboutButtonHoverHeight);
    DISTRHO::Point aboutPos(25, 23);
    buttonAbout = new DISTRHO::ImageButton(aboutImageNormal, aboutImageHover, aboutImageHover, aboutPos);
    addImageButton(buttonAbout);
}

DistrhoUIPingPongPan::~DistrhoUIPingPongPan()
{
    delete knobFreq;
    delete knobWidth;
    delete buttonAbout;
}

// -------------------------------------------------
// DSP Callbacks

void DistrhoUIPingPongPan::d_parameterChanged(uint32_t index, float value)
{
    switch (index)
    {
    case DistrhoPluginPingPongPan::paramFreq:
        knobFreq->setValue(value);
        break;
    case DistrhoPluginPingPongPan::paramWidth:
        knobWidth->setValue(value);
        break;
    }

    d_uiRepaint();
}

void DistrhoUIPingPongPan::d_programChanged(uint32_t index)
{
    if (index != 0)
        return;

    // Default values
    knobFreq->setValue(50.0f);
    knobWidth->setValue(75.0f);

    d_uiRepaint();
}

// -------------------------------------------------
// Extended Callbacks

void DistrhoUIPingPongPan::imageButtonClicked(DISTRHO::ImageButton* button)
{
    if (button != buttonAbout)
        return;

    DISTRHO::Image imageAbout(DistrhoArtwork::aboutData, DistrhoArtwork::aboutWidth, DistrhoArtwork::aboutHeight, GL_BGRA);
    showImageModalDialog(imageAbout, "About");
}

void DistrhoUIPingPongPan::imageKnobDragStarted(DISTRHO::ImageKnob* knob)
{
    if (knob == knobFreq)
        d_uiEditParameter(DistrhoPluginPingPongPan::paramFreq, true);
    else if (knob == knobWidth)
        d_uiEditParameter(DistrhoPluginPingPongPan::paramWidth, true);
}

void DistrhoUIPingPongPan::imageKnobDragFinished(DISTRHO::ImageKnob* knob)
{
    if (knob == knobFreq)
        d_uiEditParameter(DistrhoPluginPingPongPan::paramFreq, false);
    else if (knob == knobWidth)
        d_uiEditParameter(DistrhoPluginPingPongPan::paramWidth, false);
}


void DistrhoUIPingPongPan::imageKnobValueChanged(DISTRHO::ImageKnob* knob, float value)
{
    if (knob == knobFreq)
        d_setParameterValue(DistrhoPluginPingPongPan::paramFreq, value);
    else if (knob == knobWidth)
        d_setParameterValue(DistrhoPluginPingPongPan::paramWidth, value);
}

// -------------------------------------------------

START_NAMESPACE_DISTRHO

UI* createUI()
{
    return new DistrhoUIPingPongPan;
}

END_NAMESPACE_DISTRHO
