// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	Button2->Visible = false;
	Image1->Visible = false;
	CheckBox5Click(NULL);
	CheckBox4Click(NULL);
	UnicodeString MYVK_DESC[MYVK_ALL];
	MYVK_DESC[MYVK_LBUTTON] = "Left mouse button";
	MYVK_DESC[MYVK_RBUTTON] = "Right mouse button";
	MYVK_DESC[MYVK_CANCEL] = "Control-break processing";
	MYVK_DESC[MYVK_MBUTTON] = "Middle mouse button (three-button mouse)";
	MYVK_DESC[MYVK_XBUTTON1] = "X1 mouse button";
	MYVK_DESC[MYVK_XBUTTON2] = "X2 mouse button";
	MYVK_DESC[MYVK_BACK] = "BACKSPACE key";
	MYVK_DESC[MYVK_TAB] = "TAB key";
	MYVK_DESC[MYVK_CLEAR] = "CLEAR key";
	MYVK_DESC[MYVK_RETURN] = "ENTER key";
	MYVK_DESC[MYVK_SHIFT] = "SHIFT key";
	MYVK_DESC[MYVK_CONTROL] = "CTRL key";
	MYVK_DESC[MYVK_MENU] = "ALT key";
	MYVK_DESC[MYVK_PAUSE] = "PAUSE key";
	MYVK_DESC[MYVK_CAPITAL] = "CAPS LOCK key";
	MYVK_DESC[MYVK_KANA] = "IME Kana mode";
	MYVK_DESC[MYVK_HANGUEL] =
		"IME Hanguel mode (maintained for compatibility; use?MYVK_HANGUL)";
	MYVK_DESC[MYVK_HANGUL] = "IME Hangul mode";
	MYVK_DESC[MYVK_JUNJA] = "IME Junja mode";
	MYVK_DESC[MYVK_FINAL] = "IME final mode";
	MYVK_DESC[MYVK_HANJA] = "IME Hanja mode";
	MYVK_DESC[MYVK_KANJI] = "IME Kanji mode";
	MYVK_DESC[MYVK_ESCAPE] = "ESC key";
	MYVK_DESC[MYVK_CONVERT] = "IME convert";
	MYVK_DESC[MYVK_NONCONVERT] = "IME nonconvert";
	MYVK_DESC[MYVK_ACCEPT] = "IME accept";
	MYVK_DESC[MYVK_MODECHANGE] = "IME mode change request";
	MYVK_DESC[MYVK_SPACE] = "SPACEBAR";
	MYVK_DESC[MYVK_PRIOR] = "PAGE UP key";
	MYVK_DESC[MYVK_NEXT] = "PAGE DOWN key";
	MYVK_DESC[MYVK_END] = "END key";
	MYVK_DESC[MYVK_HOME] = "HOME key";
	MYVK_DESC[MYVK_LEFT] = "LEFT ARROW key";
	MYVK_DESC[MYVK_UP] = "UP ARROW key";
	MYVK_DESC[MYVK_RIGHT] = "RIGHT ARROW key";
	MYVK_DESC[MYVK_DOWN] = "DOWN ARROW key";
	MYVK_DESC[MYVK_SELECT] = "SELECT key";
	MYVK_DESC[MYVK_PRINT] = "PRINT key";
	MYVK_DESC[MYVK_EXECUTE] = "EXECUTE key";
	MYVK_DESC[MYVK_SNAPSHOT] = "PRINT SCREEN key";
	MYVK_DESC[MYVK_INSERT] = "INS key";
	MYVK_DESC[MYVK_DELETE] = "DEL key";
	MYVK_DESC[MYVK_HELP] = "HELP key";
	MYVK_DESC[MYVK_0] = "0 key";
	MYVK_DESC[MYVK_1] = "1 key";
	MYVK_DESC[MYVK_2] = "2 key";
	MYVK_DESC[MYVK_3] = "3 key";
	MYVK_DESC[MYVK_4] = "4 key";
	MYVK_DESC[MYVK_5] = "5 key";
	MYVK_DESC[MYVK_6] = "6 key";
	MYVK_DESC[MYVK_7] = "7 key";
	MYVK_DESC[MYVK_8] = "8 key";
	MYVK_DESC[MYVK_9] = "9 key";
	MYVK_DESC[MYVK_A] = "A key";
	MYVK_DESC[MYVK_B] = "B key";
	MYVK_DESC[MYVK_C] = "C key";
	MYVK_DESC[MYVK_D] = "D key";
	MYVK_DESC[MYVK_E] = "E key";
	MYVK_DESC[MYVK_F] = "F key";
	MYVK_DESC[MYVK_G] = "G key";
	MYVK_DESC[MYVK_H] = "H key";
	MYVK_DESC[MYVK_I] = "I key";
	MYVK_DESC[MYVK_J] = "J key";
	MYVK_DESC[MYVK_K] = "K key";
	MYVK_DESC[MYVK_L] = "L key";
	MYVK_DESC[MYVK_M] = "M key";
	MYVK_DESC[MYVK_N] = "N key";
	MYVK_DESC[MYVK_O] = "O key";
	MYVK_DESC[MYVK_P] = "P key";
	MYVK_DESC[MYVK_Q] = "Q key";
	MYVK_DESC[MYVK_R] = "R key";
	MYVK_DESC[MYVK_S] = "S key";
	MYVK_DESC[MYVK_T] = "T key";
	MYVK_DESC[MYVK_U] = "U key";
	MYVK_DESC[MYVK_V] = "V key";
	MYVK_DESC[MYVK_W] = "W key";
	MYVK_DESC[MYVK_X] = "X key";
	MYVK_DESC[MYVK_Y] = "Y key";
	MYVK_DESC[MYVK_Z] = "Z key";
	MYVK_DESC[MYVK_LWIN] = "Left Windows key (Natural keyboard)";
	MYVK_DESC[MYVK_RWIN] = "Right Windows key (Natural keyboard)";
	MYVK_DESC[MYVK_APPS] = "Applications key (Natural keyboard)";
	MYVK_DESC[MYVK_SLEEP] = "Computer Sleep key";
	MYVK_DESC[MYVK_NUMPAD0] = "Numeric keypad 0 key";
	MYVK_DESC[MYVK_NUMPAD1] = "Numeric keypad 1 key";
	MYVK_DESC[MYVK_NUMPAD2] = "Numeric keypad 2 key";
	MYVK_DESC[MYVK_NUMPAD3] = "Numeric keypad 3 key";
	MYVK_DESC[MYVK_NUMPAD4] = "Numeric keypad 4 key";
	MYVK_DESC[MYVK_NUMPAD5] = "Numeric keypad 5 key";
	MYVK_DESC[MYVK_NUMPAD6] = "Numeric keypad 6 key";
	MYVK_DESC[MYVK_NUMPAD7] = "Numeric keypad 7 key";
	MYVK_DESC[MYVK_NUMPAD8] = "Numeric keypad 8 key";
	MYVK_DESC[MYVK_NUMPAD9] = "Numeric keypad 9 key";
	MYVK_DESC[MYVK_MULTIPLY] = "Multiply key";
	MYVK_DESC[MYVK_ADD] = "Add key";
	MYVK_DESC[MYVK_SEPARATOR] = "Separator key";
	MYVK_DESC[MYVK_SUBTRACT] = "Subtract key";
	MYVK_DESC[MYVK_DECIMAL] = "Decimal key";
	MYVK_DESC[MYVK_DIVIDE] = "Divide key";
	MYVK_DESC[MYVK_F1] = "F1 key";
	MYVK_DESC[MYVK_F2] = "F2 key";
	MYVK_DESC[MYVK_F3] = "F3 key";
	MYVK_DESC[MYVK_F4] = "F4 key";
	MYVK_DESC[MYVK_F5] = "F5 key";
	MYVK_DESC[MYVK_F6] = "F6 key";
	MYVK_DESC[MYVK_F7] = "F7 key";
	MYVK_DESC[MYVK_F8] = "F8 key";
	MYVK_DESC[MYVK_F9] = "F9 key";
	MYVK_DESC[MYVK_F10] = "F10 key";
	MYVK_DESC[MYVK_F11] = "F11 key";
	MYVK_DESC[MYVK_F12] = "F12 key";
	MYVK_DESC[MYVK_F13] = "F13 key";
	MYVK_DESC[MYVK_F14] = "F14 key";
	MYVK_DESC[MYVK_F15] = "F15 key";
	MYVK_DESC[MYVK_F16] = "F16 key";
	MYVK_DESC[MYVK_F17] = "F17 key";
	MYVK_DESC[MYVK_F18] = "F18 key";
	MYVK_DESC[MYVK_F19] = "F19 key";
	MYVK_DESC[MYVK_F20] = "F20 key";
	MYVK_DESC[MYVK_F21] = "F21 key";
	MYVK_DESC[MYVK_F22] = "F22 key";
	MYVK_DESC[MYVK_F23] = "F23 key";
	MYVK_DESC[MYVK_F24] = "F24 key";
	MYVK_DESC[MYVK_NUMLOCK] = "NUM LOCK key";
	MYVK_DESC[MYVK_SCROLL] = "SCROLL LOCK key";
	MYVK_DESC[MYVK_LSHIFT] = "Left SHIFT key";
	MYVK_DESC[MYVK_RSHIFT] = "Right SHIFT key";
	MYVK_DESC[MYVK_LCONTROL] = "Left CONTROL key";
	MYVK_DESC[MYVK_RCONTROL] = "Right CONTROL key";
	MYVK_DESC[MYVK_LMENU] = "Left MENU key";
	MYVK_DESC[MYVK_RMENU] = "Right MENU key";
	MYVK_DESC[MYVK_BROWSER_BACK] = "Browser Back key";
	MYVK_DESC[MYVK_BROWSER_FORWARD] = "Browser Forward key";
	MYVK_DESC[MYVK_BROWSER_REFRESH] = "Browser Refresh key";
	MYVK_DESC[MYVK_BROWSER_STOP] = "Browser Stop key";
	MYVK_DESC[MYVK_BROWSER_SEARCH] = "Browser Search key";
	MYVK_DESC[MYVK_BROWSER_FAVORITES] = "Browser Favorites key";
	MYVK_DESC[MYVK_BROWSER_HOME] = "Browser Start and Home key";
	MYVK_DESC[MYVK_VOLUME_MUTE] = "Volume Mute key";
	MYVK_DESC[MYVK_VOLUME_DOWN] = "Volume Down key";
	MYVK_DESC[MYVK_VOLUME_UP] = "Volume Up key";
	MYVK_DESC[MYVK_MEDIA_NEXT_TRACK] = "Next Track key";
	MYVK_DESC[MYVK_MEDIA_PREV_TRACK] = "Previous Track key";
	MYVK_DESC[MYVK_MEDIA_STOP] = "Stop Media key";
	MYVK_DESC[MYVK_MEDIA_PLAY_PAUSE] = "Play/Pause Media key";
	MYVK_DESC[MYVK_LAUNCH_MAIL] = "Start Mail key";
	MYVK_DESC[MYVK_LAUNCH_MEDIA_SELECT] = "Select Media key";
	MYVK_DESC[MYVK_LAUNCH_APP1] = "Start Application 1 key";
	MYVK_DESC[MYVK_LAUNCH_APP2] = "Start Application 2 key";
	MYVK_DESC[MYVK_OEM_1] =
		"Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ';:' key";
	MYVK_DESC[MYVK_OEM_PLUS] = "For any country/region, the '+' key";
	MYVK_DESC[MYVK_OEM_COMMA] = "For any country/region, the ',' key";
	MYVK_DESC[MYVK_OEM_MINUS] = "For any country/region, the '-' key";
	MYVK_DESC[MYVK_OEM_PERIOD] = "For any country/region, the '.' key";
	MYVK_DESC[MYVK_OEM_2] =
		"Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '/?' key";
	MYVK_DESC[MYVK_OEM_3] =
		"Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '`~' key";
	MYVK_DESC[MYVK_OEM_4] =
		"Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '[{' key";
	MYVK_DESC[MYVK_OEM_5] =
		"Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '\\|' key";
	MYVK_DESC[MYVK_OEM_6] =
		"Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ']}' key";
	MYVK_DESC[MYVK_OEM_7] =
		"Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the 'single-quote/double-quote' key";
	MYVK_DESC[MYVK_OEM_8] =
		"Used for miscellaneous characters; it can vary by keyboard.";
	MYVK_DESC[MYVK_OEM_102] =
		"Either the angle bracket key or the backslash key on the RT 102-key keyboard";
	MYVK_DESC[MYVK_PROCESSKEY] = "IME PROCESS key";
	MYVK_DESC[MYVK_PACKET] =
		"Used to pass Unicode characters as if they were keystrokes. The MYVK_PACKET key is the low word of a 32-bit Virtual Key value used for non-keyboard input methods. For more information, see Remark in?KEYBDINPUT,?SendInput,?WM_KEYDOWN, and?WM_KEYUP";
	MYVK_DESC[MYVK_ATTN] = "Attn key";
	MYVK_DESC[MYVK_CRSEL] = "CrSel key";
	MYVK_DESC[MYVK_EXSEL] = "ExSel key";
	MYVK_DESC[MYVK_EREOF] = "Erase EOF key";
	MYVK_DESC[MYVK_PLAY] = "Play key";
	MYVK_DESC[MYVK_ZOOM] = "Zoom key";
	MYVK_DESC[MYVK_NONAME] = "Reserved";
	MYVK_DESC[MYVK_PA1] = "PA1 key";
	MYVK_DESC[MYVK_OEM_CLEAR] = "Clear key";
	for (int i = MYVK_LBUTTON, j = 0; i < MYVK_ALL; ++i) {
		if (MYVK_DESC[i].Length() != 0) {
			CMDMAP[j] = i;
			ComboBox1->Items->Insert(j++, MYVK_DESC[i]);
		}
	}
}

