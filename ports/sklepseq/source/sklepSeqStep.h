// sklepSeqStep.h: interface for the sklepSeqStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKLEPSEQSTEP_H__A7AE8B73_28EE_43D5_989D_AF567303C440__INCLUDED_)
#define AFX_SKLEPSEQSTEP_H__A7AE8B73_28EE_43D5_989D_AF567303C440__INCLUDED_

#include <juce.h>

class sklepSeqMainComponent;

class sklepSeqStep : public ImageButton, public MidiKeyboardState
{
	public:
		sklepSeqStep(int _index, int x, int y);
		~sklepSeqStep();
		int getX();
		int getY();
		void clicked (const ModifierKeys &modifiers);
		int getIndex();
		bool getPopup();
		bool getQuickPopup();
		void setOff();
		void setOn();

	private:
		int posX, posY;
		Image *image;
		Image *imageOver;
		Image *imageOn;
		int midiChannel;
		int index;
		bool popup;
		bool quickPop;
		const char* ion[16];
		int ions[16];
		const char* iover[16];
		int iovers[16];
		const char* ioff[16];
		int ioffs[16];
	static const char* sq_step_on_1_png;
    static const int sq_step_on_1_pngSize;
    static const char* sq_step_on_2_png;
    static const int sq_step_on_2_pngSize;
    static const char* sq_step_on_3_png;
    static const int sq_step_on_3_pngSize;
    static const char* sq_step_on_4_png;
    static const int sq_step_on_4_pngSize;
    static const char* sq_step_on_5_png;
    static const int sq_step_on_5_pngSize;
    static const char* sq_step_on_6_png;
    static const int sq_step_on_6_pngSize;
    static const char* sq_step_on_7_png;
    static const int sq_step_on_7_pngSize;
    static const char* sq_step_on_8_png;
    static const int sq_step_on_8_pngSize;
    static const char* sq_step_on_9_png;
    static const int sq_step_on_9_pngSize;
    static const char* sq_step_on_10_png;
    static const int sq_step_on_10_pngSize;
    static const char* sq_step_on_11_png;
    static const int sq_step_on_11_pngSize;
    static const char* sq_step_on_12_png;
    static const int sq_step_on_12_pngSize;
    static const char* sq_step_on_13_png;
    static const int sq_step_on_13_pngSize;
    static const char* sq_step_on_14_png;
    static const int sq_step_on_14_pngSize;
    static const char* sq_step_on_15_png;
    static const int sq_step_on_15_pngSize;
    static const char* sq_step_on_16_png;
    static const int sq_step_on_16_pngSize;

	static const char* sq_step_off_1_png;
    static const int sq_step_off_1_pngSize;
    static const char* sq_step_off_2_png;
    static const int sq_step_off_2_pngSize;
    static const char* sq_step_off_3_png;
    static const int sq_step_off_3_pngSize;
    static const char* sq_step_off_4_png;
    static const int sq_step_off_4_pngSize;
    static const char* sq_step_off_5_png;
    static const int sq_step_off_5_pngSize;
    static const char* sq_step_off_6_png;
    static const int sq_step_off_6_pngSize;
    static const char* sq_step_off_7_png;
    static const int sq_step_off_7_pngSize;
    static const char* sq_step_off_8_png;
    static const int sq_step_off_8_pngSize;
    static const char* sq_step_off_9_png;
    static const int sq_step_off_9_pngSize;
    static const char* sq_step_off_10_png;
    static const int sq_step_off_10_pngSize;
    static const char* sq_step_off_11_png;
    static const int sq_step_off_11_pngSize;
    static const char* sq_step_off_12_png;
    static const int sq_step_off_12_pngSize;
    static const char* sq_step_off_13_png;
    static const int sq_step_off_13_pngSize;
    static const char* sq_step_off_14_png;
    static const int sq_step_off_14_pngSize;
    static const char* sq_step_off_15_png;
    static const int sq_step_off_15_pngSize;
    static const char* sq_step_off_16_png;
    static const int sq_step_off_16_pngSize;

	static const char* sq_step_over_1_png;
    static const int sq_step_over_1_pngSize;
    static const char* sq_step_over_2_png;
    static const int sq_step_over_2_pngSize;
    static const char* sq_step_over_3_png;
    static const int sq_step_over_3_pngSize;
    static const char* sq_step_over_4_png;
    static const int sq_step_over_4_pngSize;
    static const char* sq_step_over_5_png;
    static const int sq_step_over_5_pngSize;
    static const char* sq_step_over_6_png;
    static const int sq_step_over_6_pngSize;
    static const char* sq_step_over_7_png;
    static const int sq_step_over_7_pngSize;
    static const char* sq_step_over_8_png;
    static const int sq_step_over_8_pngSize;
    static const char* sq_step_over_9_png;
    static const int sq_step_over_9_pngSize;
    static const char* sq_step_over_10_png;
    static const int sq_step_over_10_pngSize;
    static const char* sq_step_over_11_png;
    static const int sq_step_over_11_pngSize;
    static const char* sq_step_over_12_png;
    static const int sq_step_over_12_pngSize;
    static const char* sq_step_over_13_png;
    static const int sq_step_over_13_pngSize;
    static const char* sq_step_over_14_png;
    static const int sq_step_over_14_pngSize;
    static const char* sq_step_over_15_png;
    static const int sq_step_over_15_pngSize;
    static const char* sq_step_over_16_png;
    static const int sq_step_over_16_pngSize;
};

#endif // !defined(AFX_SKLEPSEQSTEP_H__A7AE8B73_28EE_43D5_989D_AF567303C440__INCLUDED_)
