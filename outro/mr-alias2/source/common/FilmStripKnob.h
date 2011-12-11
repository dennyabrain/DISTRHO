#ifndef PIZ_FILMSTRIPKNOB_H
#define PIZ_FILMSTRIPKNOB_H

#include "log.h"
#include "juce_amalgamated.h"

class FilmStripKnob : public Slider
{
public:
	FilmStripKnob(String const& name)
		:   Slider(name),
		filmStrip(0),
		numFrames_(4),
		isHorizontal_(true),
		frameWidth(0),
		frameHeight(0),
		sharedImage(false),
		lowquality(false)
	{};

	FilmStripKnob(String const& name, File const& image, const int numFrames, const bool stripIsHorizontal)
		:   Slider(name),
		filmStrip(image.exists() ? ImageFileFormat::loadFrom(image) : 0),
		numFrames_(numFrames),
		isHorizontal_(stripIsHorizontal),
		lowquality(false)
	{
		if(filmStrip)
		{
			if(isHorizontal_) {
				frameHeight = filmStrip->getHeight();
				frameWidth = filmStrip->getWidth() / numFrames_;
			} else {
				frameHeight = filmStrip->getHeight() / numFrames_;
				frameWidth = filmStrip->getWidth();
			}
		}
#if MAKE_LOG
		else logDebugString("failed to load " + image.getFullPathName());
#endif
	}

	FilmStripKnob(String const& name, File const& squareImage)
		: Slider(name),
		filmStrip(ImageFileFormat::loadFrom(squareImage)),
		numFrames_(100),
		isHorizontal_(true),
		frameWidth(0),
		frameHeight(0),
		sharedImage(false)
	{
		if(filmStrip)
		{
			//assume square frame
			isHorizontal_ = filmStrip->getWidth() > filmStrip->getHeight();
			if(isHorizontal_) {
				numFrames_ = filmStrip->getWidth()/filmStrip->getHeight();
				frameHeight = frameWidth = filmStrip->getHeight();
			} 
			else {
				numFrames_ = filmStrip->getHeight()/filmStrip->getWidth();
				frameHeight = frameWidth = filmStrip->getWidth();
			}
		}
#if MAKE_LOG
		else logDebugString("failed to load " + name);
#endif
	}

	~FilmStripKnob() { 
		if(!sharedImage) 
			deleteAndZero(filmStrip); 
	}

	void paint(Graphics& g)
	{
		if(filmStrip) {
			if (lowquality) g.setImageResamplingQuality(Graphics::lowResamplingQuality);
			g.fillAll(this->findColour(Slider::backgroundColourId));
			int value = int((getValue() - getMinimum()) / (getMaximum() - getMinimum()) * double(numFrames_ - 1));
			if(isHorizontal_) {
				g.drawImage(filmStrip, (getWidth()<=getHeight()) ? 0 : (getWidth()-getHeight())/2, 
					(getWidth()>=getHeight()) ? 0 : (getHeight()-getWidth())/2, 
					jmin(getWidth(),getHeight()), jmin(getWidth(),getHeight()),
					value * frameWidth, 0, frameWidth, frameHeight);
			} 
			else {
				g.drawImage(filmStrip, (getWidth()<=getHeight()) ? 0 : (getWidth()-getHeight())/2, 
					(getWidth()>=getHeight()) ? 0 : (getHeight()-getWidth())/2, 
					jmin(getWidth(),getHeight()), jmin(getWidth(),getHeight()),
					0, value * frameHeight, frameWidth, frameHeight);
			}
		}
		else {
			Slider::paint(g);
		}
	}

	void setImage(File const& image, const int numFrames, const bool stripIsHorizontal) 
	{
		filmStrip = ImageFileFormat::loadFrom(image);
		numFrames_ = numFrames;
		isHorizontal_ = stripIsHorizontal;
		sharedImage=false;

		if(filmStrip)
		{
			if(isHorizontal_) {
				frameHeight = filmStrip->getHeight();
				frameWidth = filmStrip->getWidth() / numFrames_;
			} 
			else {
				frameHeight = filmStrip->getHeight() / numFrames_;
				frameWidth = filmStrip->getWidth();
			}
		}
#if MAKE_LOG
		else logDebugString("failed to load " + image.getFullPathName());
#endif
	}

	void setImage(File const& image) 
	{
		filmStrip = ImageFileFormat::loadFrom(image);
		sharedImage=false;

		if(filmStrip)
		{
			//assume square frame
			isHorizontal_ = filmStrip->getWidth() > filmStrip->getHeight();
			if(isHorizontal_) {
				numFrames_ = filmStrip->getWidth()/filmStrip->getHeight();
				frameHeight = frameWidth = filmStrip->getHeight();
			} 
			else {
				numFrames_ = filmStrip->getHeight()/filmStrip->getWidth();
				frameHeight = frameWidth = filmStrip->getWidth();
			}
		}
#if MAKE_LOG
		else logDebugString("failed to load " + image.getFullPathName());
#endif
	}

	void setImage(Image* image) 
	{
		filmStrip = image;
		if(filmStrip)
		{
			sharedImage=true;
			//assume square frame
			isHorizontal_ = filmStrip->getWidth() > filmStrip->getHeight();
			if(isHorizontal_) {
				numFrames_ = filmStrip->getWidth()/filmStrip->getHeight();
				frameHeight = frameWidth = filmStrip->getHeight();
			} 
			else {
				numFrames_ = filmStrip->getHeight()/filmStrip->getWidth();
				frameHeight = frameWidth = filmStrip->getWidth();
			}
		}
#if MAKE_LOG
		else logDebugString("failed to load image");
#endif
	}

	int getFrameWidth() const  { return filmStrip ? frameWidth  : 100; }
	int getFrameHeight() const { return filmStrip ? frameHeight : 24;  }
	bool lowquality;

private:
	Image* filmStrip;
	int numFrames_;
	bool isHorizontal_;
	int frameWidth, frameHeight;
	bool sharedImage;
};

#endif
