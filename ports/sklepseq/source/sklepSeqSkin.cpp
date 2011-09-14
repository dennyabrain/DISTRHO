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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "sklepSeqSkin.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
sklepSeqSkin::sklepSeqSkin ()
{

    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

sklepSeqSkin::~sklepSeqSkin()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void sklepSeqSkin::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void sklepSeqSkin::resized()
{
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void sklepSeqSkin::drawDocumentWindowTitleBar (DocumentWindow &window, Graphics &g,int	w, int h, int titleSpaceX, int titleSpaceW, const Image *icon, bool drawTitleTextOnLeft)
{
    ColourGradient gradient_1 (Colour (0xffb8b8b8),
                              112.0f, 0.0f,
                              Colours::black,
                              112.0f, 24.0f,
                              false);
    g.setGradientFill (gradient_1);
    g.fillRect (0, 0, w, h);

    ColourGradient gradient_2 (Colour (0x5dbdbdbd),
                              0.0f, 16.0f,
                              Colour (0x86ffffff),
                              (float)w, 16.0f,
                              false);
    g.setGradientFill (gradient_2);
    g.fillRect (0, 0, w, h);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="sklepSeqSkin" componentName=""
                 parentClasses="public LookAndFeel, public Component" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330000013" fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="ffffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: close_window_png, 644, "C:\close_window.png"
static const unsigned char resource_sklepSeqSkin_close_window_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,16,0,0,0,16,8,6,0,0,0,31,243,255,97,0,0,0,1,115,82,71,66,0,174,206,28,233,0,
0,0,6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,17,0,0,11,17,1,127,100,95,145,0,0,0,7,116,73,77,69,7,216,6,26,17,27,42,237,52,189,178,0,0,2,4,73,68,65,84,56,203,165,147,
49,75,92,81,16,133,191,153,59,111,31,65,37,91,164,16,172,52,250,7,210,88,4,201,98,179,181,66,4,193,194,52,169,77,43,4,33,85,254,193,150,105,133,84,238,178,96,103,149,194,159,160,178,164,178,89,86,48,79,
87,178,239,189,251,38,197,102,197,77,132,8,185,48,112,25,238,156,51,231,220,25,248,207,35,7,31,15,234,193,194,59,85,125,43,34,47,0,249,71,141,187,251,160,170,170,175,177,140,95,76,77,63,45,175,44,191,
95,88,88,72,67,8,79,98,141,49,174,92,94,94,190,58,63,59,95,180,249,249,249,221,198,155,70,154,212,18,16,65,112,220,255,104,19,240,201,77,0,119,150,150,150,210,193,96,176,107,105,154,206,213,210,218,212,
115,121,68,196,84,74,4,119,39,198,106,78,1,84,245,62,170,170,162,213,106,209,237,118,169,170,138,24,35,237,118,155,86,171,133,187,163,170,184,59,89,150,1,142,137,8,170,122,15,110,102,204,206,206,210,233,
116,80,85,202,178,164,219,237,210,104,52,152,120,148,101,25,63,71,35,130,134,191,1,84,149,237,237,109,220,157,195,195,67,220,157,102,179,201,214,214,22,238,206,245,245,53,195,225,144,196,12,13,58,6,144,
7,162,221,29,21,165,94,175,83,20,5,34,194,204,204,12,183,55,55,148,49,226,238,212,106,99,207,66,8,216,132,21,32,207,115,110,110,111,233,180,219,28,31,31,179,190,190,78,81,20,28,29,29,145,231,57,205,102,
115,138,76,31,74,24,141,70,220,221,221,81,149,37,23,23,23,172,173,173,177,177,177,9,56,73,146,208,235,245,48,179,41,185,97,34,33,198,72,158,231,4,11,4,123,198,222,222,7,204,12,179,177,105,59,59,59,148,
101,36,77,211,169,111,85,85,172,170,42,47,138,66,130,5,130,143,11,146,185,100,106,6,146,36,121,108,158,17,17,215,44,203,206,250,253,62,42,58,102,13,1,11,134,5,35,252,238,226,62,130,17,194,88,198,213,213,
21,195,225,240,204,242,60,223,63,57,57,249,28,66,88,20,145,228,41,187,224,238,69,140,241,123,81,20,251,2,112,122,122,250,18,120,13,60,127,226,22,255,0,190,173,174,174,246,126,1,151,45,214,238,196,167,
41,19,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* sklepSeqSkin::close_window_png = (const char*) resource_sklepSeqSkin_close_window_png;
const int sklepSeqSkin::close_window_pngSize = 644;

// JUCER_RESOURCE: maximize_window_png, 571, "C:\maximize_window.png"
static const unsigned char resource_sklepSeqSkin_maximize_window_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,16,0,0,0,16,8,6,0,0,0,31,243,255,97,0,0,0,1,115,82,71,66,0,174,206,28,233,
0,0,0,6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,14,0,0,11,14,1,64,190,225,65,0,0,0,7,116,73,77,69,7,216,6,26,17,27,50,254,88,37,228,0,0,1,187,73,68,65,84,56,203,165,
145,193,106,83,97,16,133,191,249,255,255,222,24,186,136,4,161,89,84,179,208,144,23,80,186,144,110,237,3,248,8,37,80,112,239,66,104,35,21,42,184,241,9,124,4,247,221,23,23,197,7,176,27,105,107,23,77,130,
132,27,146,152,220,132,127,198,69,77,244,218,130,1,103,53,28,102,206,156,51,7,254,179,164,189,215,190,171,232,142,247,254,185,19,119,15,144,127,236,152,154,126,143,49,126,116,184,15,65,209,183,205,102,
115,167,94,175,39,222,251,149,174,198,24,27,23,23,23,143,79,191,156,62,10,235,235,235,187,219,207,182,73,75,41,136,32,24,102,127,201,4,108,209,9,96,70,163,209,72,186,221,238,110,40,151,203,148,238,148,
10,227,114,139,137,2,36,130,153,161,170,4,17,193,57,87,24,126,179,191,207,160,223,47,96,149,106,149,189,131,131,133,5,178,44,3,184,157,224,242,252,156,39,91,91,5,236,243,241,49,206,57,84,149,44,203,152,
78,167,56,231,8,192,13,130,251,27,27,180,90,45,228,151,84,51,227,234,236,140,24,35,253,126,159,209,104,68,146,36,120,239,111,42,48,51,212,174,175,204,231,243,37,62,157,76,232,245,122,152,41,105,154,130,
112,147,32,207,115,70,163,17,147,31,19,6,131,1,246,199,3,163,42,73,154,32,198,18,95,18,136,56,242,124,202,120,60,198,204,40,173,173,241,254,240,176,240,245,74,181,74,154,164,5,171,222,251,235,31,168,70,
242,89,142,15,129,128,241,170,253,186,16,165,45,98,180,98,158,206,57,130,170,50,155,205,8,33,252,214,182,66,153,25,34,66,200,178,172,211,233,116,106,181,90,13,231,221,74,203,170,74,231,234,138,225,112,
216,9,49,198,23,71,71,71,239,188,247,15,68,36,89,241,250,60,198,248,77,85,95,10,192,201,201,201,67,224,41,80,89,209,193,0,248,180,185,185,249,245,39,170,32,197,183,22,221,147,72,0,0,0,0,73,69,78,68,174,
66,96,130,0,0};

const char* sklepSeqSkin::maximize_window_png = (const char*) resource_sklepSeqSkin_maximize_window_png;
const int sklepSeqSkin::maximize_window_pngSize = 571;
