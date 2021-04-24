#include "N76E885.h"
#include "Version.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Function_Define.h"

#define TRIG		P21	//pin6
#define ECHO		P20	//pin5

void GPIO_Config(void);
void TIM2_Config(void);
void Capture_Config(void);
//void Input_Capture_ISR(void);

bit BIT_TMP;
uint16_t pulseWidth = 0;
uint16_t range = 0;
uint8_t count = 0;
uint8_t count2 = 0;

void Input_Capture_ISR(void) interrupt 12
{
	if(CAPCON0 & 0x01)	//IC0 flag = 1
	{
		count2++;
		clr_CAPF0;
	}
	if(CAPCON0 & 0x02)	//IC1 flag =1
	{
		clr_CAPF1;
		count++;
		pulseWidth = C1H;
		pulseWidth <<= 8;
		pulseWidth |= C1L;
	}
}

void main(void)
{
	System_Clock_Select(E_HIRCEN); //Internal 22.1184MHz
	GPIO_Config();
	set_EA;
	Capture_Config();
	TIM2_Config();

	
	while(1)
	{
		TRIG = 1;
		Delay10us(1);
		TRIG = 0;
		
		range = ((uint16_t) (((float)pulseWidth) / 58.0));
		Timer0_Delay1ms(500);
	}
}

void TIM2_Config(void)
{
	RCMP2H = HIBYTE(0);
	RCMP2L = LOBYTE(0);
	TL2 = 0; TH2 = 0;
	
	//set_EA; //enable interrupt all
	set_ET2;	//enable interrupt timer2
	set_LDEN;	//enable auto-reload for RCMP2H, RCMP2L, TH2, TL2
	
	T2MOD |= SET_BIT0; //Timer2 compare mode
	TIMER2_DIV_32;
	T2MOD |= SET_BIT3;	//auto-clear
	
	set_TR2; //T2CON |= SET_BIT2
}
void Capture_Config(void)
{	
	CAPCON0 = 0x30;	//enable input capture 1,0
	CAPCON1 = 0x01;	//IC1: rising edge detect, IC0: falling edge detect
	CAPCON2 = 0x30;	//enable noise filter on IC0,1
	set_ECAP;
}


void GPIO_Config(void)
{
	P21_PushPull_Mode;
	P20_Input_Mode;
	P03_PushPull_Mode;
	P04_PushPull_Mode;
}


