/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  27 Jun 2008 10:00:44 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_SKLEPSEQSTEPCOMPONENTEDITOR_SKLEPSEQSTEPCOMPONENTEDITOR_DDBF0930__
#define __JUCER_HEADER_SKLEPSEQSTEPCOMPONENTEDITOR_SKLEPSEQSTEPCOMPONENTEDITOR_DDBF0930__

//[Headers]     -- You can add your own extra header files here --
#include "juce.h"
#include "sklepSeqStep.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class sklepSeqStepComponentEditor  : public Component
{
public:
    //==============================================================================
    sklepSeqStepComponentEditor (MidiMessage *msg);
    ~sklepSeqStepComponentEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    sklepSeqStepComponentEditor (const sklepSeqStepComponentEditor&);
    const sklepSeqStepComponentEditor& operator= (const sklepSeqStepComponentEditor&);
};


#endif   // __JUCER_HEADER_SKLEPSEQSTEPCOMPONENTEDITOR_SKLEPSEQSTEPCOMPONENTEDITOR_DDBF0930__
