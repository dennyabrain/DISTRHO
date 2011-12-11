#include "Plugin.h"
#include "PluginEditor.h"


AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
  return new Plugin();
}

Plugin::Plugin()
{
  parameters = new Parameters(this, kInternalBlocksize);
  granulator = new Granulator(parameters, kInternalBlocksize);
  program_bank = new ProgramBank(kNumPrograms, parameters);
  current_program = 0;
}

Plugin::~Plugin()
{
  delete parameters;
  delete granulator;
  delete program_bank;
}

bool Plugin::acceptsMidi() const
{
  return false;
}

bool Plugin::isInputChannelStereoPair(int index) const
{
  return true;
}

bool Plugin::isOutputChannelStereoPair(int index) const
{
  return true;
}

bool Plugin::producesMidi() const
{
  return false;
}

const String Plugin::getName() const
{
  return "Argotlunar2";
}

const String Plugin::getInputChannelName(const int channelIndex) const
{
  return String (channelIndex + 1);
}

const String Plugin::getOutputChannelName(const int channelIndex) const
{
  return (channelIndex == 0) ? "L" : "R";
}

AudioProcessorEditor* Plugin::createEditor()
{
  return new PluginEditor(this);
}

void Plugin::prepareToPlay (double samplerate, int samples_per_block)
{
  granulator->prepareToPlay(static_cast<float>(samplerate));
  sendChangeMessage();
}

void Plugin::releaseResources()
{
  granulator->releaseResources();
}

void Plugin::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
  if (getNumInputChannels() != 2 && getNumOutputChannels() != 2) {
    return;
  }
  float* chan1 = buffer.getSampleData(0);
  float* chan2 = buffer.getSampleData(1);
  int sampleframes = buffer.getNumSamples();
  int blocks = sampleframes / kInternalBlocksize;

  if (getPlayHead() != 0 && getPlayHead()->getCurrentPosition(pos)) {
    parameters->time_quantizer->setPositionInfo(&pos);
  } else {
    parameters->setQuantizationDisabled();
  }

  for (int i = 0; i < blocks; i++) {
    granulator->processInternalBlock(chan1, chan2, kInternalBlocksize);
    chan1 += kInternalBlocksize;
    chan2 += kInternalBlocksize;
    parameters->time_quantizer->incrementPositionInfo();
  }

  int intrablock_samples_remaining = sampleframes % kInternalBlocksize;
  if (intrablock_samples_remaining)
    granulator->processInternalBlock(chan1, chan2, intrablock_samples_remaining);
}

int Plugin::getNumParameters()
{
  return static_cast<int>(NUMPARAMS);
}

float Plugin::getParameter (int index)
{
  if (index == kProgram) {
    return static_cast<float>(current_program / (kNumPrograms - 1));
  } else {
    return parameters->param[index];
  }
}

const String Plugin::getParameterName (int index)
{
  return parameters->getParameterName(index);
}

const String Plugin::getParameterText (int index)
{
  if (index == kProgram) {
    return String(current_program + 1);
  }
  else return parameters->getParameterText(index);
}

std::vector<String> Plugin::getScaleNames()
{
  return granulator->grain_param_generator->pitch_quantizer->getNames();
}

void Plugin::setParameter(int index, float new_value)
{
  if (index == kProgram) {
    int selected_program = static_cast<int>(new_value * (kNumPrograms - 1));
    if (current_program != selected_program) {
      setCurrentProgram(selected_program);
    }
    return;
  }
  parameters->setParameter(index, new_value, false);
  sendChangeMessage();
}

const String Plugin::getProgramName(int index)
{
  return program_bank->getProgramName(index);
}

void Plugin::changeProgramName(int index, const String& newName)
{
  program_bank->setProgramName(index, newName);
  sendChangeMessage();
}

int Plugin::getCurrentProgram()
{
  return current_program;
}

bool Plugin::getEditorSavedState()
{
  return saved_state;
}

void Plugin::setSavedState(bool state)
{
  if (saved_state != state) {
    saved_state = state;
    sendChangeMessage();
  }
}

int Plugin::getNumPrograms()
{
  return kNumPrograms;
}

void Plugin::getCurrentProgramStateInformation(MemoryBlock& destData)
{
  //save current settings
  program_bank->saveParametersToProgram(current_program);
  saveProgramTo(current_program);
  setSavedState(true);

  //output program to host
  XmlElement* program = program_bank->getProgram(current_program);
  copyXmlToBinary (*program, destData);
  delete program;
}

void Plugin::initCurrentProgram()
{
  program_bank->initProgram(current_program);
  program_bank->loadParametersFromProgram(current_program);
  setSavedState(true);
}

void Plugin::saveProgramTo(int index)
{
  String current_program_name = program_bank->getProgramName(current_program);
  program_bank->saveParametersToProgram(index);
  program_bank->setProgramName(index, current_program_name);
  current_program = index;
  setSavedState(true);
}

void Plugin::setCurrentProgram(int index)
{
  program_bank->loadParametersFromProgram(index);
  current_program = index;
  setSavedState(true);
  sendChangeMessage();
}

void Plugin::setCurrentProgramStateInformation(const void* data, int sizeInBytes)
{
  //load program from host
  XmlElement* const xml_state = getXmlFromBinary(data, sizeInBytes);
  if (xml_state != 0) {
    program_bank->setProgram(current_program, xml_state);
    setCurrentProgram(current_program);
    delete xml_state;
  }
}

void Plugin::getStateInformation (MemoryBlock& destData)
{
  // save current program
  program_bank->saveParametersToProgram(current_program);
  setSavedState(true);
  // output program_bank to host
  XmlElement* bank = program_bank->getBank();
  copyXmlToBinary(*bank, destData);
  delete bank;
}

void Plugin::setStateInformation (const void* data, int sizeInBytes)
{
  //load bank from host
  XmlElement* const xml_state = getXmlFromBinary(data, sizeInBytes);
  if (xml_state != 0) {
    program_bank->setBank(xml_state);
    setCurrentProgram(current_program);
    delete xml_state;
  }
}

