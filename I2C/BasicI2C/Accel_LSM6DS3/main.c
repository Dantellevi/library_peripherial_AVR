
#include "Main.h"



int main(void)
{
	
	Usart_Init(115200);
	Accel_Ini();

   
    while (1) 
    {
		Accel_ReadAcc();
    }
}

