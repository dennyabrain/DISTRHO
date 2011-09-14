/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jul 2008 3:59:00 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "stepEditNote.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
stepEditNote::stepEditNote (myMidiMessage *msg)
    : midiKeyboard (0),
      veloSlider (0),
      noteLength (0)
{
    addAndMakeVisible (midiKeyboard = new myMidiKeyboardComponent (midiKeyboardState,
                                                                   MidiKeyboardComponent::verticalKeyboardFacingRight, msg));
    midiKeyboard->setName (T("Midi Keyboard"));

    addAndMakeVisible (veloSlider = new Slider (T("Velocity")));
    veloSlider->setTooltip (T("Velocity"));
    veloSlider->setRange (1, 127, 1);
    veloSlider->setSliderStyle (Slider::LinearVertical);
    veloSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    veloSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    veloSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0xffffff));
    veloSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x0));
    veloSlider->addListener (this);

    addAndMakeVisible (noteLength = new Slider (T("Note Length")));
    noteLength->setTooltip (T("Note Length"));
    noteLength->setRange (1, 32, 1);
    noteLength->setSliderStyle (Slider::IncDecButtons);
    noteLength->setTextBoxStyle (Slider::TextBoxLeft, false, 20, 14);
    noteLength->addListener (this);


    //[UserPreSize]
	midiMessage = msg;

	midiKeyboardState.addListener (this);
	veloSlider->setValue (midiMessage->getMidiMessage()->getVelocity());
	noteLength->setValue (midiMessage->getLength());
    //[/UserPreSize]

    setSize (112, 224);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

stepEditNote::~stepEditNote()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (midiKeyboard);
    deleteAndZero (veloSlider);
    deleteAndZero (noteLength);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void stepEditNote::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void stepEditNote::resized()
{
    midiKeyboard->setBounds (0, 0, 80, 200);
    veloSlider->setBounds (88, 0, 24, 200);
    noteLength->setBounds (8, 206, 88, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void stepEditNote::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == veloSlider)
    {
        //[UserSliderCode_veloSlider] -- add your slider handling code here..
		if (midiMessage)
		{
			midiMessage->getMidiMessage()->setVelocity ((float)veloSlider->getValue());
		}
        //[/UserSliderCode_veloSlider]
    }
    else if (sliderThatWasMoved == noteLength)
    {
        //[UserSliderCode_noteLength] -- add your slider handling code here..
		if (midiMessage)
		{
			midiMessage->setLength ((short)noteLength->getValue());
		}
        //[/UserSliderCode_noteLength]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void stepEditNote::handleNoteOn (MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float velocity)
{
	Logger::writeToLog (T("midiKeyboard listener noteon"));
	if (midiMessage)
	{
		Logger::writeToLog (String::formatted (T("change note number: %d"), midiNoteNumber));
		midiMessage->getMidiMessage()->setNoteNumber(midiNoteNumber);
		midiMessage->getMidiMessage()->setVelocity(velocity);
	}
}

void stepEditNote::handleNoteOff (MidiKeyboardState *source, int midiChannel, int midiNoteNumber)
{
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="stepEditNote" componentName=""
                 parentClasses="public Component, public MidiKeyboardStateListener"
                 constructorParams="myMidiMessage *msg" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="112" initialHeight="224">
  <BACKGROUND backgroundColour="ffffff"/>
  <GENERICCOMPONENT name="Midi Keyboard" id="1d491a13579ae9cc" memberName="midiKeyboard"
                    virtualName="" explicitFocusOrder="0" pos="0 0 80 200" class="myMidiKeyboardComponent"
                    params="midiKeyboardState,&#10;MidiKeyboardComponent::verticalKeyboardFacingRight, msg"/>
  <SLIDER name="Velocity" id="f4dabf8bc7889870" memberName="veloSlider"
          virtualName="" explicitFocusOrder="0" pos="88 0 24 200" tooltip="Velocity"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="0"
          min="1" max="127" int="1" style="LinearVertical" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Note Length" id="8dd68f1f1ef8d0fe" memberName="noteLength"
          virtualName="" explicitFocusOrder="0" pos="8 206 88 16" tooltip="Note Length"
          min="1" max="32" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="20" textBoxHeight="14" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
