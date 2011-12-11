/*
 *  MyThread.h
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

#include "includes.h"
#include "MidiDevice.h"

class MyThread : public Thread
{
public:
	MyThread();
	~MyThread();
	void run();
	
	void setLfoRate(double rate) {m_lfoRate = rate;};
	void setLfoDepth(double depth) {m_lfoDepth = depth;};
	void setCenterVal(int value) {m_centerVal = value;};
	void setLfoWaveform(int waveform);
	
	void setOutChannel(int outchannel) {m_outChannel = outchannel;};
	void setOutCC(int outcc) {m_outCC = outcc;};
	
	void setSyncSource(int source) {m_syncSource = source;};
	void setSyncRate(double syncRate) {m_syncRate = syncRate;};
	void setSyncDivider(int divider) {m_syncDivider = divider;};
	
	void setMidiDevice(MidiDevice* device) {m_midiDevice = device;};
	
	void resetIndex();
	
private:
	enum {waveTableSize = 100000};
	int m_index;
	float m_Sine [waveTableSize];
	float m_Saw [waveTableSize];
	float m_Triangle [waveTableSize];
	float m_Square [waveTableSize];
	float *waveTablePointer;
	
	bool m_active;
	int m_msgPerSec;
	
	double m_lfoRate;
	double m_lfoDepth;
	int m_centerVal;
	int m_lfoWaveform;
	
	int m_outChannel;
	int m_outCC;
	
	int m_syncSource;	//0=internal, 1=external
	double m_syncRate;
	int m_syncDivider;
	
	double m_timeDif;
	double m_lastTime;
	
	
	MidiDevice* m_midiDevice;
};
