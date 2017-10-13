#include "font.h"

#define DDR_LCD DDRD
#define PORT_LCD PORTD
#define BL 6
#define RST 7
#define CS 2   //=CE
#define RS 3   //=DC
#define MOSI 4
#define SCK 5


#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	
#define GRAY1   0x8410      	
#define GRAY2   0x4208

#define PWMBacklight OCR2

void write_byte(unsigned char c,unsigned char com);
void Reset();
void TFTInit();
void WriteTwoByte(unsigned char LCD_DataH,unsigned char LCD_DataL);
void TFTSingleColor(unsigned int color);
void WriteChar8x11(unsigned char x0, unsigned char y0, unsigned char s, unsigned int color);
void WriteChar5x7(unsigned char x0,unsigned char y0,unsigned char s,unsigned int color);
void WriteString8x11(unsigned char x0,unsigned char y0,unsigned char *s,unsigned int color);
void WriteString5x7(unsigned char x0,unsigned char y0,unsigned char *s,unsigned int color);
void DrawLine(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned int color);
void DrawRectangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned int color, unsigned char fill);
void DrawCircle(unsigned char x0, unsigned char y0, unsigned char R, unsigned int color, unsigned char fill);
void DrawTriangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned int color, unsigned char fill);
void BacklightInit();

void BacklightInit()
{
  TCCR2|=(1<<CS20)|(1<<CS21)|(1<<CS22);
  CB(TCCR2,WGM20);
  CB(TCCR2,WGM21);
  CB(TCCR2,COM21);
  CB(TCCR2,COM20);
  PWMBacklight=250;
  TIMSK|=(1<<OCIE2)|(1<<TOIE2);
  TCNT2=0;
}

void write_byte(unsigned char c,unsigned char com)//0-command 1-data
{
  CB(PORT_LCD,CS);
  if(com==0)
    CB(PORT_LCD,RS);
  else
    SB(PORT_LCD,RS);
  SB(PORT_LCD,SCK);
  for(unsigned char i=0;i<8;i++)
  {
    if(((c>>(7-i))&1) == 1)
      SB(PORT_LCD,MOSI);
    else
      CB(PORT_LCD,MOSI);
    CB(PORT_LCD,SCK);
    SB(PORT_LCD,SCK);
  }
  SB(PORT_LCD,CS);
}
void Reset()
{
  CB(PORT_LCD,RST);
  delay_ms(1);
  SB(PORT_LCD,RST);
  delay_ms(1);
}

void TFTInit()
{
  SB(DDR_LCD,BL);
  SB(DDR_LCD,RST);
  SB(DDR_LCD,CS);
  SB(DDR_LCD,RS);
  SB(DDR_LCD,SCK);
  SB(DDR_LCD,MOSI);
  SB(PORT_LCD,BL);
  Reset();
  unsigned int i=0;
  write_byte(0xB9,0);//SETEXTC
  write_byte(0xFF,1);
  write_byte(0x83,1);
  write_byte(0x53,1);

  write_byte(0xB0,0);//RADJ
  write_byte(0x3C,1);
  write_byte(0x01,1);

  write_byte(0xB6,0);//VCOM
  write_byte(0x94,1);
  write_byte(0x6C,1);
  write_byte(0x50,1);

  write_byte(0xB1,0);//PWR
  write_byte(0x00,1);
  write_byte(0x01,1);
  write_byte(0x1B,1);
  write_byte(0x03,1);
  write_byte(0x01,1);
  write_byte(0x08,1);
  write_byte(0x77,1);
  write_byte(0x89,1);

  write_byte(0xE0,0); //Gamma setting for tpo Panel
  write_byte(0x50,1);
  write_byte(0x77,1);
  write_byte(0x40,1);
  write_byte(0x08,1);
  write_byte(0xBF,1);
  write_byte(0x00,1);
  write_byte(0x03,1);
  write_byte(0x0F,1);
  write_byte(0x00,1);
  write_byte(0x01,1);
  write_byte(0x73,1);
  write_byte(0x00,1);
  write_byte(0x72,1);
  write_byte(0x03,1);
  write_byte(0xB0,1);
  write_byte(0x0F,1);
  write_byte(0x08,1);
  write_byte(0x00,1);
  write_byte(0x0F,1);

  write_byte(0x3A,0);
  write_byte(0x05,1);  //05

  write_byte(0x36,0);
  write_byte(0xC0,1); //83  //0B

  write_byte(0x11,0); // SLPOUT
  delay_us(150);

  write_byte(0x29,0);    // display on
  delay_us(150);

  write_byte(0x2D,0);  //Look up table
  for(i=0;i<32;i++)
    write_byte(2*i,1); //Red
  for(i=0;i<64;i++)
    write_byte(1*i,1); //Green
  for(i=0;i<32;i++)
    write_byte(2*i,1); //Blue
	
  write_byte(0x2c,0);
  delay_us(150);	
}

void WriteTwoByte(unsigned char LCD_DataH,unsigned char LCD_DataL)
{
  write_byte(LCD_DataH,1);
  write_byte(LCD_DataL,1);
}

void OutColor(unsigned int color)
{
WriteTwoByte((color>>8),((color<<8)>>8));
}

void TFTSingleColor(unsigned int color)
{
  unsigned char i,j;
  for (i=0;i<160;i++)
    for (j=0;j<128;j++)
      OutColor(color);
}

void Area(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1)
{
  write_byte(0x2a,0);
  write_byte(0,1);
  write_byte(y0,1);
  write_byte(0,1);
  write_byte(y1,1);
  write_byte(0x2b,0);
  write_byte(0,1);
  write_byte(x0,1);
  write_byte(0,1);
  write_byte(x1,1);
  write_byte(0x2c,0);
}

