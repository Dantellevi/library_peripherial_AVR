#include "SPFD5408A.h"
extern uint32_t SysTimer;
static const uint16_t ILI932x_regValues[] = {
	ILI932X_START_OSC        , 0x0001, // Start oscillator
	TFTLCD_DELAY             , 50,     // 50 millisecond delay
	ILI932X_DRIV_OUT_CTRL    , 0x0100,
	ILI932X_DRIV_WAV_CTRL    , 0x0700,
	ILI932X_ENTRY_MOD        , 0x1030,
	ILI932X_RESIZE_CTRL      , 0x0000,
	ILI932X_DISP_CTRL2       , 0x0202,
	ILI932X_DISP_CTRL3       , 0x0000,
	ILI932X_DISP_CTRL4       , 0x0000,
	ILI932X_RGB_DISP_IF_CTRL1, 0x0,
	ILI932X_FRM_MARKER_POS   , 0x0,
	ILI932X_RGB_DISP_IF_CTRL2, 0x0,
	ILI932X_POW_CTRL1        , 0x0000,
	ILI932X_POW_CTRL2        , 0x0007,
	ILI932X_POW_CTRL3        , 0x0000,
	ILI932X_POW_CTRL4        , 0x0000,
	TFTLCD_DELAY             , 200,
	ILI932X_POW_CTRL1        , 0x1690,
	ILI932X_POW_CTRL2        , 0x0227,
	TFTLCD_DELAY             , 50,
	ILI932X_POW_CTRL3        , 0x001A,
	TFTLCD_DELAY             , 50,
	ILI932X_POW_CTRL4        , 0x1800,
	ILI932X_POW_CTRL7        , 0x002A,
	TFTLCD_DELAY             , 50,
	ILI932X_GAMMA_CTRL1      , 0x0000,
	ILI932X_GAMMA_CTRL2      , 0x0000,
	ILI932X_GAMMA_CTRL3      , 0x0000,
	ILI932X_GAMMA_CTRL4      , 0x0206,
	ILI932X_GAMMA_CTRL5      , 0x0808,
	ILI932X_GAMMA_CTRL6      , 0x0007,
	ILI932X_GAMMA_CTRL7      , 0x0201,
	ILI932X_GAMMA_CTRL8      , 0x0000,
	ILI932X_GAMMA_CTRL9      , 0x0000,
	ILI932X_GAMMA_CTRL10     , 0x0000,
	ILI932X_GRAM_HOR_AD      , 0x0000,
	ILI932X_GRAM_VER_AD      , 0x0000,
	ILI932X_HOR_START_AD     , 0x0000,
	ILI932X_HOR_END_AD       , 0x00EF,
	ILI932X_VER_START_AD     , 0X0000,
	ILI932X_VER_END_AD       , 0x013F,
	ILI932X_GATE_SCAN_CTRL1  , 0xA700, // Driver Output Control (R60h)
	ILI932X_GATE_SCAN_CTRL2  , 0x0003, // Driver Output Control (R61h)
	ILI932X_GATE_SCAN_CTRL3  , 0x0000, // Driver Output Control (R62h)
	ILI932X_PANEL_IF_CTRL1   , 0X0010, // Panel Interface Control 1 (R90h)
	ILI932X_PANEL_IF_CTRL2   , 0X0000,
	ILI932X_PANEL_IF_CTRL3   , 0X0003,
	ILI932X_PANEL_IF_CTRL4   , 0X1100,
	ILI932X_PANEL_IF_CTRL5   , 0X0000,
	ILI932X_PANEL_IF_CTRL6   , 0X0000,
	ILI932X_DISP_CTRL1       , 0x0133, // Main screen turn on
};


//===============================================================


int16_t PaperColor = 0;
uint8_t rotation   = 0;

int16_t ScreenMinX = 0;
int16_t ScreenMaxX = 0;
int16_t ScreenMinY = 0;
int16_t ScreenMaxY = 0;

int16_t SaveScreenMinX = 0;
int16_t SaveScreenMaxX = 0;
int16_t SaveScreenMinY = 0;
int16_t SaveScreenMaxY = 0;

int16_t OutTextPosX;
int16_t OutTextPosY;


//===============================================================
//===============================================================
void delay_ms(uint32_t N)
{
	uint32_t d = SysTimer + N;
	
	while (SysTimer < d)
	{
	}
}

//===============================================================
void delay_us(uint32_t N)
{
	uint32_t d;
	uint8_t i;
	
	for (d=0; d<N; d++)
	{
		for (i=0; i<25; i++)
		{
			d = d;
		}
	}
}


void InitDataPortOut(void)
{
	DATADDR=0xFF;
	DATAPORT=0x00;
}

void InitDataPortIN(void)
{
	DATADDR=0x00;
	DATAPORT=0x00;
}

void InitPortControl(void)
{
	COMMAND_DDR|=(1<<RS)|(1<<RES)|(1<<RD)|(1<<WR)|(1<<CS);
	COMMAND_PORT&=~((1<<RS)|(1<<RES)|(1<<RD)|(1<<WR)|(1<<CS));


}


