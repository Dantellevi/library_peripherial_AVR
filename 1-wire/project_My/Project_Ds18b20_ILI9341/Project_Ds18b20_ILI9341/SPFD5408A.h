#ifndef SPFD5408A_H_
#define SPFD5408A_H_


#include "Main.h"
#include <avr/pgmspace.h>


// Register names from Peter Barrett's Microtouch code
#define ILI932X_START_OSC          0x00
#define ILI932X_DRIV_OUT_CTRL      0x01
#define ILI932X_DRIV_WAV_CTRL      0x02
#define ILI932X_ENTRY_MOD          0x03
#define ILI932X_RESIZE_CTRL        0x04
#define ILI932X_DISP_CTRL1         0x07
#define ILI932X_DISP_CTRL2         0x08
#define ILI932X_DISP_CTRL3         0x09
#define ILI932X_DISP_CTRL4         0x0A
#define ILI932X_RGB_DISP_IF_CTRL1  0x0C
#define ILI932X_FRM_MARKER_POS     0x0D
#define ILI932X_RGB_DISP_IF_CTRL2  0x0F
#define ILI932X_POW_CTRL1          0x10
#define ILI932X_POW_CTRL2          0x11
#define ILI932X_POW_CTRL3          0x12
#define ILI932X_POW_CTRL4          0x13
#define ILI932X_GRAM_HOR_AD        0x20
#define ILI932X_GRAM_VER_AD        0x21
#define ILI932X_RW_GRAM            0x22
#define ILI932X_POW_CTRL7          0x29
#define ILI932X_FRM_RATE_COL_CTRL  0x2B
#define ILI932X_GAMMA_CTRL1        0x30
#define ILI932X_GAMMA_CTRL2        0x31
#define ILI932X_GAMMA_CTRL3        0x32
#define ILI932X_GAMMA_CTRL4        0x35
#define ILI932X_GAMMA_CTRL5        0x36
#define ILI932X_GAMMA_CTRL6        0x37
#define ILI932X_GAMMA_CTRL7        0x38
#define ILI932X_GAMMA_CTRL8        0x39
#define ILI932X_GAMMA_CTRL9        0x3C
#define ILI932X_GAMMA_CTRL10       0x3D
#define ILI932X_HOR_START_AD       0x50
#define ILI932X_HOR_END_AD         0x51
#define ILI932X_VER_START_AD       0x52
#define ILI932X_VER_END_AD         0x53
#define ILI932X_GATE_SCAN_CTRL1    0x60
#define ILI932X_GATE_SCAN_CTRL2    0x61
#define ILI932X_GATE_SCAN_CTRL3    0x6A
#define ILI932X_PART_IMG1_DISP_POS 0x80
#define ILI932X_PART_IMG1_START_AD 0x81
#define ILI932X_PART_IMG1_END_AD   0x82
#define ILI932X_PART_IMG2_DISP_POS 0x83
#define ILI932X_PART_IMG2_START_AD 0x84
#define ILI932X_PART_IMG2_END_AD   0x85
#define ILI932X_PANEL_IF_CTRL1     0x90
#define ILI932X_PANEL_IF_CTRL2     0x92
#define ILI932X_PANEL_IF_CTRL3     0x93
#define ILI932X_PANEL_IF_CTRL4     0x95
#define ILI932X_PANEL_IF_CTRL5     0x97
#define ILI932X_PANEL_IF_CTRL6     0x98
#define TFTLCD_DELAY               0xFF




#define TFTWIDTH   240
#define TFTHEIGHT  320

//TFTSetOrientation const
extern uint8_t rotation;
#define TFTPortrait      0
#define TFTLandscape     1
#define TFTBackPortrait  2
#define TFTBackLandscape 3

// Current window param
extern int16_t ScreenMinX;
extern int16_t ScreenMaxX;
extern int16_t ScreenMinY;
extern int16_t ScreenMaxY;

// Background color
extern int16_t PaperColor;

#define Black     0x0000
#define Red       0xF800
#define Orange    0xFBE0
#define Yellow    0xFFE0
#define Green     0x07E0
#define Cyan      0x07FF
#define Blue      0x001F
#define Magenta   0xF81F
#define Violet    0x881F
#define White     0xFFFF


typedef struct {
	int16_t x, y;
} TFTPoint, *TFTPointPtr;


#define MaxPolygonPointNum 50

#define asLine   0x00
#define asFill   0x01
#define asChord  0x02
#define asEdged  0x04

#define tsNormal 0x00
#define tsBold   0x01
#define tsItalic 0x02


#define DATAPORT PORTA
#define DATADDR  DDRA



#define COMMAND_PORT PORTC
#define COMMAND_DDR DDRC

#define RS  2   //RS(comm - 0; data - 1)
#define RES 0  //(active - 0)
#define RD  4	//(read_active - 0)
#define CS  1  //(chip_select_active - 0)
#define WR  3	//(write_active - 0)

#define RS_ON COMMAND_PORT|=(1<<RS)
#define RS_OFF COMMAND_PORT&=~(1<<RS)

#define RD_ON COMMAND_PORT|=(1<<RD)
#define RD_OFF COMMAND_PORT&=~(1<<RD)


#define WR_ON COMMAND_PORT|=(1<<WR)
#define WR_OFF COMMAND_PORT&=~(1<<WR)

#define CS_ON COMMAND_PORT|=(1<<CS)
#define CS_OFF COMMAND_PORT&=~(1<<CS)

#define RES_ON COMMAND_PORT|=(1<<RES)
#define RES_OFF COMMAND_PORT&=~(1<<RES)






void InitTFT(void);
void TFTLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t color);
void TFTSetOrientation(uint8_t x);
void TFTFillPoly(TFTPointPtr p, uint8_t n, uint8_t fill, uint16_t color);

#endif /* SPFD5408A_H_ */