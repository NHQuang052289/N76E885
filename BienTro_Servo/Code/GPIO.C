/* P07/AIN7 - Read input voltage
   P03 - Control Servo*/

#include "N76E885.h"
#include "Version.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Function_Define.h"

#define BIT_TO_VOLTAGE 0.004887585533 //	5/1023
#define CONTROL_PIN P03

void ADC_Config(void);
uint16_t ADC_Read(void);
void ADC_ISR (void);
void TIM2_Config(void);
void Timer2_ISR(void);

bit BIT_TMP;
uint8_t i = 0;
uint16_t highTime = 0;

void main(void)
{
	float myResult = 0;
	uint16_t adcRead = 0; 

	System_Clock_Select(E_HIRCEN);	 
	ADC_Config();
	TIM2_Config();
	P03_PushPull_Mode;
	
	while(1)
	{	
		adcRead = ADC_Read();
		myResult = (adcRead* BIT_TO_VOLTAGE);
		Timer1_Delay1ms(50);
		i = ((myResult/(float)5) * 10) + 1 ;
		Timer1_Delay1ms(50);
	}
}
void ADC_Config(void)
{
	clr_VREFSEL; //VREFSEL = VDD
	//set_VREFSEL;

	ADCCON0 |= 0x07;	//AIN7 enable
	P07_Input_Mode;
	set_P07DIDS;
	
	/*ADC_DIV=2*/
	clr_ADCDIV2;
	set_ADCDIV1;
	clr_ADCDIV0;
	
	set_ADCEN; //enable ADC
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

uint16_t ADC_Read(void)
{
	uint16_t adcValue = 0x0000;
	
	clr_ADCF; //clear ADC Flag
  set_ADCS;	//ADC Start
	while(ADCF == 0);
                   
	adcValue = ADCRH;
	adcValue <<= 2;
	adcValue |= ADCRL;
	
	return adcValue;
}
void Timer2_ISR(void) interrupt 5 //timer 2 event vector number 5
{
		//clear timer flag 2
	clr_TF2;
	highTime = i * 20;
	CONTROL_PIN = 1; //high pulse
	Delay10us(highTime);
	CONTROL_PIN = 0;
}
void ADC_ISR (void) interrupt 11
{
	clr_ADCF;                               //clear ADC interrupt flag
}

