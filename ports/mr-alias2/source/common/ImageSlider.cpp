#include "ImageSlider.h"

//==============================================================================
ImageSlider::ImageSlider (const String& sliderName)
  : Slider (sliderName),
    minOffset (0),
    maxOffset (0),
    thumbImage (0),
	bgImage(0),
	sharedImages(true)
{
	//this->setPopupDisplayEnabled(true,0);
    setOrientation (ImageSlider::LinearVertical);
}

ImageSlider::~ImageSlider()
{
	if (!sharedImages) {
		if (thumbImage) deleteAndZero(thumbImage);
		if (bgImage) deleteAndZero(bgImage);
	}
}

//==============================================================================
void ImageSlider::setOrientation (const SliderOrientation orientation)
{
    if (orientation == ImageSlider::LinearHorizontal)
    {
        setSliderStyle (Slider::LinearHorizontal);
    }
    else if (orientation == ImageSlider::LinearVertical)
    {
        setSliderStyle (Slider::LinearVertical);
    }
}

//==============================================================================
void ImageSlider::setThumbImage (Image* newImage)
{
	sharedImages = true;
    thumbImage = newImage;
}

void ImageSlider::setImages (Image* newThumb, Drawable* newBackground)
{
	sharedImages = true;
    thumbImage = newThumb;
    bgImage = newBackground;
}

void ImageSlider::setThumbImage (File const& newImageFile)
{
	sharedImages = false;
	thumbImage = ImageFileFormat::loadFrom(newImageFile);
}

void ImageSlider::setBackgroundImage (File const& newImageFile)
{
	sharedImages = false;
	bgImage = Drawable::createFromImageFile(newImageFile);
}

void ImageSlider::setThumbOffsetInImage (const int newMinOffset, const int newMaxOffset)
{
    minOffset = newMinOffset;
    maxOffset = newMaxOffset;
}

//==============================================================================
void ImageSlider::paint (Graphics& g)
{
	if (thumbImage==0) {
		Slider::paint(g);
	}
	else {
		float x = 0, y = 0;
		float w = (float)thumbImage->getWidth();
		float h = (float)thumbImage->getHeight();
		const bool sliderEnabled = isEnabled();
		const bool hightlight = isMouseOverOrDragging();
		g.fillAll(this->findColour(Slider::backgroundColourId));
		if (getSliderStyle() == Slider::LinearVertical)
		{
			w = getWidth()*0.6f;
			h = thumbImage->getHeight() * w/(float)thumbImage->getWidth();
			x = (getWidth() - w) / 2;
			y = (getHeight() - h) * (1.0f - (float)valueToProportionOfLength (getValue()));

			if(bgImage==0) {
				// draw background line
				//g.setColour (Colours::darkgrey.withAlpha (sliderEnabled ? 0.3f : 0.1f));
				//g.fillRect (getWidth()/2, (int)(h/2), getWidth()/2-1, getHeight()-(int)(h));
				g.setColour (Colours::black.withAlpha (sliderEnabled ? 0.2f : 0.1f));
				g.drawRect (getWidth()/2, (int)(h/2), (int)(w*0.5f), getHeight()-(int)(h), 1);
				g.setColour (Colours::black.withAlpha (0.1f));
				g.drawHorizontalLine (getHeight()/2, getWidth()*0.5f, getWidth()*0.5f+w*0.5f);

				g.setColour (Colours::black.withAlpha (sliderEnabled ? 0.5f : 0.3f));
				g.drawVerticalLine (getWidth()/2, h/4.f, getHeight()-h/4.f);
			}
			else {
				bgImage->drawWithin(g,Rectangle<float>(0,0,getWidth(),getHeight()),RectanglePlacement::stretchToFit, 0);
			}
		}
		else if (getSliderStyle() == Slider::LinearHorizontal)
		{
			h = getHeight()*0.9f;
			w = thumbImage->getWidth() * h/(float)thumbImage->getHeight();
			x = (getWidth() - w) * (float)valueToProportionOfLength (getValue());
			y = (getHeight() - h) / 2;

			if (bgImage==0) {
				// draw background line
				//g.setColour (Colours::darkgrey.withAlpha (sliderEnabled ? 0.3f : 0.1f));
				//g.fillRect ((int)(w/2), getHeight()/2, getWidth()-(int)(w), getHeight()/2-1);
				g.setColour (Colours::black.withAlpha (sliderEnabled ? 0.2f : 0.1f));
				g.drawRect ((int)(w/2), getHeight()/2, getWidth()-(int)(w), (int)(h*0.5f), 1);
				g.setColour (Colours::black.withAlpha (0.1f));
				g.drawVerticalLine (getWidth()/2, getHeight()*0.5f, getHeight()*0.5f+h*0.5f);

				g.setColour (Colours::black.withAlpha (sliderEnabled ? 0.5f : 0.3f));
				g.drawHorizontalLine (getHeight()/2, w/4.f, getWidth()-w/4.f);
			}
			else {
				bgImage->drawWithin(g,Rectangle<float>(0,0,getWidth(),getHeight()),RectanglePlacement::stretchToFit, 0);
			}
		}

        if (! sliderEnabled)
            g.setOpacity (0.6f);
        else
            g.setOpacity (1.0f);

        // draw thumb image
        g.drawImage (thumbImage,
                        (int)x, (int)y, (int)w, (int)h,
						0, 0, thumbImage->getWidth(), thumbImage->getHeight());

        if (sliderEnabled && hightlight)
        {
            // g.setColour (Colours::yellow.withAlpha (0.25f));
            // g.fillRect ((int) x, (int) y, thumbImage->getWidth(), thumbImage->getHeight());
        }
    }
}
