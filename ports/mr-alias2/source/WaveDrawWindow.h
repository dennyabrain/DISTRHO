/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  15 Nov 2009 10:21:36 am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_WAVEDRAWWINDOW_WAVEDRAWWINDOW_70A89B17__
#define __JUCER_HEADER_WAVEDRAWWINDOW_WAVEDRAWWINDOW_70A89B17__

//[Headers]     -- You can add your own extra header files here --
//[/Headers]

#include "WaveDrawer.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class WaveDrawWindow  : public Component,
                        public ButtonListener
{
public:
    //==============================================================================
    WaveDrawWindow (AudioProcessorEditor* owner_, MrAlias2* plugin_);
    ~WaveDrawWindow();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setWave(int index);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    AudioProcessorEditor* owner;
    MrAlias2* plugin;
	int waveNumber;
    //[/UserVariables]

    //==============================================================================
    WaveDrawer* waveDrawer;
    TextButton* sineButton;
    TextButton* sawButton;
    TextButton* squareButton;
    TextButton* triangleButton;
    TextButton* invertButton;
    TextButton* reverseButton;
    TextButton* saveButton;
    TextButton* loadButton;
    TextButton* normalizeButton;
    TextButton* recordButton;
    TextButton* copyButton;
    TextButton* rampButton;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    WaveDrawWindow (const WaveDrawWindow&);
    const WaveDrawWindow& operator= (const WaveDrawWindow&);
};


#endif   // __JUCER_HEADER_WAVEDRAWWINDOW_WAVEDRAWWINDOW_70A89B17__
