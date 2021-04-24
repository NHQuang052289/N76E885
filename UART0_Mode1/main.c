#include "N76E885.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Function_Define.h"
#include "string.h"
#include <stdio.h>

#define u8recv_buff_size 50 // Receive Buffer Size. (0 - 255)

uint8_t xdata recv_buffer[u8recv_buff_size] = {0}; // Receive_Buffer.
bit BIT_TMP;

void UART0_Write(char* str)
{
	while(*str)
	{
		Send_Data_To_UART0(*(str++));
	}
}
void UART0_Read(uint8_t* str)
{
	uint8_t i = 0, j = 0;
	do
	{
		*(str + i) = Receive_Data_From_UART0();
		j = *(str + i);
		i++;
	}while(j != '\n');
	*(str + (i-1)) = '\0';
}
void main(void)
{
	uint8_t* user_msg = "\r\nStart\r\n";
	uint8_t* crlf = "\n";
	uint8_t user_buffer[5] = {0};
	uint8_t len = 0;
	P03_Quasi_Mode;//TX
	P20_Quasi_Mode;//RX

	InitialUART0_Timer1_Type1(9600);  
	UART0_Write(user_msg);

	while(1)
	{
		UART0_Read(recv_buffer);
		
		len = strlen(recv_buffer);
		sprintf(user_buffer, "%d", len);
		UART0_Write(crlf);
		UART0_Write(user_buffer);
		//UART0_Write(crlf);
		
		UART0_Write(recv_buffer);
	}
}