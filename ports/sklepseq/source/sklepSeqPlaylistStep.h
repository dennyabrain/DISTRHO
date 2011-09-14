/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  23 Jun 2008 9:22:28 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_SKLEPSEQPLAYLISTSTEP_SKLEPSEQPLAYLISTSTEP_656DC97D__
#define __JUCER_HEADER_SKLEPSEQPLAYLISTSTEP_SKLEPSEQPLAYLISTSTEP_656DC97D__

//[Headers]     -- You can add your own extra header files here --
#include "juce.h"
class sklepSeqPlaylistComponent;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class sklepSeqPlaylistStep  : public Component,
                              public ButtonListener
{
public:
    //==============================================================================
    sklepSeqPlaylistStep (int _x, int _y);
    ~sklepSeqPlaylistStep();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	int getXindex();
	int getYindex();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

    // Binary resources:
    static const char* boing_png;
    static const int boing_pngSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	int index;
	Image *image;
	int x,y;
    //[/UserVariables]

    //==============================================================================
    ImageButton* imageButton;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    sklepSeqPlaylistStep (const sklepSeqPlaylistStep&);
    const sklepSeqPlaylistStep& operator= (const sklepSeqPlaylistStep&);
};


#endif   // __JUCER_HEADER_SKLEPSEQPLAYLISTSTEP_SKLEPSEQPLAYLISTSTEP_656DC97D__
