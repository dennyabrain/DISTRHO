// sklepSeqCursorComponent.h: interface for the sklepSeqCursorComponent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKLEPSEQCURSORCOMPONENT_H__3F42890E_F4E2_4B05_B2CC_A98DE6F0484D__INCLUDED_)
#define AFX_SKLEPSEQCURSORCOMPONENT_H__3F42890E_F4E2_4B05_B2CC_A98DE6F0484D__INCLUDED_

#include <juce.h>

class sklepSeqCursorComponent : public Component  
{
	public:
		sklepSeqCursorComponent(Image i, int x, int y);
		~sklepSeqCursorComponent();
		void paint(Graphics &g);
		int getX();
		int getY();
		
	private:
		int posX, posY;
		Image image;
};

#endif // !defined(AFX_SKLEPSEQCURSORCOMPONENT_H__3F42890E_F4E2_4B05_B2CC_A98DE6F0484D__INCLUDED_)
