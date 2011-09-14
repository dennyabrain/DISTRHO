#ifndef __JUCER_HEADER_SKLEPSEQPLAYLIST_SKLEPSEQPLAYLIST_C0CEEDD__
#define __JUCER_HEADER_SKLEPSEQPLAYLIST_SKLEPSEQPLAYLIST_C0CEEDD__

#include <juce.h>
#include "sklepSeqPlaylistView.h"

class sklepSeqTransportComponent;

class sklepSeqPlaylist  : public DocumentWindow
{
	public:
		sklepSeqPlaylist (sklepSeqTransportComponent *_p);
		~sklepSeqPlaylist();
		void closeButtonPressed();
		juce_UseDebuggingNewOperator

	private:
		sklepSeqPlaylistView* playlistView;
		sklepSeqTransportComponent *parent;
		sklepSeqPlaylist (const sklepSeqPlaylist&);
		const sklepSeqPlaylist& operator= (const sklepSeqPlaylist&);
};


#endif 
