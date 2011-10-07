/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  26 Oct 2009 6:56:46 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_MAINCOMPONENT_MAINCOMPONENT_6DFE9A3C__
#define __JUCER_HEADER_MAINCOMPONENT_MAINCOMPONENT_6DFE9A3C__

//[Headers]     -- You can add your own extra header files here --

/*
 *  MainComponent.h
 *  midilfo
 *
 *  Midi-Lfo: This is a small project using the JUCE library.
 *	It provides a user tweakable Midi LFO. This sends a
 *	(selectable) CC with LFO modulated values to a
 *	(selectable) Midi output.
 *
 *	Copyright (C) 2009, Christian Stoecklmeier and Volker Duemke
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful, but
 *	WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *	See the GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "includes.h"
class MidiDevice;
class ProcessingCore;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainComponent  : public Component,
                       public SliderListener,
                       public ComboBoxListener,
                       public ButtonListener
{
public:
    //==============================================================================
    MainComponent ();
    ~MainComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MidiDevice* midiDevice;
	ProcessingCore* processingCore;

	bool m_setupIsShown;
    //[/UserVariables]

    //==============================================================================
    GroupComponent* groupComponentLFO;
    GroupComponent* groupComponentMidiConn;
    Label* label2;
    Label* labeldivider;
    Slider* sliderDivider;
    Slider* sliderOutCC;
    Slider* sliderRate;
    Slider* sliderDepth;
    Label* labelrate;
    ComboBox* comboBoxWaveform1;
    Label* labelwaveform1;
    Label* labelSyncInput;
    Label* label;
    ComboBox* comboBoxMidiInput;
    ComboBox* comboBoxMidiOut;
    TextButton* textButtonRescan;
    ComboBox* comboBoxOutCh;
    GroupComponent* groupComponentSync;
    ToggleButton* toggleButtonSyncInternal;
    ToggleButton* toggleButtonSyncExternal;
    Label* labelchannel;
    Label* labelCCNo;
    Label* labelcenterval;
    Slider* sliderCenterVal;
    TextButton* textButtonSetup;
    ToggleButton* toggleButtonMidiActive;
    Label* labeldepth;
    TextButton* textButtonAbout;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    MainComponent (const MainComponent&);
    const MainComponent& operator= (const MainComponent&);
};


#endif   // __JUCER_HEADER_MAINCOMPONENT_MAINCOMPONENT_6DFE9A3C__
