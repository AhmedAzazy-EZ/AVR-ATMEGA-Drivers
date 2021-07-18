/*
 * USART.c
 *
 * Created: 18-Jul-21
 *  Author: Ahmed Azazy
 */ 

#include <avr/io.h>
#include "USART.h"

void USART_Init(USART_t * USART)
	{
		UCSRA |=((USART->DoubleSpeed) << U2X);
		UCSRA |=((USART->MultiProcessor) << MPCM);
		UCSRB |=(USART->RX_CompleteInterrupt << RXCIE);
		UCSRB |=(USART->TX_CompleteInterrupt << TXCIE);
		UCSRB |=(USART->DataReg_EmptyInterrupt << UDRIE);
		UCSRB |=(USART->EnableReciver << RXEN);
		UCSRB |=(USART->EnableTransmitter << TXEN);
		UCSRB |= (((USART->dataSize)&(1<<2)));
		UCSRC |= ((USART->modeSelect << UMSEL) | (1<<URSEL));
		UCSRC |= (((USART->parity)<< UPM) | (1<<URSEL));
		UCSRC |= (((USART->stopBit)<< USBS) | (1<<URSEL));
		UCSRC |= ((((USART->dataSize)&3) << UCSZ0) | (1<<URSEL));
		
		volatile uint32_t UBRR_Value = F_CPU;
		
		if(USART->modeSelect == ASYNCHRONOUS)
			{
				volatile uint32_t denominator = (uint32_t )8 * (2 - USART->DoubleSpeed) * USART->baudRate;
				UBRR_Value = ((F_CPU) / denominator) - 1;
			}
		
		else if (USART->modeSelect == SYNCHRONOUS)
		{
			UBRR_Value = ((F_CPU) / ((uint32_t )2 * USART->baudRate)) - 1;
			UCSRC |= (((USART->clockPolarity) << UCPOL) | (1<<URSEL));
	
		}
			
		 UBRRL = (UBRR_Value & 0xff);
		 UBRRH = ((UBRR_Value >> 8) & 0xF); 		
	}


void USART_TransmitChar(USART_t * USART , void * data)
{
	if(USART->dataSize == _8_Bits)
		{
			while ( !( UCSRA & (1<<UDRE)) );
			UDR = *((char *) data);
		}
	else if(USART->dataSize == _9_Bits)
		{
			while ( !( UCSRA & (1<<UDRE)) );
			UCSRB &=~(1<<TXB8);
			UCSRB |= ((*(uint16_t *) data) & (1<<8))>>8;
			UDR = *(char *) data;
		}
}

void USART_RecieveChar(USART_t * USART , uint16_t * data )
{
	if(USART->dataSize == _8_Bits)
	{
		while ( !( UCSRA & (1<<RXC)) );
		*data = UDR;
	}
	
	else if(USART->dataSize == _9_Bits)
	{
		
		while ( !( UCSRA & (1<<RXC)) );
		*data = 0x00;
		*data |= (UCSRB & (1 << RXB8))>>RXB8;
		*data<<= 8;
		*data |= UDR;
	}
}


void USART_RecieverEnable(void )
{
	UCSRB |= (1<<RXEN);
}

void USART_RecieverDisable(void )
{
	UCSRB &=~ (1<<RXEN);
}

void USART_Reciever_Int_Enable(void )
{
	UCSRB |= (1<<RXCIE);
}

void USART_Reciever_Int_Disable(void )
{
	UCSRB &=~ (1<<RXCIE);
}

void USART_TransmitterEnable(void )
{
	UCSRB |= (1<<TXEN);
}

void USART_TransmitterDisable(void )
{
	UCSRB &=~(1<<TXEN);
}

void USART_Transmitter_Int_Enable(void )
{
	UCSRB |= (1<<TXCIE);
}

void USART_Transmitter_Int_Disable(void )
{
	UCSRB &=~ (1<<TXCIE);
}

void USART_UDR_Empty_Int_Enable(void )
{
	UCSRB |= (1<<UDRIE);
}

void USART_UDR_Empty_Int_Disable(void )
{
	UCSRB &=~ (1<<UDRIE);
}