inline void mouseclick(int index) {
	int clicktype = (index & 0x1) ?
		(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP) :
		MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
	for (int i = (index >> 1) + 1; i--;) {
		mouse_event(clicktype, 0, 0, 0, 0);
	}
}

inline void TForm1::keyboardclick(void) {
	if (CheckBox1->Checked) {
		keybd_event(VK_CONTROL, 0, 0, 0);
	}
	if (CheckBox2->Checked) {
		keybd_event(VK_MENU, 0, 0, 0);
	}
	if (CheckBox3->Checked) {
		keybd_event(VK_SHIFT, 0, 0, 0);
	}
	keybd_event(CMDMAP[ComboBox1->ItemIndex], 0, 0, 0);
	keybd_event(CMDMAP[ComboBox1->ItemIndex], 0, KEYEVENTF_KEYUP, 0);
	if (CheckBox3->Checked) {
		keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
	}
	if (CheckBox2->Checked) {
		keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	}
	if (CheckBox1->Checked) {
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	}
}

void __fastcall TForm1::Button1Click(TObject *Sender) {
	int SleepTime;
	bStop = false;
	Button1->Visible = false;
	Button2->Visible = true;
	Image2->Visible = false;
	Image1->Visible = true;
	SleepTime = MaskEdit1->Text.ToInt();
	while (1) {
		for (int i = 0; i < SleepTime * 10; ++i) {
			Sleep(100);
			Application->ProcessMessages();
			StatusBar1->SimpleText = IntToStr((SleepTime * 10 - i) * 100)
				+ " ms";
		}
		if (bStop) {
			break;
		}
		StatusBar1->SimpleText = "Click!!";
		if (RadioGroup2->Enabled) {
			if (RadioGroup2->ItemIndex == 0) {
				keyboardclick();
			}
		}
		if (CheckBox5->Checked) {
			mouseclick(RadioGroup1->ItemIndex);
		}
		if (RadioGroup2->Enabled) {
			if (RadioGroup2->ItemIndex == 1) {
				keyboardclick();
			}
		}
		else {
			keyboardclick();
		}
	}
	Button1->Visible = true;
	Button2->Visible = false;
	Image2->Visible = true;
	Image1->Visible = false;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender) {
	bStop = true;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender) {
	RegisterHotKey(Handle, 12345678, NULL, 121);
	RegisterHotKey(Handle, 87654321, NULL, 122);
	Application->OnMessage = StrtLgIn;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::StrtLgIn(tagMSG &Msg, bool &Handled) {
	TObject *Sender;
	if (Msg.message == WM_HOTKEY && Msg.wParam == 12345678)
		Button1Click(Sender);
	else if (Msg.message == WM_HOTKEY && Msg.wParam == 87654321)
		Button2Click(Sender);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox5Click(TObject *Sender) {
	if (CheckBox5->Checked) {
		RadioGroup1->Enabled = True;
		if (CheckBox4->Checked) {
			RadioGroup2->Enabled = True;
		}
	}
	else {
		RadioGroup1->Enabled = False;
		if (CheckBox4->Checked) {
			RadioGroup2->Enabled = False;
		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox4Click(TObject *Sender) {
	if (CheckBox4->Checked) {
		if (CheckBox5->Checked) {
			RadioGroup2->Enabled = True;
		}
		ComboBox1->Enabled = True;
		ComboBox1->ItemIndex = 50;
		CheckBox1->Enabled = True;
		CheckBox2->Enabled = True;
		CheckBox3->Enabled = True;
	}
	else {
		RadioGroup2->Enabled = False;
		ComboBox1->Enabled = False;
		CheckBox1->Enabled = False;
		CheckBox2->Enabled = False;
		CheckBox3->Enabled = False;
	}
}
// ---------------------------------------------------------------------------
