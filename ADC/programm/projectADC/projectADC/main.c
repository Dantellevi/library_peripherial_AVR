

#include "Main.h"

char buffer[80];
char bufferTemp[80];
void portInit(void)
{


}


int main(void)
{

	portInit();
    adc_init(FLAG_EXTERN_AREF,5.0);
	LCDinit();
    while (1) 
    {
	//================================Работа с датчиком температуры LM35==================
		LCDstringXY("Hello",0,0);
		sprintf(bufferTemp,"Temp=%.1f\1C",Tempratelm35(ADC_CH_1));
		LCDstringXY(bufferTemp,1,1);
		sprintf(bufferTemp,"Temp=%.1f\1C",Tempratelm35(ADC_CH_3));
		LCDstringXY(bufferTemp,1,2);
		////===============================Работа с датчиком влажности============================
		if (Val_humidity_sensor(ADC_CH_6)==0)
		{
		LCDstringXY("Low   Humanity",0,3);
		sprintf(buffer,"%u",Val_humidity_sensor(ADC_CH_6));
		LCDstringXY(buffer,13,3);
		}
		else if (Val_humidity_sensor(ADC_CH_6)==2)
		{
		LCDstringXY("High  Humanity",0,3);
		sprintf(buffer," %u",Val_humidity_sensor(ADC_CH_6));
		LCDstringXY(buffer,13,3);
		}
		else if (Val_humidity_sensor(ADC_CH_6)==1)
		{
		LCDstringXY("Midle Humanity",0,3);
		sprintf(buffer," %u",Val_humidity_sensor(ADC_CH_6));
		LCDstringXY(buffer,13,3);
		}
		
		//LCDdataXY(GetValueKey_Board(ADC_CH_2),0,1);
		//========================Работа с матричной клавиатурой АЦП=================================
		//uint8_t b= password_confird(ADC_CH_2);
		//if (b==1)
		//{
			//LCDstringXY("Password    OK",0,3);
		//}
		//else if (b==0)
		//{
			//LCDstringXY("Password Error",0,3);
		//}
		//=============================Работа с датчиком магнитного поля SS495a==========================
		//sprintf(buffer,"Gause=%.1f G",Get_Gause_SS495a(ADC_CH_7));
		//LCDstringXY(buffer,0,0);
		_delay_ms(200);
    }
}

