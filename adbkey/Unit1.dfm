object Form1: TForm1
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'adbUI'
  ClientHeight = 305
  ClientWidth = 874
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Scaled = False
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object RepeatEdit: TMaskEdit
    Left = 54
    Top = 61
    Width = 48
    Height = 53
    EditMask = '!90;1;_'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -37
    Font.Name = 'Tahoma'
    Font.Style = []
    MaxLength = 2
    ParentFont = False
    TabOrder = 0
    Text = '01'
  end
  object Button_up: TButton
    Tag = 19
    Left = 54
    Top = 8
    Width = 48
    Height = 48
    Caption = #9608
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -96
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = Button_Click
  end
  object Button_left: TButton
    Tag = 21
    Left = 4
    Top = 62
    Width = 48
    Height = 48
    Caption = #9608
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -96
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = Button_Click
  end
  object Button_right: TButton
    Tag = 22
    Left = 105
    Top = 62
    Width = 48
    Height = 48
    Caption = #9608
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -96
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = Button_Click
  end
  object Button_down: TButton
    Tag = 20
    Left = 54
    Top = 115
    Width = 48
    Height = 48
    Caption = #9608
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -96
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = Button_Click
  end
  object ButtonFocus: TButton
    Left = 162
    Top = 109
    Width = 50
    Height = 25
    Caption = 'GetFocus'
    TabOrder = 5
    OnClick = ButtonFocusClick
  end
  object ButtonUnlock: TButton
    Tag = 82
    Left = 161
    Top = 78
    Width = 50
    Height = 25
    Caption = 'UnLock'
    TabOrder = 6
    OnClick = Button1StepClick
  end
  object ButtonEnter: TButton
    Tag = 66
    Left = 162
    Top = 170
    Width = 50
    Height = 25
    Caption = 'Enter'
    TabOrder = 7
    OnClick = Button1StepClick
  end
  object ComboBoxKey: TComboBox
    Left = 161
    Top = 8
    Width = 240
    Height = 27
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 8
  end
  object ButtonInput: TButton
    Left = 162
    Top = 39
    Width = 239
    Height = 25
    Caption = 'InputSelect'
    TabOrder = 9
    OnClick = ButtonInputClick
  end
  object ButtonBack: TButton
    Tag = 4
    Left = 161
    Top = 140
    Width = 50
    Height = 25
    Caption = 'Back'
    TabOrder = 10
    OnClick = Button1StepClick
  end
  object ButtonInfo: TButton
    Left = 283
    Top = 108
    Width = 25
    Height = 25
    Hint = 'information'
    Caption = 'Info'
    TabOrder = 11
    OnClick = Button1StepAPKClck
  end
  object CheckBoxfae: TCheckBox
    Left = 4
    Top = 164
    Width = 42
    Height = 17
    Caption = 'FAE'
    TabOrder = 12
  end
  object ButtonUtil: TButton
    Left = 283
    Top = 139
    Width = 25
    Height = 25
    Hint = 'Utility'
    Caption = 'Util'
    TabOrder = 13
    OnClick = Button1StepAPKClck
  end
  object ButtonX: TButton
    Left = 314
    Top = 78
    Width = 25
    Height = 25
    Hint = 'xpowerbar'
    Caption = 'X'
    TabOrder = 14
    OnClick = Button1StepAPKClck
  end
  object ButtonY: TButton
    Left = 314
    Top = 108
    Width = 25
    Height = 25
    Hint = 'ypowerbar'
    Caption = 'Y'
    TabOrder = 15
    OnClick = Button1StepAPKClck
  end
  object ButtonAllX: TButton
    Left = 314
    Top = 139
    Width = 25
    Height = 25
    Hint = 'xallpoint'
    Caption = 'AllX'
    TabOrder = 16
    OnClick = Button1StepAPKClck
  end
  object ButtonAllY: TButton
    Left = 314
    Top = 170
    Width = 25
    Height = 25
    Hint = 'yallpoint'
    Caption = 'AllY'
    TabOrder = 17
    OnClick = Button1StepAPKClck
  end
  object ButtonK: TButton
    Left = 345
    Top = 77
    Width = 25
    Height = 25
    Hint = 'calibrate'
    Caption = 'K'
    TabOrder = 18
    OnClick = Button1StepAPKClck
  end
  object ButtonBL: TButton
    Left = 376
    Top = 78
    Width = 25
    Height = 25
    Hint = 'blmode'
    Caption = 'BL'
    TabOrder = 19
    OnClick = Button1StepAPKClck
  end
  object ButtonAP: TButton
    Left = 376
    Top = 109
    Width = 25
    Height = 25
    Hint = 'apmode'
    Caption = 'AP'
    TabOrder = 20
    OnClick = Button1StepAPKClck
  end
  object ButtonEBG: TButton
    Left = 345
    Top = 108
    Width = 25
    Height = 25
    Hint = 'erasebackground'
    Caption = 'EBG'
    TabOrder = 21
    OnClick = Button1StepAPKClck
  end
  object ButtonReset: TButton
    Left = 376
    Top = 138
    Width = 25
    Height = 25
    Hint = 'reset'
    Caption = 'Rst'
    TabOrder = 22
    OnClick = Button1StepAPKClck
  end
  object ButtonReboot: TButton
    Left = 217
    Top = 78
    Width = 50
    Height = 25
    Caption = 'Reboot'
    TabOrder = 23
    OnClick = ButtonRebootClick
  end
  object EditCMD: TEdit
    Left = 4
    Top = 262
    Width = 397
    Height = 33
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 24
    OnKeyPress = EditCMDKeyPress
  end
  object StringGridHistory: TStringGrid
    Left = 584
    Top = 0
    Width = 290
    Height = 305
    Align = alRight
    ColCount = 2
    DefaultColWidth = 40
    FixedColor = clWindow
    RowCount = 12
    ScrollBars = ssNone
    TabOrder = 25
    OnDblClick = StringGridHistoryDblClick
    OnMouseDown = StringGridHistoryMouseDown
    ColWidths = (
      40
      252)
    RowHeights = (
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24)
  end
  object ListBoxScript: TListBox
    Left = 407
    Top = 8
    Width = 171
    Height = 253
    ItemHeight = 13
    TabOrder = 26
    OnDblClick = ListBoxScriptDblClick
    OnDragDrop = ListBoxScriptDragDrop
    OnDragOver = ListBoxScriptDragOver
  end
  object ButtonScript: TButton
    Left = 448
    Top = 267
    Width = 89
    Height = 30
    Caption = 'Run Script'
    Enabled = False
    TabOrder = 27
    OnClick = ButtonScriptClick
  end
  object CheckBoxTCPIP: TCheckBox
    Left = 4
    Top = 180
    Width = 50
    Height = 17
    Caption = 'IP'
    TabOrder = 28
  end
  object MaskEditIP: TMaskEdit
    Left = 36
    Top = 178
    Width = 122
    Height = 21
    EditMask = '!099.099.099.099:9999;1;'
    MaxLength = 20
    TabOrder = 29
    Text = '192.168.007.071:5555'
    OnExit = MaskEditIPExit
  end
  object ButtonMain: TButton
    Left = 283
    Top = 77
    Width = 25
    Height = 25
    Hint = 'mainpage'
    Caption = 'Main'
    TabOrder = 30
    OnClick = Button1StepAPKClck
  end
  object EditPath: TEdit
    Left = 87
    Top = 203
    Width = 154
    Height = 21
    TabOrder = 31
    Text = '/sdcard/'
  end
  object CheckBoxPath: TCheckBox
    Left = 4
    Top = 205
    Width = 81
    Height = 17
    Caption = 'Default Path'
    Checked = True
    State = cbChecked
    TabOrder = 32
    OnClick = CheckBoxPathClick
  end
  object ButtonSetFile: TButton
    Left = 247
    Top = 201
    Width = 154
    Height = 23
    Caption = 'hex File'
    TabOrder = 33
    OnClick = ButtonSetFileClick
  end
  object ButtonPerm: TButton
    Tag = 1
    Left = 217
    Top = 109
    Width = 50
    Height = 25
    Caption = 'SetPerm.'
    TabOrder = 34
    OnClick = ButtonRebootClick
  end
  object ButtonBurn: TButton
    Tag = 2
    Left = 4
    Top = 230
    Width = 397
    Height = 25
    Hint = 'upgrade'
    Caption = 'Upgrade Firmware'
    Enabled = False
    TabOrder = 35
    OnClick = Button1StepAPKClck
  end
  object OpenDialog1: TOpenDialog
    Filter = 'HEX|*.hex'
    Left = 240
    Top = 152
  end
end
