#include "N76E885.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Function_Define.h"

bit BIT_TMP;

void PIN_ISR(void) interrupt 7
{
	PIF = 0x00;
	//Timer1_Delay1ms(50);
	P03 = 0;
}
void GPIO_Config(void)
{
	P03_PushPull_Mode;
	P34_Input_Mode;
}
void EXTI_Config(void)
{
	set_EA;
	set_EPI;
	PICON = 0xFF;
	PINEN = 0xFF;
	//PIPEN = 0xFF;
}
void main(void)
{
	System_Clock_Select(E_HIRCEN);   //Fosc = 2~25MHz XTAL
	GPIO_Config();
	EXTI_Config();

	while(1)
	{
		Timer0_Delay1ms(1000);
		P03 = 1;	//off led
	}
}