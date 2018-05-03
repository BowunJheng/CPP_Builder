// ---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>
#include <map>

// ---------------------------------------------------------------------------
class TForm1 : public TForm {
__published: // IDE-managed Components

	TMaskEdit *RepeatEdit;
	TButton *Button_up;
	TButton *Button_left;
	TButton *Button_right;
	TButton *Button_down;
	TButton *ButtonFocus;
	TButton *ButtonUnlock;
	TButton *ButtonEnter;
	TComboBox *ComboBoxKey;
	TButton *ButtonInput;
	TButton *ButtonBack;
	TButton *ButtonInfo;
	TCheckBox *CheckBoxfae;
	TButton *ButtonUtil;
	TButton *ButtonX;
	TButton *ButtonY;
	TButton *ButtonAllX;
	TButton *ButtonAllY;
	TButton *ButtonK;
	TButton *ButtonBL;
	TButton *ButtonAP;
	TButton *ButtonEBG;
	TButton *ButtonReset;
	TButton *ButtonReboot;
	TEdit *EditCMD;
	TStringGrid *StringGridHistory;
	TListBox *ListBoxScript;
	TButton *ButtonScript;
	TCheckBox *CheckBoxTCPIP;
	TMaskEdit *MaskEditIP;
	TButton *ButtonMain;
	TEdit *EditPath;
	TCheckBox *CheckBoxPath;
	TButton *ButtonSetFile;
	TButton *ButtonPerm;
	TButton *ButtonBurn;
	TOpenDialog *OpenDialog1;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ButtonFocusClick(TObject *Sender);
	void __fastcall Button1StepClick(TObject *Sender);
	void __fastcall Button_Click(TObject *Sender);
	void __fastcall ButtonInputClick(TObject *Sender);
	void __fastcall Button1StepAPKClck(TObject *Sender);
	void __fastcall ButtonRebootClick(TObject *Sender);
	void __fastcall EditCMDKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall StringGridHistoryDblClick(TObject *Sender);
	void __fastcall ListBoxScriptDragDrop(TObject *Sender, TObject *Source,
		int X, int Y);
	void __fastcall ListBoxScriptDragOver(TObject *Sender, TObject *Source,
		int X, int Y, TDragState State, bool &Accept);
	void __fastcall StringGridHistoryMouseDown(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall ListBoxScriptDblClick(TObject *Sender);
	void __fastcall ButtonScriptClick(TObject *Sender);
	void __fastcall MaskEditIPExit(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall CheckBoxPathClick(TObject *Sender);
	void __fastcall ButtonSetFileClick(TObject *Sender);

private: // User declarations

	POINT TrPoint[3];

	std::map<int, UnicodeString>AllKeyMap;
	std::map<int, UnicodeString>::iterator it;
	std::pair<std::map<int, UnicodeString>::iterator, bool>ret;
	void __fastcall RecordMyCMD(const char * lpCmdLine);

	int CmdCounter;
	bool TCPIPMODE;

public: // User declarations

	__fastcall TForm1(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
// ---------------------------------------------------------------------------
#endif
