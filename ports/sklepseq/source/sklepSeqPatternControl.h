/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  19 Jul 2008 7:21:22 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_SKLEPSEQPATTERNCONTROL_SKLEPSEQPATTERNCONTROL_1649D679__
#define __JUCER_HEADER_SKLEPSEQPATTERNCONTROL_SKLEPSEQPATTERNCONTROL_1649D679__

//[Headers]     -- You can add your own extra header files here --
#include "juce.h"
#include "sklepSeqPattern.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class sklepSeqPatternControl  : public Component,
                                public ChangeBroadcaster,
                                public ComboBoxListener,
                                public SliderListener,
                                public ButtonListener
{
public:
    //==============================================================================
    sklepSeqPatternControl ();
    ~sklepSeqPatternControl();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setPattern (sklepSeqPattern *p);
	int getMidiChannel();
	int getMidiDevice();
	bool getSyncMode();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);

    // Binary resources:
    static const char* rondw_03_png;
    static const int rondw_03_pngSize;
    static const char* rondw_11_png;
    static const int rondw_11_pngSize;
    static const char* rondw_12_png;
    static const int rondw_12_pngSize;
    static const char* rondw_13_png;
    static const int rondw_13_pngSize;
    static const char* rondw_14_png;
    static const int rondw_14_pngSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	int pId;
    //[/UserVariables]

    //==============================================================================
    ComboBox* deviceList;
    Slider* midiCh;
    Label* label;
    Label* label2;
    Label* patternId;
    ToggleButton* syncTypeToggle;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    sklepSeqPatternControl (const sklepSeqPatternControl&);
    const sklepSeqPatternControl& operator= (const sklepSeqPatternControl&);
};


#endif   // __JUCER_HEADER_SKLEPSEQPATTERNCONTROL_SKLEPSEQPATTERNCONTROL_1649D679__
