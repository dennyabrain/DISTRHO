/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  5 Nov 2008 11:08:58 am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_PIZBUTTON_PIZBUTTON_AB78F7ED__
#define __JUCER_HEADER_PIZBUTTON_PIZBUTTON_AB78F7ED__

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
class PizButton  : public Button
{
public:
    //==============================================================================
    PizButton ();
    ~PizButton();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void resized();
    void paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown);

    // Binary resources:
    static const char* pirate_png;
    static const int pirate_pngSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    Image internalCachedImage1;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    PizButton (const PizButton&);
    const PizButton& operator= (const PizButton&);
};


#endif   // __JUCER_HEADER_PIZBUTTON_PIZBUTTON_AB78F7ED__
