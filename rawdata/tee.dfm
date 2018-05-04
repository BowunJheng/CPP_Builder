object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'TeeChart'
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
  object PreviousButton: TButton
    Left = 790
    Top = 480
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Previous'
    TabOrder = 0
    OnClick = PreviousButtonClick
  end
  object NextButton: TButton
    Left = 871
    Top = 480
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Next'
    TabOrder = 1
    OnClick = NextButtonClick
  end
  object TrackBar1: TTrackBar
    Left = 0
    Top = 480
    Width = 595
    Height = 45
    Anchors = [akLeft, akRight, akBottom]
    PageSize = 1
    TabOrder = 2
    OnChange = TrackBar1Change
  end
  object TeePageEdit: TEdit
    Left = 687
    Top = 480
    Width = 97
    Height = 27
    Anchors = [akRight, akBottom]
    Color = clSilver
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnMouseDown = TeePageEditMouseDown
  end
  object PlayStopButton: TButton
    Left = 656
    Top = 480
    Width = 25
    Height = 25
    Anchors = [akRight, akBottom]
    TabOrder = 4
    OnClick = PlayStopButtonClick
  end
  object TimeOutMaskEdit: TMaskEdit
    Left = 601
    Top = 482
    Width = 47
    Height = 21
    Anchors = [akRight, akBottom]
    EditMask = '9999 ms;0;0'
    MaxLength = 7
    TabOrder = 5
    Text = ' 1'
  end
  object Chart1: TChart
    Left = 0
    Top = 0
    Width = 952
    Height = 474
    AllowPanning = pmNone
    BackWall.Brush.Gradient.Direction = gdBottomTop
    BackWall.Brush.Gradient.EndColor = clWhite
    BackWall.Brush.Gradient.StartColor = 15395562
    BackWall.Brush.Gradient.Visible = True
    BackWall.Transparent = False
    BackWall.Visible = False
    BottomWall.Visible = False
    Foot.Font.Name = 'Verdana'
    Gradient.Direction = gdBottomTop
    Gradient.EndColor = clWhite
    Gradient.MidColor = 15395562
    Gradient.StartColor = 15395562
    Gradient.Visible = True
    LeftWall.Color = 14745599
    LeftWall.Visible = False
    Legend.Font.Name = 'Verdana'
    Legend.Visible = False
    RightWall.Color = 14745599
    SubFoot.Font.Name = 'Verdana'
    SubTitle.Font.Name = 'Verdana'
    Title.Font.Name = 'Verdana'
    Title.Text.Strings = (
      'Ilitek')
    BottomAxis.Axis.Color = 4210752
    BottomAxis.Grid.Color = 11119017
    BottomAxis.LabelsFont.Name = 'Verdana'
    BottomAxis.TicksInner.Color = 11119017
    BottomAxis.Title.Font.Name = 'Verdana'
    BottomAxis.Title.Visible = False
    Chart3DPercent = 62
    DepthAxis.Axis.Color = 4210752
    DepthAxis.Grid.Color = 11119017
    DepthAxis.LabelsFont.Name = 'Verdana'
    DepthAxis.TicksInner.Color = 11119017
    DepthAxis.Title.Font.Name = 'Verdana'
    DepthAxis.Title.Visible = False
    DepthAxis.Visible = True
    DepthTopAxis.Axis.Color = 4210752
    DepthTopAxis.Grid.Color = 11119017
    DepthTopAxis.LabelsFont.Name = 'Verdana'
    DepthTopAxis.TicksInner.Color = 11119017
    DepthTopAxis.Title.Font.Name = 'Verdana'
    DepthTopAxis.Title.Visible = False
    DepthTopAxis.Visible = True
    LeftAxis.Axis.Color = 4210752
    LeftAxis.Grid.Color = 11119017
    LeftAxis.LabelsFont.Name = 'Verdana'
    LeftAxis.TicksInner.Color = 11119017
    LeftAxis.Title.Font.Name = 'Verdana'
    LeftAxis.Title.Visible = False
    RightAxis.Axis.Color = 4210752
    RightAxis.Grid.Color = 11119017
    RightAxis.LabelsFont.Name = 'Verdana'
    RightAxis.TicksInner.Color = 11119017
    RightAxis.Title.Font.Name = 'Verdana'
    RightAxis.Title.Visible = False
    TopAxis.Axis.Color = 4210752
    TopAxis.Grid.Color = 11119017
    TopAxis.LabelsFont.Name = 'Verdana'
    TopAxis.TicksInner.Color = 11119017
    TopAxis.Title.Font.Name = 'Verdana'
    TopAxis.Title.Visible = False
    View3DOptions.Orthogonal = False
    View3DOptions.Zoom = 75
    View3DWalls = False
    Align = alTop
    ParentShowHint = False
    ShowHint = True
    TabOrder = 6
    OnMouseMove = Chart1MouseMove
    OnMouseWheel = Chart1MouseWheel
    DefaultCanvas = 'TGDIPlusCanvas'
    PrintMargins = (
      15
      25
      15
      25)
    ColorPaletteIndex = 13
    object GroupBox1: TGroupBox
      Left = 0
      Top = 360
      Width = 89
      Height = 114
      Caption = 'Trigger'
      TabOrder = 0
    end
    object Series1: TSurfaceSeries
      HorizAxis = aBothHorizAxis
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Emboss.Color = 8487297
      Marks.Shadow.Color = 8553090
      Marks.ShapeStyle = fosRoundRectangle
      Marks.Style = smsPercent
      Marks.Visible = False
      ShowInLegend = False
      VertAxis = aBothVertAxis
      SideBrush.Color = clWhite
      SideBrush.Style = bsClear
      UseColorRange = False
      UsePalette = True
      XValues.Name = 'X'
      XValues.Order = loNone
      YValues.Name = 'Y'
      YValues.Order = loNone
      ZValues.Name = 'Z'
      ZValues.Order = loNone
    end
    object ChartTool1: TRotateTool
      Pen.Color = clWhite
      Pen.Mode = pmXor
    end
  end
  object LargeCheckBox: TCheckBox
    Left = 8
    Top = 374
    Width = 75
    Height = 30
    Caption = 'Large than'
    TabOrder = 7
  end
  object LessCheckBox: TCheckBox
    Left = 8
    Top = 432
    Width = 75
    Height = 17
    Caption = 'Less than'
    TabOrder = 8
  end
  object LargeMaskEdit: TMaskEdit
    Left = 48
    Top = 402
    Width = 35
    Height = 24
    EditMask = '9999;0;0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    MaxLength = 4
    ParentFont = False
    TabOrder = 9
    Text = ' 128'
  end
  object LessMaskEdit: TMaskEdit
    Left = 48
    Top = 450
    Width = 33
    Height = 24
    EditMask = '9999;0;0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    MaxLength = 4
    ParentFont = False
    TabOrder = 10
    Text = ' 128'
  end
end
