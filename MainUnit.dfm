object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'SoftCube'
  ClientHeight = 446
  ClientWidth = 788
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  OnCloseQuery = FormCloseQuery
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object MainStatusBar: TStatusBar
    Left = 0
    Top = 430
    Width = 788
    Height = 16
    Panels = <>
    SimplePanel = True
    SimpleText = #1055#1088#1086#1089#1090#1086#1081
  end
  object MainPageControl: TPageControl
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 782
    Height = 424
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = #1056#1077#1084#1086#1085#1090
      DesignSize = (
        774
        396)
      object MainDBGrid: TDBGrid
        AlignWithMargins = True
        Left = 0
        Top = 36
        Width = 774
        Height = 360
        Margins.Left = 0
        Margins.Top = 36
        Margins.Right = 0
        Margins.Bottom = 0
        Align = alClient
        BorderStyle = bsNone
        DataSource = OrdersTabDS
        DefaultDrawing = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        Options = [dgTitles, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
        ParentFont = False
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        OnDrawColumnCell = MainDBGridDrawColumnCell
        OnDblClick = MainDBGridDblClick
        OnTitleClick = MainDBGridTitleClick
        Columns = <
          item
            Alignment = taCenter
            Expanded = False
            FieldName = 'OrdNum'
            Title.Alignment = taCenter
            Title.Caption = #8470' '#1079#1072#1082#1072#1079#1072
            Width = 60
            Visible = True
          end
          item
            Alignment = taCenter
            Expanded = False
            FieldName = 'DevStatusStr'
            Title.Alignment = taCenter
            Title.Caption = #1057#1086#1089#1090#1086#1103#1085#1080#1077
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'OwnName'
            Title.Alignment = taCenter
            Title.Caption = #1047#1072#1082#1072#1079#1095#1080#1082
            Width = 170
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'DevModel'
            Title.Alignment = taCenter
            Title.Caption = #1059#1089#1090#1088#1086#1081#1089#1090#1074#1086
            Width = 220
            Visible = True
          end
          item
            Alignment = taCenter
            Expanded = False
            FieldName = 'OwnTel'
            Title.Alignment = taCenter
            Title.Caption = #1058#1077#1083'.'#1047#1072#1082#1072#1079#1095#1080#1082#1072
            Width = 120
            Visible = True
          end
          item
            Alignment = taCenter
            Expanded = False
            FieldName = 'DateIn'
            Title.Alignment = taCenter
            Title.Caption = #1044#1072#1090#1072' '#1087#1088#1080#1077#1084#1072
            Width = 80
            Visible = True
          end>
      end
      object NewOrdButton: TButton
        Left = 644
        Top = 1
        Width = 127
        Height = 25
        Anchors = [akTop, akRight]
        Caption = #1053#1086#1074#1099#1081' '#1079#1072#1082#1072#1079
        TabOrder = 1
        OnClick = NewOrdButtonClick
      end
      object SearchEdit: TEdit
        Left = 3
        Top = 3
        Width = 635
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 2
        OnKeyPress = SearchEditKeyPress
      end
    end
    object Торговля: TTabSheet
      Caption = #1058#1086#1088#1075#1086#1074#1083#1103
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
    end
  end
  object MainMenu: TMainMenu
    Left = 728
    Top = 368
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083
    end
    object N2: TMenuItem
      Caption = #1055#1088#1072#1074#1082#1072
    end
    object N3: TMenuItem
      Caption = #1042#1080#1076
      object N6: TMenuItem
        Caption = #1055#1086#1082#1072#1079#1099#1074#1072#1090#1100' '#1074#1099#1076#1072#1085#1085#1099#1077' '#1079#1072#1082#1072#1079#1099
        OnClick = N6Click
      end
    end
    object N4: TMenuItem
      Caption = #1048#1085#1089#1090#1088#1091#1084#1077#1085#1090#1099
    end
    object N5: TMenuItem
      Caption = #1054#1090#1095#1077#1090#1099
    end
  end
  object MainADOConnection: TADOConnection
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 48
    Top = 264
  end
  object OrdersTab: TADOTable
    Connection = MainADOConnection
    CursorType = ctStatic
    TableName = 'OrdersTab'
    Left = 48
    Top = 310
    object OrdersTabOrdNum: TSmallintField
      FieldName = 'OrdNum'
    end
    object OrdersTabDevModel: TWideStringField
      FieldName = 'DevModel'
      Size = 64
    end
    object OrdersTabDevID: TWideStringField
      FieldName = 'DevID'
      Size = 32
    end
    object OrdersTabDevDefect: TWideStringField
      FieldName = 'DevDefect'
      Size = 128
    end
    object OrdersTabDevRem: TWideStringField
      FieldName = 'DevRem'
      Size = 128
    end
    object OrdersTabDevStatus: TWordField
      FieldName = 'DevStatus'
    end
    object OrdersTabItsWar: TBooleanField
      FieldName = 'ItsWar'
    end
    object OrdersTabDevResult: TWideMemoField
      FieldName = 'DevResult'
      BlobType = ftWideString
    end
    object OrdersTabItsNotif: TBooleanField
      FieldName = 'ItsNotif'
    end
    object OrdersTabOwnName: TWideStringField
      FieldName = 'OwnName'
      Size = 32
    end
    object OrdersTabOwnTel: TWideStringField
      FieldName = 'OwnTel'
      Size = 16
    end
    object OrdersTabMaxPrice: TSmallintField
      FieldName = 'MaxPrice'
    end
    object OrdersTabWorkPrice: TSmallintField
      FieldName = 'WorkPrice'
    end
    object OrdersTabDateIn: TDateTimeField
      FieldName = 'DateIn'
    end
    object OrdersTabDateOut: TDateTimeField
      FieldName = 'DateOut'
    end
    object OrdersTabDateWar: TDateTimeField
      FieldName = 'DateWar'
    end
    object OrdersTabDevStatusStr: TStringField
      FieldKind = fkLookup
      FieldName = 'DevStatusStr'
      LookupDataSet = StatusTab
      LookupKeyFields = 'StatusKey'
      LookupResultField = 'StatusShort'
      KeyFields = 'DevStatus'
      Size = 32
      Lookup = True
    end
  end
  object OrdersTabDS: TDataSource
    DataSet = OrdersTab
    Left = 112
    Top = 312
  end
  object StatusTab: TADOTable
    Connection = MainADOConnection
    CursorType = ctStatic
    TableName = 'StatusTab'
    Left = 48
    Top = 360
  end
end
