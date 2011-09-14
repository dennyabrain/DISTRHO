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

#ifndef __JUCER_HEADER_STEPEDITSYSEX_STEPEDITSYSEX_4791C31A__
#define __JUCER_HEADER_STEPEDITSYSEX_STEPEDITSYSEX_4791C31A__

//[Headers]     -- You can add your own extra header files here --
#include "juce.h"
#include "myMidiMessage.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class stepEditSysex  : public Component,
                       public ButtonListener
{
public:
    //==============================================================================
    stepEditSysex (myMidiMessage *msg);
    ~stepEditSysex();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setMidiRawData (String t);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	uint8 *midiRawData;
	int midiRawDataLen;
	myMidiMessage *midiMessage;
    //[/UserVariables]

    //==============================================================================
    TextEditor* midiData;
    TextButton* saveButton;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    stepEditSysex (const stepEditSysex&);
    const stepEditSysex& operator= (const stepEditSysex&);
};


#endif   // __JUCER_HEADER_STEPEDITSYSEX_STEPEDITSYSEX_4791C31A__
