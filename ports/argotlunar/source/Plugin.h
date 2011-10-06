#ifndef PLUGIN_H
#define PLUGIN_H

#include <vector>
#include "juce.h"
#include "JucePluginCharacteristics.h"
#include "Debug.h"
#include "Filter.h"
#include "Granulator.h"
#include "Misc.h"
#include "ProgramBank.h"

class GrainParametersGenerator;
class Granulator;
class ProgramBank;
class PitchQuantizer;

class Plugin : public AudioProcessor, public ChangeBroadcaster
{
public:

  Plugin();
  ~Plugin();
  // Overrides
  AudioProcessorEditor* createEditor();
  bool hasEditor() const { return true; }
  void prepareToPlay (double samplerate, int samples_per_block);
  void releaseResources();
  void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
  float getParameter (int index);
  void setParameter(int index, float new_value);
  const String getParameterName (int index);
  const String getParameterText (int index);
  int getCurrentProgram();
  int getNumPrograms();
  const String getProgramName(int index);
  void changeProgramName(int index, const String& newName);
  void getCurrentProgramStateInformation (MemoryBlock& destData);
  void setCurrentProgramStateInformation(const void* data, int sizeInBytes);
  void getStateInformation (MemoryBlock& destData);
  void setStateInformation (const void* data, int sizeInBytes);
  void setCurrentProgram(int index);
  void setPlayHead(AudioPlayHead *const newPlayHead);
  int getNumParameters();
  bool acceptsMidi() const;
  const String getInputChannelName (const int channelIndex) const;
  const String getName() const;
  const String getOutputChannelName (const int channelIndex) const;
  bool isInputChannelStereoPair (int index) const;
  bool isOutputChannelStereoPair (int index) const;
  bool producesMidi() const;
  // New methods
  bool getEditorSavedState();
  void initCurrentProgram();
  void saveProgramTo(int index);
  void setSavedState(bool state);
  std::vector<String> getScaleNames();

  static const int kNumPrograms = 16;
  static const int kInternalBlocksize = 32;

  Parameters* parameters;
  Granulator* granulator;

private:
  int current_program;
  bool saved_state;
  AudioPlayHead::CurrentPositionInfo pos;
  ProgramBank* program_bank;
};

#endif //PLUGIN_H
