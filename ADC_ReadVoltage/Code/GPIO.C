#include "N76E885.h"
#include "Version.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Function_Define.h"

#define BIT_TO_VOLTAGE 0.004887585533 //	5/1023

void setup(void);
uint16_t ADC_Read(void);
//void ADC_ISR (void);

bit BIT_TMP;

void main(void)
{
	float myResult = 0;
	uint16_t adc_Read = 0; 
	
	System_Clock_Select(E_HIRCEN);	
	P07_Input_Mode;
	setup();
	adc_Read = ADC_Read();
	
	while(1)
	{
		adc_Read = ADC_Read();
		myResult = (adc_Read* BIT_TO_VOLTAGE);
		Timer1_Delay1ms(500);
	}
}
void setup(void)
{
	clr_VREFSEL; //VREFSEL = VDD
	//set_VREFSEL;

	ADCCON0 |= 0x07;	//AIN7 enable
	P07_Input_Mode;
	set_P07DIDS;
	
	/*ADC_DIV=4*/	//ADCCON1 |= 0x20
	clr_ADCDIV2;
	set_ADCDIV1;
	clr_ADCDIV0;
	
	set_ADCEN; //enable ADC
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
//int test = 0;
//void ADC_ISR (void) interrupt 11
//{
//	test = 1;
//	clr_ADCF;                               //clear ADC interrupt flag
//}
