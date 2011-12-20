#ifndef __MIDIKEYBOARD_PLUGIN_CHARACTERISTICS_H__
#define __MIDIKEYBOARD_PLUGIN_CHARACTERISTICS_H__

//==============================================================================
/*                              Generic settings                              */
#define PIZMIDI                                     1
#define JucePlugin_Name                             "midiKeyboard"
#define JucePlugin_Desc                             "MIDI Keyboard Plugin"
#define JucePlugin_Manufacturer                     "Insert Piz Here"
#define JucePlugin_ManufacturerCode                 'IPHz'
#define JucePlugin_PluginCode                       'keyb'
#define JucePlugin_MaxNumInputChannels              2
#define JucePlugin_MaxNumOutputChannels             2
#define JucePlugin_PreferredChannelConfigurations   { 2, 2 }
#define JucePlugin_IsSynth                          1
#define JucePlugin_WantsMidiInput                   1
#define JucePlugin_ProducesMidiOutput               1
#define JucePlugin_TailLengthSeconds                0
#define JucePlugin_SilenceInProducesSilenceOut      0
#define JucePlugin_EditorRequiresKeyboardFocus      0
#define JucePlugin_VersionCode                      0x00010400
#define JucePlugin_VersionString                    "1.4"

//==============================================================================
/*                                VST settings                                */
#define JUCE_USE_VSTSDK_2_4                 1
#define JucePlugin_VSTUniqueID              JucePlugin_PluginCode
#if JucePlugin_IsSynth
  #define JucePlugin_VSTCategory            kPlugCategSynth
#else
  #define JucePlugin_VSTCategory            kPlugCategEffect
#endif

//==============================================================================
/*                              AudioUnit settings                            */
#if JucePlugin_IsSynth
  #define JucePlugin_AUMainType             kAudioUnitType_MusicDevice
#else
  #define JucePlugin_AUMainType             kAudioUnitType_Effect
#endif
#define JucePlugin_AUSubType                JucePlugin_PluginCode
#define JucePlugin_AUExportPrefix           midiKeyboard
#define JucePlugin_AUExportPrefixQuoted     "midiKeyboard"
#define JucePlugin_AUManufacturerCode       JucePlugin_ManufacturerCode
#define JucePlugin_CFBundleIdentifier       "org.thepiz.midiKeyboard"

//==============================================================================
/*                                RTAS settings                               */
#if JucePlugin_IsSynth
  #define JucePlugin_RTASCategory           ePlugInCategory_SWGenerators
#else
  #define JucePlugin_RTASCategory           ePlugInCategory_None
#endif
#define JucePlugin_RTASManufacturerCode     JucePlugin_ManufacturerCode
#define JucePlugin_RTASProductId            JucePlugin_PluginCode

//==============================================================================

#define JUCE_ObjCExtraSuffix PIZ_MIDIKEYBOARD_120

#endif