void DrawPixel(unsigned char x0, unsigned char y0, unsigned int color)
{
  Area((160-x0),y0,(160-x0),y0);
  OutColor(color);
}

void WriteChar8x11(unsigned char x0, unsigned char y0, unsigned char s, unsigned int color)
{
    unsigned char x,y,c;
    Area((19-x0)*8, y0*11, (19-x0)*8+7, y0*11+10);
    for(y=0;y<8;y++)
      for(x=0;x<11;x++)
        {
       if(s>=192)
         c=65;
       else
        c=0;
       if((Font_8x11[s-32-c][x]&(1<<y))!=0)
         OutColor(color);
       else
         OutColor(BLACK);
        }
}

void WriteString8x11(unsigned char x0,unsigned char y0,unsigned char *s,unsigned int color)
{
  int i,x,y,xx,c;
  xx=19-x0;
  for(i = 0;s[i]!='\0';i++)
    {
    Area(xx*8, y0*11, xx*8+7, y0*11+10);
    for(y=0;y<8;y++)
      for(x=0;x<11;x++)
        {
       if(s[i]>=192)
         c=65;
       else
        c=0;
       if((Font_8x11[s[i]-32-c][x]&(1<<y))!=0)
         OutColor(color);
       else
         OutColor(BLACK);		
       }
    if(xx==0)
      {
      xx=19;
      y0++;
     }
    else
      xx--;
    if(y0>10)
      y0=0;
    }     	
}

void WriteChar5x7(unsigned char x0,unsigned char y0,unsigned char s,unsigned int color)
{
    unsigned char x,y,c;
    Area((31-x0)*5, y0*7, (31-x0)*5+4, y0*7+6);
    for(y=0;y<5;y++)
      for(x=0;x<7;x++)
        {
       if(s>=192)
         c=65;
       else
        c=0;
       if((Font_5x7[s-32-c][x]&(1<<y))!=0)
         OutColor(color);
       else
         OutColor(BLACK);
        }
}

void WriteString5x7(unsigned char x0,unsigned char y0,unsigned char *s,unsigned int color)
{
 unsigned char i,x,y,xx,c;
  xx=31-x0;
  for(i=0;s[i]!='\0';i++)
    {
    Area(xx*5, y0*7, xx*5+4, y0*7+6);	
    for(y=0;y<5;y++)
      for(x=0;x<7;x++)
        {
       if(s[i]>=192)
         c=65;
       else
        c=0;
       if((Font_5x7[s[i]-32-c][x]&(1<<y))!=0)
         OutColor(color);
       else
         OutColor(BLACK);		
       }
    if(xx==0)
      {
      xx=31;
      y0++;
     }
    else
      xx--;
    if(y0>17)
      y0=0;
    }
}

void DrawLine(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned int color)
{
  const signed char signX=(x0<x1) ? 1 : -1;
  const signed char signY=(y0<y1) ? 1 : -1;
  const unsigned char deltaX=((x1-x0)>0) ? (x1-x0) : (x0-x1);
  const unsigned char deltaY=((y1-y0)>0) ? (y1-y0) : (y0-y1);
  short int error = deltaX - deltaY;
  DrawPixel(x1,y1,color);
  while((x0!=x1)||(y0!=y1))
  {
  DrawPixel(x0,y0,color);
    int error2=error*2;
    if(error2 > (-deltaY))
        {
          error -= deltaY;
          x0+=signX;
        }
        if(error2 < deltaX)
        {
          error+=deltaX;
          y0+=signY;
        }
    }
}

void DrawRectangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned int color, unsigned char fill)
{
  unsigned char x,y;
  if(fill==0)
  {
    DrawLine(x0,y0,x1,y0,color);
    DrawLine(x0,y1,x1,y1,color);
    DrawLine(x0,y0,x0,y1,color);
    DrawLine(x1,y0,x1,y1,color);
  }
  else
  {
    Area((160-x1), y0, (160-x0), y1);
    for(x=0;x<(x1-x0);x++)
        for(y=0;y<(y1-y0+1);y++)
          OutColor(color);
  }
}
void DrawCircle(unsigned char x0, unsigned char y0, unsigned char R, unsigned int color, unsigned char fill )
{
	unsigned char x=0;
	short int y=R;
	short int delta=(1-2*R);
	short int error=0;
	while(y>=0)
          {
                if(fill==0)
                {
		  DrawPixel(x0+x-1, y0+y, color);
		  DrawPixel(x0+x-1, y0-y, color);
		  DrawPixel(x0-x+2, y0+y, color);
		  DrawPixel(x0-x+2, y0-y, color);
                }
                else
                {
                  DrawLine(x0+x-1,y0-y,x0+x-1,y0+y,color);
                  DrawLine(x0-x+2,y0-y,x0-x+2,y0+y,color);
                }
		error = 2*(delta+y)-1;
		if((delta<0)&&(error<=0))
                  {
			x++;
			delta+=(2*x + 1);
			continue;
		  }
		error=2*(delta-x)-1;
		if((delta > 0)&&(error>0))
                {
			y--;
			delta+=(1-2*y);
			continue;
		}
		x++;
		delta+=(2*(x - y));
		y--;
	}
}
void DrawTriangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned int color, unsigned char fill)
{
DrawLine(x0,y0,x1,y1,color);
DrawLine(x1,y1,x2,y2,color);
DrawLine(x2,y2,x0,y0,color);
}

