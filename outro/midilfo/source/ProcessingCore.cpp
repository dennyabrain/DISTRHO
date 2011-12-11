/*
 *  ProcessingCore.cpp
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

#include "ProcessingCore.h"

ProcessingCore::ProcessingCore()
{	
}

ProcessingCore::~ProcessingCore()
{
	stop();

// don´t delete this, or the other modules will complain deleting it!
//	if (m_midiDevice != 0)
//		deleteAndZero(m_midiDevice);
}

void ProcessingCore::start()
{
	myThread.setMidiDevice(m_midiDevice);
	myThread.startThread(10);
}

void ProcessingCore::stop()
{
	myThread.stopThread(20);
}