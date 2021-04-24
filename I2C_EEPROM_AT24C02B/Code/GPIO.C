#include "EEPROM.h"
#include <stdio.h>

bit BIT_TMP;

void main(void)
{
	uint8_t myValue = 0x00;
	P03_Quasi_Mode;//TX
	P20_Quasi_Mode;//RX
	P04_PushPull_Mode;
	
	System_Clock_Select(E_HIRCEN);
	InitialUART0_Timer1_Type1(9600);
	TI = 1;
	printf("Start I2C\r\n");
	I2C_Init();
	
	EEPROM_Write(256, 0xC8);
	while(1)
	{
		
		myValue = EEPROM_Read(256);
		if(myValue == 0xC8) P04 = ~P04;
		printf("Value = %x\n", myValue);
		Timer0_Delay1ms(1000);
	}
}