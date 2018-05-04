object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Record & Replay'
  ClientHeight = 513
  ClientWidth = 952
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    952
    513)
  PixelsPerInch = 96
  TextHeight = 13
  object LoadTextFile: TButton
    Left = 869
    Top = 16
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'LoadTextFile'
    TabOrder = 0
    OnClick = LoadTextFileClick
  end
  object RichEdit1: TRichEdit
    Left = 0
    Top = 0
    Width = 857
    Height = 513
    Align = alLeft
    Anchors = [akLeft, akTop, akRight, akBottom]
    Font.Charset = CHINESEBIG5_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Lines.Strings = (
      '')
    ParentFont = False
    PopupMenu = PopupMenu1
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 1
    Zoom = 100
    OnKeyDown = RichEdit1KeyDown
  end
  object PageMaskEdit: TMaskEdit
    Left = 863
    Top = 112
    Width = 42
    Height = 27
    Anchors = [akTop, akRight]
    EditMask = '9999;0;0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    MaxLength = 4
    ParentFont = False
    TabOrder = 2
    Text = ''
    OnMouseDown = PageMaskEditMouseDown
  end
  object Jump: TButton
    Left = 869
    Top = 145
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Jump 10%'
    Enabled = False
    TabOrder = 3
    OnClick = JumpClick
  end
  object PageEdit: TEdit
    Left = 906
    Top = 112
    Width = 42
    Height = 27
    Anchors = [akTop, akRight]
    Color = clActiveBorder
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    TabOrder = 4
  end
  object LargeCheckBox: TCheckBox
    Left = 863
    Top = 200
    Width = 79
    Height = 17
    Anchors = [akTop, akRight]
    Caption = 'Large than'
    TabOrder = 5
    OnClick = LargeCheckBoxClick
  end
  object LessCheckBox: TCheckBox
    Left = 863
    Top = 256
    Width = 70
    Height = 17
    Anchors = [akTop, akRight]
    Caption = 'Less than'
    TabOrder = 6
    OnClick = LargeCheckBoxClick
  end
  object LargeMaskEdit: TMaskEdit
    Left = 896
    Top = 223
    Width = 41
    Height = 27
    Anchors = [akTop, akRight]
    EditMask = '9999;0;0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    MaxLength = 4
    ParentFont = False
    TabOrder = 7
    Text = ' 128'
  end
  object LessMaskEdit: TMaskEdit
    Left = 896
    Top = 279
    Width = 41
    Height = 27
    Anchors = [akTop, akRight]
    EditMask = '9999;0;0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    MaxLength = 4
    ParentFont = False
    TabOrder = 8
    Text = ' 128'
  end
  object MarkButton: TButton
    Left = 869
    Top = 312
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Mark'
    Enabled = False
    TabOrder = 9
    OnClick = MarkButtonClick
  end
  object ZoomAButton: TButton
    Left = 863
    Top = 64
    Width = 42
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Zoom+'
    Enabled = False
    TabOrder = 10
    OnClick = ZoomAButtonClick
  end
  object ZoomBButton: TButton
    Left = 906
    Top = 64
    Width = 42
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Zoom-'
    Enabled = False
    TabOrder = 11
    OnClick = ZoomBButtonClick
  end
  object RecoveryButton: TButton
    Left = 869
    Top = 343
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Recovery'
    Enabled = False
    TabOrder = 12
    OnClick = RecoveryButtonClick
  end
  object D3Button: TButton
    Left = 869
    Top = 472
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = '3D'
    Enabled = False
    TabOrder = 13
    OnClick = D3ButtonClick
  end
  object OpenTextFileDialog1: TOpenTextFileDialog
    DefaultExt = 'txt'
    Filter = 'Text File (*.TXT)|*.txt|Any File (*.*)|*.*'
    Left = 608
    Top = 16
  end
  object PopupMenu1: TPopupMenu
    Left = 680
    Top = 16
    object Undo1: TMenuItem
      Caption = 'Undo'
      OnClick = Undo1Click
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object Cut1: TMenuItem
      Caption = 'Cut'
      Enabled = False
      OnClick = Cut1Click
    end
    object Copy1: TMenuItem
      Caption = 'Copy'
      OnClick = Copy1Click
    end
    object Paste1: TMenuItem
      Caption = 'Paste'
      Enabled = False
      OnClick = Paste1Click
    end
    object Delete1: TMenuItem
      Caption = 'Delete'
      Enabled = False
      OnClick = Delete1Click
    end
    object N2: TMenuItem
      Caption = '-'
    end
    object SelectAll1: TMenuItem
      Caption = 'Select All'
      OnClick = SelectAll1Click
    end
  end
end
