/*
 *  MyMidiInputCallback.h
 *  MidiLFO
 *
 *  Midi-Lfo: This is a small project using the JUCE library.
 *	It provides a user tweakable Midi LFO. This sends a
 *	(selectable) CC with LFO modulated values to a
 *	(selectable) Midi output.
 *
 *	Copyright (C) 2009, Christian Stoecklmeier and Volker Duemke
 * 
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful, but
 *	WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *	See the GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MY_MIDI_INPUT_CALLBACK_H
#define MY_MIDI_INPUT_CALLBACK_H

#include "includes.h"

class ProcessingCore;

class MyMidiInputCallback : public MidiInputCallback
{
public:
	
	MyMidiInputCallback();
	~MyMidiInputCallback();
	
  void handleIncomingMidiMessage (MidiInput *source, 
                                  const MidiMessage &message);

  void handlePartialSysexMessage (MidiInput *source, 
                                  const juce::uint8 *messageData, 
                                  const int numBytesSoFar, 
                                  const double timestamp);
	
	void setProcessingCore(ProcessingCore* core);
		

private:
	ProcessingCore* myProcessingCore;
	
	uint32 m_oldTime;
	uint32 m_time;
	uint32 m_totalTime;
	
	int m_tickCounter;
	bool m_firstrun;
};




#endif //MY_MIDI_INPUT_CALLBACK_H