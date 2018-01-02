#include "LM35lib.h"



/*
===================Название функции:Tempratelm35=============================
=================Функция возращает температуру с датчика LM35========================
			принимает unsigned char - канал считывания данных с АЦП
			возращает float- возращаем значение температуры с датчика LM35

 */
float Tempratelm35(unsigned char channel)
{
	float temp;
	temp=(adc_data(channel)*5.0)/10.24;
	
	return temp;

}




/*
===================Название функции:Val_humidity_sensor=============================
=================Функция возращает значение с  датчика влажности========================
			принимает unsigned char - канал считывания данных с АЦП
			возращает float- возращаем значение температуры с датчика LM35

 */
unsigned char Val_humidity_sensor(unsigned char channel)
{

	unsigned int data;
	data=adc_data(channel);
	if (data>=0 && data<=300)
	{
		return LOW_LEVEL_HUMIDITY;
	}
	else if(data>300 && data<=700)
	{
		return MIDLLE_LEVEL_HUMIDITY;
	}
	else if(data>700)
	{
	return HIGH_LEVEL_HUMIDITY;
	}
	
		

	

}




float  Get_Gause_SS495a(unsigned char channel)
{
	float vg=0.0014;
	float g=1.0;
	float Vgause;
	Vgause=adc_voltage(channel);
	float Gaus;
	Gaus=(Vgause*g)/vg;
	return Gaus;

}
