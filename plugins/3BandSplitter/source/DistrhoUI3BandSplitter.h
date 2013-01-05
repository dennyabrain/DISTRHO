/*
 * DISTRHO 3BandSplitter Plugin, based on 3BandSplitter by Michael Gruhn
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

#ifndef __DISTRHO_UI_3BANDSPLITTER_H__
#define __DISTRHO_UI_3BANDSPLITTER_H__

#include "DistrhoUIOpenGLExt.h"

#include "DistrhoArtwork.h"
#include "DistrhoPlugin3BandSplitter.h"

// -------------------------------------------------

class DistrhoUI3BandSplitter : public DISTRHO::OpenGLExtUI
{
public:
    DistrhoUI3BandSplitter();
    ~DistrhoUI3BandSplitter();

    // ---------------------------------------------
protected:

    // Information
    unsigned int d_width()
    {
        return DistrhoArtwork::backgroundWidth;
    }

    unsigned int d_height()
    {
        return DistrhoArtwork::backgroundHeight;
    }

    // DSP Callbacks
    void d_parameterChanged(uint32_t index, float value);
    void d_programChanged(uint32_t index);

    // Extended Callbacks
    void imageButtonClicked(DISTRHO::ImageButton* button);
    void imageKnobDragStarted(DISTRHO::ImageKnob* knob);
    void imageKnobDragFinished(DISTRHO::ImageKnob* knob);
    void imageKnobValueChanged(DISTRHO::ImageKnob* knob, float value);
    void imageSliderDragStarted(DISTRHO::ImageSlider* slider);
    void imageSliderDragFinished(DISTRHO::ImageSlider* slider);
    void imageSliderValueChanged(DISTRHO::ImageSlider* slider, float value);

private:
    DISTRHO::ImageSlider* sliderLow;
    DISTRHO::ImageSlider* sliderMid;
    DISTRHO::ImageSlider* sliderHigh;
    DISTRHO::ImageSlider* sliderMaster;
    DISTRHO::ImageKnob* knobLowMid;
    DISTRHO::ImageKnob* knobMidHigh;
    DISTRHO::ImageButton* buttonAbout;
};

// -------------------------------------------------

#endif // __DISTRHO_UI_3BANDSPLITTER_H__