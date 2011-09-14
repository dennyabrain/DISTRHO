// myMidiKeyboardComponent.h: interface for the myMidiKeyboardComponent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYMIDIKEYBOARDCOMPONENT_H__21851312_52BC_4C0F_A29A_1E85DB787C3A__INCLUDED_)
#define AFX_MYMIDIKEYBOARDCOMPONENT_H__21851312_52BC_4C0F_A29A_1E85DB787C3A__INCLUDED_

#include <juce.h>
#include "myMidiMessage.h"

class myMidiKeyboardComponent : public MidiKeyboardComponent
{
	public:
		myMidiKeyboardComponent(MidiKeyboardState &_state, const Orientation _orientation, myMidiMessage *msg);
		~myMidiKeyboardComponent();
		void drawWhiteNote (int midiNoteNumber, Graphics &g, int x, int y, int w, int h, bool isDown, bool isOver, const Colour &lineColour, const Colour &textColour);
		void drawBlackNote (int midiNoteNumber, Graphics &g, int x, int y, int w, int h, bool isDown, bool isOver, const Colour &noteFillColour);
		bool mouseDownOnKey (int midiNoteNumber, const MouseEvent &e);

	private:
		myMidiMessage *midiMessage;
		int noteNumber;
};

#endif // !defined(AFX_MYMIDIKEYBOARDCOMPONENT_H__21851312_52BC_4C0F_A29A_1E85DB787C3A__INCLUDED_)
