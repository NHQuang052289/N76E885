#ifndef _dht11_h_
#define _dht11_h_

#include "N76E885.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Function_Define.h"

#define HIGH	1
#define LOW		0

#define DHT11_PIN					P05
#define DHT11_PIN_ENABLE	P05_Quasi_Mode
#define DHT11_PIN_HIGH		set_P05
#define DHT11_PIN_LOW			clr_P05

void delay_us(unsigned int value);
void DHT11_Init(void);
uint8_t get_byte(void);
uint8_t get_data(void);

#endif