#ifndef __MrAlias2ccmapslider__
#define __MrAlias2ccmapslider__

class CCMapSlider: public Slider {
public:
    CCMapSlider(const String &name);
    ~CCMapSlider();
	const String getTextFromValue (double value);
};

#endif

