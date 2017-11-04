#include <HAL.h>
#include <EERTOS.h>

// Global Variables
volatile u08 ADATA;
volatile u08 Cycle;

#define buffer_MAX 16				// Длина текстового буффера
char buffer[buffer_MAX] = "Speed 0000  RPM\n"; // А вот и он сам
u08 buffer_index;					// Текущий элемент буффера



//RTOS Interrupt
ISR(RTOS_ISR)
{
TimerService();						// Прерывание ядра диспетчера
}

/*
// All Interrupts
ISR(ADC_vect)
{
ADATA = ADCH;
UDR = ADCH;
}
*/

ISR(INT0_vect)				// Обработчик прерывания INT0
{
Cycle++;					// Увеличиваем число оборотов
}

ISR (USART_UDRE_vect)		// Прерывание по опустошению буффера УАПП
{
if (buffer[buffer_index]) UDR = buffer[buffer_index];  // Если текущее значение не 0х00 вывод

buffer_index ++;			// Увеличиваем индекс

if(buffer_index == buffer_MAX)  // Вывели весь буффер? 
	{
	UCSRB &=~(1<<UDRIE);		// Запрещаем прерывание по опустошению - передача закончена
	}
}
// Прототипы задач ============================================================
//void Task1 (void);
//void Task2 (void);
//void Task3 (void);
//============================================================================
//Область задач
//============================================================================

/*
void Task1 (void)
{
SetTimerTask(Task2,100);
LED_PORT  ^=1<<LED3;
}

void Task2 (void)
{
SetTimerTask(Task1,100);
LED_PORT  &= ~(1<<LED3);
}

void ScanADC(void)
{
SetTimerTask(ScanADC,100);
ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADSC)|(1<<ADATE)|(3<<ADPS0);
}

void UpdatePWM(void)
{
SetTimerTask(UpdatePWM,200);
OCR0=ADATA;
}
*/

void Catch(void)    // Задача подсчета и обработки данных. 
{
u16 RPM=0;
SetTimerTask(Catch,2000); 	// Время подсчета - 2с

buffer[7]=0;				// Зануляем знакоместа в буффере
buffer[8]=0;				// Чтобы там не было пустых мест
buffer[9]=0;				// Иначе будет гнать при снежении оборотов

RPM = Cycle*30;				// Вычисляем число оборотов в минуту

itoa(RPM,buffer+6,10);		// Перевеодим его в ASCII строку. Вписывая в наш буффер

SEND(buffer[0]);			// Запускаем передачу (макрос в файле HAL.h)

Cycle = 0;					// Обнуляем счетчик циклов
}
//==============================================================================
int main(void)
{
InitAll();			// Инициализируем периферию
InitRTOS();			// Инициализируем ядро
RunRTOS();			// Старт ядра. 

// Запуск фоновых задач.
//SetTask(Task1);
//SetTask(ScanADC);
//SetTask(UpdatePWM);
SetTask(Catch);

while(1) 		// Главный цикл диспетчера
{
wdt_reset();	// Сброс собачьего таймера
TaskManager();	// Вызов диспетчера
}

return 0;
}
