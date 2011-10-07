/*
 *  MyMidiInputCallback.cpp
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

#include <iostream>
#include <iomanip>
#include "MyMidiInputCallback.h"
#include "ProcessingCore.h"

MyMidiInputCallback::MyMidiInputCallback()
:m_oldTime(0)
,m_time(0)
,m_totalTime(0)
,m_tickCounter(0)
,myProcessingCore(0)
,m_firstrun(true)
{
}

MyMidiInputCallback::~MyMidiInputCallback()
{
}

void MyMidiInputCallback::handleIncomingMidiMessage (MidiInput *source,
													 const MidiMessage &message)
{
	//std::cout<<"Debug: Midi Input in Callback"<<std::endl;
	
	if (message.isSongPositionPointer())
	{
		m_time = 0;
		m_oldTime = 0;
		m_totalTime = 0;
		m_tickCounter = 0;
		//reset thread when sync starts
		myProcessingCore->stop();
		myProcessingCore->start();
		
		m_firstrun = true;
	}
	
	if (!message.isMidiClock())
		return;
	
	m_oldTime = m_time;
	m_time = Time::getMillisecondCounterHiRes();
		
	if (m_tickCounter < 24) 
	{
		uint32 cycleDuration = 0;
		
		if (m_firstrun)
			cycleDuration = 0;	//sic. want to make clear that cycleDuration is not touched on firstrun
		else
			cycleDuration = (m_time - m_oldTime);	//milliseconds per 96th note
		
		m_firstrun = false;

		m_totalTime += cycleDuration;
		
		m_tickCounter++;
	}
	else
	{
		
		double quarterNotesPerSecond = 1000.0f/(double)m_totalTime;
		
		//std::cout << "Debug: quarterNotesPerSecond " << quarterNotesPerSecond << std::endl;
		
		myProcessingCore->setParameterSyncRate(quarterNotesPerSecond);
		
		m_totalTime = 0;
		
		m_tickCounter = 0;
	}
	
}


void MyMidiInputCallback::handlePartialSysexMessage (MidiInput *source, const juce::uint8 *messageData, const int numBytesSoFar, const double timestamp)
{
}


void MyMidiInputCallback::setProcessingCore (ProcessingCore* core)
{
	myProcessingCore = core;
}
