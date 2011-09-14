/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jul 2008 2:05:35 pm

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
#include "sklepSeqMainComponent.h"
//[/Headers]

#include "stepQuickEdit.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
stepQuickEdit::stepQuickEdit (sklepSeqMainComponent *parent, myMidiMessage *msg)
    : typeCombo (0)
{
    addAndMakeVisible (typeCombo = new ComboBox ("Type"));
    typeCombo->setTooltip ("Type");
    typeCombo->setEditableText (false);
    typeCombo->setJustificationType (Justification::centredLeft);
    typeCombo->setTextWhenNothingSelected (String::empty);
    typeCombo->setTextWhenNoChoicesAvailable ("(no choices)");
    typeCombo->addItem ("Note On", 1);
    typeCombo->addItem ("Controller", 2);
    typeCombo->addItem ("SysEx", 3);
    typeCombo->addItem ("Program Change", 4);
    typeCombo->addItem ("MMC", 5);
    typeCombo->addListener (this);


    //[UserPreSize]
	midiMessage		= msg;
	midiBuffer		= 0;

	editorComponent = 0;
	messageTypeChanged();
    //[/UserPreSize]

    setSize (128, 272);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

stepQuickEdit::~stepQuickEdit()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (typeCombo);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void stepQuickEdit::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    ColourGradient gradient_1 (Colour (0xad353535),
                              56.0f, 0.0f,
                              Colours::black,
                              56.0f, 256.0f,
                              false);
    g.setGradientFill (gradient_1);
    g.fillRoundedRectangle (0.0f, 0.0f, 128.0f, 272.0f, 10.0000f);

    //[UserPaint] Add your own custom painting code here..
	LookAndFeel::drawGlassLozenge (g, 4, 2, 120, 16, Colour(64,64,64).withAlpha (0.8f), 0.0f, 5.0f, false, false, false, true);
    //[/UserPaint]
}

void stepQuickEdit::resized()
{
    typeCombo->setBounds (16, 254, 96, 16);
    //[UserResized] Add your own custom resize handling here..
	if (editorComponent)
		editorComponent->setBounds (8,24,112,224);
    //[/UserResized]
}

