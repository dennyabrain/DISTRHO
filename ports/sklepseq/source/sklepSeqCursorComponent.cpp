// sklepSeqCursorComponent.cpp: implementation of the sklepSeqCursorComponent class.
//
//////////////////////////////////////////////////////////////////////

#include "sklepSeqCursorComponent.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sklepSeqCursorComponent::sklepSeqCursorComponent(Image i, int x, int y)
{
	setBufferedToImage (true);
	posX		= x;
	posY		= y;
	image		= i;
}

sklepSeqCursorComponent::~sklepSeqCursorComponent()
{
}

void sklepSeqCursorComponent::paint(Graphics &g)
{
	g.drawImage (image, 0, 0, 48, 48, 0, 0, 48, 48);
}

int sklepSeqCursorComponent::getX()
{
	return (posX);
}

int sklepSeqCursorComponent::getY()
{
	return (posY);
}
