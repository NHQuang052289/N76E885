
#include "N76E885.h"
#include "Version.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Function_Define.h"

#define Fosc 10000

volatile uint32_t overLoad = 0;
volatile uint32_t endTime = 0;
volatile uint32_t startTime = 0;
volatile uint32_t pulseTime = 0;
volatile float frq = 0;
bit BIT_TMP;

void TIM1_Config(void);
void TIM1_ISR(void);
void TIM2_Config(void);
void TIM2_ISR(void);
void Capture_TIM2_Config(void);
void Input_Capture_ISR(void);
void GPIO_Config(void);

void main(void)
{
	
	System_Clock_Select(E_LIRCEN); //Internal 10KHz
	set_EA; //enable interrupt all
	GPIO_Config();
	TIM1_Config();
	TIM2_Config();
	Capture_TIM2_Config();
	
	
	while(1)
	{
		frq = ((float)10000 / (float)pulseTime);
		Timer3_Delay1ms(100);
	}
}

void TIM1_Config(void)
{
	set_TR1; //run timer 1
	//set_EA; //enable interrupt all
	set_ET1; //enable timer 1 interrupt
	set_T1M; //CKCON   |= SET_BIT4
	TIMER1_MODE1_ENABLE; //TMOD&=0x0F;TMOD|=0x10
	TH1 = 0; TL1 = 0;
	P1M1 |= SET_BIT3; //Timer 1 output Enabled from T1 pin
}
void TIM1_ISR(void) interrupt 3
{
	clr_TF1;//
	TH1 = 0;
	TL1 = 0;
}

void TIM2_Config(void)
{
	
	//set_EA; //enable interrupt all
	set_ET2;	//enable interrupt timer2
	set_TR2; //T2CON |= SET_BIT2
	T2CON &= ~SET_BIT0;
	T2MOD = 0x00;
	//TL2 = 0; TH2 = 0;
}
int test_tim2_isr = 0;
void TIM2_ISR(void) interrupt 5
{
	clr_TF2;
	overLoad++;
	test_tim2_isr++;
}

void Capture_TIM2_Config(void)
{
	CAPCON0 |= SET_BIT4; //input capture 0 enable
	CAPCON1 &= 0xFC; //falling edge
	CAPCON2 |= SET_BIT4; //enable noise filter on IC0
	set_ECAP;	//enable input capture interrupt
	//set_CAPCR;	//Timer 2 value is auto-cleared as 0000H when a capture event occurs.
}
int test_IC_isr = 0;
void Input_Capture_ISR(void) interrupt 12// vertor number 12
{
	if((CAPCON0 & 0x01) == 1)
	{
		test_IC_isr++;
		clr_CAPF0;	//CAPCON0 &= ~SET_BIT0
		endTime = C0H;
		endTime <<= 8;
		endTime |= C0L;
		pulseTime = ((overLoad << 16) - startTime + endTime);
		startTime = endTime;
		overLoad = 0;
	}
}
void GPIO_Config(void)
{
	P21_PushPull_Mode; //T1 output
	P20_Input_Mode;	//T2 capture
}


