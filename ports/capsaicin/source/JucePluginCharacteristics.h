/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2007 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU Lesser General Public License, as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================
*/

#ifndef __JUCETICE_XSYNTH_PLUGIN_CHARACTERISTICS_H__
#define __JUCETICE_XSYNTH_PLUGIN_CHARACTERISTICS_H__

#define JucePlugin_Name                     "Capsaicin"
#define JucePlugin_Desc                     "Hot-Spicy synth"
#define JucePlugin_Manufacturer             "kRAkEn/gORe"
#define JucePlugin_ManufacturerCode         'kNGr'
#define JucePlugin_PluginCode               'jcp0'
#define JucePlugin_MaxNumInputChannels              0
#define JucePlugin_MaxNumOutputChannels             2
#define JucePlugin_PreferredChannelConfigurations   { 0, 1 }, { 0, 2 }
#define JucePlugin_IsSynth                          1
#define JucePlugin_WantsMidiInput                   1
#define JucePlugin_ProducesMidiOutput               0
#define JucePlugin_TailLengthSeconds                0
#define JucePlugin_SilenceInProducesSilenceOut      0
#define JucePlugin_EditorRequiresKeyboardFocus      1

#define JucePlugin_VersionCode              0x00000101
#define JucePlugin_VersionString            "0.1.1"

#define JucePlugin_VSTUniqueID              JucePlugin_PluginCode
#define JucePlugin_VSTCategory              kPlugCategSynth
#define JucePlugin_AUMainType               kAudioUnitType_MusicDevice
#define JucePlugin_AUSubType                JucePlugin_PluginCode
#define JucePlugin_AUExportPrefix           capsaicinAU
#define JucePlugin_AUExportPrefixQuoted     "capsaicinAU"
#define JucePlugin_AUManufacturerCode       JucePlugin_ManufacturerCode
#define JucePlugin_RTASCategory             ePlugInCategory_SWGenerators
#define JucePlugin_RTASManufacturerCode     JucePlugin_ManufacturerCode
#define JucePlugin_RTASProductId            JucePlugin_PluginCode

#define JucePlugin_LV2URI                   "urn:juced:Capsaicin"
#define JucePlugin_LV2Category              "InstrumentPlugin"
#define JucePlugin_WantsLV2State            1
#define JucePlugin_WantsLV2InstanceAccess   1

//==============================================================================

#endif
