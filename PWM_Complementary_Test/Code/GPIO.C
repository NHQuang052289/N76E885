#include "N76E885.h"
#include "Version.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Function_Define.h"
#include <absacc.h>  

#define PWM_ENABLE_ALL PIO=0xFF

void set_PWM_Period(uint16_t valuePeriod);
void set_PWM01(uint16_t value);
void set_PWM23(uint16_t value);
void set_PWM45(uint16_t value);
void set_PWM67(uint16_t value);
void GPIO_Config();
void set_PWM_Dead_Time(uint8_t value);

bit BIT_TMP;

void main(void)
{	
	int i = 0;
	
	System_Clock_Select(E_HIRCEN); //Internal 22.1184MHz
	
	GPIO_Config();
	PWM_ENABLE_ALL;	//PIO=0xFF
	PWM_COMPLEMENTARY_MODE;	//PWMCON1|=0x40;PWMCON1&=0x7F
	PWM_CENTER_TYPE;	//PWMCON1|= SET_BIT4
	PWM_CLOCK_FSYS;	//CKCON&=0xBF 
	PWM_CLOCK_DIV_64;
	PWM0_OUTPUT_INVERSE;
	PWM1_OUTPUT_INVERSE;
	
	
	set_PWM_Period(600);
	set_PWM_Dead_Time(40);
	PWM01_DEADTIME_ENABLE;
	while(1)
	{
    for(i = 0; i < 600; i++)
    {
      set_PWM01(i);
      Timer0_Delay1ms(5);
    }
//    for(i = 600; i > 0; i--)
//    {
//      set_PWM01(i);
//      Timer0_Delay1ms(5);
//    }
	}
	
}

void set_PWM_Dead_Time(uint8_t value)
{
	BIT_TMP = EA;
	EA = 0;
	TA = 0xAA;
	TA = 0x55;
	PDTCNT = value;
	EA = BIT_TMP;
	
}
	
void GPIO_Config()
{
	P10_PushPull_Mode;	//pwm0 	-	r
	P11_PushPull_Mode;	//pwm1	-	r
	P02_PushPull_Mode;	//pwm2	-	g
	P03_PushPull_Mode;	//pwm3	- g
	P05_PushPull_Mode;	//pwm4	-	b
	P06_PushPull_Mode;	//pwm5	-	b
	P07_PushPull_Mode;	//pwm6
	P26_PushPull_Mode;	//pwm7	
}

void set_PWM_Period(uint16_t valuePeriod)
{
	set_CLRPWM; //Clearing PWM 12bit counter.
	PWMPL = LOBYTE(valuePeriod);
	PWMPH = HIBYTE(valuePeriod);
	set_PWMRUN; //run PWM
}
void set_PWM01(uint16_t value)
{
	PWM01L = LOBYTE(value);
	PWM01H = HIBYTE(value);
	set_LOAD;
}
void set_PWM23(uint16_t value)
{
	PWM23L = LOBYTE(value);
	PWM23H = HIBYTE(value);
	set_LOAD;
}
void set_PWM45(uint16_t value)
{
	PWM45L = LOBYTE(value);
	PWM45H = HIBYTE(value);
	set_LOAD;
}
void set_PWM67(uint16_t value)
{
	PWM67L = LOBYTE(value);
	PWM67H = HIBYTE(value);
	set_LOAD;
}