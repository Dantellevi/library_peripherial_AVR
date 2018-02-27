
#include "Main.h"

unsigned char	nDevices;	// количество сенсоров
unsigned char	owDevicesIDs[MAXDEVICES][8];	// Их ID
float t;


unsigned char search_ow_devices(void) // поиск всех устройств на шине
{
	unsigned char	i;
	unsigned char	id[OW_ROMCODE_SIZE];
	unsigned char	diff, sensors_count;

	sensors_count = 0;

	for( diff = OW_SEARCH_FIRST; diff != OW_LAST_DEVICE && sensors_count < MAXDEVICES ; )
	{
		OW_FindROM( &diff, &id[0] );

		if( diff == OW_PRESENCE_ERR ) break;

		if( diff == OW_DATA_ERR )	break;

		for (i=0;i<OW_ROMCODE_SIZE;i++)
		owDevicesIDs[sensors_count][i] = id[i];
		
		sensors_count++;
	}
	return sensors_count;

}
unsigned char	themperature[3]; // в этот массив будет записана температура




int main(void)
{
	DDRB = 0b00000010; PORTB = 0b00000010;
	DDRC = 0b00000000; PORTC = 0b00000000;
	DDRD = 0b00000010; PORTD = 0b00000000;
	char buffer[80];
	Usart_Init(9600);
	timerDelayInit();
    /* Replace with your application code */

	Usart_PrintString("Hello Temp!!!\r\n");
	_delay_ms(1000);
	nDevices = search_ow_devices(); // ищем все устройства
	sprintf(buffer,"--------Found %u Devices---------- \r\n",(int)nDevices);
	Usart_PrintString(buffer);
	for (int i=0;i<80;i++)
	{
		buffer[i]=0;
	}
	_delay_ms(500);
	
    while (1) 
    {
		for (unsigned char i=0; i<nDevices; i++) // теперь сотируем устройства и запрашиваем данные
		{
			switch (owDevicesIDs[i][0])
			{
				case OW_DS18B20_FAMILY_CODE:
				{
					Usart_PrintString("\r\n");
					sprintf(buffer,"Address %u:",(unsigned int)owDevicesIDs[i]);
					Usart_PrintString(buffer);
					Usart_PrintString(" - Thermometer DS18B20");
					timerDelayMs(800);
					unsigned char	data[2];// переменная для хранения старшего и младшего байта данных
					DS18x20_ReadData(owDevicesIDs[i], data); // считываем данные
					t = DS18x20_ConvertToThemperatureFl(data); // преобразовываем температуру в человекопонятный вид
					sprintf(buffer,"T=%3.2f C:",t);
					Usart_PrintString(buffer);
					break;
				}
			}
		}
		_delay_ms(400);

	}
}

