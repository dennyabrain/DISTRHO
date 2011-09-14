/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  26 Jun 2008 7:31:47 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_SKLEPSEQSKIN_SKLEPSEQSKIN_B664AADE__
#define __JUCER_HEADER_SKLEPSEQSKIN_SKLEPSEQSKIN_B664AADE__

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
class sklepSeqSkin  : public LookAndFeel,
                      public Component
{
public:
    //==============================================================================
    sklepSeqSkin ();
    ~sklepSeqSkin();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void drawDocumentWindowTitleBar (DocumentWindow &window, Graphics &g,int	w, int h, int titleSpaceX, int titleSpaceW, const Image *icon, bool drawTitleTextOnLeft);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();

    // Binary resources:
    static const char* close_window_png;
    static const int close_window_pngSize;
    static const char* maximize_window_png;
    static const int maximize_window_pngSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    sklepSeqSkin (const sklepSeqSkin&);
    const sklepSeqSkin& operator= (const sklepSeqSkin&);
};


#endif   // __JUCER_HEADER_SKLEPSEQSKIN_SKLEPSEQSKIN_B664AADE__
