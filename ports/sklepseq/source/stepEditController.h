/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  2 Jul 2008 9:33:57 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_STEPEDITCONTROLLER_STEPEDITCONTROLLER_1DE3B48D__
#define __JUCER_HEADER_STEPEDITCONTROLLER_STEPEDITCONTROLLER_1DE3B48D__

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
class stepEditController  : public Component,
                            public SliderListener,
                            public ComboBoxListener
{
public:
    //==============================================================================
    stepEditController (myMidiMessage *msg);
    ~stepEditController();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setMidiData();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	enum controllerType
	{
		CC,
		RPN,
		NRPN
	};

	MidiBuffer midiBuf;
	myMidiMessage *midiMessage;
    //[/UserVariables]

    //==============================================================================
    Slider* controllerValue;
    Slider* controllerNumber;
    Label* label;
    Label* label2;
    ComboBox* typeCombo;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    stepEditController (const stepEditController&);
    const stepEditController& operator= (const stepEditController&);
};


#endif   // __JUCER_HEADER_STEPEDITCONTROLLER_STEPEDITCONTROLLER_1DE3B48D__
