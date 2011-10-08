/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  8 Nov 2009 10:35:07 am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_MRALIASEDITOR_MRALIASGUI_C5A89275__
#define __JUCER_HEADER_MRALIASEDITOR_MRALIASGUI_C5A89275__

//[Headers]     -- You can add your own extra header files here --
#include "MrAlias2.h"
#include "juce.h"
#include "common/piz_LookAndFeel.h"
#include "CCMapSlider.h"
#include "piz_ComboBox.h"
//[/Headers]

#include "led.h"
#include "PizButton.h"
#include "AboutBox.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MrAlias2Editor  : public AudioProcessorEditor,
                        public ChangeListener,
                        public FileDragAndDropTarget,
                        public PizComboBoxListener,
                        public ComboBoxListener,
                        public SliderListener,
                        public ButtonListener,
                        public LabelListener
{
public:
    //==============================================================================
    MrAlias2Editor (MrAlias2* const ownerFilter);
    ~MrAlias2Editor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void changeListenerCallback (ChangeBroadcaster* source);
    bool isInterestedInFileDrag (const StringArray& files);
    void filesDropped (const StringArray& filenames, int mouseX, int mouseY);
    void sliderDragStarted (Slider* slider); //slider mousedown
    void sliderDragEnded (Slider* slider); //slider mouseup
    void mouseDown (const MouseEvent& e);
    void mouseUp (const MouseEvent& e);
	void buttonStateChanged(Button* buttonThatWasClicked);
	void showControlMenu(Component* c);
	//[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);
    void labelTextChanged (Label* labelThatHasChanged);

    // Binary resources:
    static const char* mralias2_png;
    static const int mralias2_pngSize;
    static const char* alias_svg2;
    static const int alias_svg2Size;
    static const char* title_svg2;
    static const int title_svg2Size;
    static const char* whitetitle_svg;
    static const int whitetitle_svgSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    enum componenttypes {sliderType,buttonType,comboBoxType};
    ComponentBoundsConstrainer resizeLimits;
    TooltipWindow tooltipWindow;

    void updateParametersFromFilter();

    inline float mapToVSTRange(Slider* source);
    inline void setVSTSlider(Slider* slider, float x);
    inline int getSliderIndex(Slider* slider);
    inline void getComponentIndexAndType(Component* c, int &index, int &type);
    Slider* getSliderByIndex(int index);
    int oldccmap[numParams];
    CCMapSlider* ccmapbox[numParams];

    MrAlias2* getFilter() const throw() { return (MrAlias2*) getAudioProcessor(); }

    bool init;

    double aspectRatio;

//    float* params;
//    int* ccmap;

    //[/UserVariables]

    //==============================================================================
    PizComboBox* patchBox;
    Slider* sAlias;
    Slider* sCutoff;
    Slider* sDivide;
    Slider* sAtt;
    Slider* sRate;
    Slider* sSineMix;
    Slider* sSineRes;
    Slider* sPostDivide;
    Slider* sClip;
    Slider* sAInertia;
    Slider* sDec;
    Slider* sSus;
    Slider* sRel;
    Slider* sDivEnv;
    Slider* sRes;
    Slider* sBRMix;
    Slider* sVolume;
    Slider* sSineFreq;
    Slider* sVelSens;
    Slider* sFiltEnv;
    Slider* sFVSens;
    Slider* sPBRange;
    Slider* sInputGain;
    Slider* sWet;
    Slider* sOscGain;
    Slider* sThresh;
    Slider* sFreq1;
    Slider* sRingMod;
    Slider* sFAtt;
    Slider* sFDec;
    Slider* sFSus;
    Slider* sFRel;
    LED* audioled;
    Slider* sStereo;
    Slider* sOscMix;
    LED* clipled;
    TextButton* sMode;
    Slider* sStereo2;
    Slider* sM1;
    Slider* sPhMod;
    Slider* sDivMix;
    Label* info;
    PizButton* pizButton;
    Slider* sFKeyFollow;
    TextButton* nextButton;
    TextButton* prevButton;
    TextButton* sReset;
    Slider* sOPLP;
    Slider* sPostDivMix;
    TextButton* sSavePatch;
    TextButton* sSavePatch2;
    Label* info3;
    Label* info2;
    TextButton* loadButton;
    ComboBox* filterModeBox;
    Slider* sOctave1;
    ComboBox* comboBox;
    Slider* sOctave2;
    ComboBox* comboBox2;
    Slider* sChannel;
    Slider* sOctave;
    TextButton* sUseProgCh;
    Slider* sM1Mix;
    TextButton* randomButton;
    TextButton* limiterButton;
    TextButton* sExp;
    TextButton* sFExp;
    LED* midiled;
    TextButton* saveSnapshotButtonB;
    TextButton* recallSnapshotButtonB;
    Slider* sMorph;
    TextButton* saveSnapshotButtonA;
    TextButton* recallSnapshotButtonA;
    AboutBox* aboutbox;
    TextButton* sPitchShift;
    ResizableCornerComponent* resizer;
    Drawable* drawable1;
    Image cachedImage_mralias2_png;
    Path internalPath2;
    Path internalPath3;
    Drawable* drawable4;
    Path internalPath5;
    Path internalPath6;
    Drawable* drawable7;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    MrAlias2Editor (const MrAlias2Editor&);
    const MrAlias2Editor& operator= (const MrAlias2Editor&);
};


#endif   // __JUCER_HEADER_MRALIASEDITOR_MRALIASGUI_C5A89275__
