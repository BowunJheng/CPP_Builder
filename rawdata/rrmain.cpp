// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "rrmain.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCLTee.TeeSurfa"
#pragma resource "*.dfm"
TForm1 *Form1;
const int MAX_ZX = 300;
const UnicodeString Stop = "Stop";

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	MARKFLAG = 0;
	StopFlag = 0;
	PageMaskEdit->PopupMenu = new TPopupMenu(NULL);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::LoadTextFileClick(TObject *Sender) {
	if (OpenTextFileDialog1->Execute()) {
		if (FileExists(OpenTextFileDialog1->FileName)) {
			MemStream = new TMemoryStream();
			MemStream->LoadFromFile(OpenTextFileDialog1->FileName);
			RichEdit1->Clear();
			TotalString = ParseTextFile(1);
			RichEdit1->Text = TotalString;
			PageMaskEdit->EditText = GetZeroString(0);
			Jump->Enabled = true;
			ZoomAButton->Enabled = true;
			ZoomBButton->Enabled = true;
			D3Button->Enabled = true;
		}
		else {
			ShowMessage("No Exist");
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::GetTXRX(void) {
	char all4_c[2];
	UnicodeString UStringTmp;
	int Start_Flag = 0, NewLineCounter;
	if (MemStream != NULL) {
		all4_c[0] = all4_c[1] = 0;
		TX = RX = 0;
		MemStream->Position = 0;
		while (MemStream->Position < MemStream->Size) {
			NewLineCounter = 0;
			MemStream->Read(&all4_c[1], 1);
			if (all4_c[1] >= 48 && all4_c[1] <= 57) {
				Start_Flag = 1;
				UStringTmp += all4_c[1];
			}
			else if (all4_c[1] == 0x20 || all4_c[1] == 0xd ||
				all4_c[1] == 0xa || all4_c[1] == ',') {
				if (Start_Flag == 1) {
					if (UStringTmp.Length() != 0) {
						if (all4_c[1] != 0xa && TX == 0) {
							RX++;
						}
						UStringTmp = "";
					}
					if (all4_c[0] == 0xd && all4_c[1] == 0xa) {
						if (MemStream->Position < MemStream->Size) {
							do {
								MemStream->Read(all4_c, 2);
								while ((all4_c[0] == 0x20 || all4_c[0] == 0xa)
									&& MemStream->Position < MemStream->Size) {
									MemStream->Position--;
									MemStream->Read(all4_c, 2);
								}
								NewLineCounter++;
							}
							while (all4_c[0] == 0xd && all4_c[1] == 0xa &&
								(MemStream->Position < MemStream->Size));
							MemStream->Position -= 2;
						}
						TX++;
						if (NewLineCounter > 1 || MemStream->Position >=
							MemStream->Size) {
							break;
						}
					}
				}
			}
			else if (all4_c[1] == '/' || all4_c[1] == '[') {
				if (MemStream->Position < MemStream->Size) {
					do {
						MemStream->Read(all4_c, 2);
						MemStream->Position--;
					}
					while ((all4_c[0] != 0xd || all4_c[1] != 0xa)
						&& MemStream->Position < MemStream->Size);
				}
			}
			all4_c[0] = all4_c[1];
		}
	}
}

// ---------------------------------------------------------------------------
UnicodeString __fastcall TForm1::ParseTextFile(int InitFlag) {
	char all4_c[2];
	UnicodeString UStringTmp, RetString = "";
	int ShowOnceFlag = 0, Start_Flag = 0, tx, rx, NewLineCounter;
	DATAMAX = INT_MIN;
	DATAMIN = INT_MAX;
	if (MemStream != NULL) {
		if (InitFlag != 0) {
			GetTXRX();
		}
		RESIZESCALE = 1;
		array3D.resize(MAX_ZX*RESIZESCALE);
		for (int i = 0; i < MAX_ZX; ++i) {
			array3D[i].resize(TX);
			for (int j = 0; j < TX; ++j)
				array3D[i][j].resize(RX);
		}
		UStringTmp = "";
		MemStream->Position = 0;
		all4_c[0] = all4_c[1] = 0;
		ZX = tx = rx = 0;
		while (MemStream->Position < MemStream->Size) {
			NewLineCounter = 0;
			MemStream->Read(&all4_c[1], 1);
			if (all4_c[1] >= 48 && all4_c[1] <= 57) {
				Start_Flag = 1;
				UStringTmp += all4_c[1];
			}
			else if (all4_c[1] == 0x20 || all4_c[1] == 0xd ||
				all4_c[1] == 0xa || all4_c[1] == ',') {
				if (Start_Flag == 1) {
					if (UStringTmp.Length() != 0) {
						if (all4_c[1] != 0xa) {
							array3D[ZX][tx][rx] = StrToInt(UStringTmp);
							if (DATAMAX < array3D[ZX][tx][rx]) {
								DATAMAX = array3D[ZX][tx][rx];
							}
							if (DATAMIN > array3D[ZX][tx][rx]) {
								DATAMIN = array3D[ZX][tx][rx];
							}
							RetString += UStringTmp + " ";
							rx = (rx >= (RX - 1)) ? 0 : (rx + 1);
						}
						UStringTmp = "";
					}
					if (all4_c[0] == 0xd && all4_c[1] == 0xa) {
						if (MemStream->Position < MemStream->Size) {
							do {
								MemStream->Read(all4_c, 2);
								while ((all4_c[0] == 0x20 || all4_c[0] == 0xa)
									&& MemStream->Position < MemStream->Size) {
									MemStream->Position--;
									MemStream->Read(all4_c, 2);
								}
								NewLineCounter++;
							}
							while (all4_c[0] == 0xd && all4_c[1] == 0xa &&
								(MemStream->Position < MemStream->Size));
							MemStream->Position -= 2;
						}
						RetString += "\n";
						if (NewLineCounter == 1) {
							tx = (tx >= (TX - 1)) ? 0 : (tx + 1);
						}
						else if (NewLineCounter > 1 || MemStream->Position >=
							MemStream->Size) {
							RetString += "\n\n";
							if (all4_c[0] != 0xd || all4_c[1] != 0xa) {
								RetString.SetLength(RetString.Length() - 1);
								if (ZX >= (MAX_ZX * RESIZESCALE - 1)) {
									RESIZESCALE++;
									array3D.resize(MAX_ZX*RESIZESCALE);
									for (int i = MAX_ZX;
									i < MAX_ZX * RESIZESCALE; ++i) {
										array3D[i].resize(TX);
										for (int j = 0; j < TX; ++j)
										array3D[i][j].resize(RX);
									}
								}
							}
							ZX++;
							tx = 0;
						}
						rx = 0;
					}
				}
			}
			else if (all4_c[1] == '/' || all4_c[1] == '[') {
				if (MemStream->Position < MemStream->Size) {
					do {
						MemStream->Read(all4_c, 2);
						MemStream->Position--;
					}
					while ((all4_c[0] != 0xd || all4_c[1] != 0xa)
						&& MemStream->Position < MemStream->Size);
				}
			}
			else if (ShowOnceFlag == 0) {
				UStringTmp += all4_c[1];
				ShowMessage("Special letter=" + UStringTmp);
				ShowOnceFlag = 1;
				break;
			}
			all4_c[0] = all4_c[1];
		}
	}
	PageEdit->Text = IntToStr(ZX);
	return RetString;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Undo1Click(TObject * Sender) {
	if (RichEdit1->CanUndo) {
		RichEdit1->Undo();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Cut1Click(TObject * Sender) {
	if (RichEdit1->SelLength != 0) {
		RichEdit1->CutToClipboard(); ;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Copy1Click(TObject * Sender) {
	if (RichEdit1->SelLength != 0) {
		RichEdit1->CopyToClipboard(); ;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Paste1Click(TObject * Sender) {
	RichEdit1->PasteFromClipboard();
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Delete1Click(TObject * Sender) {
	if (RichEdit1->SelLength != 0) {
		RichEdit1->SelText = "";
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::SelectAll1Click(TObject * Sender) {
	RichEdit1->SelectAll();
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::RichEdit1KeyDown(TObject * Sender, WORD & Key,
	TShiftState Shift) {
	if (Shift.Contains(ssCtrl)) {
		switch (Key) {
		case 'z':
		case 'Z':
			Undo1Click(Sender);
			break;
		case 'x':
		case 'X':
			Cut1Click(Sender);
			break;
		case 'c':
		case 'C':
			Copy1Click(Sender);
			break;
		case 'v':
		case 'V':
			Paste1Click(Sender);
			break;
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::JumpClick(TObject *Sender) {
	int JumpPage = StrToInt(PageMaskEdit->EditText);
	if (JumpPage == ZX) {
		JumpPage = 0;
	}
	else if (JumpPage < ZX) {
		JumpPage += (int)(ZX * .1);
		if (JumpPage > ZX)
			JumpPage = ZX;
	}
	JumptoPage(JumpPage);
}

// ---------------------------------------------------------------------------
UnicodeString __fastcall TForm1::GetZeroString(int JumpPage) {
	UnicodeString RetStr;
	if (JumpPage < 10) {
		RetStr = "000";
	}
	else if (JumpPage < 100) {
		RetStr = "00";
	}
	else if (JumpPage < 1000) {
		RetStr = "0";
	}
	RetStr += IntToStr(JumpPage);
	return RetStr;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::LargeCheckBoxClick(TObject *Sender) {
	if (Jump->Enabled && (LargeCheckBox->Checked || LessCheckBox->Checked)) {
		MarkButton->Enabled = true;
	}
	else {
		MarkButton->Enabled = false;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::ZoomAButtonClick(TObject *Sender) {
	RichEdit1->Font->Size = RichEdit1->Font->Size + 2;
	if (MARKFLAG == 1) {
		MarkButtonClick(Sender);
	}
}

// ---------------------------------------------------------------------------

void __fastcall TForm1::ZoomBButtonClick(TObject *Sender) {
	int size = RichEdit1->Font->Size;
	size = (size > 2) ? (size - 2) : 2;
	RichEdit1->Font->Size = size;
	if (MARKFLAG == 1) {
		MarkButtonClick(Sender);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::MarkButtonClick(TObject *Sender) {
	UnicodeString Nodetmp, SaveName = RecoveryButton->Caption;
	TColor defaultcolor = RichEdit1->Font->Color;
	int LARGENUM, LESSNUM;
	bool EnableColor;
	if (LargeCheckBox->Checked && LessCheckBox->Checked) {
		if (StrToInt(LargeMaskEdit->EditText) >
			StrToInt(LessMaskEdit->EditText)) {
			LargeCheckBox->Checked = false;
			ShowMessage("Bad Range");
			return;
		}
	}
	RecoveryButton->Caption = Stop;
	RecoveryButton->Enabled = true;
	MarkButton->Enabled = false;
	RichEdit1->Clear();
	if (LargeCheckBox->Checked) {
		LARGENUM = StrToInt(LargeMaskEdit->EditText);
	}
	if (LessCheckBox->Checked) {
		LESSNUM = StrToInt(LessMaskEdit->EditText);
	}
	if (LargeCheckBox->Checked && LessCheckBox->Checked) {
		for (int z = 0; z < ZX; ++z) {
			for (int i = 0; i < TX; ++i) {
				for (int j = 0; j < RX; ++j) {
					Nodetmp = IntToStr(array3D[z][i][j]);
					EnableColor =
						(array3D[z][i][j] > LARGENUM && array3D[z][i][j] <
						LESSNUM);
					if (EnableColor) {
						RichEdit1->SelStart = RichEdit1->GetTextLen();
						RichEdit1->SelLength = 0;
						RichEdit1->SelAttributes->Color = clBlue;
					}
					RichEdit1->SelStart = RichEdit1->GetTextLen();
					RichEdit1->SelText = Nodetmp + " ";
					if (EnableColor) {
						RichEdit1->SelStart = RichEdit1->GetTextLen();
						RichEdit1->SelLength = 0;
						RichEdit1->SelAttributes->Color = defaultcolor;
					}
				}
				RichEdit1->SelStart = RichEdit1->GetTextLen();
				RichEdit1->SelText = "\r\n";
				Application->ProcessMessages();
			}
			RichEdit1->SelStart = RichEdit1->GetTextLen();
			RichEdit1->SelText = "\r\n";
			if (StopFlag == 1) {
				break;
			}
		}
	}
	else if (LargeCheckBox->Checked) {
		for (int z = 0; z < ZX; ++z) {
			for (int i = 0; i < TX; ++i) {
				for (int j = 0; j < RX; ++j) {
					Nodetmp = IntToStr(array3D[z][i][j]);
					EnableColor = (array3D[z][i][j] > LARGENUM);
					if (EnableColor) {
						RichEdit1->SelStart = RichEdit1->GetTextLen();
						RichEdit1->SelLength = 0;
						RichEdit1->SelAttributes->Color = clRed;
					}
					RichEdit1->SelStart = RichEdit1->GetTextLen();
					RichEdit1->SelText = Nodetmp + " ";
					if (EnableColor) {
						RichEdit1->SelStart = RichEdit1->GetTextLen();
						RichEdit1->SelLength = 0;
						RichEdit1->SelAttributes->Color = defaultcolor;
					}
				}
				RichEdit1->SelStart = RichEdit1->GetTextLen();
				RichEdit1->SelText = "\r\n";
				Application->ProcessMessages();
			}
			RichEdit1->SelStart = RichEdit1->GetTextLen();
			RichEdit1->SelText = "\r\n";
			if (StopFlag == 1) {
				break;
			}
		}
	}
	else if (LessCheckBox->Checked) {
		for (int z = 0; z < ZX; ++z) {
			for (int i = 0; i < TX; ++i) {
				for (int j = 0; j < RX; ++j) {
					Nodetmp = IntToStr(array3D[z][i][j]);
					EnableColor = (array3D[z][i][j] < LESSNUM);
					if (EnableColor) {
						RichEdit1->SelStart = RichEdit1->GetTextLen();
						RichEdit1->SelLength = 0;
						RichEdit1->SelAttributes->Color = clGreen;
					}
					RichEdit1->SelStart = RichEdit1->GetTextLen();
					RichEdit1->SelText = Nodetmp + " ";
					if (EnableColor) {
						RichEdit1->SelStart = RichEdit1->GetTextLen();
						RichEdit1->SelLength = 0;
						RichEdit1->SelAttributes->Color = defaultcolor;
					}
				}
				RichEdit1->SelStart = RichEdit1->GetTextLen();
				RichEdit1->SelText = "\r\n";
				Application->ProcessMessages();
			}
			RichEdit1->SelStart = RichEdit1->GetTextLen();
			RichEdit1->SelText = "\r\n";
			if (StopFlag == 1) {
				break;
			}
		}
	}
	RecoveryButton->Caption = SaveName;
	MARKFLAG = 1;
	StopFlag = 0;
	MarkButton->Enabled = true;
}

// ---------------------------------------------------------------------------

void __fastcall TForm1::RecoveryButtonClick(TObject *Sender) {
	if (RecoveryButton->Caption.Compare(Stop) == 0) {
		StopFlag = 1;
	}
	else {
		RichEdit1->Text = TotalString;
		RecoveryButton->Enabled = false;
		MARKFLAG = 0;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::D3ButtonClick(TObject *Sender) {
	try {
		Form2 = new TForm2(Application);
		// Form2->ShowModal();
		Form2->Show();
		// delete Form2;
	}
	catch (Exception &exception) {
		delete Form2;
		Application->ShowException(&exception);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::PageMaskEditMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y) {
	if (Jump->Enabled == false)
		return;
	int JumpPage = StrToInt(PageMaskEdit->EditText);
	if (Button == mbLeft) {
		JumpPage++;
	}
	else if (Button == mbRight) {
		JumpPage--;
	}
	if (JumpPage > ZX) {
		JumpPage = 0;
	}
	else if (JumpPage < 0) {
		JumpPage = ZX;
	}
	JumptoPage(JumpPage);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::JumptoPage(int JumpPage) {
	PageMaskEdit->EditText = GetZeroString(JumpPage);
	RichEdit1->SetFocus();
	RichEdit1->SelStart = RichEdit1->Perform(EM_LINEINDEX,
		JumpPage * (TX + 1), (NativeInt)0);
}

// ---------------------------------------------------------------------------
