
#define JucePlugin_MaxNumInputChannels       0
#define JucePlugin_MaxNumOutputChannels      0

#define JucePlugin_Name                     "sklepSeq"
#define JucePlugin_Manufacturer             "kubiak"
#define JucePlugin_ManufacturerCode         'kubi'
#define JucePlugin_PluginCode               'sksq'
#define JucePlugin_IsSynth                  0
#define JucePlugin_ProducesMidiOutput       1
#define JucePlugin_WantsMidiInput           1
#define JucePlugin_PreferredChannelConfigurations {}
#define JucePlugin_SilenceInProducesSilenceOut 1
#define JucePlugin_EditorRequiresKeyboardFocus 1
#define JucePlugin_TailLengthSeconds 0

#define JucePlugin_VersionCode              0x00010100
#define JucePlugin_VersionString            "1.0"
#define JUCE_USE_VSTSDK_2_4                 1

#define JucePlugin_VSTUniqueID              JucePlugin_PluginCode

#if JucePlugin_IsSynth
  #define JucePlugin_VSTCategory            kPlugCategSynth
#else
  #define JucePlugin_VSTCategory            kPlugCategEffect
#endif
#define JucePlugin_AUSubType                JucePlugin_PluginCode

#define JucePlugin_AUExportPrefix           sklepSeq

#define JucePlugin_AUExportPrefixQuoted     "sklepSeq"
#define JucePlugin_AUManufacturerCode       JucePlugin_ManufacturerCode
#define JucePlugin_CFBundleIdentifier       "ch.sklepSeq"

#define JucePlugin_AUCocoaViewClassName     sklepSeq
#if JucePlugin_IsSynth
  #define JucePlugin_RTASCategory           ePlugInCategory_SWGenerators
#else
  #define JucePlugin_RTASCategory           ePlugInCategory_None
#endif

#define JucePlugin_RTASManufacturerCode     JucePlugin_ManufacturerCode

#define JucePlugin_RTASProductId            JucePlugin_PluginCode

#define JucePlugin_WinBag_path              "C:\\essentials\\PT_73_SDK\\WinBag"

#if JucePlugin_IsSynth
  #define JucePlugin_AUMainType             kAudioUnitType_MusicDevice
#else
  #define JucePlugin_AUMainType             kAudioUnitType_MusicEffect
#endif

#ifndef JucePlugin_Build_Standalone
 #define JucePlugin_Build_Standalone    0
#endif

#if ! JucePlugin_Build_Standalone
 #ifndef JucePlugin_Build_VST
   #define JucePlugin_Build_VST         1
 #endif

 #ifndef JucePlugin_Build_RTAS
   #define JucePlugin_Build_RTAS        0
 #endif

 #ifndef JucePlugin_Build_AU
   #define JucePlugin_Build_AU          1
 #endif
#endif
