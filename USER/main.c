
//***********************************************************

#include "sys.h"
//#include "common.h"


//***********************************************************
#define GSM_RST PAout(12)
#define PSTR(A) (unsigned char*)(A)


int main ( void )
{
	SystemInit();//ϵͳʱ�ӵȳ�ʼ��
	delay_init ( 72 );	  //��ʱ��ʼ��
	NVIC_Configuration();//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	Uart1Init ( 115200 ); //���ڳ�ʼ��Ϊ115200
	Uart2Init ( 115200 ); //���ڳ�ʼ��Ϊ115200
//	Uart3Init(115200);//���ڳ�ʼ��Ϊ115200


	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOB, ENABLE );
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOD, ENABLE );
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOC, ENABLE );
	GPIO_Configuration_LCD();
	GPIO_ResetBits ( GPIOC, GPIO_Pin_10 );
//	LED_LINGHT = 1;
	LCD_Init();
	LCD_Clear();
//	LCD_WriteString_en ( 0, 0, PSTR("gsm starting") );
//	LCD_WriteString_en ( 1, 1, PSTR("gsm starting") );
//	LCD_WriteString_en ( 2, 2, PSTR("gsm starting") );
//	LCD_WriteString_en ( 3, 3, PSTR("gsm starting") );
//	LCD_WriteString_en ( 4, 4, PSTR("gsm starting") );
	Timerx_Init ( 1000, 7199 ); //10Khz�ļ���Ƶ�ʣ�1000��Ϊ10ms
	LED_Init();	 //LED�˿ڳ�ʼ��

	LED1_ON;
	LED2_ON;
	LED3_ON;
	LED4_ON;
	delay_s ( 1 );
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;

	GSM_RST = 0; //����GSMģ��

	CleanGsmRcv();

	while ( !Hand ( PSTR("SIM900") ) ) //��GSMģ�����֣��ж��Ƿ��յ�GSMģ�鷵�ص�OK
	{
		Uart2SendStr ( PSTR("ATI\r") ); //�򿪻�������
		delay_s ( 1 );
	}

	CleanGsmRcv();//������ջ���
	LED1_ON;



	while ( ! ( Hand ( PSTR("+CREG: 1,1") ) || Hand ( PSTR("+CREG: 1,5") ) ) ) //����Ƿ���ע�ᵽ������
	{
		Uart2SendStr ( PSTR("AT+CREG=1\r") ); //���÷�����״̬Ϊ������ʾ
		delay_s ( 1 );
		Uart2SendStr ( PSTR("AT+CREG?\r") ); //��������״̬
		delay_s ( 1 );
	}

	CleanGsmRcv();//������ջ���
	LED2_ON;

	while ( 1 )
	{
		Uart2SendStr ( PSTR("AT+CIPCLOSE\r") ); //����ǰ�ȹر���ǰ������״̬
		delay_s ( 1 );
		Uart2SendStr ( PSTR("AT+CIPSHUT\r") ); //����ǰ�ȹر���ǰ������״̬
		delay_s ( 1 );
		Uart2SendStr ( PSTR("AT+CLPORT=\"TCP\",\"2022\"\r") ); //����ָ��ָ�����ض˿�
		delay_s ( 1 );
		Uart2SendStr ( PSTR("AT+CIPHEAD=1\r") ); //����ָ��ָ�����ض˿�
		delay_s ( 1 );
		CleanGsmRcv();//������ջ���
		Uart2SendStr ( PSTR("AT+CIPSTART=\"TCP\",\"123.79.0.241\",\"8080\"\r") ); //���ӷ�������ַ123.79.0.241���������˿ں�8080

		while ( ! ( Hand ( PSTR("CONNECT OK") ) ) ); //����Ƿ��յ� CONNECT OK ,��������ӳɹ�

		LED3_ON;
		Uart2SendStr ( PSTR("AT+CIPSEND\r") );
		delay_s ( 1 );
		Uart2SendStr ( PSTR("����LED0����LED1����Ӧ��LED�����Ŷ��") ); //���������������
		delay_s ( 1 );
		Uart2SendHex ( 0x1a ); //��0x1a����
		CleanGsmRcv();//������ջ���

		while ( 1 )
		{
			if ( ( Hand ( PSTR("+IPD") ) && ( Hand ( PSTR("LED1") ) || Hand ( PSTR("led1") ) ) ) )
			{
				LED4_ON;
				CleanGsmRcv();//������ջ���
			}

			if ( ( Hand ( PSTR("+IPD") ) && ( Hand ( PSTR("LED0") ) || Hand ( PSTR("led0") ) ) ) )
			{
				LED4_OFF;
				CleanGsmRcv();//������ջ���
			}
		}

	}

}

