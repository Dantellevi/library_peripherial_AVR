#include "ST7735.h"

//-------------------------------------------------------------------------
// �������� ������� �� ������� � ��������� ����� ��������
//
//-------------------------------------------------------------------------

void lcd_st7735_send_cmd(char cmd)
{
	A0_COM;
	SPI_M_byte_io(cmd);
	
}

//-------------------------------------------------------------------------
// �������� ������ �� ������� � ��������� ����� ��������
//
//-------------------------------------------------------------------------

void lcd_st7735_send_data(char data)
{
	A0_DAT;
	SPI_M_byte_io(data);
}

//-------------------------------------------------------------------------
//	������� ������������� �������.
//
//-------------------------------------------------------------------------

void lcd_st7735_init(void)
{
	// ������������� SPI
	SPI_InitTypeDef SPI_InitType;

	SPI_InitType.SPI_set = SPI_ON;
	SPI_InitType.SPI_Mode = SPI_MASTER;
	SPI_InitType.SPI_Prescaler = SPI_PRESCALER_2;
	SPI_InitType.SPI_Polaric = SPI_CPOL_LOW;
	SPI_InitType.SPI_Phase = SPI_CPHA_1EDGE;
	SPI_InitType.SPI_Direct = SPI_DIRECT_MSB;

	SPI_init(&SPI_InitType);
	
	// ��������� ������
	DDR_CS  |= (1 << CS);
	DDR_A0  |= (1 << A0);
	DDR_RES |= (1 << RES);
	
	// ������ ������ ������ � ��������
	CS_ON;
	
	// ���������� ����� �������
	RES_ON;
	_delay_ms(LCD_DELAY);
	RES_OFF;
	_delay_ms(LCD_DELAY);
	
	// ������������� �������
	lcd_st7735_send_cmd(0x11);  // ����� ������ ������� ���� - ���� ������� ����������

	_delay_ms(LCD_DELAY);       // �����

	lcd_st7735_send_cmd(0x3A);  // ����� �����:

	lcd_st7735_send_data(0x05); // 16 ���

	lcd_st7735_send_cmd(0x36);  // ����������� ������ �����������:
	
	lcd_st7735_send_data(0x14); // ����� �����, ������ �� ����, ������� ������ RGB 5-6-5

	lcd_st7735_send_cmd(0x29);  // ��������� �����������
	
	CS_OFF;
}

//-------------------------------------------------------------------------
// ����������� ������� ������ ��� ����������
//
//-------------------------------------------------------------------------

void lcd_st7735_at(char startX, char startY, char stopX, char stopY)
{
	lcd_st7735_send_cmd(0x2A);
	lcd_st7735_send_data(0x00);
	lcd_st7735_send_data(startX);
	lcd_st7735_send_data(0x00);
	lcd_st7735_send_data(stopX);
	
	lcd_st7735_send_cmd(0x2B);
	lcd_st7735_send_data(0x00);
	lcd_st7735_send_data(startY);
	lcd_st7735_send_data(0x00);
	lcd_st7735_send_data(stopY);
}

//-------------------------------------------------------------------------
// ����� �������
//
//-------------------------------------------------------------------------

void lcd_st7735_put_pix(char x, char y, unsigned int color)
{
	CS_ON;
	
	lcd_st7735_at(x, y, x, y);
	lcd_st7735_send_cmd(0x2C);
	lcd_st7735_send_data((char)((color & 0xFF00)>>8));
	lcd_st7735_send_data((char) (color & 0x00FF));
	
	CS_OFF;
}

//-------------------------------------------------------------------------
// ������� ���������� ������������� ������� ������ �������� ������
//
//-------------------------------------------------------------------------

void lcd_st7735_full_rect(char startX, char startY, char stopX, char stopY, unsigned char color)
{
	char y;
	char x;

	CS_ON;

	lcd_st7735_at(startY, startX, stopY, stopX);

	lcd_st7735_send_cmd(0x2C);

	for (y=startX;y<stopX+1;y++)
	for (x=startY;x<stopY+1;x++)
	{
		lcd_st7735_send_data((char)((color & 0xFF00)>>8));
		lcd_st7735_send_data((char) (color & 0x00FF));
	}
	
	CS_OFF;
}

//-------------------------------------------------------------------------
// ������� ��������� �����
//
//-------------------------------------------------------------------------

