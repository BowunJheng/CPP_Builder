// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>

#include "Unit1.h"
#define	LINEMAX	120
#define	MAXDELAY	300
#define	DEFAULTPATH	"/sdcard/"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
const char CMDpreStr[] = "cmd /c \"adb shell input keyevent ";
const char APKCMDpreStr[] =
	"cmd /c \"adb shell am start -n ilitek.android/.Command -e cmd ";
const char APKfaeCMDpreStr[] =
	"cmd /c \"adb shell am start -n ilitek.androidfae/.Command -e cmd ";
const char *CMDARRAY[2] = {
	"cmd /c \"adb shell reboot\"",
		"cmd /c \"adb shell chmod 777 /dev/ili* /dev/i2c*\""};
#define	CMDTOTALNUM	86
const char *CMDName[CMDTOTALNUM] = {
	"KEYCODE_UNKNOWN", "KEYCODE_MENU", "KEYCODE_SOFT_RIGHT", "KEYCODE_HOME",
	"KEYCODE_BACK", "KEYCODE_CALL", "KEYCODE_ENDCALL", "KEYCODE_0", "KEYCODE_1",
	"KEYCODE_2", "KEYCODE_3", "KEYCODE_4", "KEYCODE_5", "KEYCODE_6",
	"KEYCODE_7", "KEYCODE_8", "KEYCODE_9", "KEYCODE_STAR", "KEYCODE_POUND",
	"KEYCODE_DPAD_UP", "KEYCODE_DPAD_DOWN", "KEYCODE_DPAD_LEFT",
	"KEYCODE_DPAD_RIGHT", "KEYCODE_DPAD_CENTER", "KEYCODE_VOLUME_UP",
	"KEYCODE_VOLUME_DOWN", "KEYCODE_POWER", "KEYCODE_CAMERA", "KEYCODE_CLEAR",
	"KEYCODE_A", "KEYCODE_B", "KEYCODE_C", "KEYCODE_D", "KEYCODE_E",
	"KEYCODE_F", "KEYCODE_G", "KEYCODE_H", "KEYCODE_I", "KEYCODE_J",
	"KEYCODE_K", "KEYCODE_L", "KEYCODE_M", "KEYCODE_N", "KEYCODE_O",
	"KEYCODE_P", "KEYCODE_Q", "KEYCODE_R", "KEYCODE_S", "KEYCODE_T",
	"KEYCODE_U", "KEYCODE_V", "KEYCODE_W", "KEYCODE_X", "KEYCODE_Y",
	"KEYCODE_Z", "KEYCODE_COMMA", "KEYCODE_PERIOD", "KEYCODE_ALT_LEFT",
	"KEYCODE_ALT_RIGHT", "KEYCODE_SHIFT_LEFT", "KEYCODE_SHIFT_RIGHT",
	"KEYCODE_TAB", "KEYCODE_SPACE", "KEYCODE_SYM", "KEYCODE_EXPLORER",
	"KEYCODE_ENVELOPE", "KEYCODE_ENTER", "KEYCODE_DEL", "KEYCODE_GRAVE",
	"KEYCODE_MINUS", "KEYCODE_EQUALS", "KEYCODE_LEFT_BRACKET",
	"KEYCODE_RIGHT_BRACKET", "KEYCODE_BACKSLASH", "KEYCODE_SEMICOLON",
	"KEYCODE_APOSTROPHE", "KEYCODE_SLASH", "KEYCODE_AT", "KEYCODE_NUM",
	"KEYCODE_HEADSETHOOK", "KEYCODE_FOCUS", "KEYCODE_PLUS", "KEYCODE_MENU",
	"KEYCODE_NOTIFICATION", "KEYCODE_SEARCH", "TAG_LAST_KEYCODE"};

