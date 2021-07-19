/*
 * SPI Drivers.c
 *
 * Created: 19-Jul-21
 * Author : Ahmed Azazy
 */



#include <avr/io.h>
#include "SPI.h"
#define F_CPU 8000000U
#include <util/delay.h>
SPI_t spi;
uint8_t name[] = {'A','h','m','e','d',' ','A','z','a','z','y' , 0x01 , 0};
uint8_t data = 0;
int main(void)
{

	DDRB = 0xBF;
	spi.SPI_Interrupt = DISABLE;
	spi.SPI_Enable = ENABLE;
	spi.dataOrder = LSB_FIRST;
	spi.SPI_Mode = SPI_MASTER;
	spi.clockPolarity = RISING_LEADING;
	spi.clockPhase = SAMPLE_ON_TRAILING;
	spi.clockRate = SPI_128_PRESCALE;

	SPI_Init(&spi);

    while (1)
    {
		while(name[data])
			{
				SPI_Send_Receive(name[data]);
				data++;
			}

        _delay_ms(2000);
        data = 0;
    }
}

