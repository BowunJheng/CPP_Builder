// ---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <algorithm>
#pragma hdrstop

#include "FileCtrl.hpp"
#include "cal.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCLTee.CandleCh"
#pragma link "VCLTee.TeeTools"
#pragma link "VCLTee.TeeSurfa"
#pragma resource "*.dfm"
TForm1 *Form1;

const UnicodeString MYVERSION = "V0.3";
const int SELDIRHELP = 1000;
const UnicodeString Str000 = "原始值";
const UnicodeString Str001 = "上下差值";
const UnicodeString Str002 = "左右差值";
const UnicodeString Str003 = "差差值";
const UnicodeString Str004 = "總共分析檔案數目:";
const UnicodeString Str005 = "佔用百分數:";
const UnicodeString Str006 = "抓取的資料";
const UnicodeString Sign001 = "==============================";
const char filterstr[] = "Data___Tx";
const char MatchStart[] = "Nodes_Data_Summary";
const char MatchEnd[] = "Failed_Nodes_Summary";
const char MatchStr[TForm1::LastOne][20] = {
	"Y_Driven_Maximun_", "Y_Driven_Minimun_", "Maximun_Window1__",
	"Maximun_Window2__"};
const int MAXLEVELSTEP = 26; // 255/10

UnicodeString Dir = "";
TMemoryStream *MemStream;

// ---------------------------------------------------------------------------
bool MyCompare(TForm1::OneItem* left, TForm1::OneItem* right) {
	return (left->GetValue() < right->GetValue());
}

// ---------------------------------------------------------------------------
bool CompareConditionLess(int left, int right) {
	if (left == -1 && right != -1)
		return false;
	else if (left != -1 && right == -1)
		return true;
	return (left < right);
}

// ---------------------------------------------------------------------------
bool CompareConditionMore(int left, int right) {
	if (left == -1 && right != -1)
		return false;
	else if (left != -1 && right == -1)
		return true;
	return (left > right);
}

// ---------------------------------------------------------------------------
bool ScoreCompare(TForm1::SortItem* left, TForm1::SortItem* right) {
	return CompareConditionLess(left->GetSortScore(TForm1::ScoreNum),
		right->GetSortScore(TForm1::ScoreNum));
}

// ---------------------------------------------------------------------------
bool WeightScoreCompare(TForm1::SortItem* left, TForm1::SortItem* right) {
	return CompareConditionLess(left->GetSortScore(TForm1::WeightScoreNum),
		right->GetSortScore(TForm1::WeightScoreNum));
}

// ---------------------------------------------------------------------------
bool ScoreCompareINV(TForm1::SortItem* left, TForm1::SortItem* right) {
	return CompareConditionMore(left->GetSortScore(TForm1::ScoreNum),
		right->GetSortScore(TForm1::ScoreNum));
}

// ---------------------------------------------------------------------------
bool WeightScoreCompareINV(TForm1::SortItem* left, TForm1::SortItem* right) {
	return CompareConditionMore(left->GetSortScore(TForm1::WeightScoreNum),
		right->GetSortScore(TForm1::WeightScoreNum));
}

