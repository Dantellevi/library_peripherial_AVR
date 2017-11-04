#include "LM35lib.h"



/*
===================Íàçâàíèå ôóíêöèè:Tempratelm35=============================
=================Ôóíêöèÿ âîçğàùàåò òåìïåğàòóğó ñ äàò÷èêà LM35========================
			ïğèíèìàåò unsigned char - êàíàë ñ÷èòûâàíèÿ äàííûõ ñ ÀÖÏ
			âîçğàùàåò float- âîçğàùàåì çíà÷åíèå òåìïåğàòóğû ñ äàò÷èêà LM35

 */
float Tempratelm35(unsigned char channel)
{
	float temp;
	temp=(adc_data(channel)*5.0)/10.24;
	
	return temp;

}




/*
===================Íàçâàíèå ôóíêöèè:Val_humidity_sensor=============================
=================Ôóíêöèÿ âîçğàùàåò çíà÷åíèå ñ  äàò÷èêà âëàæíîñòè========================
			ïğèíèìàåò unsigned char - êàíàë ñ÷èòûâàíèÿ äàííûõ ñ ÀÖÏ
			âîçğàùàåò float- âîçğàùàåì çíà÷åíèå òåìïåğàòóğû ñ äàò÷èêà LM35

 */
unsigned char Val_humidity_sensor(unsigned char channel)
{

	unsigned int data;
	data=adc_data(channel);
	if (data>=0 && data<=300)
	{
		return LOW_LEVEL_HUMIDITY;
	}
	else if(data>300 &&data<=700)
	{
		return MIDLLE_LEVEL_HUMIDITY;
	}
	else
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
