#ifndef PIZ_IMAGESLIDER
#define PIZ_IMAGESLIDER

#include "log.h"
#include "juce_amalgamated.h"


//==============================================================================
/**
     An image based slider.
*/
class ImageSlider : public Slider
{
public:

    //==============================================================================
    enum SliderOrientation
    {
        LinearHorizontal = 0,
        LinearVertical   = 1
    };

    //==============================================================================
    /** Constructor */
    ImageSlider (const String& sliderName);

    /** Destructor */
    ~ImageSlider();

    //==============================================================================
    void setOrientation (const SliderOrientation orientation);

    //==============================================================================
    void setThumbImage (Image* newImage);
    void setThumbImage (File const& newImageFile);
    void setThumbOffsetInImage (const int newMinOffset, const int newMaxOffset);

    void setBackgroundImage (File const& newImageFile);

	void setImages(Image* newThumb, Drawable* newBackground);

	//==============================================================================
    /** @internal */
    void paint (Graphics& g);

private:
    int minOffset, maxOffset;
    Image* thumbImage;
	Drawable* bgImage;
	bool sharedImages;
};


#endif

