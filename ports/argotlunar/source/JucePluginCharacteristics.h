#ifndef __PLUGINCHARACTERISTICS_D4EFFF1A__
#define __PLUGINCHARACTERISTICS_D4EFFF1A__

#define JucePlugin_Name                 "Argotlunar"
#define JucePlugin_Desc                 "Granulator"
#define JucePlugin_Manufacturer         "Argotlunar"
#define JucePlugin_ManufacturerCode     'AL'
#define JucePlugin_PluginCode           'ARG1'
#define JucePlugin_MaxNumInputChannels  2
#define JucePlugin_MaxNumOutputChannels 2
#define JucePlugin_PreferredChannelConfigurations {2, 2}
#define JucePlugin_IsSynth              0
#define JucePlugin_WantsMidiInput       0
#define JucePlugin_ProducesMidiOutput   0
#define JucePlugin_WantsLV2TimePos      1
#define JucePlugin_SilenceInProducesSilenceOut  0
#define JucePlugin_TailLengthSeconds    0
#define JucePlugin_EditorRequiresKeyboardFocus  1
#define JucePlugin_VersionCode          0x10000
#define JucePlugin_VersionString        "2.0.0"
#define JucePlugin_VSTUniqueID          JucePlugin_PluginCode
#define JucePlugin_VSTCategory          kPlugCategEffect
#define JucePlugin_LV2Category          "ModulatorPlugin"
#define JucePlugin_AUMainType           kAudioUnitType_Effect
#define JucePlugin_AUSubType            JucePlugin_PluginCode
#define JucePlugin_AUExportPrefix       ArgotlunarAU
#define JucePlugin_AUExportPrefixQuoted "ArgotlunarAU"
#define JucePlugin_AUManufacturerCode   JucePlugin_ManufacturerCode
#define JucePlugin_CFBundleIdentifier   Argotlunar.JuceDemoPlugin
#define JucePlugin_AUCocoaViewClassName ArgotlunarAU_V1
#define JucePlugin_RTASCategory         ePlugInCategory_None
#define JucePlugin_RTASManufacturerCode JucePlugin_ManufacturerCode
#define JucePlugin_RTASProductId        JucePlugin_PluginCode
#define JUCE_USE_VSTSDK_2_4             1

#endif   // __PLUGINCHARACTERISTICS_D4EFFF1A__
