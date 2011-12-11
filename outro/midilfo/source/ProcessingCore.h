/*
 *  ProcessingCore.h
 *  midilfo
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

#include "MidiDevice.h"
#include "MyThread.h"

class ProcessingCore
{

public:
	ProcessingCore();
	~ProcessingCore();
	void start();
	void stop();
			
	void setParameterRate (double rate) {myThread.setLfoRate(rate);};
	void setParameterDepth (double depth) {myThread.setLfoDepth(depth);};
	void setParameterCenterVal (int value) {myThread.setCenterVal(value);};
	void setParameterWaveform (int waveform) {myThread.setLfoWaveform(waveform);};
	
	void setParameterOutChannel (int outChannel) {myThread.setOutChannel(outChannel);};
	void setParameterOutCC (int outCC) {myThread.setOutCC(outCC);};

	void setParameterSyncSource (int source) {myThread.setSyncSource(source);};
	void setParameterSyncRate (double syncRate) {myThread.setSyncRate(syncRate);};
	void setParameterSyncDivider (int divider) {myThread.setSyncDivider(divider);};
	void resetIndex(){myThread.resetIndex();};

	
	void setMidiDevice(MidiDevice* device) {m_midiDevice = device;};
	
private:
	
	// dont create thread as a pointer
	MyThread myThread;
	
	MidiDevice* m_midiDevice;
};
