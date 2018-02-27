
#include "Main.h"



int main(void)
{
    I2C_Init();
    while (1) 
    {
		I2CStart();
		//I2C_SendByteByADDR(0b00111111,0);
		for (uint8_t i=0;i<100;i++)
		{
			I2C_SendByte(i);
			_delay_ms(500);
		}
		I2CStop();

    }
}

