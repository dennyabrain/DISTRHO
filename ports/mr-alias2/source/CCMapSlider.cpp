#include "juce.h"
#include "CCMapSlider.h"

CCMapSlider::CCMapSlider (const String& name)
  : Slider (name)
{
    setWantsKeyboardFocus (false);
    setRepaintsOnMouseActivity (true);

    lookAndFeelChanged();
    //updateText();
}

CCMapSlider::~CCMapSlider()
{
    deleteAllChildren();
}

const String CCMapSlider::getTextFromValue(double value) {
    if (value==-1) return "(Unset)";
    if (value==128) return "Velocity";
    if (value==129) return "Channel Pressure";
    if (value==130) return "Poly Aftertouch";
    return String(value);
}
