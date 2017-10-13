/*
 * ST7735lib2.c
 *
 * Created: 12.10.2017 12:24:47
 * Author : Dante_L_Levi
 */ 

#include "Main.h"

void Port_init(void)
{

DDRD|=(1<<PD5);
PORTD|=(1<<PD5);
}


int main(void)
{
Port_init();
spi_init();
st7735_init();

st7735_set_orientation(ST7735_LANDSCAPE);
st7735_fill_rect(0, 0, 80, 60, ST7735_COLOR_BLACK);

    /* Replace with your application code */
    while (1) 
    {
    }
}

