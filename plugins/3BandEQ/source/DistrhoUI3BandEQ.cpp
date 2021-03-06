/*
 * DISTRHO 3BandEQ Plugin, based on 3BandEQ by Michael Gruhn
 * Copyright (C) 2012-2013 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * For a full copy of the license see the doc/LGPL.txt file.
 */

#include "DistrhoUI3BandEQ.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

DistrhoUI3BandEQ::DistrhoUI3BandEQ()
    : OpenGLUI(),
      fAboutWindow(this)
{
    // background
    fImgBackground = Image(DistrhoArtwork3BandEQ::backgroundData, DistrhoArtwork3BandEQ::backgroundWidth, DistrhoArtwork3BandEQ::backgroundHeight, GL_BGR);

    // about
    Image imageAbout(DistrhoArtwork3BandEQ::aboutData, DistrhoArtwork3BandEQ::aboutWidth, DistrhoArtwork3BandEQ::aboutHeight, GL_BGR);
    fAboutWindow.setImage(imageAbout);

    // sliders
    Image sliderImage(DistrhoArtwork3BandEQ::sliderData, DistrhoArtwork3BandEQ::sliderWidth, DistrhoArtwork3BandEQ::sliderHeight);
    Point<int> sliderPosStart(57, 43);
    Point<int> sliderPosEnd(57, 43 + 160);

    // slider Low
    fSliderLow = new ImageSlider(this, sliderImage);
    fSliderLow->setStartPos(sliderPosStart);
    fSliderLow->setEndPos(sliderPosEnd);
    fSliderLow->setRange(-24.0f, 24.0f);
    fSliderLow->setValue(0.0f);
    fSliderLow->setCallback(this);

    // slider Mid
    sliderPosStart.setX(120);
    sliderPosEnd.setX(120);
    fSliderMid = new ImageSlider(*fSliderLow);
    fSliderMid->setStartPos(sliderPosStart);
    fSliderMid->setEndPos(sliderPosEnd);

    // slider High
    sliderPosStart.setX(183);
    sliderPosEnd.setX(183);
    fSliderHigh = new ImageSlider(*fSliderLow);
    fSliderHigh->setStartPos(sliderPosStart);
    fSliderHigh->setEndPos(sliderPosEnd);

    // slider Master
    sliderPosStart.setX(287);
    sliderPosEnd.setX(287);
    fSliderMaster = new ImageSlider(*fSliderLow);
    fSliderMaster->setStartPos(sliderPosStart);
    fSliderMaster->setEndPos(sliderPosEnd);

    // knobs
    Image knobImage(DistrhoArtwork3BandEQ::knobData, DistrhoArtwork3BandEQ::knobWidth, DistrhoArtwork3BandEQ::knobHeight);

    // knob Low-Mid
    fKnobLowMid = new ImageKnob(this, knobImage);
    fKnobLowMid->setPos(65, 269);
    fKnobLowMid->setRange(0.0f, 1000.0f);
    fKnobLowMid->setValue(220.0f);
    fKnobLowMid->setRotationAngle(270);
    fKnobLowMid->setCallback(this);

    // knob Mid-High
    fKnobMidHigh = new ImageKnob(this, knobImage);
    fKnobMidHigh->setPos(159, 269);
    fKnobMidHigh->setRange(1000.0f, 20000.0f);
    fKnobMidHigh->setValue(2000.0f);
    fKnobMidHigh->setRotationAngle(270);
    fKnobMidHigh->setCallback(this);

    // about button
    Image aboutImageNormal(DistrhoArtwork3BandEQ::aboutButtonNormalData, DistrhoArtwork3BandEQ::aboutButtonNormalWidth, DistrhoArtwork3BandEQ::aboutButtonNormalHeight);
    Image aboutImageHover(DistrhoArtwork3BandEQ::aboutButtonHoverData, DistrhoArtwork3BandEQ::aboutButtonHoverWidth, DistrhoArtwork3BandEQ::aboutButtonHoverHeight);
    fButtonAbout = new ImageButton(this, aboutImageNormal, aboutImageHover, aboutImageHover);
    fButtonAbout->setPos(264, 300);
    fButtonAbout->setCallback(this);
}

DistrhoUI3BandEQ::~DistrhoUI3BandEQ()
{
    delete fSliderLow;
    delete fSliderMid;
    delete fSliderHigh;
    delete fSliderMaster;
    delete fKnobLowMid;
    delete fKnobMidHigh;
    delete fButtonAbout;
}

// -----------------------------------------------------------------------
// DSP Callbacks

