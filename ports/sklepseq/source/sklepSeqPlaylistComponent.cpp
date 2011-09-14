/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  23 Jun 2008 9:24:31 pm

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

#include "sklepSeqPlaylistComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
sklepSeqPlaylistComponent::sklepSeqPlaylistComponent ()
{

    //[UserPreSize]
    //[/UserPreSize]

    setSize (2048, 2048);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

sklepSeqPlaylistComponent::~sklepSeqPlaylistComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void sklepSeqPlaylistComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
	g.setFont (Font(18));

	for (int x=0;x<64;x++)
	{
		g.drawSingleLineText (String (x), 4, (x*32)+20);
	}

	g.fillCheckerBoard (Rectangle<int>(32,0,getWidth(),getHeight()),32,32,Colour (127,127,127), Colour (64,64,64));
    //[/UserPaint]
}

void sklepSeqPlaylistComponent::resized()
{
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void sklepSeqPlaylistComponent::mouseDown (const MouseEvent &e)
{
	Logger::writeToLog (String::formatted (T("x:%d [%d] y:%d [%d]"), e.x, e.x/32, e.y, e.y/32));

	const int x = (e.x-32) /32;
	const int y = e.y /32;

	if (!steps[x][y])
	{
		Logger::writeToLog (T("this step does not exist"));
		sklepSeqPlaylistStep *s = new sklepSeqPlaylistStep (x,y);
		s->setBounds ((x+1)*32,y*32,32,32);
		addAndMakeVisible (s);

		steps[x].add (s);
	}
}

void sklepSeqPlaylistComponent::stepClicked (int _x, int _y)
{
	Logger::writeToLog (String::formatted (T("created step clicked %d %d"), _x, _y));

	for (int k=0;k<steps[_x].size(); k++)
	{
		if (steps[_x][k])
		{
			const int y = steps[_x][k]->getYindex();
			if (y == _y)
			{
				Logger::writeToLog (T("found this step"));
				steps[_x].remove(k);

				break;
			}
		}
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="sklepSeqPlaylistComponent"
                 componentName="" parentClasses="public Component" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330000013" fixedSize="0" initialWidth="2048"
                 initialHeight="2048">
  <BACKGROUND backgroundColour="ffffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
