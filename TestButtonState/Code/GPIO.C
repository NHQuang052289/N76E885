#include "N76E885.h"
#include "Version.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Function_Define.h"
#include <absacc.h>  

	/*define GPIO*/
#define RED			P04
#define YELLOW	P03
#define BUTTON	P34

	/*define state button*/
#define KEY_STATE_0 				0 // Button status bit
#define KEY_STATE_1         1
#define KEY_STATE_2         2
#define KEY_STATE_3         3

#define LONG_KEY_TIME 			200 // seconds long press
#define SINGLE_KEY_TIME 		2 // Short press debounce time
 
#define N_KEY								0 	//No state
#define S_KEY 							1 	//Click
#define L_KEY 							10 	//Long press

bit BIT_TMP;

uint8_t key_driver(void);
void GPIO_Config(void);
//uint8_t type_button(void); -- cannot fix longPress

void main(void)
{
	uint8_t stateY = 1, stateR = 1;
	System_Clock_Select(E_HIRCEN);   //Internal 22.1184MHz
	GPIO_Config();
	
	while(1)
	{
		if(key_driver() == S_KEY)
		{
			stateY ^= 1;
			YELLOW = stateY;
		}
		else if(key_driver() == L_KEY)
		{
			stateR ^= 1;
			RED = stateR;
		}
	}
}
void GPIO_Config(void)
{
	/*Config Led*/
	P03_PushPull_Mode;
	P04_PushPull_Mode;
	/*Config button pin*/
	P34_Input_Mode;
}

uint8_t key_driver(void)
{
	static uint8_t keyState = KEY_STATE_0;	//button state var
	static uint16_t pressTime = 0;	//timing press time
	uint8_t keyReturn = N_KEY;
	
	switch(keyState)
	{
		case KEY_STATE_0:	//not press
			if(BUTTON == 0)	//press button
			{
				pressTime = 0;	//clear time press
				keyState = KEY_STATE_1;
			}
		break;
		
		case KEY_STATE_1:	//debounce software
			if(BUTTON == 0)	//press button
			{
				pressTime++;
				if(pressTime >= SINGLE_KEY_TIME)
				{
					keyState = KEY_STATE_2;
				}
				Timer0_Delay1ms(10);
			}
			else keyState = KEY_STATE_0;
		break;
			
		case KEY_STATE_2:	//Determine the type of button valid: whether to click or long press
			if(BUTTON == 1)	//release button =>> is a click
			{
				keyReturn = S_KEY;
				keyState = KEY_STATE_0;
			}
			else	//continue press
			{
				pressTime++;
				if(pressTime >= LONG_KEY_TIME)
				{
					keyReturn = L_KEY;
					keyState = KEY_STATE_3;
				}
				Timer0_Delay1ms(10);
			}
		break;
			
		case KEY_STATE_3:
			if(BUTTON == 1) keyState = KEY_STATE_0;
		break;
		
		default:
			keyState = KEY_STATE_0;
		break;
	}
	return keyReturn;
}
//uint8_t type_button(void)
//{
//	uint8_t preState = 0, type = N_KEY;
//	uint16_t cnt = 0;
//	
//	if(BUTTON == 0)	//if press
//	{
//		//Timer0_Delay1ms(20);
//		preState = 1;
//		cnt++;
//		Timer0_Delay1ms(1);
//	}
//	if((BUTTON == 1) && (preState == 1))
//	{
//		preState = 0;
//		cnt = 0;
//		type = S_KEY; 
//	}
//	else if((preState == 1) &&(cnt == 2000))
//	{
//		preState = 0;
//		cnt = 0;
//		type = L_KEY;
//	}
//	return type;
//}