void ResetTFT(void)
{
	CS_ON;
	RS_ON;
	RD_ON;
	WR_ON;
	DATAPORT|=0xFF;
	RES_ON;
	_delay_ms(10);
	RES_OFF;
	_delay_ms(10);
	RES_ON;
	_delay_ms(250);
}

void Write8(uint16_t data)
{
	DATAPORT&=0xFF;
	DATAPORT|=(data)& 0xFF;
	WR_OFF;
	WR_ON;
}


void writeRegister16(uint16_t a, uint16_t d)
{
	uint8_t hi, lo;
	hi = (a) >> 8;
	lo = (a);
	RS_OFF;
	Write8(hi);
	Write8(lo);
	hi = (d) >> 8;
	lo = (d);
	RS_ON ;
	Write8(hi);
	Write8(lo);
}


void TFTSetWindow(int x1, int y1, int x2, int y2) 
{
	int x, y, t;

	SaveScreenMinX = ScreenMinX;
	SaveScreenMaxX = ScreenMaxX;
	SaveScreenMinY = ScreenMinY;
	SaveScreenMaxY = ScreenMaxY;
	
	ScreenMinX = x1;
	ScreenMaxX = x2;
	ScreenMinY = y1;
	ScreenMaxY = y2;
	
	
	CS_OFF;
	switch(rotation)
	{
		default:
		x  = x1;
		y  = y1;
		break;
		
		case TFTLandscape:
		t  = y1;
		y1 = x1;
		x1 = TFTWIDTH  - 1 - y2;
		y2 = x2;
		x2 = TFTWIDTH  - 1 - t;
		
		x  = x2;
		y  = y1;
		break;
		
		case 2:
		t  = x1;
		x1 = TFTWIDTH  - 1 - x2;
		x2 = TFTWIDTH  - 1 - t;
		t  = y1;
		y1 = TFTHEIGHT - 1 - y2;
		y2 = TFTHEIGHT - 1 - t;
		
		x  = x2;
		y  = y2;
		break;
		
		case 3:
		t  = x1;
		x1 = y1;
		y1 = TFTHEIGHT - 1 - x2;
		x2 = y2;
		y2 = TFTHEIGHT - 1 - t;
		
		x  = x1;
		y  = y2;
		break;
	}
	
	writeRegister16(ILI932X_HOR_START_AD, x1); // Set address window
	writeRegister16(ILI932X_HOR_END_AD,   x2);
	writeRegister16(ILI932X_VER_START_AD, y1);
	writeRegister16(ILI932X_VER_END_AD,   y2);
	writeRegister16(ILI932X_GRAM_HOR_AD,  x ); // Set address counter to top left
	writeRegister16(ILI932X_GRAM_VER_AD,  y );


}


//===========================================================
void TFTRestoreWindow(void)
{
	TFTSetWindow(SaveScreenMinX, SaveScreenMinY, SaveScreenMaxX, SaveScreenMaxY);
}


//===========================================================
void TFTSetOrientation(uint8_t x)
{
	uint16_t t;
	
	rotation = x;
	CS_OFF;
	switch(rotation)
	{
		case TFTLandscape       : t = 0x1028;
		writeRegister16(ILI932X_ENTRY_MOD, t); // MADCTL
		TFTSetWindow(0, 0, TFTHEIGHT - 1, TFTWIDTH - 1);
		break;
		case TFTBackPortrait    : t = 0x1000;
		writeRegister16(ILI932X_ENTRY_MOD, t); // MADCTL
		TFTSetWindow(0, 0, TFTWIDTH - 1, TFTHEIGHT - 1);
		break;
		case TFTBackLandscape   : t = 0x1018;
		writeRegister16(ILI932X_ENTRY_MOD, t); // MADCTL
		TFTSetWindow(0, 0, TFTHEIGHT - 1, TFTWIDTH - 1);
		break;
		default /*TFTPortrait*/ : t = 0x1030;
		writeRegister16(ILI932X_ENTRY_MOD, t); // MADCTL
		TFTSetWindow(0, 0, TFTWIDTH - 1, TFTHEIGHT - 1);
		break;
	}
}


//===========================================================
void TFTPixel(int16_t x, int16_t y, uint16_t color)
{
	int16_t t;

	if((x < ScreenMinX) || (y < ScreenMinY) || (x > ScreenMaxX) || (y > ScreenMaxY)) return;

	switch(rotation)
	{
		case TFTLandscape:
		t = x;
		x = TFTWIDTH  - 1 - y;
		y = t;
		break;
		case TFTBackPortrait:
		x = TFTWIDTH  - 1 - x;
		y = TFTHEIGHT - 1 - y;
		break;
		case TFTBackLandscape:
		t = x;
		x = y;
		y = TFTHEIGHT - 1 - t;
		break;
	}
	writeRegister16(ILI932X_GRAM_HOR_AD, x);
	writeRegister16(ILI932X_GRAM_VER_AD, y);
	writeRegister16(ILI932X_RW_GRAM, color);
}




