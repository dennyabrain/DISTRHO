#include "sklepSeqPlaylist.h"
#include "sklepSeqPlaylistComponent.h"
#include "sklepSeqTransportComponent.h"

sklepSeqPlaylist::sklepSeqPlaylist (sklepSeqTransportComponent *_p) : DocumentWindow (T("Playlist"), Colours::white, DialogWindow::allButtons, true)
{
	parent = _p;
	setContentComponent (playlistView = new sklepSeqPlaylistView ());

	setResizable (true, true);
	centreWithSize (400, 400);
}

sklepSeqPlaylist::~sklepSeqPlaylist()
{
}

void sklepSeqPlaylist::closeButtonPressed()
{
	parent->closePlaylist();
	delete this;
}