void DistrhoUI3BandEQ::d_parameterChanged(uint32_t index, float value)
{
    switch (index)
    {
    case DistrhoPlugin3BandEQ::paramLow:
        fSliderLow->setValue(value);
        break;
    case DistrhoPlugin3BandEQ::paramMid:
        fSliderMid->setValue(value);
        break;
    case DistrhoPlugin3BandEQ::paramHigh:
        fSliderHigh->setValue(value);
        break;
    case DistrhoPlugin3BandEQ::paramMaster:
        fSliderMaster->setValue(value);
        break;
    case DistrhoPlugin3BandEQ::paramLowMidFreq:
        fKnobLowMid->setValue(value);
        break;
    case DistrhoPlugin3BandEQ::paramMidHighFreq:
        fKnobMidHigh->setValue(value);
        break;
    }
}

void DistrhoUI3BandEQ::d_programChanged(uint32_t index)
{
    if (index != 0)
        return;

    // Default values
    fSliderLow->setValue(0.0f);
    fSliderMid->setValue(0.0f);
    fSliderHigh->setValue(0.0f);
    fSliderMaster->setValue(0.0f);
    fKnobLowMid->setValue(220.0f);
    fKnobMidHigh->setValue(2000.0f);
}

// -----------------------------------------------------------------------
// Widget Callbacks

void DistrhoUI3BandEQ::imageButtonClicked(ImageButton* button, int)
{
    if (button != fButtonAbout)
        return;

    fAboutWindow.exec();
}

void DistrhoUI3BandEQ::imageKnobDragStarted(ImageKnob* knob)
{
    if (knob == fKnobLowMid)
        d_editParameter(DistrhoPlugin3BandEQ::paramLowMidFreq, true);
    else if (knob == fKnobMidHigh)
        d_editParameter(DistrhoPlugin3BandEQ::paramMidHighFreq, true);
}

void DistrhoUI3BandEQ::imageKnobDragFinished(ImageKnob* knob)
{
    if (knob == fKnobLowMid)
        d_editParameter(DistrhoPlugin3BandEQ::paramLowMidFreq, false);
    else if (knob == fKnobMidHigh)
        d_editParameter(DistrhoPlugin3BandEQ::paramMidHighFreq, false);
}

void DistrhoUI3BandEQ::imageKnobValueChanged(ImageKnob* knob, float value)
{
    if (knob == fKnobLowMid)
        d_setParameterValue(DistrhoPlugin3BandEQ::paramLowMidFreq, value);
    else if (knob == fKnobMidHigh)
        d_setParameterValue(DistrhoPlugin3BandEQ::paramMidHighFreq, value);
}

void DistrhoUI3BandEQ::imageSliderDragStarted(ImageSlider* slider)
{
    if (slider == fSliderLow)
        d_editParameter(DistrhoPlugin3BandEQ::paramLow, true);
    else if (slider == fSliderMid)
        d_editParameter(DistrhoPlugin3BandEQ::paramMid, true);
    else if (slider == fSliderHigh)
        d_editParameter(DistrhoPlugin3BandEQ::paramHigh, true);
    else if (slider == fSliderMaster)
        d_editParameter(DistrhoPlugin3BandEQ::paramMaster, true);
}

void DistrhoUI3BandEQ::imageSliderDragFinished(ImageSlider* slider)
{
    if (slider == fSliderLow)
        d_editParameter(DistrhoPlugin3BandEQ::paramLow, false);
    else if (slider == fSliderMid)
        d_editParameter(DistrhoPlugin3BandEQ::paramMid, false);
    else if (slider == fSliderHigh)
        d_editParameter(DistrhoPlugin3BandEQ::paramHigh, false);
    else if (slider == fSliderMaster)
        d_editParameter(DistrhoPlugin3BandEQ::paramMaster, false);
}

void DistrhoUI3BandEQ::imageSliderValueChanged(ImageSlider* slider, float value)
{
    if (slider == fSliderLow)
        d_setParameterValue(DistrhoPlugin3BandEQ::paramLow, value);
    else if (slider == fSliderMid)
        d_setParameterValue(DistrhoPlugin3BandEQ::paramMid, value);
    else if (slider == fSliderHigh)
        d_setParameterValue(DistrhoPlugin3BandEQ::paramHigh, value);
    else if (slider == fSliderMaster)
        d_setParameterValue(DistrhoPlugin3BandEQ::paramMaster, value);
}

void DistrhoUI3BandEQ::onDisplay()
{
    fImgBackground.draw();
}

// -----------------------------------------------------------------------

UI* createUI()
{
    return new DistrhoUI3BandEQ();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