//===========================================================
void TFTClrScr(void)
{
	uint32_t i;
	uint8_t hi, lo;
	
	TFTSetOrientation(rotation);

	hi = PaperColor>>8;
	lo = PaperColor;
	writeRegister16(ILI932X_RW_GRAM, PaperColor);
	for (i=0; i<TFTWIDTH*TFTHEIGHT-1; i++)
	{
		Write8(hi);
		Write8(lo);
	}
}


//===========================================================
void InitTFT(void)
{
	uint16_t a, d;
	uint8_t i;

	InitDataPortOut();
	InitPortControl();

	ResetTFT();

	CS_OFF;
	
	i = 0;
	while(i < sizeof(ILI932x_regValues)/sizeof(uint16_t))
	{
		a = pgm_read_word(&ILI932x_regValues[i++]);
		d = pgm_read_word(&ILI932x_regValues[i++]);
		
		if(a == TFTLCD_DELAY)
		 delay_ms(d);
		else
		writeRegister16(a, d);
		
	}
	
	TFTSetOrientation(TFTLandscape);
	PaperColor = 0;
	TFTClrScr();
}

//===============================================================
void TFTLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t color)
{
	int dx, dy, i1, i2, i, kx, ky;
	int d;
	int x, y;
	int flag;

	dy = y2 - y1;
	dx = x2 - x1;
	if (dx==0 && dy==0)
	{
		TFTPixel(x1,y1, color);
		return;
	}
	
	kx = 1;
	ky = 1;

	if (dx < 0)
	{
		dx = -dx;
		kx = -1;
	}
	else
	if (dx==0)
	kx = 0;

	if (dy < 0)
	{
		dy = -dy;
		ky = -1;
	}

	if(dx<dy)
	{
		flag = 0;
		d = dx;
		dx = dy;
		dy = d;
	}
	else
	flag = 1;

	i1 = dy + dy;
	d = i1 - dx;
	i2 = d - dx;
	x = x1;
	y = y1;

	for (i=0; i<dx; i++)
	{
		TFTPixel(x,y, color);

		if (flag)
		x += kx;
		else
		y += ky;

		if (d < 0)
		d += i1;
		else
		{
			d += i2;
			if (flag)
			y += ky;
			else
			x += kx;
		}
	}
	TFTPixel(x,y, color);
}



void TFTFillPoly(TFTPointPtr p, uint8_t n, uint8_t fill, uint16_t color)
{
	int16_t i;
	int16_t j;
	int16_t index;
	int16_t y;
	int16_t miny, maxy, pmaxy;
	int16_t x1, y1;
	int16_t x2, y2;
	int16_t ind1, ind2;
	int16_t ints;
	int16_t polyInts[MaxPolygonPointNum];
	
	if ((n <= 0)||(n>MaxPolygonPointNum))
	return;

	if (fill)
	{
		miny = p[0].y;
		maxy = p[0].y;
		for (i = 1; (i < n); i++)
		{
			if (p[i].y < miny)
			miny = p[i].y;
			
			if (p[i].y > maxy)
			maxy = p[i].y;
		}
		pmaxy = maxy;
		
		if (miny < ScreenMinY)
		miny = ScreenMinY;
		
		if (maxy > ScreenMaxY)
		maxy = ScreenMaxY;
		
		for (y = miny; (y <= maxy); y++)
		{
			ints = 0;
			for (i = 0; (i < n); i++)
			{
				if (i)
				{
					ind1 = i - 1;
					ind2 = i;
				}
				else
				{
					ind1 = n - 1;
					ind2 = 0;
				}
				
				y1 = p[ind1].y;
				y2 = p[ind2].y;
				if (y1 < y2)
				{
					x1 = p[ind1].x;
					x2 = p[ind2].x;
				}
				else if (y1 > y2)
				{
					y2 = p[ind1].y;
					y1 = p[ind2].y;
					x2 = p[ind1].x;
					x1 = p[ind2].x;
				}
				else
				{
					continue;
				}

				if ((y >= y1) && (y < y2))
				{
					polyInts[ints++] = (int16_t) ((float) ((y - y1) * (x2 - x1))/(float) (y2 - y1) + 0.5 + x1);
				}
				else
				if ((y == pmaxy) && (y == y2))
				{
					polyInts[ints++] = x2;
				}
			}

			for (i=1; (i<ints); i++)
			{
				index = polyInts[i];
				j = i;
				while ((j > 0) && (polyInts[j-1] > index))
				{
					polyInts[j] = polyInts[j-1];
					j--;
				}
				polyInts[j] = index;
			}
			
			for (i=0; (i < (ints-1)); i += 2)
			{
				TFTLine(polyInts[i], y, polyInts[i+1], y, color);
			}
		}
	}
	else
	{
		for (i = 0; (i < n); i++)
		{
			if (i)
			{
				ind1 = i - 1;
				ind2 = i;
			}
			else
			{
				ind1 = n - 1;
				ind2 = 0;
			}
			
			TFTLine(p[ind1].x, p[ind1].y, p[ind2].x, p[ind2].y, color);
		}
	}
	
}







