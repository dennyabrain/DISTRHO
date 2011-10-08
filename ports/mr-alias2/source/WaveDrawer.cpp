/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  13 Oct 2009 9:16:52 am

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
//[/Headers]

#include "WaveDrawer.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
float WaveDrawer::linearInterpolate(int x,int y1,int y2,int x1,int x2) {
      float slope = (float)(y2-y1)/(float)(x2-x1);
      float y0 = y1 - slope * x1;
      return slope * x + y0;
}
//[/MiscUserDefs]

//==============================================================================
WaveDrawer::WaveDrawer (AudioProcessorEditor* owner_, MrAlias2* plugin_)
    : owner(owner_),
      plugin(plugin_)
{

    //[UserPreSize]
	waveNumber=0;
	wave = plugin->getDrawableWave(0);
	this->setMouseClickGrabsKeyboardFocus(false);
	lastX = lastY = -1;
    //[/UserPreSize]

    setSize (256, 128);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

WaveDrawer::~WaveDrawer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void WaveDrawer::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    //[UserPaint] Add your own custom painting code here..
	float halfHeight = (float)getHeight()*0.5f;
	float increment = (float)getWidth()/256.f;
	g.setColour(Colours::darkgoldenrod);
    for (int x=0;x<256;x++)
    {
		if(fabs(wave[x])>0.01)
			g.drawLine (x*increment, halfHeight, x*increment, jlimit(0.f,(float)getHeight(),(-1.f*wave[x]+1.f)*halfHeight), increment);
    }
    //[/UserPaint]
}

void WaveDrawer::resized()
{
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void WaveDrawer::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
	int x = jlimit(0,256,e.x*256/getWidth());
	if (e.mods.isPopupMenu()) wave[x] = 0.f;
	else wave[x] = -1.f*jlimit(-1.f,1.f,2.f*(float)e.y/(float)getHeight()-1.f);
	plugin->getCallbackLock().enter();
	plugin->updateDrawableWave(waveNumber);
	plugin->getCallbackLock().exit();
	repaint();
    //[/UserCode_mouseDown]
}

void WaveDrawer::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
	int x = jlimit(0,256,e.x*256/getWidth());
	int y = jlimit(0,getHeight(),e.y);
	if (lastX!=-1) {
		if (lastX<x) {
			for (int i=lastX;i<x;i++) {
				if (e.mods.isPopupMenu()) wave[i] = 0.f;
				else {
					float data = linearInterpolate(i,lastY,y,lastX,x);
					wave[i] = -1.f*(2.f*data/(float)getHeight()-1.f);
				}
			}
		}
		else if (lastX>x) {
			for (int i=lastX;i>x;i--) {
				if (e.mods.isPopupMenu()) wave[i] = 0.f;
				else {
					float data = linearInterpolate(i,lastY,y,lastX,x);
					wave[i] = -1.f*(2.f*data/(float)getHeight()-1.f);
				}
			}
		}
	}
	lastX = x;
	lastY = y;
	plugin->getCallbackLock().enter();
	plugin->updateDrawableWave(waveNumber);
	plugin->getCallbackLock().exit();
	repaint();
    //[/UserCode_mouseDrag]
}

void WaveDrawer::mouseUp (const MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
	lastY=-1;
	lastX=-1;
    //[/UserCode_mouseUp]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="WaveDrawer" componentName=""
                 parentClasses="public Component" constructorParams="AudioProcessorEditor* owner_, MrAlias2* plugin_"
                 variableInitialisers="owner(owner_),&#10;plugin(plugin_)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330000013" fixedSize="1"
                 initialWidth="256" initialHeight="128">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseUp (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff000000"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
