
#include "Main.h"





int main(void)
{
    LCDinit();
	
	char buffer[10];
	HC_SRC04_Init();
	Init_Interruot_HC04(FLAG_INT0);
	sei();
    while (1) 
    {
		LCDstringXY("Hello!!!",0,0);
		sprintf(buffer,"ras= %u  cm",GetValueHSR04());
		LCDstringXY(buffer,1,1);
		LCDputsIntGotoXY(TCNT1,2,2);
		_delay_ms(1000);
		LCDclear();
		
		
		



    }
}

