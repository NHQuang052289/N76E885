#include "EEPROM.h"

void EEPROM_Write(uint8_t address, uint8_t value)
{
	I2C_Start();
	I2C_Write(SLAW);
	I2C_Write(address);
	I2C_Write(value);
	I2C_Stop();
}
uint8_t EEPROM_Read(uint8_t address)
{
	uint8_t value = 0x00;
	
	/*find to address in EEPROM*/
	I2C_Start();
	I2C_Write(SLAW);	
	I2C_Write(address);
	
	/*Start Read*/
	I2C_Start();
	I2C_Write(SLAR);
	value = I2C_Read(I2C_NACK);
	I2C_Stop();
	
	return value;
}