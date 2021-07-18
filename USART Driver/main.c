/*
 * UART Driver.c
 *
 * Created: 18-Jul-21
 * Author : PC
 */


#include <avr/io.h>
#include "USART.h"

USART_t usart;
char name[] = "Ahmed Azazy-EZ ";
uint8_t data = 0;

int main(void)
{
	DDRD = 0xFF;
    usart.DoubleSpeed = DISABLE;
	usart.MultiProcessor = DISABLE;
	usart.RX_CompleteInterrupt = DISABLE;
	usart.TX_CompleteInterrupt = DISABLE;
	usart.DataReg_EmptyInterrupt = DISABLE;
	usart.EnableReciver = DISABLE;
	usart.EnableTransmitter = ENABLE;
	usart.dataSize = _8_Bits;
	usart.modeSelect = ASYNCHRONOUS;
	usart.parity = NO_PARITY;
	usart.stopBit = _1_STOP_BIT;
	usart.baudRate = 38400;

	USART_Init(&usart);

    while (1)
    {
		while(name[data])
		{
			USART_TransmitChar(&usart , &name[data]);
			data++;
		}
		_delay_ms(5000);
		data=0;
    }
}

