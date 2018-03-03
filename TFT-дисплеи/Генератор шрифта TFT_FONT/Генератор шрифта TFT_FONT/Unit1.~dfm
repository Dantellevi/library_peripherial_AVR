object Form1: TForm1
  Left = 144
  Top = 32
  Width = 1071
  Height = 861
  Caption = 'FONT GENERATION V1.0 CODE by OXFORD 2016   '
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 8
    Top = 8
    Width = 800
    Height = 400
  end
  object Image2: TImage
    Left = 832
    Top = 8
    Width = 105
    Height = 105
  end
  object Memo2: TMemo
    Left = 8
    Top = 424
    Width = 1025
    Height = 369
    Lines.Strings = (
      
        '//short BUF_CHAR[255]; //'#1041#1091#1092#1077#1088' '#1076#1083#1103' '#1089#1080#1084#1074#1086#1083#1072', '#1074#1099#1074#1086#1076#1080#1090#1089#1103' '#1077#1076#1080#1085#1099#1084' '#1087#1086#1090 +
        #1086#1082#1086#1084' '#1085#1072' '#1101#1082#1088#1072#1085
      
        '// uint8_t ASCII - '#1089#1080#1084#1074#1086#1083' '#1082#1086#1090#1086#1088#1099#1081' '#1085#1091#1078#1085#1086' '#1085#1072#1087#1077#1095#1072#1090#1072#1090#1100', '#1087#1077#1088#1077#1076#1072#1077#1090#1089#1103' '#1082 +
        #1072#1082' '#1077#1089#1090#1100
      '// FONT_HEIGHT - '#1042#1099#1089#1086#1090#1072' '#1096#1088#1080#1092#1090#1072' ('#1075#1077#1085#1077#1088#1080#1088#1091#1077#1090#1089#1103' '#1076#1077#1092#1072#1081#1085#1086#1084')'
      '// FONT_NAME - '#1048#1084#1103' '#1096#1088#1080#1092#1090#1072' ('#1075#1077#1085#1077#1088#1080#1088#1091#1077#1090#1089' '#1076#1077#1092#1072#1081#1085#1086#1084')'
      '//'
      '/*'
      
        'void GUI_CHAR_OUT(uint8_t ASCII, uint16_t X_POS, uint16_t Y_POS,' +
        ' uint16_t FONT_COLOR, uint16_t BACK_COLOR)'
      '{'
      #9'uint16_t X, Y;'
      #9'char CHAR_WIDTH = FONT_NAME[ASCII][FONT_HEIGHT];'
      #9'short INDEX = 0;'
      ''
      '    for (Y = 0; Y < FONT_HEIGHT; Y++ ) {'
      ''
      '        for(X = 0; X < CHAR_WIDTH; X++)'
      '        {'
      '        '#9'unsigned short temp = FONT_NAME[ASCII][Y];'
      '            if((temp >> X) & 0x01)'
      '            {'
      '            '#9'BUF_CHAR[INDEX] = BACK_COLOR;'
      '            } else'
      '            {'
      '            '#9'BUF_CHAR[INDEX] = FONT_COLOR;'
      '            }'
      '            INDEX ++;'
      '        }'
      '    }'
      #9#9
      #9
      '  TFT_CS_LOW;'
      
        #9'TFT_AREA(X_POS, X_POS + CHAR_WIDTH - 1, Y_POS,  Y_POS + FONT_HE' +
        'IGHT - 1);'
      #9'TFT_DC_HIGH;'
      '  TFT_OUT_CHAR(CHAR_WIDTH * FONT_HEIGHT, (uint32_t) &BUF_CHAR);'#9
      #9'TFT_CS_HIGH;'
      '}'
      '*/')
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object GroupBox1: TGroupBox
    Left = 832
    Top = 120
    Width = 209
    Height = 289
    Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 45
      Height = 13
      Caption = #1064#1056#1048#1060#1058':'
    end
    object Label2: TLabel
      Left = 8
      Top = 45
      Width = 48
      Height = 13
      Caption = #1056#1040#1047#1052#1045#1056':'
    end
    object Label3: TLabel
      Left = 8
      Top = 69
      Width = 85
      Height = 13
      Caption = #1052#1040#1050#1057' '#1042#1067#1057#1054#1058#1040':'
    end
    object Label4: TLabel
      Left = 64
      Top = 24
      Width = 63
      Height = 13
      Caption = #1053#1077' '#1074#1099#1073#1088#1072#1085
    end
    object Label5: TLabel
      Left = 64
      Top = 45
      Width = 7
      Height = 13
      Caption = '0'
    end
    object Label6: TLabel
      Left = 104
      Top = 69
      Width = 7
      Height = 13
      Caption = '0'
    end
    object Label7: TLabel
      Left = 8
      Top = 93
      Width = 88
      Height = 13
      Caption = #1052#1040#1050#1057' '#1064#1048#1056#1048#1053#1040':'
    end
    object Label8: TLabel
      Left = 104
      Top = 93
      Width = 7
      Height = 13
      Caption = '0'
    end
    object Label9: TLabel
      Left = 8
      Top = 136
      Width = 7
      Height = 13
      Caption = '1'
    end
    object Label10: TLabel
      Left = 8
      Top = 184
      Width = 7
      Height = 13
      Caption = '2'
    end
    object Label11: TLabel
      Left = 24
      Top = 248
      Width = 123
      Height = 26
      Caption = #1042' '#1054#1057' '#1086#1090#1082#1083#1102#1095#1080#1090#1100' '#1072#1085#1090#1080#1083#1080#1079#1080#1085#1075' '#1096#1088#1080#1092#1090#1086#1074'.'
      WordWrap = True
    end
    object Button1: TButton
      Left = 32
      Top = 176
      Width = 153
      Height = 25
      Caption = #1057#1086#1079#1076#1072#1090#1100' '#1092#1072#1081#1083
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 32
      Top = 128
      Width = 153
      Height = 25
      Caption = #1042#1099#1073#1088#1072#1090#1100' '#1096#1088#1080#1092#1090
      TabOrder = 1
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 24
      Top = 216
      Width = 169
      Height = 25
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1088#1077#1076#1072#1082#1090#1086#1088
      TabOrder = 2
    end
  end
  object FontDialog: TFontDialog
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Device = fdBoth
    Options = []
    Left = 952
    Top = 24
  end
end
