// sklepSeqPlaylistView.h: interface for the sklepSeqPlaylistView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKLEPSEQPLAYLISTVIEW_H__5C279655_CBE5_44B5_8DA0_70C196309B9F__INCLUDED_)
#define AFX_SKLEPSEQPLAYLISTVIEW_H__5C279655_CBE5_44B5_8DA0_70C196309B9F__INCLUDED_

#include <juce.h>
#include "sklepSeqPlaylistComponent.h"
class sklepSeqPlaylistView : public Component  
{
	public:
		sklepSeqPlaylistView();
		~sklepSeqPlaylistView();
		void resized();

	private:
		Viewport *playlist;
		ResizableCornerComponent* resizer;
		ComponentBoundsConstrainer resizeLimits;
};

#endif // !defined(AFX_SKLEPSEQPLAYLISTVIEW_H__5C279655_CBE5_44B5_8DA0_70C196309B9F__INCLUDED_)
