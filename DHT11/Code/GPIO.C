#include "dht11.h"
#include <stdio.h>

uint8_t value[5];
uint8_t buffer[20];

bit BIT_TMP;
//void UART0_Write(char* str)
//{
//	while(*str)
//	{
//		Send_Data_To_UART0(*(str++));
//	}
//}
void main(void)
{
	uint8_t state = 0;
	P03_Quasi_Mode;//TX
	P20_Quasi_Mode;//RX
	System_Clock_Select(E_HIRCEN);
	
	InitialUART0_Timer1_Type1(9600);
	DHT11_Init();
	printf("Start\r\n");
	
	while(1)
	{
		state = get_data();
		switch(state)
		{
			case 1:
			{
				printf("chua thay dht11 response\r\n");
				break;
			}
			case 2:
			{
				printf("Response fail!\r\n");
				break;
			}
			case 3:
			{
				printf("Checksum error! \r\n");
				break;
			}
			default:
			{
//				sprintf(buffer, "H1: %x %\r\n", value[0]);
//				UART0_Write(buffer);
//				sprintf(buffer, "T1: %x doC\r\n", value[2]);
//				UART0_Write(buffer);
//				sprintf(buffer, "CS: %x \r\n", value[4]);	
//				UART0_Write(buffer);
					printf("H = %1x   \r\n", value[0]);
					printf("T = %x    \r\n", value[2]);
					printf("Check sum = %x\r\n", value[4]);
				break;
			}
		}
		Timer0_Delay1ms(3000);
	}
	
}