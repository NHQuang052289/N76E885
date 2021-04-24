#include "N76E885.h"
#include "Version.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Function_Define.h"

void WatchDog_Config(void);


bit BIT_TMP;
uint8_t i =0;
	
void main(void)
{

	P03_PushPull_Mode;
	P04_PushPull_Mode;
	System_Clock_Select(E_HIRCEN);   //Internal 22.1184MHz
	
	/*Start program*/
	Timer0_Delay1ms(1000);
	for(i = 0; i <= 7; i++)
	{
		P03 = ~P03;	//yellow
		Timer0_Delay1ms(100);
	}
	
	WatchDog_Config();

	while(1)
	{

		for(i = 0; i <= 15; i++)
		{
			P04 = ~P04;	//red
			Timer0_Delay1ms(200);
			set_WDCLR;	//clear WDT counter 
		}
		while(1);	
	}
}
void WatchDog_Config(void)
{
//	clr_WDTRF;
	TA = 0xAA;
	TA = 0x55;
	WDCON = 0x07; //set diver = 1/256
	set_WDCLR;	//clear WDT counter
//  while((WDCON | ~SET_BIT6) == 0xFF); //if WDCLR = 1, do nothing
//	set_EA;
//	set_EWDT;
	//set_WDTEN;
}
