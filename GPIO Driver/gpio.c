/*
 * gpio.c
 *
 * Created: 15-Jul-21 3:35:57 AM
 *  Author: Ahmed Azazy
 */ 

#include <avr/io.h>
#include "gpio.h"

void clearBit(GPIO_t * GPIO , uint8_t bitNum)
	{
		GPIO->PORT&=~(1<<bitNum);
	}
	
void setBit(GPIO_t * GPIO , uint8_t bitNum)
	{
		GPIO->PORT|=(1<<bitNum);
	}
