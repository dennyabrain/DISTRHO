/*

    IMPORTANT! This file is auto-generated each time you save your
    project - if you alter its contents, your changes may be overwritten!

    There's a section below where you can add your own custom code safely, and the
    Introjucer will preserve the contents of that block, but the best way to change
    any of these definitions is by using the Introjucer's project settings.

    Any commented-out settings will assume their default values.

*/

#ifndef __JUCE_APPCONFIG_FFQIFG__
#define __JUCE_APPCONFIG_FFQIFG__

//==============================================================================
// [BEGIN_USER_CODE_SECTION]

// (You can add your own code in this section, and the Introjucer will not overwrite it)
enum OperatingSystemType
{
	MacOSX_10_4 = 0x1004,
	MacOSX_10_5 = 0x1005,
	MacOSX_10_6 = 0x1006,
	MacOSX_10_7 = 0x1007,
	MacOSX_10_8 = 0x1008,
};
// [END_USER_CODE_SECTION]

//==============================================================================
// Audio plugin settings..

#ifndef  JucePlugin_Name
 #define JucePlugin_Name                   "midiChords"
#endif
#ifndef  JucePlugin_Desc
 #define JucePlugin_Desc                   "midiChords"
#endif
#ifndef  JucePlugin_Manufacturer
 #define JucePlugin_Manufacturer           "Insert Piz Here"
#endif
#ifndef  JucePlugin_ManufacturerCode
 #define JucePlugin_ManufacturerCode       'IPHz'
#endif
#ifndef  JucePlugin_PluginCode
 #define JucePlugin_PluginCode             'mCrd'
#endif
#ifndef  JucePlugin_MaxNumInputChannels
 #define JucePlugin_MaxNumInputChannels    0
#endif
#ifndef  JucePlugin_MaxNumOutputChannels
 #define JucePlugin_MaxNumOutputChannels   0
#endif
#ifndef  JucePlugin_PreferredChannelConfigurations
 #define JucePlugin_PreferredChannelConfigurations  {0, 0}
#endif
#ifndef  JucePlugin_IsSynth
 #define JucePlugin_IsSynth                0
#endif
#ifndef  JucePlugin_WantsMidiInput
 #define JucePlugin_WantsMidiInput         1
#endif
#ifndef  JucePlugin_ProducesMidiOutput
 #define JucePlugin_ProducesMidiOutput     1
#endif
#ifndef  JucePlugin_SilenceInProducesSilenceOut
 #define JucePlugin_SilenceInProducesSilenceOut  0
#endif
#ifndef  JucePlugin_TailLengthSeconds
 #define JucePlugin_TailLengthSeconds      0
#endif
#ifndef  JucePlugin_EditorRequiresKeyboardFocus
 #define JucePlugin_EditorRequiresKeyboardFocus  0
#endif
#ifndef  JucePlugin_VersionCode
 #define JucePlugin_VersionCode            0x10202
#endif
#ifndef  JucePlugin_VersionString
 #define JucePlugin_VersionString          "1.2.2"
#endif
#ifndef  JucePlugin_VSTUniqueID
 #define JucePlugin_VSTUniqueID            JucePlugin_PluginCode
#endif
#ifndef  JucePlugin_VSTCategory
 #define JucePlugin_VSTCategory            kPlugCategSynth
#endif
#ifndef  JucePlugin_AUMainType
 #define JucePlugin_AUMainType             kAudioUnitType_MusicDevice
#endif
#ifndef  JucePlugin_AUSubType
 #define JucePlugin_AUSubType              JucePlugin_PluginCode
#endif
#ifndef  JucePlugin_AUExportPrefix
 #define JucePlugin_AUExportPrefix         midiChordsAU
#endif
#ifndef  JucePlugin_AUExportPrefixQuoted
 #define JucePlugin_AUExportPrefixQuoted   "midiChordsAU"
#endif
#ifndef  JucePlugin_AUManufacturerCode
 #define JucePlugin_AUManufacturerCode     JucePlugin_ManufacturerCode
#endif
#ifndef  JucePlugin_CFBundleIdentifier
 #define JucePlugin_CFBundleIdentifier     org.thepiz.midiChords
#endif
#ifndef  JucePlugin_AUCocoaViewClassName
 #define JucePlugin_AUCocoaViewClassName   midiChordsAU_V1
#endif
#ifndef  JucePlugin_RTASCategory
 #define JucePlugin_RTASCategory           ePlugInCategory_SWGenerators
#endif
#ifndef  JucePlugin_RTASManufacturerCode
 #define JucePlugin_RTASManufacturerCode   JucePlugin_ManufacturerCode
#endif
#ifndef  JucePlugin_RTASProductId
 #define JucePlugin_RTASProductId          JucePlugin_PluginCode
#endif

#define JucePlugin_LV2URI               "http://thepiz.org/plugins/?p=midiChords"
#define JucePlugin_WantsLV2State        1
#define JucePlugin_WantsLV2TimePos      1

#endif  // __JUCE_APPCONFIG_FFQIFG__
