/*
 * DS1307.c
 *
 * Created: 07.02.2018 15:17:48
 * Author : Dante_L_Levi
 */ 

 #include "Main.h"

 unsigned char sec,min,hour,day,date,month,year;




 /*
 ============================Функция чтения данных с микросхемы ds1307=============
 */
 void Read_RTCTime(void)
 {
	//Читаем время
	I2C_SendByteAddR(0,0b11010000); //переходим на адрес 0
	_delay_ms(300);
	Start_I2C();
	I2C_SendByte(0b11010001); //отправим в устройство бит чтения
	sec = I2C_ReadByte();
	min = I2C_ReadByte();
	hour = I2C_ReadByte();
    day = I2C_ReadByte();
	date = I2C_ReadByte();
	month = I2C_ReadByte();
	year = I2C_ReadLastByte();
	Stop_I2C();
	sec = RTC_ConvertFromDec(sec); //Преобразуем в десятичный формат
	min = RTC_ConvertFromDec(min); //Преобразуем в десятичный формат
	hour = RTC_ConvertFromDec(hour); //Преобразуем в десятичный формат
	day = RTC_ConvertFromDec(day); //Преобразуем в десятичный формат
	year = RTC_ConvertFromDec(year); //Преобразуем в десятичный формат
	month = RTC_ConvertFromDec(month); //Преобразуем в десятичный формат
	date = RTC_ConvertFromDec(date); //Преобразуем в десятичный формат
	//-------------------------------------------
	Usart_char_out(date/10+0x30);//Преобразуем число в код числа
	Usart_char_out(date%10+0x30);//Преобразуем число в код числа
	Usart_char_out('.');
	Usart_char_out(month/10+0x30);//Преобразуем число в код числа
	Usart_char_out(month%10+0x30);//Преобразуем число в код числа
	Usart_char_out('.');
	Usart_char_out(year/10+0x30);//Преобразуем число в код числа
	Usart_char_out(year%10+0x30);//Преобразуем число в код числа
	Usart_char_out(' ');
	Usart_char_out('-');
	Usart_char_out(day+0x30);//Преобразуем число в код числа
	Usart_char_out('-');
	Usart_char_out(' ');
	Usart_char_out(' ');
	Usart_char_out(hour/10+0x30);//Преобразуем число в код числа
	Usart_char_out(hour%10+0x30);//Преобразуем число в код числа
	Usart_char_out(':');
	Usart_char_out(min/10+0x30);//Преобразуем число в код числа
	Usart_char_out(min%10+0x30);//Преобразуем число в код числа
	Usart_char_out(':');
	Usart_char_out(sec/10+0x30);//Преобразуем число в код числа
	Usart_char_out(sec%10+0x30);//Преобразуем число в код числа
	Usart_char_out(0x0d);//переход в начало строки
	Usart_char_out(0x0a);//перевод каретки
 
 }


int main(void)
{
	I2C_Init();
	Usart_Init(9600);

	//=============================Установка времени=============
	Start_I2C();
	I2C_SendByte(0b11010000);
	I2C_SendByte(0);//переходим по адрессу 0х00(секунды)
	I2C_SendByte(RTC_ConvertFromBinDec(0)); //секунды
	I2C_SendByte(RTC_ConvertFromBinDec(44)); //минуты
	I2C_SendByte(RTC_ConvertFromBinDec(15)); //часы
	I2C_SendByte(RTC_ConvertFromBinDec(3)); //день недели
	I2C_SendByte(RTC_ConvertFromBinDec(7)); //дата
	I2C_SendByte(RTC_ConvertFromBinDec(2)); //месяц
	I2C_SendByte(RTC_ConvertFromBinDec(18)); //год
	Stop_I2C();
	//===========================================================





    while (1) 
    {
		Read_RTCTime();
		_delay_ms(500);

    }
}

