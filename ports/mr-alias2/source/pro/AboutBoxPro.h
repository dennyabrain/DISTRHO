/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  14 Oct 2009 8:36:19 am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_ABOUTBOX_ABOUTBOXPRO_9E5AF27A__
#define __JUCER_HEADER_ABOUTBOX_ABOUTBOXPRO_9E5AF27A__

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
class AboutBox  : public Button
{
public:
    //==============================================================================
    AboutBox ();
    ~AboutBox();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void resized();
    void paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown);

    // Binary resources:
    static const char* mrAlias2aboutBox_svg;
    static const int mrAlias2aboutBox_svgSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    Drawable* drawable1;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    AboutBox (const AboutBox&);
    const AboutBox& operator= (const AboutBox&);
};


#endif   // __JUCER_HEADER_ABOUTBOX_ABOUTBOXPRO_9E5AF27A__
