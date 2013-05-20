/*
 * DISTRHO PingPongPan Plugin, based on PingPongPan by Michael Gruhn
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
 * For a full copy of the license see the LGPL.txt file
 */

#ifndef __DISTRHO_UI_PINGPONGPAN_HPP__
#define __DISTRHO_UI_PINGPONGPAN_HPP__

#include "DistrhoUIOpenGL.hpp"
#include "dgl/ImageButton.hpp"
#include "dgl/ImageKnob.hpp"

#include "DistrhoArtworkPingPongPan.hpp"
#include "DistrhoPluginPingPongPan.hpp"

START_NAMESPACE_DISTRHO

// -------------------------------------------------

class DistrhoUIPingPongPan : public OpenGLUI,
                             public ImageButton::Callback,
                             public ImageKnob::Callback
{
public:
    DistrhoUIPingPongPan();
    ~DistrhoUIPingPongPan();

protected:

    // ---------------------------------------------
    // Information

    unsigned int d_width() const
    {
        return DistrhoArtworkPingPongPan::backgroundWidth;
    }

    unsigned int d_height() const
    {
        return DistrhoArtworkPingPongPan::backgroundHeight;
    }

    // ---------------------------------------------
    // DSP Callbacks

    void d_parameterChanged(uint32_t index, float value);
    void d_programChanged(uint32_t index);

    // ---------------------------------------------
    // Widget Callbacks

    void imageButtonClicked(ImageButton* button, int);
    void imageKnobDragStarted(ImageKnob* knob);
    void imageKnobDragFinished(ImageKnob* knob);
    void imageKnobValueChanged(ImageKnob* knob, float value);

    void onDisplay();

private:
    Image fImgBackground;

    ImageKnob*   fKnobFreq;
    ImageKnob*   fKnobWidth;
    ImageButton* fButtonAbout;
};

// -------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // __DISTRHO_UI_PINGPONGPAN_HPP__
