#include "N76E885.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Function_Define.h"

bit BIT_TMP;

void GPIO_Config(void);
void EXTI_Config(void);

void EXTI_INT0(void) interrupt 0
{
	//clr_IE0;
	Timer1_Delay1ms(50);
	P03 = 0;
}

void main(void)
{
	GPIO_Config();
	EXTI_Config();
	while(1)
	{
		Timer0_Delay1ms(1000);
		P03 = 1;	//off led
	}
}

void GPIO_Config(void)
{
	P00_Input_Mode;	//P0M1|=SET_BIT0;P0M2&=~SET_BIT0
	P03_PushPull_Mode;	//P0M1&=~SET_BIT3;P0M2|=SET_BIT3
}
void EXTI_Config(void)
{
	set_EA;
	set_EX0;
	clr_IT0;	//low level triggered - auto clear flag

	//set_IT0;	//falling edge triggered - flag clear by software

}