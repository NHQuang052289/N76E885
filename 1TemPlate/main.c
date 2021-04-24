#include "N76E885.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Function_Define.h"

bit BIT_TMP;

void main(void)
{
	int cnt = 0;
//	P03_PushPull_Mode;
//	P04_PushPull_Mode;
	System_Clock_Select(E_HIRCEN);   //Fosc = 2~25MHz XTAL
	P0M1 &= 0xF7; P0M2 |= 0x08;  //P03 as pushpull mode
	P0M1 &= 0xEF; P0M2 |= 0x10;	 //P04 as pushpull mode
	
	while(1)
	{
		P03 = 0;
		Timer0_Delay1ms(500);
		P03 = 1;
		
		P04 = 0;
		Timer0_Delay1ms(500);
		P04 = 1;
		cnt++;
	}
}