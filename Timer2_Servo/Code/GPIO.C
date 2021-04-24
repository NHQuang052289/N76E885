
#include "N76E885.h"
#include "Version.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Function_Define.h"

#define CONTROL_PIN		P03

void GPIO_Config(void);
void TIM2_Config(void);
void Timer2_I2SR(void);

bit BIT_TMP;
uint8_t i = 9;
uint16_t highTime = 0;
void main(void)
{
	System_Clock_Select(E_HIRCEN); //Internal 22.1184MHz
	GPIO_Config();
	TIM2_Config();
	while(1)
	{

	}
}

void TIM2_Config(void)
{
	
	set_EA; //enable interrupt all
	set_ET2;	//enable interrupt timer2
	set_TR2; //T2CON |= SET_BIT2
	TIMER2_DIV_64;	
	TIMER2_Auto_Reload_Delay_Mode;	//T2CON&=~SET_BIT0;T2MOD|=SET_BIT7;T2MOD|=SET_BIT3
	RCMP2H = HIBYTE(TIMER_DIV64_VALUE_20ms);
	RCMP2L = LOBYTE(TIMER_DIV64_VALUE_20ms);
	TL2 = 0; TH2 = 0;
}

void Timer2_ISR(void) interrupt 5 //timer 2 event vector number 5
{
		//clear timer flag 2
	clr_TF2;
	highTime = i * 20;
	CONTROL_PIN = 1; //high pulse
	Delay10us(highTime);
//	Timer0_Delay1ms(2);
	CONTROL_PIN = 0;
}
void GPIO_Config(void)
{
	P03_PushPull_Mode;
}