UnicodeString HexFileName;
UnicodeString HexFileFullName;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	for (int i = 0; i < CMDTOTALNUM; ++i)
		AllKeyMap.insert(std::pair<int, UnicodeString>(i, CMDName[i]));
	StringGridHistory->Cells[0][0] = "Repeat";
	StringGridHistory->Cells[1][0] = "Command";
	CmdCounter = 0;
	TCPIPMODE = false;
	TObject *Sender;
	CheckBoxPathClick(Sender);
	::SetFocus(EditCMD->Handle);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender) {
	HRGN hRgnT;
	// UP
	TrPoint[0].x = Button_up->Width / 2;
	TrPoint[0].y = 1;
	TrPoint[1].x = 0;
	TrPoint[1].y = Button_up->Height;
	TrPoint[2].x = Button_up->Width;
	TrPoint[2].y = Button_up->Height;
	hRgnT = CreatePolygonRgn(TrPoint, 3, ALTERNATE);
	SetWindowRgn(Button_up->Handle, hRgnT, TRUE);
	// Down
	TrPoint[0].x = 0;
	TrPoint[0].y = 1;
	TrPoint[1].x = Button_down->Width;
	TrPoint[1].y = 1;
	TrPoint[2].x = Button_down->Width / 2;
	TrPoint[2].y = Button_down->Height;
	hRgnT = CreatePolygonRgn(TrPoint, 3, ALTERNATE);
	SetWindowRgn(Button_down->Handle, hRgnT, TRUE);
	// Left
	TrPoint[0].x = 0;
	TrPoint[0].y = Button_left->Height / 2;
	TrPoint[1].x = Button_left->Width - 1;
	TrPoint[1].y = 0;
	TrPoint[2].x = Button_left->Width;
	TrPoint[2].y = Button_left->Height - 1;
	hRgnT = CreatePolygonRgn(TrPoint, 3, ALTERNATE);
	SetWindowRgn(Button_left->Handle, hRgnT, TRUE);
	// Right
	TrPoint[0].x = 1;
	TrPoint[0].y = 0;
	TrPoint[1].x = Button_right->Width;
	TrPoint[1].y = Button_right->Height / 2;
	TrPoint[2].x = 1;
	TrPoint[2].y = Button_right->Height;
	hRgnT = CreatePolygonRgn(TrPoint, 3, ALTERNATE);
	SetWindowRgn(Button_right->Handle, hRgnT, TRUE);
	// ComboList
	for (it = AllKeyMap.begin(); it != AllKeyMap.end(); it++) {
		if (it->first < 10)
			ComboBoxKey->Items->Add("0" + IntToStr(it->first) + "_" +
			it->second);
		else
			ComboBoxKey->Items->Add(IntToStr(it->first) + "_" + it->second);
		ComboBoxKey->ItemIndex = 0;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::ButtonFocusClick(TObject *Sender) {
	char CMDStr[LINEMAX];
	((TButton*)Sender)->Tag = 5;
	Button1StepClick(Sender);
	Sleep(MAXDELAY);
	((TButton*)Sender)->Tag = 4;
	Button1StepClick(Sender);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Button1StepClick(TObject *Sender) {
	char CMDStr[LINEMAX];
	sprintf(CMDStr, "%s%lld\"", CMDpreStr, ((TButton*)Sender)->Tag);
	RecordMyCMD(CMDStr);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Button_Click(TObject *Sender) {
	for (int i = 0; i < RepeatEdit->Text.ToInt(); ++i) {
		Button1StepClick(Sender);
		Sleep(MAXDELAY);
	}
	RepeatEdit->Text = "01";
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::ButtonInputClick(TObject *Sender) {
	((TButton*)Sender)->Tag = ComboBoxKey->Text.SubString(0, 2).ToInt();
	Button1StepClick(Sender);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Button1StepAPKClck(TObject *Sender) {
	char CMDStr[LINEMAX];
	AnsiString pushpath;
	AnsiString Cstr = ((TButton*)Sender)->Hint;
	if (Cstr == "upgrade") {
		pushpath = EditPath->Text;
		sprintf(CMDStr, "cmd /c \"adb shell rm %s\"", pushpath.c_str());
		RecordMyCMD(CMDStr);
		pushpath = HexFileFullName + " " + EditPath->Text;
		sprintf(CMDStr, "cmd /c \"adb push %s\"", pushpath.c_str());
		RecordMyCMD(CMDStr);
		((TButton*)Sender)->Tag = 1;
		ButtonRebootClick(Sender);
		((TButton*)Sender)->Tag = 4;
		Button1StepClick(Sender);
		Cstr = Cstr + " -e hex " + EditPath->Text;
	}
	if (CheckBoxfae->Checked)
		sprintf(CMDStr, "%s%s\"", APKfaeCMDpreStr, Cstr.c_str());
	else
		sprintf(CMDStr, "%s%s\"", APKCMDpreStr, Cstr.c_str());
	RecordMyCMD(CMDStr);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::ButtonRebootClick(TObject *Sender) {
	char CMDStr[LINEMAX];
	sprintf(CMDStr, "%s", CMDARRAY[((TButton*)Sender)->Tag]);
	RecordMyCMD(CMDStr);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::EditCMDKeyPress(TObject *Sender, System::WideChar &Key)
{
	if (Key != VK_RETURN)
		return;
	char CMDStr[LINEMAX];
	bool RunFlag = false, syntax = true;
	AnsiString Cstr = EditCMD->Text;
	UnicodeString DIRStr;
	int CurrIndex, SingleCMD;
	if (Cstr.SubString(0, 3).operator == ("adb")) {
		RunFlag = true;
		sprintf(CMDStr, "cmd /c \"%s\"", Cstr.c_str());
		RecordMyCMD(CMDStr);
	}

	if (RunFlag == false) {
		for (int i = 1; i <= Cstr.Length(); ++i) {
			switch (Cstr.operator[](i)) {
			case 'u':
			case 'U':
			case 'd':
			case 'D':
			case 'l':
			case 'L':
			case 'r':
			case 'R':
			case 'e':
			case 'E':
			case 'b':
			case 'B':
			case 'f':
			case 'F':
				DIRStr += Cstr.operator[](i);
				CurrIndex = i;
				for (int j = i + 1; j <= Cstr.Length(); ++j) {
					if (Cstr.operator[](j) >= '0' && Cstr.operator[](j) <= '9')
					{
						i = j;
						if (j == Cstr.Length()) {
							if (i - CurrIndex > 0)
								for (int k = 0;
								k < Cstr.SubString(CurrIndex + 1,
									i - CurrIndex).ToInt() - 1; ++k)
									DIRStr += Cstr.operator[](CurrIndex);
						}
					}
					else {
						if (i - CurrIndex > 0)
							for (int k = 0;
							k < Cstr.SubString(CurrIndex + 1,
								i - CurrIndex).ToInt() - 1; ++k)
								DIRStr += Cstr.operator[](CurrIndex);
						break;
					}
				}
				break;
			default:
				syntax = false;
			}
		}
		if (syntax) {
			for (int i = 1; i <= DIRStr.Length(); ++i) {
				switch (DIRStr.operator[](i)) {
				case 'u':
				case 'U':
					((TButton*)Sender)->Tag = 19;
					break;
				case 'd':
				case 'D':
					((TButton*)Sender)->Tag = 20;
					break;
				case 'l':
				case 'L':
					((TButton*)Sender)->Tag = 21;
					break;
				case 'r':
				case 'R':
					((TButton*)Sender)->Tag = 22;
					break;
				case 'e':
				case 'E':
					((TButton*)Sender)->Tag = 66;
					break;
				case 'b':
				case 'B':
					((TButton*)Sender)->Tag = 4;
					break;
				case 'f':
				case 'F':
					ButtonFocusClick(Sender);
				}
				if (syntax != 'f' && syntax != 'F')
					Button1StepClick(Sender);
			}
		}
		else {
			SingleCMD = -1;
			try {
				SingleCMD = Cstr.ToInt();
			}
			catch (...) {
				SingleCMD = -1;
			}
			if (SingleCMD >= 0 && SingleCMD < CMDTOTALNUM && Cstr.operator[]
				(Cstr.Length()) - '0' == SingleCMD % 10) {
				((TButton*)Sender)->Tag = SingleCMD;
				Button1StepClick(Sender);
			}
		}
	}
	EditCMD->Clear();
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::RecordMyCMD(const char * lpCmdLine) {
	bool Increase = false;
	char CMDStr[LINEMAX];
	UnicodeString IP;
	int net1, net2, host1, host2, port;
	CmdCounter = (CmdCounter >= StringGridHistory->RowCount) ?
		(StringGridHistory->RowCount - 1) : CmdCounter;
	CmdCounter++;

	if (CheckBoxTCPIP->Checked) {
		if (ParamCount() >= 1) {
			IP = ParamStr(1);
			net1 = IP.SubString(0, IP.Pos('.') - 1).TrimRight().ToInt();
			IP = IP.SubString(IP.Pos('.') + 1, IP.Length());
			net2 = IP.SubString(0, IP.Pos('.') - 1).TrimRight().ToInt();
			IP = IP.SubString(IP.Pos('.') + 1, IP.Length());
			host1 = IP.SubString(0, IP.Pos('.') - 1).TrimRight().ToInt();
			IP = IP.SubString(IP.Pos('.') + 1, IP.Length());
			host2 = IP.SubString(0, IP.Pos(':') - 1).TrimRight().ToInt();
			port = IP.SubString(IP.Pos(':') + 1, IP.Length()).TrimRight()
				.ToInt();
			if (!(net1 < 0 || net1 > 255 || net2 < 0 || net2 > 255 || host1 <
				0 || host1 > 255 || host2 < 0 || host2 > 255 || port < 0)) {
				IP = MaskEditIP->Text;
				net1 = IP.SubString(0, 3).TrimRight().ToInt();
				net2 = IP.SubString(5, 3).TrimRight().ToInt();
				host1 = IP.SubString(9, 3).TrimRight().ToInt();
				host2 = IP.SubString(13, 3).TrimRight().ToInt();
				port = IP.SubString(17, 4).TrimRight().ToInt();

			}
		}
		else {
			IP = MaskEditIP->Text;
			net1 = IP.SubString(0, 3).TrimRight().ToInt();
			net2 = IP.SubString(5, 3).TrimRight().ToInt();
			host1 = IP.SubString(9, 3).TrimRight().ToInt();
			host2 = IP.SubString(13, 3).TrimRight().ToInt();
			port = IP.SubString(17, 4).TrimRight().ToInt();
		}
		sprintf(CMDStr, "cmd /c \"adb connect %d.%d.%d.%d:%d\"", net1, net2,
			host1, host2, port);
		if (!TCPIPMODE) {
			WinExec(CMDStr, SW_HIDE);
			TCPIPMODE = true;
		}
	}
	else {
		if (TCPIPMODE) {
			WinExec("cmd /c \"adb usb\"", SW_HIDE);
			TCPIPMODE = false;
		}
	}
	if (CmdCounter > 1 && StringGridHistory->Cells[1][CmdCounter -
		1].operator == (lpCmdLine + 7)) {
		Increase = true;
		CmdCounter--;
	}
	if (CmdCounter == StringGridHistory->RowCount) {
		for (int i = 1; i < (StringGridHistory->RowCount - 1); ++i) {
			StringGridHistory->Cells[0][i] = StringGridHistory->Cells[0][i + 1];
			StringGridHistory->Cells[1][i] = StringGridHistory->Cells[1][i + 1];
		}
		CmdCounter = StringGridHistory->RowCount - 1;
	}
	if (Increase)
		StringGridHistory->Cells[0][CmdCounter] =
			StringGridHistory->Cells[0][CmdCounter].ToInt() + 1;
	else
		StringGridHistory->Cells[0][CmdCounter] = 1;
	StringGridHistory->Cells[1][CmdCounter] = lpCmdLine + 7;
	WinExec(lpCmdLine, SW_HIDE);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::StringGridHistoryDblClick(TObject *Sender) {
	if (StringGridHistory->Cells[1][StringGridHistory->Row].Length() == 0)
		return;
	char CMDStr[LINEMAX];
	sprintf(CMDStr, "cmd /c %s",
		((AnsiString)StringGridHistory->Cells[1][StringGridHistory->Row])
		.c_str());
	RecordMyCMD(CMDStr);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::ListBoxScriptDragDrop(TObject *Sender, TObject *Source,
	int X, int Y) {
	bool SameCMD = false;
	int RepeatCounter;
	if (Source == StringGridHistory) {
		if (StringGridHistory->Cells[1][StringGridHistory->Row].Length() == 0)
			return;
		if (ListBoxScript->Count) {
			if (ListBoxScript->Items->operator[](ListBoxScript->Count - 1)
				.SubString(0, ListBoxScript->Items->Text.Pos("\" ")).operator ==
				(StringGridHistory->Cells[1][StringGridHistory->Row]))
				SameCMD = true;
		}
		if (SameCMD) {
			RepeatCounter = ListBoxScript->Items->operator[]
				(ListBoxScript->Count - 1).SubString
				(ListBoxScript->Items->Text.Pos("\" ") + 1,
				ListBoxScript->Items->Text.Length()).ToInt() + 1;
			ListBoxScript->Items->Delete(ListBoxScript->Count - 1);
			ListBoxScript->Items->Add
				(StringGridHistory->Cells[1][StringGridHistory->Row] + " " +
				RepeatCounter);
		}
		else {
			ListBoxScript->Items->Add
				(StringGridHistory->Cells[1][StringGridHistory->Row] + " 1");
		}
		ButtonScript->Enabled = true;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::ListBoxScriptDragOver(TObject *Sender, TObject *Source,
	int X, int Y, TDragState State, bool &Accept) {
	if (Source == StringGridHistory) {
		Accept = true;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::StringGridHistoryMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y) {
	StringGridHistory->BeginDrag(false);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::ListBoxScriptDblClick(TObject *Sender) {
	ListBoxScript->Items->Delete(ListBoxScript->ItemIndex);
	if (ListBoxScript->Count == 0)
		ButtonScript->Enabled = false;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::ButtonScriptClick(TObject *Sender) {
	char CMDStr[LINEMAX];
	int RepeatCounter;
	for (int i = 0; i < ListBoxScript->Count; ++i) {
		sprintf(CMDStr, "cmd /c %s",
			((AnsiString)ListBoxScript->Items->operator[](i).SubString(0,
			ListBoxScript->Items->Text.Pos("\" "))).c_str());
		RepeatCounter = ListBoxScript->Items->operator[](i).SubString
			(ListBoxScript->Items->Text.Pos("\" ") + 1,
			ListBoxScript->Items->Text.Length()).ToInt();
		for (int j = 0; j < RepeatCounter; ++j)
			RecordMyCMD(CMDStr);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::MaskEditIPExit(TObject *Sender) {
	String IP = MaskEditIP->Text;
	int net1 = IP.SubString(0, 3).TrimRight().ToInt();
	int net2 = IP.SubString(5, 3).TrimRight().ToInt();
	int host1 = IP.SubString(9, 3).TrimRight().ToInt();
	int host2 = IP.SubString(13, 3).TrimRight().ToInt();
	int port = IP.SubString(17, 4).TrimRight().ToInt();

	if (net1 < 0 || net1 > 255 || net2 < 0 || net2 > 255 || host1 < 0 || host1 >
		255 || host2 < 0 || host2 > 255 || port < 0)
		throw(Exception("Not a valid IP address."));
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)

{
	char CMDStr[LINEMAX];
	if (MaskEditIP->Focused() || EditPath->Focused())
		return;
	::SetFocus(EditCMD->Handle);
	if (!EditCMD->Text.Length()) {
		switch (Key) {
		case VK_UP:
			((TButton*)Sender)->Tag = 19;
			break;
		case VK_DOWN:
			((TButton*)Sender)->Tag = 20;
			break;
		case VK_LEFT:
			((TButton*)Sender)->Tag = 21;
			break;
		case VK_RIGHT:
			((TButton*)Sender)->Tag = 22;
			break;
		case VK_RETURN:
			((TButton*)Sender)->Tag = 66;
			break;
		case VK_BACK:
			((TButton*)Sender)->Tag = 4;
			break;
		default:
			((TButton*)Sender)->Tag = -1;
			break;
		};
		if (((TButton*)Sender)->Tag != -1)
			Button1StepClick(Sender);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::CheckBoxPathClick(TObject *Sender) {
	if (CheckBoxPath->Checked) {
		EditPath->ReadOnly = true;
		EditPath->Enabled = false;
		EditPath->Text = DEFAULTPATH + HexFileName;
	}
	else {
		EditPath->ReadOnly = false;
		EditPath->Enabled = true;
		::SetFocus(EditPath->Handle);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::ButtonSetFileClick(TObject *Sender) {
	if (OpenDialog1->Execute()) {
		HexFileFullName = OpenDialog1->FileName;
		HexFileName = ExtractFileName(OpenDialog1->FileName);
		EditPath->Text = EditPath->Text + HexFileName;
		ButtonBurn->Enabled = true;
	}
}
// ---------------------------------------------------------------------------
