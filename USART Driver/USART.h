/*
 * USART.h
 *
 * Created: 18-Jul-21
 *  Author: Ahmed Azazy
 */ 


#ifndef USART_H_
#define USART_H_
#include <stdint.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define UPM (4)

typedef enum generic 
{
	DISABLE , 
	ENABLE	
}generic_t;

typedef enum ModeSelect
{
	ASYNCHRONOUS ,
	SYNCHRONOUS		
}modeSelect_t;

typedef enum Character_Size
{
	_5_Bits ,
	_6_Bits , 
	_7_Bits , 
	_8_Bits ,
	_9_Bits = 7		
}characterSize_t;

typedef enum Parity
{
	NO_PARITY ,
	EVEN_PARITY = 2 ,
	ODD_PARITY
}parity_t;

typedef enum StopBit
{
	_1_STOP_BIT ,
	_2_STOP_BIT	
}stopBit_t; 

typedef enum ClockPolarity
{
	TRANS_ON_RISING_EDGE ,
	TRANS_ON_FALLING_EDGE
}clockPolarity_t;

typedef struct USART_Type 
{
	generic_t DoubleSpeed;
	generic_t MultiProcessor;
	generic_t RX_CompleteInterrupt;
	generic_t TX_CompleteInterrupt;
	generic_t DataReg_EmptyInterrupt;
	generic_t EnableReciver;
	generic_t EnableTransmitter;
	characterSize_t dataSize;
	modeSelect_t modeSelect;
	parity_t parity;
	stopBit_t stopBit;
	clockPolarity_t clockPolarity;
	uint16_t baudRate;
}USART_t;



void USART_Init(USART_t * );
void USART_TransmitChar(USART_t *  , void * );
void USART_RecieveChar(USART_t *  , uint16_t *  );


void USART_RecieverEnable(void );
void USART_RecieverDisable(void );
void USART_Reciever_Int_Enable(void );
void USART_Reciever_Int_Disable(void );

void USART_TransmitterEnable(void );
void USART_TransmitterDisable(void );
void USART_Transmitter_Int_Enable(void );
void USART_Transmitter_Int_Disable(void );

void USART_UDR_Empty_Int_Enable(void );
void USART_UDR_Empty_Int_Disable(void );
#endif /* USART_H_ */