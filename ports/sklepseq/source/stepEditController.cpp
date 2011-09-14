/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  2 Jul 2008 9:33:57 pm

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

#include "stepEditController.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
stepEditController::stepEditController (myMidiMessage *msg)
    : controllerValue (0),
      controllerNumber (0),
      label (0),
      label2 (0),
      typeCombo (0)
{
    addAndMakeVisible (controllerValue = new Slider (T("Value")));
    controllerValue->setTooltip (T("Value"));
    controllerValue->setRange (0, 127, 1);
    controllerValue->setSliderStyle (Slider::RotaryVerticalDrag);
    controllerValue->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    controllerValue->addListener (this);

    addAndMakeVisible (controllerNumber = new Slider (T("Number")));
    controllerNumber->setTooltip (T("Number"));
    controllerNumber->setRange (0, 127, 1);
    controllerNumber->setSliderStyle (Slider::IncDecButtons);
    controllerNumber->setTextBoxStyle (Slider::TextBoxLeft, false, 35, 20);
    controllerNumber->addListener (this);

    addAndMakeVisible (label = new Label (T("new label"),
                                          T("Controller Value")));
    label->setFont (Font (15.0000f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label2 = new Label (T("new label"),
                                           T("Controller Number")));
    label2->setFont (Font (15.0000f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (typeCombo = new ComboBox (T("Controller Type")));
    typeCombo->setTooltip (T("Type"));
    typeCombo->setEditableText (false);
    typeCombo->setJustificationType (Justification::centredLeft);
    typeCombo->setTextWhenNothingSelected (String::empty);
    typeCombo->setTextWhenNoChoicesAvailable (T("(no choices)"));
    typeCombo->addItem (T("CC"), 1);
    typeCombo->addItem (T("RPN"), 2);
    typeCombo->addItem (T("NRPN"), 3);
    typeCombo->addListener (this);


    //[UserPreSize]
	midiMessage		= msg;

	if (midiMessage)
	{
		if (midiMessage->isMulti())
		{
			MidiBuffer *b = midiMessage->getMidiBuffer();
			MidiMessage msg(0xf0,0.0);
			MidiBuffer::Iterator i(*b);
			int len;
			int controllerNumberLsb=0, controllerNumberMsb=0, controllerValueLsb=0, controllerValueMsb=0;
			BitArray ctrlrValueArray;
			BitArray ctrlrNumberArray;

			while (i.getNextEvent (msg, len))
			{
				uint8 *d = msg.getRawData();
				int len  = msg.getRawDataSize();

				String t;
				for (int x=0; x<len; x++)
				{
					if (x==0)
						t << String::formatted (T("%x"), *(d+x));
					else
						t << String::formatted (T(":%x"), *(d+x));
				}

				Logger::writeToLog (T("message: ") + t);

				if (msg.getControllerNumber() == 98)
				{					
					controllerNumberMsb = msg.getControllerValue();
				}
				if (msg.getControllerNumber() == 99)
				{
					typeCombo->setSelectedId (2, true);
					controllerNumberLsb = msg.getControllerValue();
				}
				if (msg.getControllerNumber() == 100)
				{
					controllerNumberMsb = msg.getControllerValue();
				}
				if (msg.getControllerNumber() == 101)
				{
					typeCombo->setSelectedId (3, true);
					controllerNumberLsb = msg.getControllerValue();
				}
				if (msg.getControllerNumber() == 6)
				{
					controllerValueLsb = msg.getControllerValue();
				}
				if (msg.getControllerNumber() == 38)
				{
					controllerValueMsb = msg.getControllerValue();
				}
			}

			ctrlrNumberArray.setBitRangeAsInt (0, 7, controllerNumberLsb);
			ctrlrNumberArray.setBitRangeAsInt (7, 7, controllerNumberMsb);

			ctrlrValueArray.setBitRangeAsInt (0, 7, controllerValueLsb);
			ctrlrValueArray.setBitRangeAsInt (7, 7, controllerValueMsb);

			controllerNumber->setRange (0, 16383, 1);
			controllerValue->setRange (0, 16383, 1);

			controllerValue->setValue (ctrlrValueArray.getBitRangeAsInt(0,14));
			controllerNumber->setValue (ctrlrNumberArray.getBitRangeAsInt(0,14));
		}
		else
		{
			controllerNumber->setRange (0, 127, 1);
			controllerValue->setRange (0, 127, 1);

			typeCombo->setSelectedId (1, true);

			controllerNumber->setValue (midiMessage->getMidiMessage()->getControllerNumber());
			controllerValue->setValue (midiMessage->getMidiMessage()->getControllerValue());
		}
	}
    //[/UserPreSize]

    setSize (112, 224);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

stepEditController::~stepEditController()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (controllerValue);
    deleteAndZero (controllerNumber);
    deleteAndZero (label);
    deleteAndZero (label2);
    deleteAndZero (typeCombo);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void stepEditController::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void stepEditController::resized()
{
    controllerValue->setBounds (0, 24, 112, 112);
    controllerNumber->setBounds (4, 168, 108, 24);
    label->setBounds (4, 0, 104, 24);
    label2->setBounds (4, 144, 104, 24);
    typeCombo->setBounds (16, 200, 80, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void stepEditController::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == controllerValue)
    {
        //[UserSliderCode_controllerValue] -- add your slider handling code here..
		setMidiData();
        //[/UserSliderCode_controllerValue]
    }
    else if (sliderThatWasMoved == controllerNumber)
    {
        //[UserSliderCode_controllerNumber] -- add your slider handling code here..
		setMidiData();
        //[/UserSliderCode_controllerNumber]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void stepEditController::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == typeCombo)
    {
        //[UserComboBoxCode_typeCombo] -- add your combo box handling code here..
		switch (typeCombo->getSelectedId()-1)
		{
			case CC:
				controllerNumber->setRange (0, 127, 1);
				controllerValue->setRange (0, 127, 1);
				break;

			case RPN:
				controllerNumber->setRange (0, 16383, 1);
				controllerValue->setRange (0, 16383, 1);
				break;

			case NRPN:
				controllerNumber->setRange (0, 16383, 1);
				controllerValue->setRange (0, 16383, 1);
				break;

			default:
				break;
		}

		setMidiData();
        //[/UserComboBoxCode_typeCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void stepEditController::setMidiData()
{
	if (typeCombo->getSelectedId()-1 == NRPN)
	{
		/* (MSB x 128) + LSB == controller number*/
		/* (MSB x 128) + LSB == value */
		midiBuf.clear();	

		BitArray ctrlrNumber ((int)controllerNumber->getValue());
		BitArray ctrlrValue ((int)controllerValue->getValue());
		
		int ctrlrNumberLsb = ctrlrNumber.getBitRangeAsInt (0,6);
		int ctrlrNumberMsb = ctrlrNumber.getBitRangeAsInt (7,13);
		
		int ctrlrValueLsb = ctrlrValue.getBitRangeAsInt (0,6);
		int ctrlrValueMsb = ctrlrValue.getBitRangeAsInt (7,13);
	
		int firstByte = 0xb0;
	
		MidiMessage msg (firstByte, 101, ctrlrNumberLsb);
		midiBuf.addEvent (msg,0);
	
		msg = MidiMessage(firstByte, 100, ctrlrNumberMsb);
		midiBuf.addEvent (msg,1);

		msg = MidiMessage(firstByte, 6, ctrlrValueLsb);
		midiBuf.addEvent (msg,2);

		msg = MidiMessage(firstByte, 38, ctrlrValueMsb);
		midiBuf.addEvent (msg,3);

		midiMessage->setMidiMessageMulti (midiBuf);

		return;
	}


	if (typeCombo->getSelectedId()-1 == RPN)
	{
		/* (MSB x 128) + LSB == controller number*/
		/* (MSB x 128) + LSB == value */
		midiBuf.clear();
	
		BitArray ctrlrNumber ((int)controllerNumber->getValue());
		BitArray ctrlrValue ((int)controllerValue->getValue());
			
		int ctrlrNumberLsb = ctrlrNumber.getBitRangeAsInt (0,6);
		int ctrlrNumberMsb = ctrlrNumber.getBitRangeAsInt (7,13);
			
		int ctrlrValueLsb = ctrlrValue.getBitRangeAsInt (0,6);
		int ctrlrValueMsb = ctrlrValue.getBitRangeAsInt (7,13);
	
		int firstByte = 0xb0;
	
		MidiMessage msg (firstByte, 99, ctrlrNumberLsb);
		midiBuf.addEvent (msg,0);
	
		msg = MidiMessage(firstByte, 98, ctrlrNumberMsb);
		midiBuf.addEvent (msg,1);

		msg = MidiMessage(firstByte, 6, ctrlrValueLsb);
		midiBuf.addEvent (msg,2);
	
		msg = MidiMessage(firstByte, 38, ctrlrValueMsb);
		midiBuf.addEvent (msg,3);
	
		midiMessage->setMidiMessageMulti (midiBuf);
	
		return;
	}

	if (typeCombo->getSelectedId()-1 == CC)
	{
		midiMessage->setMidiMessage (MidiMessage::controllerEvent (1, (int)controllerNumber->getValue(), (int)controllerValue->getValue()));
		return;
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="stepEditController" componentName=""
                 parentClasses="public Component" constructorParams="myMidiMessage *msg"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330000013" fixedSize="1" initialWidth="112"
                 initialHeight="224">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="Value" id="594ba86bfe4c9ed5" memberName="controllerValue"
          virtualName="" explicitFocusOrder="0" pos="0 24 112 112" tooltip="Value"
          min="0" max="127" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Number" id="6ce30323c5dbf062" memberName="controllerNumber"
          virtualName="" explicitFocusOrder="0" pos="4 168 108 24" tooltip="Number"
          min="0" max="127" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="35" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="6682b679404c2a6e" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="4 0 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Controller Value" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a92dafe37c5039b7" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="4 144 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Controller Number" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="Controller Type" id="5d0d63924ddad6e8" memberName="typeCombo"
            virtualName="" explicitFocusOrder="0" pos="16 200 80 16" tooltip="Type"
            editable="0" layout="33" items="CC&#10;RPN&#10;NRPN" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