void lcd_st7735_line(int x0, int y0, int x1, int y1, unsigned int color)
{
	uint8_t steep = 0;
	
	if((abs(x1 - x0)) > (abs(y1 - y0)))
	{
		steep = 1; // ��������� ���� ������� �� ��� ��� � �� ��� �����
	}
	else
	{
		steep = 0;
	}
	uint8_t temp= 0;
	// �������� ����� �� ���������, ���� ���� ������� ������� �������
	if (steep)
	{
		temp = y0;
		y0 = x0;
		x0 = temp;
		
		temp = y1;
		y1 = x1;
		x1 = temp;
	}
	// ���� ����� ����� �� ����� �������, �� ������ ������ � ����� ������� �������
	if (y0 > y1)
	{
		temp = y0;
		y0 = y1;
		x0 = temp;
		
		temp = x0;
		y1 = x1;
		x1 = temp;
	}
	int dy = y1 - y0;
	int dx = abs(x1 - x0);
	int error = dy / 2; // ����� ������������ ����������� � ���������� �� dy, ����� ���������� �� ������ ������
	int xstep = (x0 < x1) ? 1 : -1; // �������� ����������� ����� ���������� x
	int x = x0;
	for (int y = y0; y <= y1; y++)
	{
		lcd_st7735_put_pix(steep ? x : y, steep ? y : x, color); // �� �������� ������� ���������� �� �����
		error -= dx;
		if (error < 0)
		{
			x += xstep;
			error += dy;
		}
	}
}

//-------------------------------------------------------------------------
// ��������� �������������� (�� ������������)
//
//-------------------------------------------------------------------------

void lcd_st7735_rect(char x1, char y1, char x2, char y2, int color)
{
	lcd_st7735_full_rect(x1,y1, x2,y1, color);
	lcd_st7735_full_rect(x1,y2, x2,y2, color);
	lcd_st7735_full_rect(x1,y1, x1,y2, color);
	lcd_st7735_full_rect(x2,y1, x2,y2, color);
}

//-------------------------------------------------------------------------
// ���������� ����� ������ ����� ������
//
//-------------------------------------------------------------------------

void lcd_st7735_screen(unsigned int color)
{
	lcd_st7735_full_rect(0, 0, 159, 127, color);
}

//-------------------------------------------------------------------------
// ����� ������� �� ����� �� �����������
//
//-------------------------------------------------------------------------

void lcd_st7735_putchar(char x, char y, char chr, unsigned int charColor, unsigned int bkgColor)
{
	char i;
	char j;
	char h;
	unsigned int color;
	
	CS_ON;

	lcd_st7735_at(y, x, y+12, x+8);
	lcd_st7735_send_cmd(0x2C);


	char k;
	for (i=0;i<7;i++)
	for (k=2;k>0;k--)
	{
		char chl = pgm_read_byte(&(NewBFontLAT[ ( (chr-0x20)*14 + i+ 7*(k-1)) ]));
		chl=chl<<2*(k-1); // ������ �������� ������� �������� �� 1 ������� ����� (������� ���� ����� �����)
		if (k==2) h=6; else h=7; // � ������ �������� ������� ������ 6 ����� ������ 7
		for (j=0;j<h;j++)
		{
			if (chl & 0x80) color=charColor; else color=bkgColor;
			chl = chl<<1;
			lcd_st7735_send_data((char)((color & 0xFF00)>>8));
			lcd_st7735_send_data((char) (color & 0x00FF));
		}
	}
	
	// ������ ������ �� ������� ������ ������������ ����� ��� �������� ���������
	for (j=0;j<13;j++)
	{
		lcd_st7735_send_data((char)((bkgColor & 0xFF00)>>8));
		lcd_st7735_send_data((char) (bkgColor & 0x00FF));
	}
	
	CS_OFF;
}

//-------------------------------------------------------------------------
// ����� ������ � ����� �� �����������
//
//-------------------------------------------------------------------------

void lcd_st7735_putstr(char x, char y, const char str[], unsigned int charColor, unsigned int bkgColor)
{

	while (*str!=0) {
		lcd_st7735_putchar(x, y, *str, charColor, bkgColor);
		x=x+8;
		str++;
	}
}

//-------------------------------------------------------------------------
// ����� ������ � ����� �� ������
//
//-------------------------------------------------------------------------

void lcd_st7735_putstr_xy(char x, char y, const char str[], unsigned int charColor, unsigned int bkgColor)
{
	if(y != 0)
	{
		y = (y*13)-2;
	}
	else
	{
		y = 0;
	}
	x = x*8;
	lcd_st7735_putstr(x, y, str, charColor, bkgColor);
}
