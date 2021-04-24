#include "N76E885.h"
#include "Version.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Function_Define.h"
#include <absacc.h>  

void WakeUp_Config(void);
void WakeUp_Timer_ISR(void);

bit BIT_TMP;

void main(void)
{
	int i = 0;
	System_Clock_Select(E_HIRCEN);	//Internal 22.1184MHz
	
	P03_PushPull_Mode;
	P04_PushPull_Mode;
	
	WakeUp_Config();
	
	while(1)
	{
		for(i = 0; i <= 9; i++)
		{
			P03 = ~P03;
			Timer1_Delay1ms(200);
		}
		set_WKTR;	//Wake up timer Run
		set_PD; //Power Down mode enable
		for(i = 0; i <= 7; i++)
		{
			P04 = ~P04;
			Timer1_Delay1ms(500);
		}
		set_WKTR;	//Wake up timer Run
		set_PD;	//Power Down mode enable
	}
}

void WakeUp_Config(void)
{
	WKCON = 0x03;	//diver wake-up = 1/64, source clock wakeUp is 10KHz internal
	RWK = 0x00;	//auto reload att 0x00
	set_EA; //enable interrupt all
	set_EWKT;	//enable wake up interrupt
}
void WakeUp_Timer_ISR(void) interrupt 17
{
	clr_WKTF;	//clear interrupt flag
	clr_WKTR;	//WakeUp is halted
}	