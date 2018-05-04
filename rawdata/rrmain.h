// ---------------------------------------------------------------------------

#ifndef rrmainH
#define rrmainH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
#include "VCLTee.TeeSurfa.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.CheckLst.hpp>
#include <vector>
#include "tee.h"

// ---------------------------------------------------------------------------
class TForm1 : public TForm {
__published: // IDE-managed Components

	TButton *LoadTextFile;
	TOpenTextFileDialog *OpenTextFileDialog1;
	TRichEdit *RichEdit1;
	TPopupMenu *PopupMenu1;
	TMenuItem *Undo1;
	TMenuItem *N1;
	TMenuItem *Cut1;
	TMenuItem *Copy1;
	TMenuItem *Paste1;
	TMenuItem *Delete1;
	TMenuItem *N2;
	TMenuItem *SelectAll1;
	TMaskEdit *PageMaskEdit;
	TButton *Jump;
	TEdit *PageEdit;
	TCheckBox *LargeCheckBox;
	TCheckBox *LessCheckBox;
	TMaskEdit *LargeMaskEdit;
	TMaskEdit *LessMaskEdit;
	TButton *MarkButton;
	TButton *ZoomAButton;
	TButton *ZoomBButton;
	TButton *RecoveryButton;
	TButton *D3Button;

	void __fastcall LoadTextFileClick(TObject *Sender);
	void __fastcall Undo1Click(TObject *Sender);
	void __fastcall Cut1Click(TObject *Sender);
	void __fastcall Copy1Click(TObject *Sender);
	void __fastcall Paste1Click(TObject *Sender);
	void __fastcall Delete1Click(TObject *Sender);
	void __fastcall SelectAll1Click(TObject *Sender);
	void __fastcall RichEdit1KeyDown(TObject *Sender, WORD &Key,
		TShiftState Shift);
	void __fastcall JumpClick(TObject *Sender);
	void __fastcall LargeCheckBoxClick(TObject *Sender);
	void __fastcall ZoomAButtonClick(TObject *Sender);
	void __fastcall ZoomBButtonClick(TObject *Sender);
	void __fastcall MarkButtonClick(TObject *Sender);
	void __fastcall RecoveryButtonClick(TObject *Sender);
	void __fastcall D3ButtonClick(TObject *Sender);
	void __fastcall PageMaskEditMouseDown(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y);

private: // User declarations
	void __fastcall GetTXRX(void);
	UnicodeString __fastcall ParseTextFile(int InitFlag);
	UnicodeString __fastcall GetZeroString(int JumpPage);
	void __fastcall JumptoPage(int JumpPage);

	int RESIZESCALE, MARKFLAG;
	TMemoryStream *MemStream;
	UnicodeString TotalString;
	int StopFlag;

public: // User declarations

	int ZX, TX, RX, DATAMAX, DATAMIN;

	std::vector<std::vector<std::vector<int> > >array3D;
	__fastcall TForm1(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
// ---------------------------------------------------------------------------
#endif
