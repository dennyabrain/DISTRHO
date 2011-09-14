/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  12 Jul 2008 9:28:32 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_SKLEPSEQKNOBBY_SKLEPSEQKNOBBY_2907B234__
#define __JUCER_HEADER_SKLEPSEQKNOBBY_SKLEPSEQKNOBBY_2907B234__

//[Headers]     -- You can add your own extra header files here --
#include "juce.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class sklepSeqKnobby  : public Component,
                        public SliderListener
{
public:
    //==============================================================================
    sklepSeqKnobby ();
    ~sklepSeqKnobby();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    Slider* slider;
    Slider* slider2;
    Slider* slider3;
    Slider* slider4;
    Slider* slider5;
    Slider* slider6;
    Slider* slider7;
    Slider* slider8;
    Slider* slider25;
    Slider* slider26;
    Slider* slider27;
    Slider* slider28;
    Slider* slider9;
    Slider* slider10;
    Slider* slider11;
    Slider* slider12;
    Slider* slider13;
    Slider* slider14;
    Slider* slider15;
    Slider* slider16;
    Slider* slider17;
    Slider* slider18;
    Slider* slider19;
    Slider* slider20;
    Slider* slider21;
    Slider* slider22;
    Slider* slider23;
    Slider* slider24;
    Slider* slider29;
    Slider* slider30;
    Slider* slider31;
    Slider* slider32;
    Slider* slider33;
    Slider* slider34;
    Slider* slider35;
    Slider* slider36;
    Slider* slider37;
    Slider* slider38;
    Slider* slider39;
    Slider* slider40;
    Slider* slider41;
    Slider* slider42;
    GroupComponent* groupComponent;
    GroupComponent* groupComponent2;
    GroupComponent* groupComponent3;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    sklepSeqKnobby (const sklepSeqKnobby&);
    const sklepSeqKnobby& operator= (const sklepSeqKnobby&);
};


#endif   // __JUCER_HEADER_SKLEPSEQKNOBBY_SKLEPSEQKNOBBY_2907B234__
