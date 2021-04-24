#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "I2C.h"

#define SLAW 0xA0	//slave address write
#define SLAR 0xA1	//slave address read

void EEPROM_Write(uint8_t address, uint8_t value);
uint8_t EEPROM_Read(uint8_t address);

#endif