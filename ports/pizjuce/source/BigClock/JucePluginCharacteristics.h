#ifndef __BIGCLOCK_PLUGIN_CHARACTERISTICS_H__
#define __BIGCLOCK_PLUGIN_CHARACTERISTICS_H__

//==============================================================================
/*                              Generic settings                              */
#define JucePlugin_Name                             "Big Clock"
#define JucePlugin_Desc                             "Time Counter"
#define JucePlugin_Manufacturer                     "Insert Piz Here"
#define JucePlugin_ManufacturerCode                 'IPHz'
#define JucePlugin_PluginCode                       '9wMw'
#define JucePlugin_MaxNumInputChannels              0
#define JucePlugin_MaxNumOutputChannels             2
#define PIZ_FX_MAGIC                                1
#define JucePlugin_PreferredChannelConfigurations   { 0, 2 }
#define JucePlugin_TailLengthSeconds                0
#define JucePlugin_IsSynth                          1
#define JucePlugin_WantsMidiInput                   0
#define JucePlugin_ProducesMidiOutput               0
#define JucePlugin_SilenceInProducesSilenceOut      0
#define JucePlugin_EditorRequiresKeyboardFocus      0
#define JucePlugin_VersionCode                      0x00010200
#define JucePlugin_VersionString                    "1.2"

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
  #define JucePlugin_AUMainType             kAudioUnitType_MusicEffect
#else
  #define JucePlugin_AUMainType             kAudioUnitType_Effect
#endif
#define JucePlugin_AUSubType                JucePlugin_PluginCode
#define JucePlugin_AUExportPrefix           JuceDemoAU
#define JucePlugin_AUExportPrefixQuoted     "JuceDemoAU"
#define JucePlugin_AUManufacturerCode       JucePlugin_ManufacturerCode
#define JucePlugin_CFBundleIdentifier       "com.rawmaterialsoftware.JuceDemo"

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

#define JUCE_ObjCExtraSuffix PIZ_BIGCLOCK_120

#endif
