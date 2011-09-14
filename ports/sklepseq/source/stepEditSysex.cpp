/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  2 Jul 2008 4:05:42 pm

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

#include "stepEditSysex.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
stepEditSysex::stepEditSysex (myMidiMessage *msg)
    : midiData (0),
      saveButton (0)
{
    addAndMakeVisible (midiData = new TextEditor ("Sysex Data"));
    midiData->setTooltip ("Sysex Data");
    midiData->setMultiLine (true);
    midiData->setReturnKeyStartsNewLine (false);
    midiData->setReadOnly (false);
    midiData->setScrollbarsShown (true);
    midiData->setCaretVisible (true);
    midiData->setPopupMenuEnabled (true);
    midiData->setColour (TextEditor::shadowColourId, Colour (0x73000000));
    midiData->setText (String::empty);

    addAndMakeVisible (saveButton = new TextButton ("Save"));
    saveButton->setTooltip ("Save");
    saveButton->addButtonListener (this);


    //[UserPreSize]
	midiMessage = msg;
	midiRawData = 0;

	if (midiMessage)
	{
		uint8 *d = midiMessage->getMidiMessage()->getRawData();
		int len  = midiMessage->getMidiMessage()->getRawDataSize();

		String t;
		for (int x=0; x<len; x++)
		{
			if (x==0)
				t << String::formatted ("%02x", *(d+x));
			else
				t << String::formatted (":%02x", *(d+x));
		}

		midiData->setText (t, false);
	}
    //[/UserPreSize]

    setSize (112, 224);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

stepEditSysex::~stepEditSysex()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (midiData);
    deleteAndZero (saveButton);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void stepEditSysex::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void stepEditSysex::resized()
{
    midiData->setBounds (0, 0, 112, 192);
    saveButton->setBounds (8, 200, 96, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void stepEditSysex::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == saveButton)
    {
        //[UserButtonCode_saveButton] -- add your button handler code here..
		setMidiRawData(midiData->getText());
		midiMessage->setMidiMessageRaw (midiRawData, midiRawDataLen);
        //[/UserButtonCode_saveButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void stepEditSysex::setMidiRawData (String t)
{
	if (t.isEmpty())
	{
		return;
	}
	int i	=0;
	int k	=2;
	int len	=0;

	if (midiRawData)
		free (midiRawData);

	midiRawData = (uint8 *)malloc(t.length());

	String b = t.substring (i, k);

	while (!b.isEmpty())
	{	
		*(midiRawData+len) = b.getHexValue32();

		len++;
		i=i+3;
		k=k+3;

		b = t.substring (i, k);
	}

	midiRawDataLen = len;
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="stepEditSysex" componentName=""
                 parentClasses="public Component" constructorParams="myMidiMessage *msg"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330000013" fixedSize="1" initialWidth="112"
                 initialHeight="224">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TEXTEDITOR name="Sysex Data" id="e8aa59c1e8f6cbff" memberName="midiData"
              virtualName="" explicitFocusOrder="0" pos="0 0 112 192" tooltip="Sysex Data"
              shadowcol="73000000" initialText="" multiline="1" retKeyStartsLine="0"
              readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTBUTTON name="Save" id="63dc1cd13d921b75" memberName="saveButton" virtualName=""
              explicitFocusOrder="0" pos="8 200 96 16" tooltip="Save" buttonText="Save"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
