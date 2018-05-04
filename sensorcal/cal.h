// ---------------------------------------------------------------------------

#ifndef calH
#define calH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.FileCtrl.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include "VCLTee.CandleCh.hpp"
#include "VCLTee.TeeTools.hpp"
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.Mask.hpp>
#include "VCLTee.TeeSurfa.hpp"

// ---------------------------------------------------------------------------
class TForm1 : public TForm {
__published: // IDE-managed Components

	TButton *OpenButton;
	TFileListBox *OpenFileListBox;
	TButton *RunButton;
	TPanel *txtPanel;
	TRichEdit *DataRichEdit;
	TRichEdit *UpDownRichEdit;
	TRichEdit *LeftRightRichEdit;
	TRichEdit *doubleMinusRichEdit;
	TRichEdit *OrgRichEdit;
	TVolumeSeries *MaxYChartSeries;
	TChart *MaxYChart;
	TChart *MinYChart;
	TVolumeSeries *MinYChartSeries;
	TChart *Win1Chart;
	TVolumeSeries *Win1ChartSeries;
	TChart *Win2Chart;
	TVolumeSeries *Win2ChartSeries;
	TApplicationEvents *ApplicationEvents1;
	TRadioGroup *SortRadioGroup;
	TButton *SortButton;
	TMaskEdit *Win1MaskEdit;
	TMaskEdit *Win2MaskEdit;
	TChart *RawDataChart;
	TSurfaceSeries *Series1;
	TRotateTool *ChartTool1;

	void __fastcall OpenButtonClick(TObject *Sender);
	void __fastcall OpenFileListBoxDblClick(TObject *Sender);
	void __fastcall RunButtonClick(TObject *Sender);
	void __fastcall OpenFileListBoxMouseMove(TObject *Sender, TShiftState Shift,
		int X, int Y);
	void __fastcall ApplicationEvents1ShowHint(UnicodeString &HintStr,
		bool &CanShow, THintInfo &HintInfo);
	void __fastcall SortButtonClick(TObject *Sender);

public: // User declarations

		enum {
		MatchMaxYNum, MatchMinYNum, MatchWin1Num, MatchWin2Num, LastOne
	};
	enum {
		ScoreNum, WeightScoreNum, IlitekScoreNum, LastScoreNum
	};

	class OneItem {
	private:
		int Index, Value;

	public:
		OneItem(int index, int value) {
			this->Index = index;
			this->Value = value;
		};

		int GetIndex(void) {
			return this->Index;
		};

		int GetValue(void) {
			return this->Value;
		};
	};

	class SortItem {
	private:
		int Enable, SaveData[LastOne];
		long Score, WeightScore, IlitekScore;
		UnicodeString Name;

	public:
		SortItem(int enable, long score, long weightscore, UnicodeString name) {
			this->Enable = enable;
			this->Score = score;
			this->WeightScore = weightscore;
			this->Name = name;
		};

		int GetEnable(void) {
			return this->Enable;
		};

		long GetSortScore(int index) {
			long ret = -1;
			switch (index) {
			case ScoreNum:
				ret = this->Score;
				break;
			case WeightScoreNum:
				ret = this->WeightScore;
				break;
			case IlitekScoreNum:
			default:
				ret = this->IlitekScore;
			}
			return ret;
		};

		void SetSortScore(int index, long score) {
			switch (index) {
			case ScoreNum:
				this->Score += score;
				break;
			case WeightScoreNum:
				this->WeightScore += score;
				break;
			case IlitekScoreNum:
			default:
				this->IlitekScore += score;
			}
		};

		void InitIlitekScore(long score) {
			this->IlitekScore = score;
		};

		UnicodeString GetName(void) {
			return this->Name;
		};

		void SetDataArray(int index, int value) {
			this->SaveData[index] = value;
		};

		int GetDataArray(int index) {
			return this->SaveData[index];
		};
	};

private: // User declarations

	UnicodeString __fastcall GetTXRXString(TMemoryStream *Stream, int *tx,
		int *rx);
	void __fastcall InsertToArray(std::vector<std::vector<int> > *array,
		UnicodeString PStr);
	unsigned int __fastcall GetStataistics(UnicodeString PStr,
		const char MatchStr[]);
	void __fastcall CountScore(std::vector<TForm1::OneItem*>DArray);
	void __fastcall GetGraphic(UnicodeString Title, unsigned int *SData,
		std::vector<TForm1::OneItem*>DArray);
	void __fastcall ShowGraphic(int index, UnicodeString Title,
		unsigned int *SData);
	std::vector<SortItem*>ScoreArray;

public: // User declarations
	__fastcall TForm1(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
// ---------------------------------------------------------------------------
#endif
