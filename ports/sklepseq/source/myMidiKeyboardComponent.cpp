// myMidiKeyboardComponent.cpp: implementation of the myMidiKeyboardComponent class.
//
//////////////////////////////////////////////////////////////////////

#include "myMidiKeyboardComponent.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

myMidiKeyboardComponent::myMidiKeyboardComponent(MidiKeyboardState &_state, const Orientation _orientation, myMidiMessage *msg) : MidiKeyboardComponent (_state, _orientation)
{
	midiMessage = msg;

	if (midiMessage)
	{
		if (!midiMessage->isMulti())
		{
			noteNumber = midiMessage->getMidiMessage()->getNoteNumber();
		}
	}
}

myMidiKeyboardComponent::~myMidiKeyboardComponent()
{
}

void myMidiKeyboardComponent::drawBlackNote (int midiNoteNumber, Graphics &g, int x, int y, int w, int h, bool isDown, bool isOver, const Colour &noteFillColour)
{
	noteNumber = midiMessage->getMidiMessage()->getNoteNumber();

	if (noteNumber == midiNoteNumber)
	{
		MidiKeyboardComponent::drawBlackNote (midiNoteNumber, g, x, y, w, h, isDown, isOver, Colours::blue);
	}
	else
	{
		MidiKeyboardComponent::drawBlackNote (midiNoteNumber, g, x, y, w, h, isDown, isOver, noteFillColour);
	}
}

void myMidiKeyboardComponent::drawWhiteNote (int midiNoteNumber, Graphics &g, int x, int y, int w, int h, bool isDown, bool isOver, const Colour &lineColour, const Colour &textColour)
{
	noteNumber = midiMessage->getMidiMessage()->getNoteNumber();

	if (noteNumber == midiNoteNumber)
	{
		MidiKeyboardComponent::drawBlackNote (midiNoteNumber, g, x, y, w, h, isDown, isOver, Colours::blue);
	}
	else
	{
		MidiKeyboardComponent::drawWhiteNote (midiNoteNumber, g, x, y, w, h, isDown, isOver, lineColour, textColour);
	}
}

bool myMidiKeyboardComponent::mouseDownOnKey (int midiNoteNumber, const MouseEvent &e)
{
	repaint();
	return (MidiKeyboardComponent::mouseDownOnKey (midiNoteNumber, e));
}