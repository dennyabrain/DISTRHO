/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  27 Jun 2008 10:00:44 pm

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

#include "sklepSeqStepComponentEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
sklepSeqStepComponentEditor::sklepSeqStepComponentEditor (MidiMessage *msg)
{

    //[UserPreSize]

    //[/UserPreSize]

    setSize (340, 120);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

sklepSeqStepComponentEditor::~sklepSeqStepComponentEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void sklepSeqStepComponentEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0x7dffffff));
    g.fillRoundedRectangle (0.0f, 0.0f, 340.0f, 120.0f, 10.0000f);

    g.setColour (Colour (0xffb9b9b9));
    g.drawRoundedRectangle (0.0f, 0.0f, 340.0f, 120.0f, 10.0000f, 0.1000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void sklepSeqStepComponentEditor::resized()
{
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="sklepSeqStepComponentEditor"
                 componentName="" parentClasses="public Component" constructorParams="MidiMessage *msg"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330000013" fixedSize="1" initialWidth="340"
                 initialHeight="120">
  <BACKGROUND backgroundColour="ffffff">
    <ROUNDRECT pos="0 0 340 120" cornerSize="10" fill="solid: 7dffffff" hasStroke="1"
               stroke="0.100000001, mitered, butt" strokeColour="solid: ffb9b9b9"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
