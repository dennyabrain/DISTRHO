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

#ifndef __JUCER_HEADER_STEPQUICKEDIT_STEPQUICKEDIT_B3D791C1__
#define __JUCER_HEADER_STEPQUICKEDIT_STEPQUICKEDIT_B3D791C1__

//[Headers]     -- You can add your own extra header files here --
#include "juce.h"
#include "stepEditNote.h"
#include "stepEditController.h"
#include "stepEditSysex.h"
#include "myMidiMessage.h"

class sklepSeqMainComponent;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class stepQuickEdit  : public Component,
                       public ComboBoxListener
{
public:
    //==============================================================================
    stepQuickEdit (sklepSeqMainComponent *parent, myMidiMessage *msg);
    ~stepQuickEdit();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void mouseDown (const MouseEvent& e);
	void mouseDrag (const MouseEvent& e);
	void mouseMove (const MouseEvent &e);
	void messageTypeChanged();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	MidiKeyboardState midiKeyboardState;
	ComponentDragger myDragger;
	myMidiMessage *midiMessage;
	MidiBuffer *midiBuffer;
	Component *editorComponent;

	enum editorTypes
	{
		none,
		noteOn,
		Controller,
		SysEx,
		ProgramChange,
		MMC
	};

    //[/UserVariables]

    //==============================================================================
    ComboBox* typeCombo;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    stepQuickEdit (const stepQuickEdit&);
    const stepQuickEdit& operator= (const stepQuickEdit&);
};


#endif   // __JUCER_HEADER_STEPQUICKEDIT_STEPQUICKEDIT_B3D791C1__
