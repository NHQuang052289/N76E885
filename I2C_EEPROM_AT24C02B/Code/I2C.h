#ifndef _I2C_H_
#define _I2C_H_

#include "N76E885.h"
#include "Version.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Function_Define.h"

#define I2C_GPIO_ENABLE	P23_OpenDrain_Mode; P06_OpenDrain_Mode
#define I2C_CLK 0x37 // 22.1184Mhz / 4(1+ I2C_CLK) = clock bus i2c
#define I2C_ACK 	0
#define I2C_NACK	1
#define timeOut 	1000

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
uint8_t I2C_Read(uint8_t ackMode);
void I2C_Write(uint8_t value);

#endif