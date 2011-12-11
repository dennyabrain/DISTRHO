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

#ifndef __JUCER_HEADER_WAVEDRAWER_WAVEDRAWER_4B96AD9A__
#define __JUCER_HEADER_WAVEDRAWER_WAVEDRAWER_4B96AD9A__

//[Headers]     -- You can add your own extra header files here --
#include "MrAlias2.h"
#include "juce.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class WaveDrawer  : public Component
{
public:
    //==============================================================================
    WaveDrawer (AudioProcessorEditor* owner_, MrAlias2* plugin_);
    ~WaveDrawer();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setSource(float* source) {wave=source; repaint();}
	float* getFloatData() {return wave;}
	int waveNumber;
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);
    void mouseUp (const MouseEvent& e);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	float* wave;
	int lastX, lastY;
	float linearInterpolate(int x,int y1,int y2,int x1,int x2);
    AudioProcessorEditor* owner;
    MrAlias2* plugin;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    WaveDrawer (const WaveDrawer&);
    const WaveDrawer& operator= (const WaveDrawer&);
};


#endif   // __JUCER_HEADER_WAVEDRAWER_WAVEDRAWER_4B96AD9A__
