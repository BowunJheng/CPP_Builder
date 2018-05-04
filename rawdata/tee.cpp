// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "tee.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCLTee.TeeSurfa"
#pragma link "VCLTee.TeePageNumTool"
#pragma link "VCLTee.TeeTools"
#pragma link "VCLTee.TeeSeriesRegion"
#pragma resource "*.dfm"
TForm2 *Form2;
const UnicodeString StartSign = ">";
const UnicodeString StopSign = "||";

// ---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner) : TForm(Owner) {
	TeePageEdit->PopupMenu = new TPopupMenu(NULL);
	PlayStopButton->Caption = StartSign;
	StopFlag = 0;
	PAGE = StrToInt(Form1->PageMaskEdit->EditText);
	TrackBar1->Max = Form1->ZX;
	ShowGrahpic(PAGE);

}

// ---------------------------------------------------------------------------
void __fastcall TForm2::ShowGrahpic(int ShowPage) {
	int Max = INT_MIN, Min = INT_MAX, LARGENUM, LESSNUM, StepDiff =
		(Form1->DATAMAX - Form1->DATAMIN) * .2;
	if (LargeCheckBox->Checked) {
		LARGENUM = StrToInt(LargeMaskEdit->EditText);
	}
	if (LessCheckBox->Checked) {
		LESSNUM = StrToInt(LessMaskEdit->EditText);
	}
	Series1->Clear();
	Chart1->LeftAxis->SetMinMax((Form1->DATAMIN > StepDiff) ?
		(Form1->DATAMIN - StepDiff) : 0, Form1->DATAMAX + StepDiff);
	for (int i = 0; i < Form1->TX; ++i) {
		for (int j = 0; j < Form1->RX; ++j) {
			if (Max < Form1->array3D[ShowPage][i][j]) {
				Max = Form1->array3D[ShowPage][i][j];
			}
			if (Min > Form1->array3D[ShowPage][i][j]) {
				Min = Form1->array3D[ShowPage][i][j];
			}
			Series1->AddXYZ(j, Form1->array3D[ShowPage][i][j], i);
		}
	}
	if (ShowPage == 0) {
		PreviousButton->Enabled = false;
	}
	else {
		PreviousButton->Enabled = true;
	}
	if (ShowPage == Form1->ZX) {
		NextButton->Enabled = false;
	}
	else {
		NextButton->Enabled = true;
	}
	TeePageEdit->Text = IntToStr(ShowPage) + "/" + IntToStr(Form1->ZX);
	TrackBarMutex = 0;
	if (TrackBarMutex2 == 1) {
		TrackBar1->Position = ShowPage;
	}
	TrackBarMutex2 = (TrackBarMutex2) ? 0 : 1;
	AxisSync();
	if (LargeCheckBox->Checked && LessCheckBox->Checked) {
		if (Max > LARGENUM && Min < LESSNUM) {
			StopFlag = 1;
		}
	}
	else if (LargeCheckBox->Checked) {
		if (Max > LARGENUM) {
			StopFlag = 1;
		}
	}
	else if (LessCheckBox->Checked) {
		if (Min < LESSNUM) {
			StopFlag = 1;
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::AxisSync(void) {
	Chart1->RightAxis->SetMinMax(Chart1->LeftAxis->Minimum,
		Chart1->LeftAxis->Maximum);
	Chart1->TopAxis->SetMinMax(Chart1->LeftAxis->Minimum,
		Chart1->LeftAxis->Maximum);
	Chart1->DepthTopAxis->SetMinMax(Chart1->DepthAxis->Minimum,
		Chart1->DepthAxis->Maximum);
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::PreviousButtonClick(TObject *Sender) {
	ShowGrahpic(--PAGE);
}
// ---------------------------------------------------------------------------

void __fastcall TForm2::NextButtonClick(TObject *Sender) {
	ShowGrahpic(++PAGE);
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::TeePageEditMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y) {
	if (Button == mbLeft) {
		PAGE++;
	}
	else if (Button == mbRight) {
		PAGE--;
	}
	if (PAGE > Form1->ZX) {
		PAGE = 0;
	}
	else if (PAGE < 0) {
		PAGE = Form1->ZX;
	}
	ShowGrahpic(PAGE);
}

// ---------------------------------------------------------------------------

void __fastcall TForm2::TrackBar1Change(TObject *Sender) {
	if (TrackBarMutex == 1) {
		TrackBarMutex2 = 0;
		PAGE = TrackBar1->Position;
		ShowGrahpic(PAGE);
	}
	TrackBarMutex = (TrackBarMutex) ? 0 : 1;
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::PlayStopButtonClick(TObject *Sender) {
	int DelayTime = StrToInt(TimeOutMaskEdit->EditText.SubString(0, 4));
	if (LargeCheckBox->Checked && LessCheckBox->Checked) {
		if (StrToInt(LargeMaskEdit->EditText) >
			StrToInt(LessMaskEdit->EditText)) {
			LargeCheckBox->Checked = false;
			ShowMessage("Bad Range");
			return;
		}
	}
	if (PlayStopButton->Caption == StartSign) {
		PlayStopButton->Caption = StopSign;
		while (PAGE < Form1->ZX) {
			ShowGrahpic(++PAGE);
			Sleep(DelayTime);
			Application->ProcessMessages();
			if (StopFlag == 1) {
				break;
			}
		}
		/*
		 if (PAGE == Form1->ZX) {
		 PAGE = 0;
		 ShowGrahpic(PAGE);
		 }
		 */
		StopFlag = 0;
		PlayStopButton->Caption = StartSign;
	}
	else if (PlayStopButton->Caption == StopSign) {
		StopFlag = 1;
		PlayStopButton->Caption = StartSign;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::Chart1MouseWheel(TObject *Sender, TShiftState Shift,
	int WheelDelta, TPoint &MousePos, bool &Handled) {
	float Percentage;
	if (Shift.Contains(ssCtrl)) {
		Percentage = WheelDelta * (Chart1->BottomAxis->Maximum -
			Chart1->BottomAxis->Minimum) / 1000;
		Chart1->BottomAxis->Scroll(Percentage, False);
	}
	else if (Shift.Contains(ssAlt)) {
		Percentage = -1 * WheelDelta * (Chart1->DepthAxis->Maximum -
			Chart1->DepthAxis->Minimum) / 1000;
		Chart1->DepthAxis->Scroll(Percentage, False);
	}
	else if (Shift.Contains(ssShift)) {
		Percentage = -1 * WheelDelta * (Chart1->LeftAxis->Maximum -
			Chart1->LeftAxis->Minimum) / 1000;
		Chart1->LeftAxis->Scroll(Percentage, False);
	}
	else {
		if (WheelDelta > 0) {
			Percentage = 100 + 0.045 * WheelDelta;
		}
		else {
			Percentage = 100 + 0.05 * WheelDelta;
		}
		Chart1->ZoomPercent(Percentage);
	}
	Handled = true;
	AxisSync();
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::Chart1MouseMove(TObject *Sender, TShiftState Shift,
	int X, int Y) {
	double tmpX, tmpY;
	Chart1->Series[0]->GetCursorValues(tmpX, tmpY);
	Chart1->Hint = Chart1->Series[0]->GetVertAxis->LabelValue((int)tmpY);
}
// ---------------------------------------------------------------------------