void stepQuickEdit::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == typeCombo)
    {
        //[UserComboBoxCode_typeCombo] -- add your combo box handling code here..
		if (midiMessage == 0)
			return;

		switch (typeCombo->getSelectedId())
		{
			case noteOn:
				if (!midiMessage->isMulti())
				{
					if (!midiMessage->getMidiMessage())
						return;

					if (midiMessage->getMidiMessage()->isNoteOn())
					{
						midiMessage->setMidiMessage (*midiMessage->getMidiMessage());
					}
					else
					{
						midiMessage->setMidiMessage (MidiMessage::noteOn (1, 64, 1.0f));
					}
				}
				else
				{
					midiMessage->setMidiMessage (MidiMessage::noteOn (1, 64, 1.0f));
				}
				break;

			case Controller:
				if (!midiMessage->isMulti())
				{
					if (!midiMessage->getMidiMessage())
						return;

					if (midiMessage->getMidiMessage()->isController())
					{
						midiMessage->setMidiMessage (*midiMessage->getMidiMessage());
					}
					else
					{
						midiMessage->setMidiMessage (MidiMessage::controllerEvent (1, 1, 1));
					}
				}
				else
				{
					if (midiMessage->getMidiMessage()->isController())
					{
						if (!midiMessage->getMidiMessage())
							return;

						midiMessage->setMidiMessage (*midiMessage->getMidiMessage());
					}
					else
					{
						midiMessage->setMidiMessage (MidiMessage::controllerEvent (1, 1, 1));
					}
				}
				break;

			case ProgramChange:
				if (!midiMessage->getMidiMessage())
						return;

				if (midiMessage->getMidiMessage()->isProgramChange())
				{
					if (!midiMessage->getMidiMessage())
						return;

					midiMessage->setMidiMessage (*midiMessage->getMidiMessage());
				}
				else
				{
					midiMessage->setMidiMessage (MidiMessage::programChange (1, 1));
				}
				break;

			case SysEx:
				if (!midiMessage->getMidiMessage())
						return;

				if (midiMessage->getMidiMessage()->isSysEx())
				{
					if (!midiMessage->getMidiMessage())
						return;

					midiMessage->setMidiMessage (*midiMessage->getMidiMessage());
				}
				else
				{
					uint8 d[4];
					d[0] = 0xf0;
					d[1] = 0x00;
					d[2] = 0x0f;

					midiMessage->setMidiMessage (MidiMessage (d, 3, 0));
				}
				break;

			default:
				break;
		}

		messageTypeChanged();
        //[/UserComboBoxCode_typeCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void stepQuickEdit::mouseDown (const MouseEvent& e)
{
	myDragger.startDraggingComponent (this, e);
}

void stepQuickEdit::mouseDrag (const MouseEvent& e)
{
	myDragger.dragComponent (this, e, 0);
}

void stepQuickEdit::mouseMove (const MouseEvent &e)
{
	if (e.x > 4 && e.x < 124 && e.y > 2 && e.y < 16)
	{
		setMouseCursor (MouseCursor::DraggingHandCursor);
	}
	else
	{
		setMouseCursor (MouseCursor::NormalCursor);
	}
}

void stepQuickEdit::messageTypeChanged()
{
	MidiMessage *m = 0;
	MidiBuffer *mB = 0;

	if (editorComponent)
	{
		deleteAndZero (editorComponent);
	}
	if (midiMessage == 0)
	{
		return;
	}

	m = midiMessage->getMidiMessage();

	if (m)
	{
		if (m->isNoteOn())
		{
			addAndMakeVisible (editorComponent = new stepEditNote(midiMessage));
			typeCombo->setSelectedId (noteOn, true);
		}
		else if (m->isProgramChange())
		{
			typeCombo->setSelectedId (ProgramChange, true);
		}
		else if (m->isController())
		{
			addAndMakeVisible (editorComponent = new stepEditController(midiMessage));
			typeCombo->setSelectedId (Controller, true);
		}
		else if (m->isMidiMachineControlMessage())
		{
			typeCombo->setSelectedId (MMC, true);
		}
		else if (m->isSysEx())
		{
			addAndMakeVisible (editorComponent = new stepEditSysex(midiMessage));
			typeCombo->setSelectedId (SysEx, true);
		}

		resized();
	}

	mB = midiMessage->getMidiBuffer();
	
	if (mB == 0)
		return;

	if (!m && mB)
	{
		MidiBuffer::Iterator i(*mB);
		int len;
		MidiMessage message (0xf4, 0.0);

		if (i.getNextEvent (message, len))
		{
			uint8 *data = message.getRawData();

			if (*data == 0xb0)
			{
				addAndMakeVisible (editorComponent = new stepEditController(midiMessage));
				typeCombo->setSelectedId (Controller, true);
			}

			if (*data == 0xf0)
			{
				addAndMakeVisible (editorComponent = new stepEditSysex(midiMessage));
				typeCombo->setSelectedId (SysEx, true);
			}

			resized();
		}
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="stepQuickEdit" componentName=""
                 parentClasses="public Component" constructorParams="sklepSeqMainComponent *parent, myMidiMessage *msg"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330000013" fixedSize="1" initialWidth="128"
                 initialHeight="272">
  <BACKGROUND backgroundColour="ff6262">
    <ROUNDRECT pos="0 0 128 272" cornerSize="10" fill="linear: 56 0, 56 256, 0=ad353535, 1=ff000000"
               hasStroke="0"/>
  </BACKGROUND>
  <COMBOBOX name="Type" id="5852402a7bc052e" memberName="typeCombo" virtualName=""
            explicitFocusOrder="0" pos="16 254 96 16" tooltip="Type" editable="0"
            layout="33" items="Note On&#10;Controller&#10;SysEx&#10;Program Change&#10;MMC"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
