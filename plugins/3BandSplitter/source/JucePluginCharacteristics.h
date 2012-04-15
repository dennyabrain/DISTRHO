/*

    IMPORTANT! This file is auto-generated by the Jucer each time you save your
    project - if you alter its contents, your changes may be overwritten!

    This header file contains configuration options for the plug-in. If you need to change any of
    these, it'd be wise to do so using the Jucer, rather than editing this file directly...

*/

#ifndef __JUCEPLUGINCHARACTERISTICS_H__
#define __JUCEPLUGINCHARACTERISTICS_H__

#define JucePlugin_Name                 "3BandSplitter"
#define JucePlugin_Desc                 "3BandSplitter"
#define JucePlugin_Manufacturer         "DISTRHO"
#define JucePlugin_ManufacturerCode     'DIST'
#define JucePlugin_PluginCode           'D3ES'
#define JucePlugin_MaxNumInputChannels  2
#define JucePlugin_MaxNumOutputChannels 6
#define JucePlugin_PreferredChannelConfigurations   {1, 1}, {1, 2}, {1, 3}, {2, 4}, {2, 5}, {2, 6}
#define JucePlugin_IsSynth              0
#define JucePlugin_WantsMidiInput       0
#define JucePlugin_ProducesMidiOutput   0
#define JucePlugin_SilenceInProducesSilenceOut  0
#define JucePlugin_TailLengthSeconds    0
#define JucePlugin_EditorRequiresKeyboardFocus  0
#define JucePlugin_VersionCode          0x10000
#define JucePlugin_VersionString        "1.0"
#define JucePlugin_VSTUniqueID          JucePlugin_PluginCode
#define JucePlugin_VSTCategory          kPlugCategEffect
#define JucePlugin_AUMainType           kAudioUnitType_Effect
#define JucePlugin_AUSubType            JucePlugin_PluginCode
#define JucePlugin_AUExportPrefix       DISTRHO_3BandSplitter_AU
#define JucePlugin_AUExportPrefixQuoted "DISTRHO_3BandSplitter_AU"
#define JucePlugin_AUManufacturerCode   DISTRHO_3BandSplitter_MC
#define JucePlugin_CFBundleIdentifier   com.distrho.3BandSplitter
#define JucePlugin_AUCocoaViewClassName DISTRHO_3BandSplitter_VCN
#define JucePlugin_RTASCategory         ePlugInCategory_None
#define JucePlugin_RTASManufacturerCode JucePlugin_ManufacturerCode
#define JucePlugin_RTASProductId        JucePlugin_PluginCode

#define JucePlugin_LV2URI               "http://distrho.sourceforge.net/plugins/3BandSplitter"
#define JucePlugin_LV2Category          "EQPlugin"

#endif   // __JUCEPLUGINCHARACTERISTICS_H__
