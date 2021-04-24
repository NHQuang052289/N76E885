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
#define SW P30

void set_PWM_Period(uint16_t valuePeriod);
void set_PWM01(uint16_t value);
void set_PWM23(uint16_t value);
void set_PWM45(uint16_t value);
void set_PWM67(uint16_t value);
void GPIO_Config();

bit BIT_TMP;

void main(void)
{
	int i = 0;
	System_Clock_Select(E_LIRCEN); //Internal 10KHz
	GPIO_Config();
	PWM_ENABLE_ALL;	//PIO=0xFF
	PWM_IMDEPENDENT_MODE; //PWMCON1&=0x3F
	PWM_EDGE_TYPE;	//PWMCON1&=~SET_BIT4
	PWM_CLOCK_FSYS;	//CKCON&=0xBF 
	PWM_CLOCK_DIV_2; //Fpwm = 5KHz
	PWM_OUTPUT_ALL_NORMAL;	//PNP=0x00 - PWMn signal outputs directly on PWMn pin
	
	set_PWM_Period(92); //PWM frq = 50Hz
	while(1)
	{
		set_PWM01(11);
	}
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
	P30_Input_Mode; //button pin
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