/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jul 2008 12:43:10 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_SKLEPSEQMAINCOMPONENT_SKLEPSEQMAINCOMPONENT_567E0F79__
#define __JUCER_HEADER_SKLEPSEQMAINCOMPONENT_SKLEPSEQMAINCOMPONENT_567E0F79__

//[Headers]     -- You can add your own extra header files here --
#include "juce.h"
#include "sklepSeqCursorComponent.h"
#include "sklepSeqPatternControl.h"
#include "sklepSeqMain.h"
#include "sklepSeqStep.h"
#include "sklepSeqPlaylist.h"
#include "stepQuickEdit.h"
//[/Headers]

#include "sklepSeqTransportComponent.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class sklepSeqMainComponent  : public Component,
                               public AsyncUpdater,
                               public ChangeListener,
                               public MidiKeyboardStateListener,
                               public ButtonListener
{
public:
    //==============================================================================
    sklepSeqMainComponent (DemoJuceFilter *f);
    ~sklepSeqMainComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setPosition (int beat, int bpm);
    void handleAsyncUpdate();
	void clearCursor();
	void patternChanged();
	void stepRightClicked(int i);
	void clearSteps();
	void changeListenerCallback(ChangeBroadcaster *ptr);
	void stepQuickEditClicked(sklepSeqStep *step);
	void handleNoteOn (MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float velocity);
	void handleNoteOff (MidiKeyboardState *source, int midiChannel, int midiNoteNumber);
	void mouseDown (const MouseEvent &e);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

    // Binary resources:
    static const char* sq_back_png;
    static const int sq_back_pngSize;
    static const char* sq_nazwa_png;
    static const int sq_nazwa_pngSize;
    static const char* sq_kursor_1_png;
    static const int sq_kursor_1_pngSize;
    static const char* sq_kursor_2_png;
    static const int sq_kursor_2_pngSize;
    static const char* sq_kursor_3_png;
    static const int sq_kursor_3_pngSize;
    static const char* sq_kursor_4_png;
    static const int sq_kursor_4_pngSize;
    static const char* sq_kursor_5_png;
    static const int sq_kursor_5_pngSize;
    static const char* sq_kursor_6_png;
    static const int sq_kursor_6_pngSize;
    static const char* sq_kursor_7_png;
    static const int sq_kursor_7_pngSize;
    static const char* sq_kursor_8_png;
    static const int sq_kursor_8_pngSize;
    static const char* sq_kursor_9_png;
    static const int sq_kursor_9_pngSize;
    static const char* sq_kursor_10_png;
    static const int sq_kursor_10_pngSize;
    static const char* sq_kursor_11_png;
    static const int sq_kursor_11_pngSize;
    static const char* sq_kursor_12_png;
    static const int sq_kursor_12_pngSize;
    static const char* sq_kursor_13_png;
    static const int sq_kursor_13_pngSize;
    static const char* sq_kursor_14_png;
    static const int sq_kursor_14_pngSize;
    static const char* sq_kursor_15_png;
    static const int sq_kursor_15_pngSize;
    static const char* sq_kursor_16_png;
    static const int sq_kursor_16_pngSize;
    static const char* rondw_03_png;
    static const int rondw_03_pngSize;
    static const char* lcd_bin;
    static const int lcd_binSize;
    static const char* down_big_png;
    static const int down_big_pngSize;
    static const char* down_small_png;
    static const int down_small_pngSize;
    static const char* up_big_png;
    static const int up_big_pngSize;
    static const char* up_small_png;
    static const int up_small_pngSize;
    static const char* power_off_png;
    static const int power_off_pngSize;
    static const char* power_on_png;
    static const int power_on_pngSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	OwnedArray <sklepSeqCursorComponent> cursor;
	OwnedArray <sklepSeqStep> step;
	GlowEffect glow;
	DemoJuceFilter *ownerFilter;
	int prevPos;
	double prevBpm;
	sklepSeqPatternControl *options;
	Font *lcdBigFont;
	Font *lcdSmallFont;
	bool firstHalf;
	sklepSeqPlaylist *playlist;
	stepQuickEdit *quickEdit;
    //[/UserVariables]

    //==============================================================================
    sklepSeqTransportComponent* transportComponent;
    ImageButton* optionsButton;
    Label* patternLenLabel;
    ImageButton* patternLenDown;
    ImageButton* patternLenUp;
    Label* currentPatternLabel;
    ImageButton* currentPatternDown;
    ImageButton* currentPatternUp;
    ImageButton* powerButton;
    ImageButton* upperHalf;
    ImageButton* lowerHalf;
    Image internalCachedImage1;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    sklepSeqMainComponent (const sklepSeqMainComponent&);
    const sklepSeqMainComponent& operator= (const sklepSeqMainComponent&);
};


#endif   // __JUCER_HEADER_SKLEPSEQMAINCOMPONENT_SKLEPSEQMAINCOMPONENT_567E0F79__
