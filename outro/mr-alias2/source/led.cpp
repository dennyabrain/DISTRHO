/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  30 Oct 2008 2:18:48 pm

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

#include "led.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
LED::LED ()
    : Button (String::empty)
{

    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 400);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

LED::~LED()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void LED::resized()
{
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void LED::paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    if (getToggleState())
    {
        g.fillAll (Colour (0x82ffdb00));
    }
    else
    {
        g.fillAll (Colour (0x753c1c1c));
    }
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Button" className="LED" componentName="" parentClasses="public Button"
                 constructorParams="" variableInitialisers="" snapPixels="10"
                 snapActive="1" snapShown="1" overlayOpacity="0.330000013" fixedSize="1"
                 initialWidth="400" initialHeight="400">
  <BACKGROUND backgroundColour="753c1c1c" buttonState="normal" enabled="1"/>
  <BACKGROUND backgroundColour="ffffffff" buttonState="over" enabled="0"/>
  <BACKGROUND backgroundColour="ffffffff" buttonState="down" enabled="0"/>
  <BACKGROUND backgroundColour="82ffdb00" buttonState="normal on" enabled="1"/>
  <BACKGROUND backgroundColour="0" buttonState="over on" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="down on" enabled="0"/>
  <BACKGROUND backgroundColour="ffffffff" buttonState="common background" enabled="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
