 #include "Main.h"



int main(void)
{
   char buf[50]={0};
   I2C_Init();
   Usart_Init(9600);

    while (1) 
    {
	
	sprintf(buf,"T=%c\r\n",LM75AD_Convert(LM75AD_GetTemp(0)));
    Usart_PrintString(buf);_delay_ms(1500);
	}
}

