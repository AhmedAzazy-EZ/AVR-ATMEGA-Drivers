/*
 * GPIO Drivers.c
 *
 * Created: 15-Jul-21 2:44:35 AM
 * Author : PC
 */ 

#define F_CPU 8000000U
#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"

int main(void)
{
    GPIOD->DDR = 0xFF;
	GPIOD->PORT = 0xFF;
	
	//DDRA = 0xFF;
	//PORTA = 0xFF;
	uint8_t bitNum = 0 ;
    while (1) 
    {
		
		clearBit(GPIOD , bitNum);
		_delay_ms(100);
		setBit(GPIOD , bitNum);
		bitNum++;
		if(bitNum == 8)
			bitNum = 0;
    }
}

