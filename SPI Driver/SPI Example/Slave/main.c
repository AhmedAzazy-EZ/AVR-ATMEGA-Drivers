/*
 * SPI Slave.c
 *
 * Created: 19-Jul-21
 * Author : Ahmed Azazy
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "SPI.h"
#define F_CPU 8000000U
#include <util/delay.h>
#include "application.h"

SPI_t spi;
char SPI_Buffer[100];
uint8_t data = 0;
int main(void)
{
		DDRB = 0xCF;
		DDRA = 0xFF;
		LCD_Init();
		sei();
		spi.SPI_Interrupt = ENABLE;
		spi.SPI_Enable = ENABLE;
		spi.dataOrder = LSB_FIRST;
		spi.SPI_Mode = SPI_SLAVE;
		spi.clockPolarity = RISING_LEADING;
		spi.clockPhase = SAMPLE_ON_TRAILING;
		spi.clockRate = SPI_128_PRESCALE;
	LCD_String("LOL");
	SPI_Init(&spi);
    while (1) 
    {
		//do 
		//{
		//while(!(SPSR & (1<<SPIF)));
		//SPI_Buffer[data]=SPDR;
		//} while (SPI_Buffer[data++]!= 0x01);
//
		//LCD_String(SPI_Buffer);
		//data =0;
		
    }
}

ISR(SPI_STC_vect)
{
	SPI_Buffer[data]=SPI_Send_Receive(0x00);
	if(SPI_Buffer[data++]== 0x01)
		{
			LCD_String(SPI_Buffer);
			data=0;
		}	
}