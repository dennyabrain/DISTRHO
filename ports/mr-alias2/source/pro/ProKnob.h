#ifndef MRALIASPRO_KNOB_H
#define MRALIASPRO_KNOB_H

#include "common/FilmStripKnob.h"

class ProKnob : public FilmStripKnob
{
public:
	ProKnob(String name) : FilmStripKnob(name) {
		this->setMouseClickGrabsKeyboardFocus(false);
		this->setSliderSnapsToMousePosition(false);
	}
};

#endif
