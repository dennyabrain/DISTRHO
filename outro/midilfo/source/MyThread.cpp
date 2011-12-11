/*
 *  MyThread.cpp
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

#include <iostream>
#include "MyThread.h"
#include <time.h>

#define PI 3.14159265


MyThread::MyThread()
:Thread(T("Sequencer"))
,m_index(0)
,m_lfoRate(0.1)
,m_lfoDepth(1)
,m_lfoWaveform(1)
,m_msgPerSec(100)
,m_outChannel(1)
,m_outCC(0)
,m_centerVal(63)
,m_syncSource(0) //start with internal sync
,m_syncRate(0.1)
,m_syncDivider(1)
,m_lastTime(0)
,m_timeDif(0)
{
	// sine waveTable
	for (int i=0; i<waveTableSize; i++)
	{ 
		double radians = (double)i * (double)2.0 * (double)PI / (double)waveTableSize; 
		m_Sine [i] = (sin (radians) + 1.0) * 0.5;  // sinus range (0 - 1)
	}
	
	// square waveTable
	for (int i=0; i<waveTableSize; i++)
	{
		if (i <= waveTableSize/2)
			m_Square [i] = 0;
		if (i > waveTableSize/2)
			m_Square [i] = 1;
	}
	
	// saw waveTable
	for (int i=0; i<waveTableSize; i++)
	{
		m_Saw [i] = (double)i / (double)waveTableSize;// - floor((double)i / (double)waveTableSize);
	}
	
	// triangle waveTable
	for (int i=0; i<waveTableSize; i++)
	{	
		if (i <= waveTableSize/2)
			m_Triangle [i] = ((double)i / (double)(waveTableSize)) * 2;
		if (i > waveTableSize/2)
			m_Triangle [i] = (1 - ((double)i / (double)(waveTableSize))) * 2 ;
	}
	
	// init with sinewave
	waveTablePointer = &m_Sine [0];
}
MyThread::~MyThread()
{
}
void MyThread::setLfoWaveform(int waveform)
{
	m_lfoWaveform = waveform;
	
	if (m_lfoWaveform == 0)
		waveTablePointer = &m_Sine[0];
	else 
		if (m_lfoWaveform == 1)
			waveTablePointer = &m_Square[0];
		else
			if (m_lfoWaveform == 2)
				waveTablePointer = &m_Saw[0];
			else
				if (m_lfoWaveform == 3)
					waveTablePointer = &m_Triangle[0];
}

void MyThread::run()
{
	
/*
 * ok, the idea behind this is to have the LFO waveform stored in a wavetable array.
 * we measure the time in between thread loop cycles, and that, 
 * together with the LFO rate and wavetable size determines how far we have to 
 * step ahead in the wavetable array to find the next gain value.
 * this value is scaled according to the gain and centerVal params and to fit the midi
 * range, and then sent over midi.
 * 
 * notice that the loop below is still a bit twisted around.
 * the order of the steps is better understood like commented here.
 *
 */
	
	m_index=0;
	int lastIndex=0;
	int stepsize=1;
	
	double rawLfoGain=0;
	double lfoGain=0;
	
	// thread needs to check this
	while(!threadShouldExit())
	{
		// read waveform amplitude
		rawLfoGain = waveTablePointer [m_index];
		
		lfoGain = rawLfoGain * m_lfoDepth;
		
		lastIndex = m_index;
		
		// recalc value range from (0 - 1) to (0 - 127)
		lfoGain = lfoGain * 128.0f;
		
		// recalc output value to oscillate around center value
		lfoGain = lfoGain - (m_lfoDepth * 63.0f);		//oscillate around center of MIDI values
		lfoGain += m_centerVal;		//make that center our center
		
		// set MIDI boundaries for output value
		if (lfoGain < 0) 
		{
			lfoGain = 0;
		}
		if (lfoGain > 127) 
		{
			lfoGain = 127;
		}
		
		
		m_midiDevice->sendMidiMessage(MidiMessage::controllerEvent(m_outChannel,m_outCC,lfoGain));		
		
		//calculate stepsize dependent on syncsource and on looptime
		m_timeDif = Time::getMillisecondCounterHiRes() - m_lastTime;
		
		if (m_syncSource == 0)	//internal
		{
			stepsize = (int)(((double)waveTableSize * (double)m_lfoRate) * (double)m_timeDif/1000.0f);
		}
		else if (m_syncSource == 1)	//external
		{
			stepsize = (int)(((double)waveTableSize * (double)m_syncRate / (double)m_syncDivider)  * (double)m_timeDif/1000.0f);
		}
		
		m_lastTime = Time::getMillisecondCounterHiRes();

		// calculate index to read waveform amplitude
		m_index = (lastIndex + stepsize) % waveTableSize;
		
		
		//pause thread
		double sleepTime = (1000.0f/(double)m_msgPerSec);
		sleep(sleepTime);
		
	}
}

void MyThread::resetIndex()
{
	m_index = 0;
}