// ---------------------------------------------------------------------------
bool IlitekScoreCompare(TForm1::SortItem* left, TForm1::SortItem* right) {
	return CompareConditionLess(left->GetSortScore(TForm1::IlitekScoreNum),
		right->GetSortScore(TForm1::IlitekScoreNum));
}

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	Form1->Caption = Form1->Caption + " " + MYVERSION;
	MaxYChart->Visible = false;
	MinYChart->Visible = false;
	Win1Chart->Visible = false;
	Win2Chart->Visible = false;
	Dir = ExtractFilePath(Application->ExeName);
	// Dir = "C:\\Documents and Settings\\bwcheng\\桌面\\SensorTest_v2.2.0.1\\Log\\NewRC_2013_08_06+OFFICE+0070\\";
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::OpenButtonClick(TObject *Sender) {
	if (SelectDirectory(Dir,
		TSelectDirOpts() << sdAllowCreate << sdPerformCreate << sdPrompt,
		SELDIRHELP)) {
		OpenFileListBox->Directory = Dir;
		DataRichEdit->Clear();
		MaxYChartSeries->Clear();
		MinYChartSeries->Clear();
		Win1ChartSeries->Clear();
		Win2ChartSeries->Clear();
		UpDownRichEdit->Clear();
		LeftRightRichEdit->Clear();
		doubleMinusRichEdit->Clear();
		OrgRichEdit->Clear();
		OpenFileListBox->ItemIndex = 0;
		if (OpenFileListBox->GetCount() > 0) {
			RunButton->Enabled = true;
			OpenFileListBoxDblClick(Sender);
		}
		SortButton->Enabled = false;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::OpenFileListBoxDblClick(TObject *Sender) {
	UnicodeString ProcessStr, ShowStr;
	unsigned int MaxIUD = 0, MaxILR = 0, MaxIDD = 0, abstmp, abstmp2,
		MaxColorLineStart, MaxColorLineEnd;
	int tmp, MaxUD, MaxLR, MaxDD, TX = 0, RX = 0, MaxColorLineUDx,
		MaxColorLineLRx, MaxColorLineDDx, MaxColorLineUDy, MaxColorLineLRy,
		MaxColorLineDDy;
	std::vector<std::vector<int> >arraydara;
	TColor defaultcolor = UpDownRichEdit->Font->Color;
	MaxYChart->Visible = false;
	MinYChart->Visible = false;
	Win1Chart->Visible = false;
	Win2Chart->Visible = false;
	UpDownRichEdit->Visible = true;
	LeftRightRichEdit->Visible = true;
	doubleMinusRichEdit->Visible = true;
	OrgRichEdit->Visible = true;
	MemStream = new TMemoryStream();
	MemStream->LoadFromFile(OpenFileListBox->FileName);
	DataRichEdit->Lines->LoadFromStream(MemStream);
	ProcessStr = GetTXRXString(MemStream, &TX, &RX);
	arraydara.resize(TX);
	for (int i = 0; i < TX; ++i) {
		arraydara[i].resize(RX);
	}
	InsertToArray(&arraydara, ProcessStr);
	for (int i = 0; i < TX - 1; ++i) {
		for (int j = 0; j < RX; ++j) {
			tmp = arraydara[i][j] - arraydara[i + 1][j];
			/*
			 if (((i == 0 || i == (TX - 2)) && (j <= 1 || j >= (RX - 2))) ||
			 ((i <= 1 || i >= (TX - 3)) && (j == 0 || j == (RX - 1)))) {
			 tmp = 0;
			 }
			 */
			if ((i == 0 || i == (TX - 2)) && (j == 0 || j == (RX - 1))) {
				tmp = 0;
			}
			abstmp = (tmp < 0) ? (tmp*-1) : tmp;
			if (MaxIUD < abstmp) {
				MaxIUD = abstmp;
				MaxColorLineUDx = i;
				MaxColorLineUDy = j;
				MaxUD = tmp;
			}
		}
	}
	for (int i = 0; i < TX; ++i) {
		for (int j = 0; j < RX - 1; ++j) {
			tmp = arraydara[i][j] - arraydara[i][j + 1];
			/*
			 if (((i <= 1 || i >= (TX - 2)) && (j == 0 || j == (RX - 2))) ||
			 ((i == 0 || i == (TX - 1)) && (j <= 1 || j >= (RX - 3)))) {
			 tmp = 0;
			 }
			 */
			if ((i == 0 || i == (TX - 1)) && (j == 0 || j == (RX - 2))) {
				tmp = 0;
			}
			abstmp = (tmp < 0) ? (tmp*-1) : tmp;
			if (MaxILR < abstmp) {
				MaxILR = abstmp;
				MaxColorLineLRx = i;
				MaxColorLineLRy = j;
				MaxLR = tmp;
			}
		}
	}
	for (int i = 0; i < TX - 1; ++i) {
		for (int j = 0; j < RX - 1; ++j) {
			tmp = (arraydara[i][j] - arraydara[i + 1][j]);
			abstmp = (tmp < 0) ? (tmp*-1) : tmp;
			tmp = (arraydara[i][j + 1] - arraydara[i + 1][j + 1]);
			abstmp2 = (tmp < 0) ? (tmp*-1) : tmp;
			tmp = abstmp - abstmp2;
			/*
			 if (((i == 0 || i == (TX - 2)) && (j <= 1 || j >= (RX - 3))) ||
			 ((i <= 1 || i >= (TX - 3)) && (j == 0 || j == (RX - 2)))) {
			 tmp = 0;
			 }
			 */
			if ((i == 0 || i == (TX - 2)) && (j == 0 || j == (RX - 2))) {
				tmp = 0;
			}
			abstmp = (tmp < 0) ? (tmp*-1) : tmp;
			if (MaxIDD < abstmp) {
				MaxIDD = abstmp;
				MaxColorLineDDx = i;
				MaxColorLineDDy = j;
				MaxDD = tmp;
			}
		}
	}
	OrgRichEdit->Lines->Clear();
	OrgRichEdit->Lines->Add(Str000);
	ShowStr = Sign001 + "\n\t";
	for (int j = 0; j < RX; ++j) {
		ShowStr += "[" + IntToStr(j) + "]\t";
	}
	OrgRichEdit->Lines->Add(ShowStr);
	for (int i = 0; i < TX; ++i) {
		OrgRichEdit->SelText = "[" + IntToStr(i) + "]\t";
		for (int j = 0; j < RX; ++j) {
			OrgRichEdit->SelText = IntToStr(arraydara[i][j]) + "\t";
		}
		OrgRichEdit->SelText = "\n";
	}
	UpDownRichEdit->Lines->Clear();
	ShowStr = Str001 + " MAX[" + MaxColorLineUDx + "][" + MaxColorLineUDy +
		"]=" + IntToStr(MaxUD);
	UpDownRichEdit->Lines->Add(ShowStr);
	ShowStr = Sign001 + "\n\t";
	for (int j = 0; j < RX; ++j) {
		ShowStr += "[" + IntToStr(j) + "]\t";
	}
	UpDownRichEdit->Lines->Add(ShowStr);
	for (int i = 0; i < TX - 1; ++i) {
		UpDownRichEdit->SelStart = UpDownRichEdit->GetTextLen();
		if (MaxColorLineUDx == i) {
			UpDownRichEdit->SelAttributes->Color = clRed;
		}
		UpDownRichEdit->SelText = "[" + IntToStr(i) + "]\t";
		for (int j = 0; j < RX; ++j) {
			tmp = arraydara[i][j] - arraydara[i + 1][j];
			UpDownRichEdit->SelStart = UpDownRichEdit->GetTextLen();
			if (MaxColorLineUDy == j) {
				UpDownRichEdit->SelAttributes->Color = clRed;
			}
			UpDownRichEdit->SelText = IntToStr(tmp) + "\t";
			if (MaxColorLineUDy == j && MaxColorLineUDx != i) {
				UpDownRichEdit->SelStart = UpDownRichEdit->GetTextLen();
				UpDownRichEdit->SelAttributes->Color = defaultcolor;
			}
		}
		UpDownRichEdit->SelStart = UpDownRichEdit->GetTextLen();
		if (MaxColorLineUDx == i) {
			UpDownRichEdit->SelAttributes->Color = defaultcolor;
		}
		UpDownRichEdit->SelText = "\n";
	}
	LeftRightRichEdit->Lines->Clear();
	ShowStr = Str002 + " MAX[" + MaxColorLineLRx + "][" + MaxColorLineLRy +
		"]=" + IntToStr(MaxLR);
	LeftRightRichEdit->Lines->Add(ShowStr);
	ShowStr = Sign001 + "\n\t";
	for (int j = 0; j < RX - 1; ++j) {
		ShowStr += "[" + IntToStr(j) + "]\t";
	}
	LeftRightRichEdit->Lines->Add(ShowStr);
	for (int i = 0; i < TX; ++i) {
		LeftRightRichEdit->SelStart = LeftRightRichEdit->GetTextLen();
		if (MaxColorLineLRx == i) {
			LeftRightRichEdit->SelAttributes->Color = clRed;
		}
		LeftRightRichEdit->SelText = "[" + IntToStr(i) + "]\t";
		for (int j = 0; j < RX - 1; ++j) {
			tmp = arraydara[i][j] - arraydara[i][j + 1];
			LeftRightRichEdit->SelStart = LeftRightRichEdit->GetTextLen();
			if (MaxColorLineLRy == j) {
				LeftRightRichEdit->SelAttributes->Color = clRed;
			}
			LeftRightRichEdit->SelText = IntToStr(tmp) + "\t";
			if (MaxColorLineLRy == j && MaxColorLineLRx != i) {
				LeftRightRichEdit->SelStart = LeftRightRichEdit->GetTextLen();
				LeftRightRichEdit->SelAttributes->Color = defaultcolor;
			}
		}
		LeftRightRichEdit->SelStart = LeftRightRichEdit->GetTextLen();
		if (MaxColorLineLRx == i) {
			LeftRightRichEdit->SelAttributes->Color = defaultcolor;
		}
		LeftRightRichEdit->SelText = "\n";
	}
	doubleMinusRichEdit->Lines->Clear();
	ShowStr = Str003 + " MAX[" + MaxColorLineDDx + "][" + MaxColorLineDDy +
		"]=" + IntToStr(MaxDD);
	doubleMinusRichEdit->Lines->Add(ShowStr);
	ShowStr = Sign001 + "\n\t";
	for (int j = 0; j < RX - 1; ++j) {
		ShowStr += "[" + IntToStr(j) + "]\t";
	}
	doubleMinusRichEdit->Lines->Add(ShowStr);
	for (int i = 0; i < TX - 1; ++i) {
		doubleMinusRichEdit->SelStart = doubleMinusRichEdit->GetTextLen();
		if (MaxColorLineDDx == i) {
			doubleMinusRichEdit->SelAttributes->Color = clRed;
		}
		doubleMinusRichEdit->SelText = "[" + IntToStr(i) + "]\t";
		for (int j = 0; j < RX - 1; ++j) {
			tmp = (arraydara[i][j] - arraydara[i + 1][j]);
			abstmp = (tmp < 0) ? (tmp*-1) : tmp;
			tmp = (arraydara[i][j + 1] - arraydara[i + 1][j + 1]);
			abstmp2 = (tmp < 0) ? (tmp*-1) : tmp;
			tmp = abstmp - abstmp2;
			doubleMinusRichEdit->SelStart = doubleMinusRichEdit->GetTextLen();
			if (MaxColorLineDDy == j) {
				doubleMinusRichEdit->SelAttributes->Color = clRed;
			}
			doubleMinusRichEdit->SelText = IntToStr(tmp) + '\t';
			if (MaxColorLineDDy == j && MaxColorLineDDx != i) {
				doubleMinusRichEdit->SelStart =
					doubleMinusRichEdit->GetTextLen();
				doubleMinusRichEdit->SelAttributes->Color = defaultcolor;
			}
		}
		doubleMinusRichEdit->SelStart = doubleMinusRichEdit->GetTextLen();
		if (MaxColorLineDDx == i) {
			doubleMinusRichEdit->SelAttributes->Color = defaultcolor;
		}
		doubleMinusRichEdit->SelText = "\n";
	}
	for (int i = 0; i < TX; ++i) {
		for (int j = 0; j < RX; ++j) {
			Series1->AddXYZ(j, arraydara[i][j], i);
		}
	}
	delete MemStream;
}

// ---------------------------------------------------------------------------
UnicodeString __fastcall TForm1::GetTXRXString(TMemoryStream *Stream, int *tx,
	int *rx) {
	char all4_c[2];
	UnicodeString PStr = "";
	unsigned int comparecounter;
	Stream->Position = 0;
	while (Stream->Position < Stream->Size) {
		Stream->Read(&all4_c[0], 1);
		if (all4_c[0] == filterstr[0]) {
			comparecounter = 0;
			while (comparecounter++ < (strlen(filterstr) - 2)) {
				Stream->Read(&all4_c[0], 1);
				if (all4_c[0] != filterstr[comparecounter]) {
					Stream->Position -= comparecounter;
					break;
				}
			}
			if (comparecounter == (strlen(filterstr) - 1) && Stream->Position <
				Stream->Size) {
				Stream->Read(all4_c, 2);
				do {
					Stream->Read(&all4_c[0], 1);
				}
				while (all4_c[0] != 0x20 && all4_c[0] != '\t' && all4_c[0]
					!= ',');
				do {
					Stream->Read(all4_c, 2);
					Stream->Position--;
					if (all4_c[0] >= '0' && all4_c[0] <=
						'9' && *tx == 0 && (all4_c[1] == '\n' ||
						all4_c[1] == '\t' || all4_c[1] == ' ' ||
						all4_c[1] == '"' || all4_c[1] == ',' ||
						all4_c[1] == 0xd || all4_c[1] == 0xa ||
						all4_c[1] == 0x0)) {
						(*rx)++;
					}
					PStr += all4_c[0];
				}
				while ((all4_c[0] != 0xd || all4_c[1] != 0xa)
					&& Stream->Position < Stream->Size);
				PStr = PStr.SubString(0, PStr.Length() - 2) + " \n";
				(*tx)++;
			}
		}
	}
	return PStr;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::InsertToArray(std::vector<std::vector<int> > *array,
	UnicodeString PStr) {
	unsigned int txtmp = 0, rxtmp = 0, ShowOnceFlag = 0;
	UnicodeString numtmp = "";
	for (int i = 1; i <= PStr.Length(); ++i) {
		if (PStr.operator[](i) == '\n') {
			txtmp++;
			rxtmp = 0;
		}
		else if (PStr.operator[](i) >= '0' && PStr.operator[](i) <= '9') {
			numtmp += PStr.operator[](i);
		}
		else if (PStr.operator[](i) == '\n' || PStr.operator[](i) == '\t' ||
			PStr.operator[](i) == ' ' || PStr.operator[](i) == '"' ||
			PStr.operator[](i) == ',' || PStr.operator[](i) == 0xd ||
			PStr.operator[](i) == 0xa || PStr.operator[](i) == 0x0) {
			numtmp.Trim();
			if (numtmp.Length() != 0) {
				(*array)[txtmp][rxtmp++] = numtmp.ToInt();
				numtmp = "";
			}
		}
		else if (PStr.operator[](i) == '.') {
			i += 2;
		}
		else if (ShowOnceFlag == 0) {
			ShowMessage("Special character=" + PStr);
			ShowOnceFlag = 1;
		}
	}

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::RunButtonClick(TObject *Sender) {
	UnicodeString FilePath = OpenFileListBox->Directory + "\\", CopyStr,
		DetailStr;
	char all4_c, chartmp;
	unsigned int comparecounter, CounterNum[LastOne][MAXLEVELSTEP], ret;
	int UsedFileCounter[LastOne], countertmp;
	std::vector<OneItem*>DataArray[LastOne];
	memset(CounterNum, 0, LastOne*MAXLEVELSTEP*sizeof(int));
	ScoreArray.clear();
	for (int i = 0; i < OpenFileListBox->GetCount(); ++i) {
		MemStream = new TMemoryStream();
		OpenFileListBox->ItemIndex = i;
		MemStream->LoadFromFile
			(FilePath + OpenFileListBox->Items->operator[](i));
		MemStream->Position = 0;
		while (MemStream->Position < MemStream->Size) {
			MemStream->Read(&all4_c, 1);
			if (all4_c == MatchStart[0]) {
				comparecounter = 0;
				while (comparecounter++ < (strlen(MatchStart) - 2)) {
					MemStream->Read(&all4_c, 1);
					if (all4_c != MatchStart[comparecounter]) {
						MemStream->Position -= comparecounter;
						break;
					}
				}
				if (comparecounter == (strlen(MatchStart) - 1)
					&& MemStream->Position < MemStream->Size) {
					CopyStr = "";
					do {
						MemStream->Read(&all4_c, 1);
						CopyStr += all4_c;
						if (all4_c == MatchEnd[0]) {
							comparecounter = 0;
							while (comparecounter++ < (strlen(MatchEnd) - 2)) {
								MemStream->Read(&all4_c, 1);
								if (all4_c != MatchEnd[comparecounter]) {
									MemStream->Position -= comparecounter;
									break;
								}
							}
							if (comparecounter == (strlen(MatchEnd) - 1)
								&& MemStream->Position < MemStream->Size) {
								break;
							}
						}
					}
					while (MemStream->Position < MemStream->Size);
				}
			}
		}
		countertmp = 0;
		for (int j = MatchMaxYNum; j < LastOne; ++j) {
			ret = GetStataistics(CopyStr, MatchStr[j]);
			if (ret != UINT_MAX) {
				countertmp++;
				CounterNum[j][ret / 10]++;
				DataArray[j].push_back(new OneItem(i, ret));
			}
		}
		if (countertmp == LastOne) {
			ScoreArray.push_back(new SortItem(1, -1, -1,
				OpenFileListBox->Items->operator[](i)));
			for (int j = MatchMaxYNum; j < LastOne; ++j) {
				ScoreArray.back()->SetDataArray(j,
					DataArray[j].back()->GetValue());
			}
		}
		else {
			ScoreArray.push_back(new SortItem(0, -1, -1,
				OpenFileListBox->Items->operator[](i)));
		}
		delete MemStream;
	}
	DetailStr = "";
	for (int i = MatchMaxYNum; i < LastOne; ++i) {
		DetailStr += Str006 + ": " + UnicodeString(MatchStr[i]) + "\n" +
			Sign001;
		for (unsigned int j = 0; j < DataArray[i].size(); ++j) {
			if (j % 10 == 0) {
				DetailStr +=
					"\n[" + IntToStr((__int64)DataArray[i][j]->GetIndex())
					+ "]\t";
			}
			DetailStr += IntToStr((__int64)DataArray[i][j]->GetValue()) + "\t";
		}
		DetailStr += "\n\n";
	}
	DataRichEdit->Clear();
	DataRichEdit->Lines->Add(Str004 + " " + OpenFileListBox->GetCount() + "\n");
	for (int i = MatchMaxYNum; i < LastOne; ++i) {
		sort(DataArray[i].begin(), DataArray[i].end(), MyCompare);
		CountScore(DataArray[i]);
		GetGraphic(MatchStr[i], CounterNum[i], DataArray[i]);
	}
	DataRichEdit->Lines->Add(DetailStr);
	UpDownRichEdit->Visible = false;
	LeftRightRichEdit->Visible = false;
	doubleMinusRichEdit->Visible = false;
	OrgRichEdit->Visible = false;
	MaxYChart->Visible = true;
	MinYChart->Visible = true;
	Win1Chart->Visible = true;
	Win2Chart->Visible = true;
	for (int i = MatchMaxYNum; i < LastOne; ++i) {
		ShowGraphic(i, MatchStr[i], CounterNum[i]);
	}
	SortButton->Enabled = true;
}

// ---------------------------------------------------------------------------
unsigned int __fastcall TForm1::GetStataistics(UnicodeString PStr,
	const char MatchStr[]) {
	int offsetcounter, getfirstnum;
	unsigned int startoffset, numtmp;
	startoffset = PStr.Pos(MatchStr) + strlen(MatchStr);
	if (startoffset != strlen(MatchStr)) {
		getfirstnum = 0;
		for (offsetcounter = startoffset; offsetcounter < PStr.Length();
		++offsetcounter) {
			if (getfirstnum == 0 && PStr.operator[](offsetcounter) >=
				'0' && PStr.operator[](offsetcounter) <= '9') {
				getfirstnum = 1;
				startoffset = offsetcounter;
			}
			else if (PStr.operator[](offsetcounter) == '\n' ||
				(getfirstnum == 1 && (PStr.operator[](offsetcounter) <
				'0' || PStr.operator[](offsetcounter) > '9'))) {
				break;
			}
		}
		offsetcounter -= startoffset;
		numtmp = PStr.SubString(startoffset, offsetcounter).ToInt();
		return numtmp;
	}
	return UINT_MAX;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::ShowGraphic(int index, UnicodeString Title,
	unsigned int *SData) {
	TStringList * sl = new TStringList;
	TVolumeSeries *TmpChartSeries;
	TChart *TmpChart;
	int indexStart = -1, indexEnd = -1;
	switch (index) {
	case MatchMaxYNum:
		TmpChartSeries = MaxYChartSeries;
		TmpChart = MaxYChart;
		break;
	case MatchMinYNum:
		TmpChartSeries = MinYChartSeries;
		TmpChart = MinYChart;
		break;
	case MatchWin1Num:
		TmpChartSeries = Win1ChartSeries;
		TmpChart = Win1Chart;
		break;
	case MatchWin2Num:
		TmpChartSeries = Win2ChartSeries;
		TmpChart = Win2Chart;
		break;
	default: ;
	}
	sl->Text = AnsiString(Title);
	TmpChart->Title->Text = sl;
	TmpChartSeries->Clear();
	for (int i = 0; i < MAXLEVELSTEP; ++i) {
		if (SData[i] != 0) {
			if (indexStart == -1) {
				indexStart = i;
			}
			indexEnd = i;
		}
	}
	if (indexStart != 0) {
		indexStart--;
	}
	else if (indexStart == -1) {
		indexStart = 0;
	}
	if (indexEnd != (MAXLEVELSTEP - 1)) {
		indexEnd++;
	}
	else if (indexEnd == -1) {
		indexEnd = MAXLEVELSTEP - 1;
	}
	for (int i = indexStart; i <= indexEnd; ++i) {
		TmpChartSeries->AddY((double)SData[i], IntToStr(i) + "x", clRed);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::CountScore(std::vector<OneItem*>DArray) {
	long DiffNumber = 0, DiffSummary = 0, DiffValueSummary = 0;
	if (ScoreArray[DArray[0]->GetIndex()]->GetEnable() == 1) {
		ScoreArray[DArray[0]->GetIndex()]->SetSortScore(ScoreNum, 1);
		ScoreArray[DArray[0]->GetIndex()]->SetSortScore(WeightScoreNum, 1);
	}
	for (unsigned int j = 1; j < DArray.size(); ++j) {
		if (DArray[j]->GetValue() != DArray[j - 1]->GetValue()) {
			DiffNumber++;
		}
		DiffSummary += DiffNumber;
		DiffValueSummary += DArray[j]->GetValue();
	}
	DiffSummary /= DArray.size();
	DiffValueSummary /= DArray.size();
	DiffNumber = 0;
	for (unsigned int j = 1; j < DArray.size(); ++j) {
		if (DArray[j]->GetValue() != DArray[j - 1]->GetValue()) {
			DiffNumber++;
		}
		if (ScoreArray[DArray[j]->GetIndex()]->GetEnable() == 1) {
			ScoreArray[DArray[j]->GetIndex()]->SetSortScore(ScoreNum,
				(DiffNumber - DiffSummary)*(DiffNumber - DiffSummary));
			ScoreArray[DArray[j]->GetIndex()]->SetSortScore(WeightScoreNum,
				(DArray[j]->GetValue() - DiffValueSummary)*
				(DArray[j]->GetValue() - DiffValueSummary));
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::GetGraphic(UnicodeString Title, unsigned int *SData,
	std::vector<OneItem*>DArray) {
	UnicodeString ShowSection = "";
	DataRichEdit->Lines->Add(Title);
	DataRichEdit->Lines->Add(Sign001);
	for (int i = 0; i < (MAXLEVELSTEP >> 1); ++i) {
		ShowSection += "[" + IntToStr(i) + "x]\t";
	}
	ShowSection += "\n";
	for (int i = 0; i < (MAXLEVELSTEP >> 1); ++i) {
		ShowSection += IntToStr((__int64)SData[i]) + "\t";
	}
	ShowSection += "\n";
	for (int i = (MAXLEVELSTEP >> 1); i < MAXLEVELSTEP; ++i) {
		ShowSection += "[" + IntToStr(i) + "x]\t";
	}
	ShowSection += "\n";
	for (int i = (MAXLEVELSTEP >> 1); i < MAXLEVELSTEP; ++i) {
		ShowSection += IntToStr((__int64)SData[i]) + "\t";
	}
	ShowSection += "\n\n" + Str005 + "\n";
	for (int i = 0; i <= 100; i += 10) {
		ShowSection += ">" + IntToStr(i) + "%\t";
	}
	ShowSection += "\n";
	for (int i = 0; i <= 100; i += 10) {
		ShowSection +=
			" " + IntToStr((__int64)DArray[((DArray.size() - 1) * i) / 100]
			->GetValue()) + "\t";
	}
	DataRichEdit->Lines->Add(ShowSection + "\n\n");
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::OpenFileListBoxMouseMove(TObject *Sender,
	TShiftState Shift, int X, int Y) {
	int Index;
	TPoint nPos;
	nPos.X = X;
	nPos.Y = Y;
	Index = OpenFileListBox->ItemAtPos(nPos, True);
	if (Index > -1) {
		OpenFileListBox->Hint = IntToStr(Index) + ": " +
			OpenFileListBox->Items->Strings[Index];
	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::ApplicationEvents1ShowHint(UnicodeString &HintStr,
	bool &CanShow, THintInfo &HintInfo) {
	HintInfo.ReshowTimeout = 100;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::SortButtonClick(TObject *Sender) {
	unsigned int tmp, index, LastOneData = 0, ScoreKind;
	OpenFileListBox->Items->Clear();
	switch (SortRadioGroup->ItemIndex) {
	case 0:
	case 1:
	default:
		sort(ScoreArray.begin(), ScoreArray.end(), ScoreCompare);
		ScoreKind = ScoreNum;
		break;
	case 2:
		sort(ScoreArray.begin(), ScoreArray.end(), ScoreCompareINV);
		ScoreKind = ScoreNum;
		break;
	case 3:
	case 4:
		sort(ScoreArray.begin(), ScoreArray.end(), WeightScoreCompare);
		ScoreKind = WeightScoreNum;
		break;
	case 5:
		sort(ScoreArray.begin(), ScoreArray.end(), WeightScoreCompareINV);
		ScoreKind = WeightScoreNum;
		break;
	case 6:
		for (unsigned int j = 0; j < ScoreArray.size(); ++j) {
			if ((ScoreArray[j]->GetDataArray(MatchWin1Num) <
				Win1MaskEdit->EditText.ToInt()) && (ScoreArray[j]->GetDataArray
				(MatchWin2Num) < Win2MaskEdit->EditText.ToInt())) {
				ScoreArray[j]->InitIlitekScore
					(ScoreArray[j]->GetDataArray(MatchMaxYNum));
			}
			else {
				ScoreArray[j]->InitIlitekScore(-1);
			}
		}
		sort(ScoreArray.begin(), ScoreArray.end(), IlitekScoreCompare);
		ScoreKind = IlitekScoreNum;
	}
	if (SortRadioGroup->ItemIndex == 1 || SortRadioGroup->ItemIndex == 4 ||
		SortRadioGroup->ItemIndex == 6) {
		for (int j = ScoreArray.size() - 1; j > -1; --j) {
			if (ScoreArray[j]->GetSortScore(ScoreKind) != -1) {
				LastOneData = j;
				break;
			}
		}
		tmp = (LastOneData + 1) >> 1;
		index = 0;
		if (LastOneData != 0) {
			OpenFileListBox->Items->Insert(index++, ScoreArray[tmp]->GetName());
			for (unsigned int j = 1; j < tmp; ++j) {
				OpenFileListBox->Items->Insert(index++,
					ScoreArray[tmp - j]->GetName());
				OpenFileListBox->Items->Insert(index++,
					ScoreArray[tmp + j]->GetName());
			}
			OpenFileListBox->Items->Insert(index++, ScoreArray[0]->GetName());
			if (ScoreArray.size() % 2 != 0) {
				OpenFileListBox->Items->Insert(index++,
					ScoreArray[LastOneData]->GetName());
			}
		}
		if (SortRadioGroup->ItemIndex != 6) {
			for (unsigned int j = (LastOneData + 1); j < ScoreArray.size(); ++j)
			{
				OpenFileListBox->Items->Insert(index++,
					ScoreArray[j]->GetName());
			}
		}
	}
	else {
		for (unsigned int j = 0; j < ScoreArray.size(); ++j) {
			OpenFileListBox->Items->Insert(j, ScoreArray[j]->GetName());
		}
	}
}
// ---------------------------------------------------------------------------
