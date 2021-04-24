#include "dht11.h"
#include <stdio.h>

extern uint8_t value[5];

void delay_us(unsigned int value)
{
	while(value > 0)
	{
		nop;
		value--;
	}
}
void DHT11_Init(void)
{
	DHT11_PIN_ENABLE;
	Timer0_Delay1ms(1000);
}
uint8_t get_byte(void)
{
	uint8_t i = 0, value = 0;
	for(i = 0; i < 8; i++)
	{
		value <<= 1;
		while(DHT11_PIN == LOW);	//bus still low
		Delay10us(3);	//neu dht11 send bit0, sau 30us chac chan bus se khong o muc High nua
//		delay_us(30);
		if(DHT11_PIN == HIGH)
		{
			value |= 0x01;
		}
		while(DHT11_PIN == HIGH);		
	}
	return value;
}
uint8_t get_data(void)	//lay data vao mang value[5] va dua ra danh gia ket noi
{
	uint8_t i = 0, checkSum = 0;
	uint8_t check = 0;
	
	/*Start*/
	DHT11_PIN_HIGH;
	DHT11_PIN_LOW;
	Timer0_Delay1ms(18); //giu bus o muc Low 18ms
	DHT11_PIN_HIGH;
	Delay10us(3);	//wait for dht response
//	delay_us(13);
	check = DHT11_PIN;
//	if(DHT11_PIN == HIGH)
	if(check)
	{
		return 1;	//chua thay dht11 response
	}
	
	//neu dht11 pin khac High =>> LOW => part 1 of dht11 response
	Delay10us(8);	//wait end part 1 if dht11 response
//	delay_us(83);
	check = DHT11_PIN;
//	if(DHT11_PIN == LOW)	//bus van o muc Thap
	if(!check)
	{
		return 2;	//response fail
	}
	//neu dht11 pin khac LOW => High => part 2 of dht11 response
	Delay10us(8);	
//	delay_us(80);
	for(i = 0; i <= 4; i++)
	{
		value[i] = get_byte();
	}
	DHT11_PIN_HIGH;
	
	for(i = 0; i <= 3; i++)
	{
		checkSum += value[i];
	}
	printf("============\r\n");
	printf("CS = %x\r\n", checkSum);

	if(checkSum != value[4]) return 3; //checksum error
	else return 0;
}