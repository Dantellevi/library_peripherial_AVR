#include <HAL.h>
#include <EERTOS.h>

// Global Variables
volatile u08 ADATA;
volatile u08 Cycle;

#define buffer_MAX 16				// ����� ���������� �������
char buffer[buffer_MAX] = "Speed 0000  RPM\n"; // � ��� � �� ���
u08 buffer_index;					// ������� ������� �������



//RTOS Interrupt
ISR(RTOS_ISR)
{
TimerService();						// ���������� ���� ����������
}

/*
// All Interrupts
ISR(ADC_vect)
{
ADATA = ADCH;
UDR = ADCH;
}
*/

ISR(INT0_vect)				// ���������� ���������� INT0
{
Cycle++;					// ����������� ����� ��������
}

ISR (USART_UDRE_vect)		// ���������� �� ����������� ������� ����
{
if (buffer[buffer_index]) UDR = buffer[buffer_index];  // ���� ������� �������� �� 0�00 �����

buffer_index ++;			// ����������� ������

if(buffer_index == buffer_MAX)  // ������ ���� ������? 
	{
	UCSRB &=~(1<<UDRIE);		// ��������� ���������� �� ����������� - �������� ���������
	}
}
// ��������� ����� ============================================================
//void Task1 (void);
//void Task2 (void);
//void Task3 (void);
//============================================================================
//������� �����
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

void Catch(void)    // ������ �������� � ��������� ������. 
{
u16 RPM=0;
SetTimerTask(Catch,2000); 	// ����� �������� - 2�

buffer[7]=0;				// �������� ���������� � �������
buffer[8]=0;				// ����� ��� �� ���� ������ ����
buffer[9]=0;				// ����� ����� ����� ��� �������� ��������

RPM = Cycle*30;				// ��������� ����� �������� � ������

itoa(RPM,buffer+6,10);		// ���������� ��� � ASCII ������. �������� � ��� ������

SEND(buffer[0]);			// ��������� �������� (������ � ����� HAL.h)

Cycle = 0;					// �������� ������� ������
}
//==============================================================================
int main(void)
{
InitAll();			// �������������� ���������
InitRTOS();			// �������������� ����
RunRTOS();			// ����� ����. 

// ������ ������� �����.
//SetTask(Task1);
//SetTask(ScanADC);
//SetTask(UpdatePWM);
SetTask(Catch);

while(1) 		// ������� ���� ����������
{
wdt_reset();	// ����� ��������� �������
TaskManager();	// ����� ����������
}

return 0;
}
