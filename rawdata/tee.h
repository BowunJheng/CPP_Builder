// ---------------------------------------------------------------------------

#ifndef teeH
#define teeH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VCLTee.TeeSurfa.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include "rrmain.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Mask.hpp>
#include "VCLTee.TeePageNumTool.hpp"
#include "VCLTee.TeeTools.hpp"
#include "VCLTee.TeeSeriesRegion.hpp"

// ---------------------------------------------------------------------------
class TForm2 : public TForm {
__published: // IDE-managed Components

	TButton *PreviousButton;
	TButton *NextButton;
	TEdit *TeePageEdit;
	TTrackBar *TrackBar1;
	TButton *PlayStopButton;
	TMaskEdit *TimeOutMaskEdit;
	TChart *Chart1;
	TSurfaceSeries *Series1;
	TRotateTool *ChartTool1;
	TGroupBox *GroupBox1;
	TCheckBox *LargeCheckBox;
	TCheckBox *LessCheckBox;
	TMaskEdit *LargeMaskEdit;
	TMaskEdit *LessMaskEdit;

	void __fastcall PreviousButtonClick(TObject *Sender);
	void __fastcall NextButtonClick(TObject *Sender);
	void __fastcall TeePageEditMouseDown(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall PlayStopButtonClick(TObject *Sender);
	void __fastcall Chart1MouseWheel(TObject *Sender, TShiftState Shift,
		int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall Chart1MouseMove(TObject *Sender, TShiftState Shift,
		int X, int Y);

private: // User declarations

	void __fastcall ShowGrahpic(int ShowPage);
	void __fastcall AxisSync(void);

	int PAGE, TrackBarMutex, TrackBarMutex2, StopFlag;

public: // User declarations

	__fastcall TForm2(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
// ---------------------------------------------------------------------------
#endif
