#ifndef PIZAUDIOPROCESSOR_H
#define PIZAUDIOPROCESSOR_H

#ifdef _MSC_VER
 #pragma warning (disable : 4100)
#endif

#include "JuceHeader.h"

class PizAudioProcessor : public AudioProcessor
{
public:
	PizAudioProcessor() : 
		AudioProcessor(), 
		bottomOctave(-2),
		currentPath(((File::getSpecialLocation(File::currentApplicationFile)).getParentDirectory()).getFullPathName())
	{
	}

	int getBottomOctave() {
		return bottomOctave;
	}

	bool loadDefaultFxb() 
	{
		//look for a default bank
		String defaultBank  = currentPath + File::separatorString 
			+ File::getSpecialLocation(File::currentExecutableFile).getFileNameWithoutExtension() + ".fxb";
		if (File(defaultBank).exists()) {
			juce::MemoryBlock bank = juce::MemoryBlock(0,true);
			File(defaultBank).loadFileAsData(bank);
			bank.removeSection(0,0xA0);
			setStateInformation(bank.getData(), (int)bank.getSize());
			return true;
		}
		return false;
	}

	bool loadFxbFile(File file) 
	{
		if (file.existsAsFile()) {
			juce::MemoryBlock bank = juce::MemoryBlock(0,true);
			file.loadFileAsData(bank);
			bank.removeSection(0,0xA0);
			setStateInformation(bank.getData(), (int)bank.getSize());
			return true;
		}
		return false;
	}

	bool loadDefaultFxp() 
	{
		//look for a default patch
		String defaultBank = currentPath + File::separatorString 
			+ File::getSpecialLocation(File::currentApplicationFile).getFileNameWithoutExtension() + ".fxp";
		if (File(defaultBank).exists()) {
			juce::MemoryBlock bank = juce::MemoryBlock(0,true);
			File(defaultBank).loadFileAsData(bank);
			bank.removeSection(0,0x3C);
			setCurrentProgramStateInformation(bank.getData(), (int)bank.getSize());
			return true;
		}
		return false;
	}

	bool loadFxpFile(File file)
	{
		if (file.existsAsFile()) {
			juce::MemoryBlock bank = juce::MemoryBlock(0,true);
			file.loadFileAsData(bank);
			bank.removeSection(0,0x3C);
			setCurrentProgramStateInformation(bank.getData(), (int)bank.getSize());
			return true;
		}
		return false;
	}

	int bottomOctave;
	String getCurrentPath() {return currentPath;}

private:
	String currentPath;
};

#endif