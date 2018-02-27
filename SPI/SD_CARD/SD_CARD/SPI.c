#include "SPI.h"

void port_ini(void)
{

	PORTD=0x00;
	DDRD=0xFF;
	PORTB|=(1<<SS)|(1<<MISO)|(1<<MOSI);
	DDRB|=(1<<SS)|(1<<MOSI)|(1<<SCK);

}




void SPI_SendByte (unsigned char byte)
{

	unsigned char i;
	for (i=0;i<8;i++) //движемся по битам байта
	{
		if ((byte&0x80)==0x00)//проверяем левый бит
		PORTB&=~(1<<MOSI); //если 0, то выставляем 0 на шине
		else PORTB|=(1<<MOSI); //если 1, то выставляем 1

		byte<<=1; //сдвигаем влево, в сторону старшего для проверки следующего бита
		PORTB|=(1<<SCK); //фронт на ножке SCK
		asm("nop"); //1 такт подождём
		PORTB&=~(1<<SCK); //спад на ножке SCK
	}

}


unsigned char SPI_ReceiveByte(void)
{
	unsigned char i, result=0;
	for(i=0;i<8;i++)
	{
		PORTB|=(1<<SCK);//фронт на лапке SCK
		result<<=1;//сдвигаем влево байт, чтобы записать очередной бит
		if((PINB&(1<<MISO))!=0x00)//запишем новый бит в младший разряд
		result=result|0x01;//запишем считанный с лапки порта MISO бит
		PORTB&=~(1<<SCK);//спад на лапке SCK
		asm("nop");//1 такт подождём
	}
	 return result;//вернем результат
}


//Теперь нам нужно написать функцию передачи команд в SD.

/*
У каждой команды есть индекс. У данной команды индекс 8, так как она именуется CMD8. 
Также существуют различия в типах команд. Но об этом потом, нас пока интересует именно такой тип, 
причём именно эту команду нам потом также придется передавать.

Мы видим что передача команды состоит из 48 бит, то есть из 6 байтов. Первая строка показывает позицию бита в команде, 
вторая — величину параметра в битах, третья — значение, а четвёртая — разъяснение параметра.

Стартовый бит — всегда 0.
Бит передачи — 1.
индекс команды — в случае данной команды равен 8.
затем идут зарезервированные биты — целых 20 штук, все равные нулю.
Затем идут параметры, 7 бит контрольной суммы и стоповый бит — всегда 1.
Поэтому нам нужно будет написать функцию передачи команды
Напишем её после наших функций передачи и приёма байтов, так как новая функция этими функциями будет пользоваться
*/

unsigned char SD_cmd(char dt0,char dt1,char dt2,char dt3,char dt4,char dt5)
{
	unsigned char result;
	long int cnt;
	SPI_SendByte(dt0); //индекс
	SPI_SendByte(dt1); //Аргумент
	SPI_SendByte(dt2);
	SPI_SendByte(dt3);
	SPI_SendByte(dt4);
	SPI_SendByte(dt5); //контрольная сумма
	cnt=0;
	do
	{ //Ждём ответ в формате R1 (даташит стр 109)
		result=SPI_ReceiveByte();
		cnt++;
	} while (((result&0x80)!=0x00)&&cnt<0xFFFF);
	return result;

}




/*
=======================функция — инициализация нашей карты===================

*/

unsigned char SD_Init(void)
{
	unsigned char i,temp;
	long int cnt;
	for(i=0;i<10;i++) //80 импульсов (не менее 74) Даташит стр 91
	SPI_SendByte(0xFF);
	/*
	То есть мы отправим 10 байтов FF, тем самым получится 80 единичек. 
	Причём шину SS мы перед передачей не опускаем. Правда импульсов на 
	MOSI я здесь не заметил, будут 80 импульсов на ножке SCK при поднятой MOSI. 
	Но главное работает. Остальное неважно. Вообще всё это дрыганье нужно для того, 
	чтобы таким вот образом карта поняла, что работать мы с ней собираемся именно по 
	SPI и переключилась в соответствующий режим.
	*/

	PORTB&=~(1<<SS);//опускаем SS
	temp=SD_cmd(0x40,0x00,0x00,0x00,0x00,0x95); //CMD0 Даташит стр 102 и 96
	if(temp!=0x01) return 1; //Выйти если ответ не 0x01
	SPI_SendByte(0xFF);
	cnt=0;
	do
	{
		temp=SD_cmd(0x41,0x00,0x00,0x00,0x00,0x95); //CMD1 передаем также, меняется только индекс
		SPI_SendByte(0xFF);
		cnt++;
	} while ((temp!=0x00)&&cnt<0xFFFF); //Ждёс ответа R1
	if(cnt>=0xFFFF) return 2;
	return 0;

}

/*
создадим функцию для записи блока с карты SD выше функции main(). Почему сразу записи, да потому, что читать нам ещё нечего, 
так как сначала надо что-то записать, чтобы потом прочитать и убедиться, что это именно то, что мы записали
*/

unsigned char SD_Write_Block (char* bf, unsigned char dt1, unsigned char dt2, unsigned char dt3, unsigned char dt4)
{
	unsigned char result;
	long int cnt;
	//вызов функции передачи команды
	result=SD_cmd(0x58,dt1,dt2,dt3,dt4,0x95); //CMD24 даташит стр 51 и 97-98
	if (result!=0x00) return 6; //Выйти, если результат не 0x00
	SPI_SendByte (0xFF);
	SPI_SendByte (0xFE); //Начало буфера
	//Начало буфера — это своего рода метка, она входит в пакет передачи данных, состоящий из метки начала и собственно самих данных
	for (cnt=0;cnt<512;cnt++) SPI_SendByte(bf[cnt]); //Данные
	SPI_SendByte (0xFF); //Котрольная сумма
	SPI_SendByte (0xFF);
	result=SPI_ReceiveByte();
	if ((result&0x05)!=0x05) return 6; //Выйти, если результат не 0x05 (Даташит стр 111)
	cnt=0;
	do { //Ждем окончания состояния BUSY
		result=SPI_ReceiveByte();
		cnt++;
    	} while ( (result!=0xFF)&&(cnt<0xFFFF) );

	if (cnt>=0xFFFF) return 6;

	return 0;
}



unsigned char SD_Read_Block (char* bf, unsigned char dt1, unsigned char dt2, unsigned char dt3, unsigned char dt4)
{
	unsigned char result;
	long int cnt;
	result=SD_cmd (0x51,dt1,dt2,dt3,dt4,0x95); //CMD17 даташит стр 50 и 96
	if (result!=0x00) return 5; //Выйти, если результат не 0x00
	SPI_SendByte (0xFF);
	cnt=0;
	do{ //Ждем начала блока
		result=SPI_ReceiveByte();
		cnt++;
	} while ( (result!=0xFE)&&(cnt<0xFFFF) );
	if (cnt>=0xFFFF) return 5;
	for (cnt=0;cnt<512;cnt++) bf[cnt]=SPI_ReceiveByte(); //получаем байты блока из шины в буфер

	SPI_ReceiveByte(); //Получаем контрольную сумму
	SPI_ReceiveByte();
	return 0;
}

