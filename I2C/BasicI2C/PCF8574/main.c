/*
 * PCF8574.c
 *
 * Created: 05.02.2018 15:13:36
 * Author : Dante_L_Levi
 */ 

#include "Main.h"



int main(void)
{
   I2C_Init();//инициализируем TWI
   LCD_ini();  //инициализируем дисплей
   clearlcd();//очистим дисплей
   setpos(0,0);
   str_lcd("Hello World Sania!");
   setpos(2,1);
   str_lcd("String 2");
   setpos(4,2);
   str_lcd("String 3");
   setpos(6,3);
   str_lcd("String 4");
    while (1) 
    {
    }
}

