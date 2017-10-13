/*
 * TestEnd.c
 *
 * Created: 12.10.2017 16:09:06
 * Author : Dante_L_Levi
 */ 


 #include "Main.h"
 

int main(void)
{
   lcd_st7735_init();
   LightRegul(LED_POWER);
   // Закрасить весь экран цветом
   lcd_st7735_screen(RGB16(0xFFFFFF));
   // Вывод строки
   lcd_st7735_putstr_xy(0, 0, "Наконец-то работает!!!", RGB16(GREEN),RGB16(0xFFFFFF));
   lcd_st7735_full_rect(20,40,40,80,RGB16(RED));
   lcd_st7735_triangle(45,80,70,100,95,80,YELLOW);
    DrawCircle(101,101,7,RGB16(GREEN),FILL_ON);
    while (1) 
    {
    }
}

