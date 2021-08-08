/*
 * I2C.c
 *
 * Created: 07-Aug-21
 * Author : Ahmed Azazy
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "I2C.h"
#include "application.h"

#define F_CPU 8000000U
#include "util/delay.h"
I2C_t i2c;


int main(void)
{

	DDRD = 0xFF;
	i2c.I2C_prescaler = I2C_16_PRESCALER;
	i2c.I2c_BitRate = 4;
	i2c.ACK_Generation = ENABLE;
	i2c.I2C_Enable = ENABLE;
	i2c.I2C_Interrupt = ENABLE;
	i2c.I2C_address = 100;
	i2c.I2C_GeneralCall = ENABLE;
	I2C_DataLength = 12;
	I2C_Mode = I2C_READ;
	
	I2C_Init(&i2c);
	sei();
	LCD_Init();
	LCD_String("LOL");
	_delay_ms(5000);
	LCD_String(I2C_Buffer);
    while (1) 
    {
    }
}

