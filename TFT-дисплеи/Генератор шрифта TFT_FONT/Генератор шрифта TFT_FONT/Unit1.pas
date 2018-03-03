unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, Menus;

type
  TForm1 = class(TForm)
    Image1: TImage;
    Memo2: TMemo;
    GroupBox1: TGroupBox;
    Image2: TImage;
    Button1: TButton;
    FontDialog: TFontDialog;
    Button2: TButton;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Button3: TButton;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  FONT_SIZE: Byte;
  FONT_NAME: string;
  MAX_X, MAX_Y: WORD;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var
 A, X, Y, Z: word;
 ch: byte;
 Total: word;
 str: string;

begin

   Image1.Canvas.Brush.Color := clCream;
   Image1.Canvas.FillRect(Image1.Canvas.ClipRect);

   Image1.Canvas.Font := FontDialog.Font;
   
   X := 0;
   Y := 0;
   for A := 0 to 255 do
   begin

     //Image1.Canvas.Rectangle(X - 1 , Y - 1, X + Image1.Canvas.TextWidth(char(A)) + 1, Y + Image1.Canvas.TextHeight(char(A)) + 1);
     Image1.Canvas.TextOut(x, y, char(a));
      //GetGlyphOutline
     X := X + Image1.Canvas.TextWidth(char(A));

     if X + MAX_X > 700 then
     begin
       Y := Y + Image1.Canvas.TextHeight(char(A)) + 5;
       X := 0;
     end;
   end;

   Image2.Canvas.Font := FontDialog.Font;


   Image2.Canvas.Brush.Style := bsClear; // область вывода текста не закраши-
   //#define FONT_HEIGHT 13
   //Начало const unsigned short Tahoma8[][14] =
    memo2.Lines.Add(' ');
    memo2.Lines.Add(' ');
    memo2.Lines.Add(' ');
    memo2.Lines.Add('//FONT GENERATION V1.0 CODE by OXFORD 2016');
    memo2.Lines.Add('#define FONT_HEIGHT  ' + inttostr(MAX_Y) + ' //ВЫСОТА');
    memo2.Lines.Add('#define FONT_NAME  ' + FONT_NAME + ' //НАЗВАНИЕ ШРИФТА');
    memo2.Lines.Add(' ');
    memo2.Lines.Add('const unsigned short FONT_NAME[] ['+ inttostr(MAX_Y + 1) + '] = {');
    memo2.Lines.Add(' ');
   for A := 0 to 255 do
   begin
    Image2.Canvas.Brush.Color := clFuchsia;
    Image2.Canvas.FillRect(Canvas.ClipRect);

    Image2.Canvas.Rectangle(-1 , -1, Image2.Canvas.TextWidth(char(A)) + 1, Image2.Canvas.TextHeight(char(A)) + 1);

Image2.Canvas.TextOut(0, 0, char(A));


    Image2.Canvas.textOut(0, 0, char(A));
    application.ProcessMessages;
   // sleep(500);
    Total := 0;
    str := '{';
    for Y := 0 to Image2.Canvas.TextHeight(char(A)) - 1  do
    begin
      Total := 0;
      for X := 0 to Image2.Canvas.TextWidth(char(A)) - 1 do
      begin
          if Image2.Canvas.Pixels[X, Y] <> clFuchsia then
          begin
            Total := Total or (1 shl X);
          end;
      end;
      str := str + '0x' + IntToHex(Total, 4) + ',';
    end;
    if A = 255 then
    str := str + '0x' + IntToHex(Image2.Canvas.TextWidth(char(A)), 4) +'}};' else
    str := str + '0x' + IntToHex(Image2.Canvas.TextWidth(char(A)), 4) +'},';
    memo2.Lines.Add(str);
    application.ProcessMessages;
  end;
  memo2.Lines.SaveToFile(FONT_NAME + '.h');
end;

procedure TForm1.Button2Click(Sender: TObject);
var
 W: Word;
begin
 if  FontDialog.Execute then
 begin
    FONT_NAME := FontDialog.Font.Name;
    FONT_SIZE := FontDialog.Font.Size;
    MAX_X := 0;
    MAX_Y := 0;

    Image1.Canvas.Font := FontDialog.Font;

    //Поиск ширины и высоты максимальной
    for W := 0 to 255 do
    begin
      if MAX_X < Image1.Canvas.TextWidth(char(W)) then MAX_X := Image1.Canvas.TextWidth(char(W));
      if MAX_Y < Image1.Canvas.TextHeight(char(W)) then MAX_Y := Image1.Canvas.TextHeight(char(W));
    end;

    label4.Caption := FONT_NAME;

    for W := 0 to length(FONT_NAME) do
    begin
        if FONT_NAME[W] = ' ' then FONT_NAME[W] := '_';
    end;

    label5.Caption := IntToStr(FONT_SIZE);
    label6.Caption := IntToStr(MAX_Y);
    label8.Caption := IntToStr(MAX_X);
 end;

end;

end.
