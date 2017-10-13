/*
 *
 *
 * Created: 02.10.2017 13:47:10
 * Author :Лепотенко А.С.
 */ 

#include "Main.h"

void Port_ini(void)
{


}



int main(void)
{
Port_ini();
Lcd_init();
Lcd_clear();
//переменные
//int i_data=123;
//float f_data=3.14;
//char s_data[40]="привет";



    while (1) 
    {
	//------------------------------РАБОТА С ТЕКСТОМ----------------------------
	//Lcd_prints(0,0,FONT_1X,(unsigned char *)PSTR("Привет"));
	//Lcd_prints(0,3,FONT_1X,(unsigned char *)PSTR("Hello"));
	//Lcd_update();
	//Lcd_prints(0,0,FONT_1X,(unsigned char*)PSTR("Текст работа!!"));
	//Lcd_print(0,1,FONT_1X,(unsigned char*)s_data);
	//Lcd_printf(0,2,FONT_1X,f_data,4);
	//char buffer[10];
	//itoa(i_data,buffer,10);
	//Lcd_print(0,3,FONT_1X,(unsigned char*)buffer);
	//-----------------------------РАБОТА С ИЗОБРАЖЕНИЕМ---------------------------------

	//---------------круг----------------------
	//for(int i=1;i<=10;i++)
	//{
//
	//Lcd_circle(42,24,i,PIXEL_ON);
	//_delay_ms(200);
	//Lcd_update();
	//}
	//---------------закрашенный прямоугольник-----------

	//Lcd_rect(10,30,15,50,PIXEL_XOR);
	//_delay_ms(200);
	//Lcd_update();

	//--------------------------------------------------------------
	//int ran;
	//ran=rand()%10+25;
	//for (int i=1;i<=8;i++)
	//{
	//Lcd_circle(50,10,i,PIXEL_ON);
	//}
//
	//Lcd_rect_empty(46,10,54,40,PIXEL_ON);
//
//
	//Lcd_line(46,20,30,20,PIXEL_ON);
	//Lcd_line(46,25,30,25,PIXEL_ON);
	//Lcd_line(46,35,30,35,PIXEL_ON);
	//Lcd_rect(46,10,20,8,PIXEL_ON);
	//
	//_delay_ms(100);
	//Lcd_rect(54,10,ran,8,PIXEL_OFF);
	
	//Lcd_pixel(0,0,PIXEL_ON);
	////Lcd_rect_Fill(10,10,40,30,PIXEL_ON);
	//for (int i=0;i<30;i++)
	//{
	//Lcd_rect_Fill(10,10,i,20,PIXEL_ON);
//
	//Lcd_update();
	//_delay_ms(100);
	//}
//
	//Lcd_triangle(40, 10, 50, 20,50, 10,PIXEL_ON);

	Lcd_Romb(30,5,40,25,30,45,10,20,PIXEL_ON);
	Lcd_update();
	

	

    }
}

