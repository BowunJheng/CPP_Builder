// ---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>

// ---------------------------------------------------------------------------
class TForm1 : public TForm {
__published: // IDE-managed Components
	TButton *Button1;
	TButton *Button2;
	TMaskEdit *MaskEdit1;
	TStaticText *StaticText1;
	TRadioGroup *RadioGroup1;
	TImage *Image1;
	TImage *Image2;
	TStatusBar *StatusBar1;
	TRadioGroup *RadioGroup2;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TCheckBox *CheckBox4;
	TCheckBox *CheckBox5;
	TComboBox *ComboBox1;

	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall CheckBox5Click(TObject *Sender);
	void __fastcall CheckBox4Click(TObject *Sender);

private: // User declarations
	inline void keyboardclick(void);

	enum VirtualKey {
		MYVK_LBUTTON = 0x01, MYVK_RBUTTON, MYVK_CANCEL, MYVK_MBUTTON,
		MYVK_XBUTTON1, MYVK_XBUTTON2, MYVK_BACK = 0x08, MYVK_TAB, MYVK_CLEAR =
			0x0C, MYVK_RETURN, MYVK_SHIFT = 0x10, MYVK_CONTROL, MYVK_MENU,
		MYVK_PAUSE, MYVK_CAPITAL, MYVK_KANA, MYVK_HANGUEL = 0x15, MYVK_HANGUL =
			0x15, MYVK_JUNJA = 0x17, MYVK_FINAL, MYVK_HANJA, MYVK_KANJI = 0x19,
		MYVK_ESCAPE = 0x1B, MYVK_CONVERT, MYVK_NONCONVERT, MYVK_ACCEPT,
		MYVK_MODECHANGE, MYVK_SPACE, MYVK_PRIOR, MYVK_NEXT, MYVK_END, MYVK_HOME,
		MYVK_LEFT, MYVK_UP, MYVK_RIGHT, MYVK_DOWN, MYVK_SELECT, MYVK_PRINT,
		MYVK_EXECUTE, MYVK_SNAPSHOT, MYVK_INSERT, MYVK_DELETE, MYVK_HELP,
		MYVK_0, MYVK_1, MYVK_2, MYVK_3, MYVK_4, MYVK_5, MYVK_6, MYVK_7, MYVK_8,
		MYVK_9, MYVK_A = 0x41, MYVK_B, MYVK_C, MYVK_D, MYVK_E, MYVK_F, MYVK_G,
		MYVK_H, MYVK_I, MYVK_J, MYVK_K, MYVK_L, MYVK_M, MYVK_N, MYVK_O, MYVK_P,
		MYVK_Q, MYVK_R, MYVK_S, MYVK_T, MYVK_U, MYVK_V, MYVK_W, MYVK_X, MYVK_Y,
		MYVK_Z, MYVK_LWIN, MYVK_RWIN, MYVK_APPS, MYVK_SLEEP = 0x5F,
		MYVK_NUMPAD0, MYVK_NUMPAD1, MYVK_NUMPAD2, MYVK_NUMPAD3, MYVK_NUMPAD4,
		MYVK_NUMPAD5, MYVK_NUMPAD6, MYVK_NUMPAD7, MYVK_NUMPAD8, MYVK_NUMPAD9,
		MYVK_MULTIPLY, MYVK_ADD, MYVK_SEPARATOR, MYVK_SUBTRACT, MYVK_DECIMAL,
		MYVK_DIVIDE, MYVK_F1, MYVK_F2, MYVK_F3, MYVK_F4, MYVK_F5, MYVK_F6,
		MYVK_F7, MYVK_F8, MYVK_F9, MYVK_F10, MYVK_F11, MYVK_F12, MYVK_F13,
		MYVK_F14, MYVK_F15, MYVK_F16, MYVK_F17, MYVK_F18, MYVK_F19, MYVK_F20,
		MYVK_F21, MYVK_F22, MYVK_F23, MYVK_F24, MYVK_NUMLOCK = 0x90,
		MYVK_SCROLL, MYVK_LSHIFT = 0xA0, MYVK_RSHIFT, MYVK_LCONTROL,
		MYVK_RCONTROL, MYVK_LMENU, MYVK_RMENU, MYVK_BROWSER_BACK,
		MYVK_BROWSER_FORWARD, MYVK_BROWSER_REFRESH, MYVK_BROWSER_STOP,
		MYVK_BROWSER_SEARCH, MYVK_BROWSER_FAVORITES, MYVK_BROWSER_HOME,
		MYVK_VOLUME_MUTE, MYVK_VOLUME_DOWN, MYVK_VOLUME_UP,
		MYVK_MEDIA_NEXT_TRACK, MYVK_MEDIA_PREV_TRACK, MYVK_MEDIA_STOP,
		MYVK_MEDIA_PLAY_PAUSE, MYVK_LAUNCH_MAIL, MYVK_LAUNCH_MEDIA_SELECT,
		MYVK_LAUNCH_APP1, MYVK_LAUNCH_APP2, MYVK_OEM_1 = 0xBA, MYVK_OEM_PLUS,
		MYVK_OEM_COMMA, MYVK_OEM_MINUS, MYVK_OEM_PERIOD, MYVK_OEM_2, MYVK_OEM_3,
		MYVK_OEM_4 = 0xDB, MYVK_OEM_5, MYVK_OEM_6, MYVK_OEM_7, MYVK_OEM_8,
		MYVK_OEM_102 = 0xE2, MYVK_PROCESSKEY = 0xE5, MYVK_PACKET = 0xE7,
		MYVK_ATTN = 0xF6, MYVK_CRSEL, MYVK_EXSEL, MYVK_EREOF, MYVK_PLAY,
		MYVK_ZOOM, MYVK_NONAME, MYVK_PA1, MYVK_OEM_CLEAR = 0xFE, MYVK_ALL
	};

	int CMDMAP[MYVK_ALL];

public: // User declarations
	__fastcall TForm1(TComponent* Owner);
	void __fastcall StrtLgIn(tagMSG &Msg, bool &Handled);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
bool bStop = false;
// ---------------------------------------------------------------------------
#endif
