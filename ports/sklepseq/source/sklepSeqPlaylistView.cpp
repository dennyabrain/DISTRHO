// sklepSeqPlaylistView.cpp: implementation of the sklepSeqPlaylistView class.
//
//////////////////////////////////////////////////////////////////////

#include "sklepSeqPlaylistView.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sklepSeqPlaylistView::sklepSeqPlaylistView()
{
	addAndMakeVisible (resizer = new ResizableCornerComponent (this, &resizeLimits));
    resizeLimits.setSizeLimits (150, 150, 800, 800);

	addAndMakeVisible (playlist = new Viewport (String::empty));
    playlist->setViewedComponent (new sklepSeqPlaylistComponent());
}

sklepSeqPlaylistView::~sklepSeqPlaylistView()
{
	deleteAndZero (playlist);
	deleteAndZero (resizer);
}

void sklepSeqPlaylistView::resized()
{
	resizer->setBounds (getWidth() - 16, getHeight() - 16, 16, 16);
	playlist->setBounds (0,0,getWidth()-16,getHeight()-16);
}