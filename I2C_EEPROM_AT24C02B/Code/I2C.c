#include "I2C.h"

void I2C_Init(void)
{
	I2C_GPIO_ENABLE;
	I2CLK = I2C_CLK;  //feed I2C_CLK value to I2CLK register
	set_I2CEN;	//enable I2C module
}
void I2C_Start(void)
{
	uint16_t t = timeOut;
	set_STA; //Start condition
	clr_SI;	//clear I2C interrupt flag
	while((SI == 0) && (t > 0))
	{
		t--;
	}
}
void I2C_Stop(void)
{
	uint16_t t = timeOut;
	clr_SI;	//clear I2C interrupt flag
	set_STO;	//Stop condition
	while((STO == 1) && (t > 0))
	{
		t--;
	}
}
uint8_t I2C_Read(uint8_t ackMode)
{
	uint16_t t = timeOut;
	uint8_t value = 0x00;
	
	set_AA;	//ACK returned
	clr_SI;
	while((SI == 0) && (t > 0))
	{
		t--;
	}
	
	value = I2DAT;	//value in I2DAT register passed to variable 'value'
	
	if(ackMode == I2C_NACK)
	{
		t = timeOut;
		clr_AA;	//NACK returned
		while((SI == 0) && (t > 0))
		{
			t--;
		}
	}
	
	return value;
}
void I2C_Write(uint8_t value)
{
	uint16_t t = timeOut;
	I2DAT = value;
	clr_STA;
	clr_SI;
	while((SI == 0) && (t > 0))
	{
		t--;
	}
}
