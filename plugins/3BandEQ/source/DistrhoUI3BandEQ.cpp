/*
 * DISTRHO 3BandEQ Plugin, based on 3BandEQ by Michael Gruhn
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

#include "DistrhoUI3BandEQ.h"

// -------------------------------------------------

DistrhoUI3BandEQ::DistrhoUI3BandEQ()
    : DISTRHO::OpenGLExtUI()
{
    // background
    DISTRHO::Image bgImage(DistrhoArtwork::backgroundData, DistrhoArtwork::backgroundWidth, DistrhoArtwork::backgroundHeight, GL_BGR);
    setBackgroundImage(bgImage);

    // sliders
    DISTRHO::Image sliderImage(DistrhoArtwork::sliderData, DistrhoArtwork::sliderWidth, DistrhoArtwork::sliderHeight);
    DISTRHO::Point sliderPosStart(57, 43);
    DISTRHO::Point sliderPosEnd(57, 43 + 160);

    // slider Low
    sliderLow = new DISTRHO::ImageSlider(sliderImage, sliderPosStart, sliderPosEnd);
    sliderLow->setRange(-24.0f, 24.0f);
    sliderLow->setValue(0.0f);
    addImageSlider(sliderLow);

    // slider Mid
    sliderPosStart.setX(120);
    sliderPosEnd.setX(120);
    sliderMid = new DISTRHO::ImageSlider(sliderImage, sliderPosStart, sliderPosEnd);
    sliderMid->setRange(-24.0f, 24.0f);
    sliderMid->setValue(0.0f);
    addImageSlider(sliderMid);

    // slider High
    sliderPosStart.setX(183);
    sliderPosEnd.setX(183);
    sliderHigh = new DISTRHO::ImageSlider(sliderImage, sliderPosStart, sliderPosEnd);
    sliderHigh->setRange(-24.0f, 24.0f);
    sliderHigh->setValue(0.0f);
    addImageSlider(sliderHigh);

    // slider Master
    sliderPosStart.setX(287);
    sliderPosEnd.setX(287);
    sliderMaster = new DISTRHO::ImageSlider(sliderImage, sliderPosStart, sliderPosEnd);
    sliderMaster->setRange(-24.0f, 24.0f);
    sliderMaster->setValue(0.0f);
    addImageSlider(sliderMaster);

    // knobs
    DISTRHO::Image knobImage(DistrhoArtwork::knobData, DistrhoArtwork::knobWidth, DistrhoArtwork::knobHeight);
    DISTRHO::Point knobPos(66, 270);

    // knob Low-Mid
    knobLowMid = new DISTRHO::ImageKnob(knobImage, knobPos);
    knobLowMid->setRange(0.0f, 1000.0f);
    knobLowMid->setValue(220.0f);
    addImageKnob(knobLowMid);

    // knob Mid-High
    knobPos.setX(160);
    knobMidHigh = new DISTRHO::ImageKnob(knobImage, knobPos);
    knobMidHigh->setRange(1000.0f, 20000.0f);
    knobMidHigh->setValue(2000.0f);
    addImageKnob(knobMidHigh);

    // about button
    DISTRHO::Image aboutImageNormal(DistrhoArtwork::aboutButtonNormalData, DistrhoArtwork::aboutButtonNormalWidth, DistrhoArtwork::aboutButtonNormalHeight);
    DISTRHO::Image aboutImageHover(DistrhoArtwork::aboutButtonHoverData, DistrhoArtwork::aboutButtonHoverWidth, DistrhoArtwork::aboutButtonHoverHeight);
    DISTRHO::Point aboutPos(264, 300);
    buttonAbout = new DISTRHO::ImageButton(aboutImageNormal, aboutImageHover, aboutImageHover, aboutPos);
    addImageButton(buttonAbout);
}

DistrhoUI3BandEQ::~DistrhoUI3BandEQ()
{
    delete sliderLow;
    delete sliderMid;
    delete sliderHigh;
    delete sliderMaster;
    delete knobLowMid;
    delete knobMidHigh;
    delete buttonAbout;
}

// -------------------------------------------------
// DSP Callbacks

void DistrhoUI3BandEQ::d_parameterChanged(uint32_t index, float value)
{
    switch (index)
    {
    case DistrhoPlugin3BandEQ::paramLow:
        sliderLow->setValue(value);
        break;
    case DistrhoPlugin3BandEQ::paramMid:
        sliderMid->setValue(value);
        break;
    case DistrhoPlugin3BandEQ::paramHigh:
        sliderHigh->setValue(value);
        break;
    case DistrhoPlugin3BandEQ::paramMaster:
        sliderMaster->setValue(value);
        break;
    case DistrhoPlugin3BandEQ::paramLowMidFreq:
        knobLowMid->setValue(value);
        break;
    case DistrhoPlugin3BandEQ::paramMidHighFreq:
        knobMidHigh->setValue(value);
        break;
    }

    d_uiRepaint();
}

void DistrhoUI3BandEQ::d_programChanged(uint32_t index)
{
    if (index != 0)
        return;

    // Default values
    sliderLow->setValue(0.0f);
    sliderMid->setValue(0.0f);
    sliderHigh->setValue(0.0f);
    sliderMaster->setValue(0.0f);
    knobLowMid->setValue(220.0f);
    knobMidHigh->setValue(2000.0f);

    d_uiRepaint();
}

// -------------------------------------------------
// Extended Callbacks

void DistrhoUI3BandEQ::imageButtonClicked(DISTRHO::ImageButton* button)
{
    if (button != buttonAbout)
        return;

    DISTRHO::Image imageAbout(DistrhoArtwork::aboutData, DistrhoArtwork::aboutWidth, DistrhoArtwork::aboutHeight, GL_BGRA);
    showImageModalDialog(imageAbout, "About");
}

void DistrhoUI3BandEQ::imageKnobDragStarted(DISTRHO::ImageKnob* knob)
{
    if (knob == knobLowMid)
        d_uiEditParameter(DistrhoPlugin3BandEQ::paramLowMidFreq, true);
    else if (knob == knobMidHigh)
        d_uiEditParameter(DistrhoPlugin3BandEQ::paramMidHighFreq, true);
}

void DistrhoUI3BandEQ::imageKnobDragFinished(DISTRHO::ImageKnob* knob)
{
    if (knob == knobLowMid)
        d_uiEditParameter(DistrhoPlugin3BandEQ::paramLowMidFreq, false);
    else if (knob == knobMidHigh)
        d_uiEditParameter(DistrhoPlugin3BandEQ::paramMidHighFreq, false);
}


void DistrhoUI3BandEQ::imageKnobValueChanged(DISTRHO::ImageKnob* knob, float value)
{
    if (knob == knobLowMid)
        d_setParameterValue(DistrhoPlugin3BandEQ::paramLowMidFreq, value);
    else if (knob == knobMidHigh)
        d_setParameterValue(DistrhoPlugin3BandEQ::paramMidHighFreq, value);
}

void DistrhoUI3BandEQ::imageSliderDragStarted(DISTRHO::ImageSlider* slider)
{
    if (slider == sliderLow)
        d_uiEditParameter(DistrhoPlugin3BandEQ::paramLow, true);
    else if (slider == sliderMid)
        d_uiEditParameter(DistrhoPlugin3BandEQ::paramMid, true);
    else if (slider == sliderHigh)
        d_uiEditParameter(DistrhoPlugin3BandEQ::paramHigh, true);
    else if (slider == sliderMaster)
        d_uiEditParameter(DistrhoPlugin3BandEQ::paramMaster, true);
}

void DistrhoUI3BandEQ::imageSliderDragFinished(DISTRHO::ImageSlider* slider)
{
    if (slider == sliderLow)
        d_uiEditParameter(DistrhoPlugin3BandEQ::paramLow, false);
    else if (slider == sliderMid)
        d_uiEditParameter(DistrhoPlugin3BandEQ::paramMid, false);
    else if (slider == sliderHigh)
        d_uiEditParameter(DistrhoPlugin3BandEQ::paramHigh, false);
    else if (slider == sliderMaster)
        d_uiEditParameter(DistrhoPlugin3BandEQ::paramMaster, false);
}

void DistrhoUI3BandEQ::imageSliderValueChanged(DISTRHO::ImageSlider* slider, float value)
{
    if (slider == sliderLow)
        d_setParameterValue(DistrhoPlugin3BandEQ::paramLow, value);
    else if (slider == sliderMid)
        d_setParameterValue(DistrhoPlugin3BandEQ::paramMid, value);
    else if (slider == sliderHigh)
        d_setParameterValue(DistrhoPlugin3BandEQ::paramHigh, value);
    else if (slider == sliderMaster)
        d_setParameterValue(DistrhoPlugin3BandEQ::paramMaster, value);
}

// -------------------------------------------------

START_NAMESPACE_DISTRHO

UI* createUI()
{
    return new DistrhoUI3BandEQ;
}

END_NAMESPACE_DISTRHO
