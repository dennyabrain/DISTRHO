/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  23 Jun 2008 9:24:31 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_SKLEPSEQPLAYLISTCOMPONENT_SKLEPSEQPLAYLISTCOMPONENT_AB1FE1E5__
#define __JUCER_HEADER_SKLEPSEQPLAYLISTCOMPONENT_SKLEPSEQPLAYLISTCOMPONENT_AB1FE1E5__

//[Headers]     -- You can add your own extra header files here --
#include "juce.h"
#include "sklepSeqPlaylistStep.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class sklepSeqPlaylistComponent  : public Component
{
public:
    //==============================================================================
    sklepSeqPlaylistComponent ();
    ~sklepSeqPlaylistComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void mouseDown (const MouseEvent &e);
	void stepClicked (int _x, int _y);
	
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	Image *stepImage;
	OwnedArray <sklepSeqPlaylistStep> steps[32];

    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    sklepSeqPlaylistComponent (const sklepSeqPlaylistComponent&);
    const sklepSeqPlaylistComponent& operator= (const sklepSeqPlaylistComponent&);
};


#endif   // __JUCER_HEADER_SKLEPSEQPLAYLISTCOMPONENT_SKLEPSEQPLAYLISTCOMPONENT_AB1FE1E5__
