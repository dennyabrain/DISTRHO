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

//[Headers] You can add your own extra header files here...

/*
 *  MainComponent.cpp
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
 *	the Free Software Foundation; either version 3 of the License, or
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

#include "MidiDevice.h"
#include "ProcessingCore.h"
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent ()
    : groupComponentLFO (0),
      groupComponentMidiConn (0),
      label2 (0),
      labeldivider (0),
      sliderDivider (0),
      sliderOutCC (0),
      sliderRate (0),
      sliderDepth (0),
      labelrate (0),
      comboBoxWaveform1 (0),
      labelwaveform1 (0),
      labelSyncInput (0),
      label (0),
      comboBoxMidiInput (0),
      comboBoxMidiOut (0),
      textButtonRescan (0),
      comboBoxOutCh (0),
      groupComponentSync (0),
      toggleButtonSyncInternal (0),
      toggleButtonSyncExternal (0),
      labelchannel (0),
      labelCCNo (0),
      labelcenterval (0),
      sliderCenterVal (0),
      textButtonSetup (0),
      toggleButtonMidiActive (0),
      labeldepth (0),
      textButtonAbout (0)
{
    addAndMakeVisible (groupComponentLFO = new GroupComponent (T("LFO"),
                                                               T("LFO")));

    addAndMakeVisible (groupComponentMidiConn = new GroupComponent (T("new group midi"),
                                                                    T("MIDI Out")));

    addAndMakeVisible (label2 = new Label (T("new label"),
                                           String::empty));
    label2->setFont (Font (15.0000f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (Label::backgroundColourId, Colour (0xffc1d0ff));
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (labeldivider = new Label (T("new label divider"),
                                                 T("Divider")));
    labeldivider->setFont (Font (15.0000f, Font::plain));
    labeldivider->setJustificationType (Justification::centredLeft);
    labeldivider->setEditable (false, false, false);
    labeldivider->setColour (TextEditor::textColourId, Colours::black);
    labeldivider->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (sliderDivider = new Slider (T("slider Divider")));
    sliderDivider->setRange (1, 4, 1);
    sliderDivider->setSliderStyle (Slider::RotaryVerticalDrag);
    sliderDivider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    sliderDivider->addListener (this);

    addAndMakeVisible (sliderOutCC = new Slider (T("new slider OutCC")));
    sliderOutCC->setRange (0, 127, 1);
    sliderOutCC->setSliderStyle (Slider::LinearVertical);
    sliderOutCC->setTextBoxStyle (Slider::TextBoxRight, false, 80, 24);
    sliderOutCC->addListener (this);

    addAndMakeVisible (sliderRate = new Slider (T("slider Rate")));
    sliderRate->setRange (0.1, 12, 0.05);
    sliderRate->setSliderStyle (Slider::RotaryVerticalDrag);
    sliderRate->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    sliderRate->addListener (this);

    addAndMakeVisible (sliderDepth = new Slider (T("slider Depth")));
    sliderDepth->setRange (0, 1, 0.001);
    sliderDepth->setSliderStyle (Slider::RotaryVerticalDrag);
    sliderDepth->setTextBoxStyle (Slider::TextBoxBelow, false, 60, 20);
    sliderDepth->addListener (this);

    addAndMakeVisible (labelrate = new Label (T("new label rate"),
                                              T("Rate/Hz")));
    labelrate->setFont (Font (15.0000f, Font::plain));
    labelrate->setJustificationType (Justification::centredLeft);
    labelrate->setEditable (false, false, false);
    labelrate->setColour (TextEditor::textColourId, Colours::black);
    labelrate->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (comboBoxWaveform1 = new ComboBox (T("combo box Waveform1")));
    comboBoxWaveform1->setEditableText (false);
    comboBoxWaveform1->setJustificationType (Justification::centredLeft);
    comboBoxWaveform1->setTextWhenNothingSelected (T("Sine"));
    comboBoxWaveform1->setTextWhenNoChoicesAvailable (T("(no choices)"));
    comboBoxWaveform1->addItem (T("Sine"), 1);
    comboBoxWaveform1->addItem (T("Square"), 2);
    comboBoxWaveform1->addItem (T("Saw"), 3);
    comboBoxWaveform1->addItem (T("Triangle"), 4);
    comboBoxWaveform1->addListener (this);

    addAndMakeVisible (labelwaveform1 = new Label (T("new label waveform1"),
                                                   T("Waveform")));
    labelwaveform1->setFont (Font (15.0000f, Font::plain));
    labelwaveform1->setJustificationType (Justification::centredLeft);
    labelwaveform1->setEditable (false, false, false);
    labelwaveform1->setColour (TextEditor::textColourId, Colours::black);
    labelwaveform1->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (labelSyncInput = new Label (T("new label sync"),
                                                   T("Sync-Input")));
    labelSyncInput->setFont (Font (15.0000f, Font::plain));
    labelSyncInput->setJustificationType (Justification::centredLeft);
    labelSyncInput->setEditable (false, false, false);
    labelSyncInput->setColour (TextEditor::textColourId, Colours::black);
    labelSyncInput->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label = new Label (T("new label"),
                                          T("Output")));
    label->setFont (Font (15.0000f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (comboBoxMidiInput = new ComboBox (T("new combo box MidiInput")));
    comboBoxMidiInput->setEditableText (false);
    comboBoxMidiInput->setJustificationType (Justification::centredLeft);
    comboBoxMidiInput->setTextWhenNothingSelected (T("Midi In"));
    comboBoxMidiInput->setTextWhenNoChoicesAvailable (T("(no choices)"));
    comboBoxMidiInput->addListener (this);

    addAndMakeVisible (comboBoxMidiOut = new ComboBox (T("new combo box Midi Out")));
    comboBoxMidiOut->setEditableText (false);
    comboBoxMidiOut->setJustificationType (Justification::centredLeft);
    comboBoxMidiOut->setTextWhenNothingSelected (T("Midi Out"));
    comboBoxMidiOut->setTextWhenNoChoicesAvailable (T("(no choices)"));
    comboBoxMidiOut->addListener (this);

    addAndMakeVisible (textButtonRescan = new TextButton (T("new button rescan")));
    textButtonRescan->setButtonText (T("Rescan Midi Devices"));
    textButtonRescan->addButtonListener (this);

    addAndMakeVisible (comboBoxOutCh = new ComboBox (T("new combo OutCh")));
    comboBoxOutCh->setEditableText (false);
    comboBoxOutCh->setJustificationType (Justification::centredLeft);
    comboBoxOutCh->setTextWhenNothingSelected (T("1"));
    comboBoxOutCh->setTextWhenNoChoicesAvailable (T("(no choices)"));
    comboBoxOutCh->addItem (T("1"), 1);
    comboBoxOutCh->addItem (T("2"), 2);
    comboBoxOutCh->addItem (T("3"), 3);
    comboBoxOutCh->addItem (T("4"), 4);
    comboBoxOutCh->addItem (T("5"), 5);
    comboBoxOutCh->addItem (T("6"), 6);
    comboBoxOutCh->addItem (T("7"), 7);
    comboBoxOutCh->addItem (T("8"), 8);
    comboBoxOutCh->addItem (T("9"), 9);
    comboBoxOutCh->addItem (T("10"), 10);
    comboBoxOutCh->addItem (T("11"), 11);
    comboBoxOutCh->addItem (T("12"), 12);
    comboBoxOutCh->addItem (T("13"), 13);
    comboBoxOutCh->addItem (T("14"), 14);
    comboBoxOutCh->addItem (T("15"), 15);
    comboBoxOutCh->addItem (T("16"), 16);
    comboBoxOutCh->addListener (this);

    addAndMakeVisible (groupComponentSync = new GroupComponent (T("new group Sync"),
                                                                T("Sync")));

    addAndMakeVisible (toggleButtonSyncInternal = new ToggleButton (T("new toggle button Sync Internal")));
    toggleButtonSyncInternal->setButtonText (T("internal"));
    toggleButtonSyncInternal->setRadioGroupId (1);
    toggleButtonSyncInternal->addButtonListener (this);
    toggleButtonSyncInternal->setToggleState (true, false);

    addAndMakeVisible (toggleButtonSyncExternal = new ToggleButton (T("new toggle button Sync External")));
    toggleButtonSyncExternal->setButtonText (T("external"));
    toggleButtonSyncExternal->setRadioGroupId (1);
    toggleButtonSyncExternal->addButtonListener (this);

    addAndMakeVisible (labelchannel = new Label (T("new label channel"),
                                                 T("Channel")));
    labelchannel->setFont (Font (15.0000f, Font::plain));
    labelchannel->setJustificationType (Justification::centredLeft);
    labelchannel->setEditable (false, false, false);
    labelchannel->setColour (TextEditor::textColourId, Colours::black);
    labelchannel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (labelCCNo = new Label (T("new label CC No"),
                                              T("CC #")));
    labelCCNo->setFont (Font (15.0000f, Font::plain));
    labelCCNo->setJustificationType (Justification::centredLeft);
    labelCCNo->setEditable (false, false, false);
    labelCCNo->setColour (Label::backgroundColourId, Colour (0xffc1d0ff));
    labelCCNo->setColour (TextEditor::textColourId, Colours::black);
    labelCCNo->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (labelcenterval = new Label (T("new label centerval"),
                                                   T("CenterVal")));
    labelcenterval->setFont (Font (15.0000f, Font::plain));
    labelcenterval->setJustificationType (Justification::centredLeft);
    labelcenterval->setEditable (false, false, false);
    labelcenterval->setColour (TextEditor::textColourId, Colours::black);
    labelcenterval->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (sliderCenterVal = new Slider (T("new slider CenterVal")));
    sliderCenterVal->setRange (0, 127, 1);
    sliderCenterVal->setSliderStyle (Slider::RotaryVerticalDrag);
    sliderCenterVal->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    sliderCenterVal->addListener (this);

    addAndMakeVisible (textButtonSetup = new TextButton (T("new button Setup")));
    textButtonSetup->setButtonText (T("Setup"));
    textButtonSetup->addButtonListener (this);

    addAndMakeVisible (toggleButtonMidiActive = new ToggleButton (T("new toggle Button Midi Active")));
    toggleButtonMidiActive->setButtonText (T("on/off"));
    toggleButtonMidiActive->addButtonListener (this);
    toggleButtonMidiActive->setToggleState (true, false);

    addAndMakeVisible (labeldepth = new Label (T("new label depth"),
                                               T("Depth")));
    labeldepth->setFont (Font (15.0000f, Font::plain));
    labeldepth->setJustificationType (Justification::centredLeft);
    labeldepth->setEditable (false, false, false);
    labeldepth->setColour (TextEditor::textColourId, Colours::black);
    labeldepth->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (textButtonAbout = new TextButton (T("new button about")));
    textButtonAbout->setButtonText (T("?"));
    textButtonAbout->addButtonListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (200, 320);

    //[Constructor] You can add your own custom stuff here..

	m_setupIsShown = true;

	sliderDepth->setValue(1);
	sliderCenterVal->setValue(63);

	sliderDivider->setVisible(false);
	labeldivider->setVisible(false);

	//Create Modules
	midiDevice = new MidiDevice;
	processingCore = new ProcessingCore;

	//Init Modules
	textButtonRescan->triggerClick();


	//Wire them together
	midiDevice->setProcessingCore(processingCore);
	processingCore->setMidiDevice(midiDevice);

	processingCore->start();


    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (groupComponentLFO);
    deleteAndZero (groupComponentMidiConn);
    deleteAndZero (label2);
    deleteAndZero (labeldivider);
    deleteAndZero (sliderDivider);
    deleteAndZero (sliderOutCC);
    deleteAndZero (sliderRate);
    deleteAndZero (sliderDepth);
    deleteAndZero (labelrate);
    deleteAndZero (comboBoxWaveform1);
    deleteAndZero (labelwaveform1);
    deleteAndZero (labelSyncInput);
    deleteAndZero (label);
    deleteAndZero (comboBoxMidiInput);
    deleteAndZero (comboBoxMidiOut);
    deleteAndZero (textButtonRescan);
    deleteAndZero (comboBoxOutCh);
    deleteAndZero (groupComponentSync);
    deleteAndZero (toggleButtonSyncInternal);
    deleteAndZero (toggleButtonSyncExternal);
    deleteAndZero (labelchannel);
    deleteAndZero (labelCCNo);
    deleteAndZero (labelcenterval);
    deleteAndZero (sliderCenterVal);
    deleteAndZero (textButtonSetup);
    deleteAndZero (toggleButtonMidiActive);
    deleteAndZero (labeldepth);
    deleteAndZero (textButtonAbout);

    //[Destructor]. You can add your own custom destruction code here..

	deleteAndZero (processingCore);
	deleteAndZero (midiDevice);


    //[/Destructor]
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffc1d0ff));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainComponent::resized()
{
    groupComponentLFO->setBounds (8, 0, 184, 126);
    groupComponentMidiConn->setBounds (8, 131, 184, 80);
    label2->setBounds (104, 131, 63, 16);
    labeldivider->setBounds (14, 43, 45, 23);
    sliderDivider->setBounds (16, 62, 40, 56);
    sliderOutCC->setBounds (120, 179, 64, 24);
    sliderRate->setBounds (16, 62, 40, 56);
    sliderDepth->setBounds (63, 62, 48, 56);
    labelrate->setBounds (12, 43, 49, 24);
    comboBoxWaveform1->setBounds (88, 17, 96, 23);
    labelwaveform1->setBounds (16, 17, 64, 23);
    labelSyncInput->setBounds (16, 251, 71, 24);
    label->setBounds (16, 147, 47, 24);
    comboBoxMidiInput->setBounds (88, 251, 96, 24);
    comboBoxMidiOut->setBounds (72, 147, 112, 24);
    textButtonRescan->setBounds (16, 288, 136, 24);
    comboBoxOutCh->setBounds (72, 179, 40, 24);
    groupComponentSync->setBounds (8, 211, 184, 72);
    toggleButtonSyncInternal->setBounds (16, 227, 72, 23);
    toggleButtonSyncExternal->setBounds (88, 227, 72, 23);
    labelchannel->setBounds (16, 179, 48, 24);
    labelCCNo->setBounds (116, 179, 32, 24);
    labelcenterval->setBounds (110, 43, 56, 23);
    sliderCenterVal->setBounds (109, 62, 56, 56);
    textButtonSetup->setBounds (160, 100, 24, 16);
    toggleButtonMidiActive->setBounds (104, 127, 80, 23);
    labeldepth->setBounds (67, 43, 38, 23);
    textButtonAbout->setBounds (160, 288, 24, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sliderDivider)
    {
        //[UserSliderCode_sliderDivider] -- add your slider handling code here..
		processingCore->setParameterSyncDivider(sliderDivider->getValue());
        //[/UserSliderCode_sliderDivider]
    }
    else if (sliderThatWasMoved == sliderOutCC)
    {
        //[UserSliderCode_sliderOutCC] -- add your slider handling code here..
		processingCore->setParameterOutCC(sliderOutCC->getValue());
        //[/UserSliderCode_sliderOutCC]
    }
    else if (sliderThatWasMoved == sliderRate)
    {
        //[UserSliderCode_sliderRate] -- add your slider handling code here..
		processingCore->setParameterRate(sliderRate->getValue());
        //[/UserSliderCode_sliderRate]
    }
    else if (sliderThatWasMoved == sliderDepth)
    {
        //[UserSliderCode_sliderDepth] -- add your slider handling code here..
		processingCore->setParameterDepth(sliderDepth->getValue());
        //[/UserSliderCode_sliderDepth]
    }
    else if (sliderThatWasMoved == sliderCenterVal)
    {
        //[UserSliderCode_sliderCenterVal] -- add your slider handling code here..
		processingCore->setParameterCenterVal(sliderCenterVal->getValue());
        //[/UserSliderCode_sliderCenterVal]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void MainComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == comboBoxWaveform1)
    {
        //[UserComboBoxCode_comboBoxWaveform1] -- add your combo box handling code here..
		processingCore->setParameterWaveform(comboBoxWaveform1->getSelectedItemIndex());
        //[/UserComboBoxCode_comboBoxWaveform1]
    }
    else if (comboBoxThatHasChanged == comboBoxMidiInput)
    {
        //[UserComboBoxCode_comboBoxMidiInput] -- add your combo box handling code here..
		midiDevice->setMidiInputSync(comboBoxMidiInput->getSelectedItemIndex());
        //[/UserComboBoxCode_comboBoxMidiInput]
    }
    else if (comboBoxThatHasChanged == comboBoxMidiOut)
    {
        //[UserComboBoxCode_comboBoxMidiOut] -- add your combo box handling code here..
		midiDevice->setMidiOutput(comboBoxMidiOut->getSelectedItemIndex());
        //[/UserComboBoxCode_comboBoxMidiOut]
    }
    else if (comboBoxThatHasChanged == comboBoxOutCh)
    {
        //[UserComboBoxCode_comboBoxOutCh] -- add your combo box handling code here..
		processingCore->setParameterOutChannel(comboBoxOutCh->getSelectedId());
        //[/UserComboBoxCode_comboBoxOutCh]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void MainComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == textButtonRescan)
    {
        //[UserButtonCode_textButtonRescan] -- add your button handler code here..

		String text = comboBoxMidiInput->getText();
		comboBoxMidiInput->clear(true);
		StringArray midiInDevicesList = MidiInput::getDevices();
		for (int i=0;i<midiInDevicesList.size();i++)
		{
			comboBoxMidiInput->addItem(midiInDevicesList[i],i+1);
			if(midiInDevicesList[i]==text)
				comboBoxMidiInput->setSelectedItemIndex (i, true);
		}

		text = comboBoxMidiOut->getText();
		comboBoxMidiOut->clear(true);
		StringArray midiOutDevicesList = MidiOutput::getDevices();
		for (int i=0;i<midiOutDevicesList.size();i++)
		{
			comboBoxMidiOut->addItem(midiOutDevicesList[i],i+1);
			if(midiOutDevicesList[i]==text)
				comboBoxMidiOut->setSelectedItemIndex (i, true);
		}
        //[/UserButtonCode_textButtonRescan]
    }
    else if (buttonThatWasClicked == toggleButtonSyncInternal)
    {
        //[UserButtonCode_toggleButtonSyncInternal] -- add your button handler code here..
		if (toggleButtonSyncInternal->getToggleState() == 1)
		{
			sliderDivider->setVisible(false);
			labeldivider->setVisible(false);
			sliderRate->setVisible(true);
			labelrate->setVisible(true);

			processingCore->setParameterSyncSource(0);
		}
        //[/UserButtonCode_toggleButtonSyncInternal]
    }
    else if (buttonThatWasClicked == toggleButtonSyncExternal)
    {
        //[UserButtonCode_toggleButtonSyncExternal] -- add your button handler code here..
		if (toggleButtonSyncExternal->getToggleState() == 1)
		{
			sliderDivider->setVisible(true);
			labeldivider->setVisible(true);
			sliderRate->setVisible(false);
			labelrate->setVisible(false);

			processingCore->setParameterSyncSource(1);
		}
        //[/UserButtonCode_toggleButtonSyncExternal]
    }
    else if (buttonThatWasClicked == textButtonSetup)
    {
        //[UserButtonCode_textButtonSetup] -- add your button handler code here..
		if (m_setupIsShown == true)
		{
			setSize (200, 128);
			m_setupIsShown = false;
		}
		else
		{
			setSize (200, 320);
			m_setupIsShown = true;
		}
        //[/UserButtonCode_textButtonSetup]
    }
    else if (buttonThatWasClicked == toggleButtonMidiActive)
    {
        //[UserButtonCode_toggleButtonMidiActive] -- add your button handler code here..
		if (toggleButtonMidiActive->getToggleState() == true)
		{
			processingCore->start();
		}
		if (toggleButtonMidiActive->getToggleState() == false)
		{
			processingCore->stop();
		}
        //[/UserButtonCode_toggleButtonMidiActive]
    }
    else if (buttonThatWasClicked == textButtonAbout)
    {
        //[UserButtonCode_textButtonAbout] -- add your button handler code here..

		AlertWindow::showMessageBox  	(AlertWindow::InfoIcon,
										 String::formatted(T("About")),
										 String::formatted(T("MidiLFO V1.0\n\nCopyright (C) 2009, Christian Stoecklmeier and Volker Duemke\n\nReleased under GPL V2.0\nsee http://www.gnu.org/licenses\nand http://sourceforge.net/projects/midilfo")),
										 String::formatted(T("Yeah!"))
										 );

        //[/UserButtonCode_textButtonAbout]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="200" initialHeight="320">
  <BACKGROUND backgroundColour="ffc1d0ff"/>
  <GROUPCOMPONENT name="LFO" id="a34a67e90c344bd0" memberName="groupComponentLFO"
                  virtualName="" explicitFocusOrder="0" pos="8 0 184 126" title="LFO"/>
  <GROUPCOMPONENT name="new group midi" id="f34758ab98d83d03" memberName="groupComponentMidiConn"
                  virtualName="" explicitFocusOrder="0" pos="8 131 184 80" title="MIDI Out"/>
  <LABEL name="new label" id="37b0df15bedfa0ae" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="104 131 63 16" bkgCol="ffc1d0ff"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label divider" id="beffd3aa6db6d3b9" memberName="labeldivider"
         virtualName="" explicitFocusOrder="0" pos="14 43 45 23" edTextCol="ff000000"
         edBkgCol="0" labelText="Divider" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="slider Divider" id="612ea0c5ebd0b6e5" memberName="sliderDivider"
          virtualName="" explicitFocusOrder="0" pos="16 62 40 56" min="1"
          max="4" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider OutCC" id="39be37adb14d9b3b" memberName="sliderOutCC"
          virtualName="" explicitFocusOrder="0" pos="120 179 64 24" min="0"
          max="127" int="1" style="LinearVertical" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="24" skewFactor="1"/>
  <SLIDER name="slider Rate" id="df9dbd739d636e37" memberName="sliderRate"
          virtualName="" explicitFocusOrder="0" pos="16 62 40 56" min="0.1"
          max="12" int="0.05" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider Depth" id="9299a52d4a5880ff" memberName="sliderDepth"
          virtualName="" explicitFocusOrder="0" pos="63 62 48 56" min="0"
          max="1" int="0.001" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label rate" id="345250a324f36406" memberName="labelrate"
         virtualName="" explicitFocusOrder="0" pos="12 43 49 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Rate/Hz" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="combo box Waveform1" id="e9a39d9a4163961f" memberName="comboBoxWaveform1"
            virtualName="" explicitFocusOrder="0" pos="88 17 96 23" editable="0"
            layout="33" items="Sine&#10;Square&#10;Saw&#10;Triangle" textWhenNonSelected="Sine"
            textWhenNoItems="(no choices)"/>
  <LABEL name="new label waveform1" id="40cf0d69cc756d18" memberName="labelwaveform1"
         virtualName="" explicitFocusOrder="0" pos="16 17 64 23" edTextCol="ff000000"
         edBkgCol="0" labelText="Waveform" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label sync" id="2431c376243b70af" memberName="labelSyncInput"
         virtualName="" explicitFocusOrder="0" pos="16 251 71 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sync-Input" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5a58caf637385ed9" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="16 147 47 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box MidiInput" id="c3084f4229443218" memberName="comboBoxMidiInput"
            virtualName="" explicitFocusOrder="0" pos="88 251 96 24" editable="0"
            layout="33" items="" textWhenNonSelected="Midi In" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box Midi Out" id="fc5de07b2c383ee2" memberName="comboBoxMidiOut"
            virtualName="" explicitFocusOrder="0" pos="72 147 112 24" editable="0"
            layout="33" items="" textWhenNonSelected="Midi Out" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="new button rescan" id="b83a8d30e8e4bc1a" memberName="textButtonRescan"
              virtualName="" explicitFocusOrder="0" pos="16 288 136 24" buttonText="Rescan Midi Devices"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="new combo OutCh" id="a7c0115fdd86a174" memberName="comboBoxOutCh"
            virtualName="" explicitFocusOrder="0" pos="72 179 40 24" editable="0"
            layout="33" items="1&#10;2&#10;3&#10;4&#10;5&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15&#10;16&#10;" textWhenNonSelected="1"
            textWhenNoItems="(no choices)"/>
  <GROUPCOMPONENT name="new group Sync" id="d231a63987a1adb2" memberName="groupComponentSync"
                  virtualName="" explicitFocusOrder="0" pos="8 211 184 72" title="Sync"/>
  <TOGGLEBUTTON name="new toggle button Sync Internal" id="fa67cba02652722" memberName="toggleButtonSyncInternal"
                virtualName="" explicitFocusOrder="0" pos="16 227 72 23" buttonText="internal"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="1"/>
  <TOGGLEBUTTON name="new toggle button Sync External" id="6cce64ad40b6854e"
                memberName="toggleButtonSyncExternal" virtualName="" explicitFocusOrder="0"
                pos="88 227 72 23" buttonText="external" connectedEdges="0" needsCallback="1"
                radioGroupId="1" state="0"/>
  <LABEL name="new label channel" id="9c9d081177339171" memberName="labelchannel"
         virtualName="" explicitFocusOrder="0" pos="16 179 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Channel" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label CC No" id="220de9f995fabfb8" memberName="labelCCNo"
         virtualName="" explicitFocusOrder="0" pos="116 179 32 24" bkgCol="ffc1d0ff"
         edTextCol="ff000000" edBkgCol="0" labelText="CC #" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label centerval" id="c9c5c77ed75bec4" memberName="labelcenterval"
         virtualName="" explicitFocusOrder="0" pos="110 43 56 23" edTextCol="ff000000"
         edBkgCol="0" labelText="CenterVal" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider CenterVal" id="8ead7912cca5197f" memberName="sliderCenterVal"
          virtualName="" explicitFocusOrder="0" pos="109 62 56 56" min="0"
          max="127" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="new button Setup" id="729ba0dc9f172d05" memberName="textButtonSetup"
              virtualName="" explicitFocusOrder="0" pos="160 100 24 16" buttonText="Setup"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="new toggle Button Midi Active" id="7909aa34fbcabc31" memberName="toggleButtonMidiActive"
                virtualName="" explicitFocusOrder="0" pos="104 127 80 23" buttonText="on/off"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <LABEL name="new label depth" id="8665fc2c95202943" memberName="labeldepth"
         virtualName="" explicitFocusOrder="0" pos="67 43 38 23" edTextCol="ff000000"
         edBkgCol="0" labelText="Depth" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button about" id="2cf53823ac4d2d58" memberName="textButtonAbout"
              virtualName="" explicitFocusOrder="0" pos="160 288 24 24" buttonText="?"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
