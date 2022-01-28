/*
 * UART.c
 *
 * Created: 1/24/2022 8:21:18 PM
 *  Author: No. 01
 */ 

#include "../../01-LIB/STD_types.h"
#include "../../01-LIB/Registers.h"

#include "UART_interface.h"
#include "UART_config.h"

#define HIGH 1
#define LOW 0

void UART_init()
{
	//set baud rate
	UBRRL=(uint8_t)(BAUD_RATE);
	//select UBRRH and shift right the baud rate to set the remaining bits
	UBRRH_UCSRC= (uint8_t)(BAUD_RATE>> REG_SIZE);
	//enable transmit and receive of UART
	UCSRB= (HIGH<<RXEN) | (HIGH<<TXEN);   
	// select UCSRC register and configure 8 bits of data in a frame with 1 stop bit and user configured parity
	UBRRH_UCSRC = (HIGH<<URSEL) | (PARITY_MODE<<UPM0) | (STOP_MODE<<USBS) | (HIGH<<UCSZ1) | (HIGH <<UCSZ0); 
}
void UART_receiveChar(uint8_t* u8_val)
{
	while(LOW==((UCSRA&(HIGH<<RXC))>>RXC));
	*u8_val=UDR;
}
void UART_sendChar(uint8_t u8_char)
{
	while(LOW==((UCSRA&(HIGH<<UDRE))>>UDRE));
	UDR=u8_char;
}
void UART_sendString(uint8_t* u8_str)
{
	uint8_t u8_index=0;
	while((u8_str[u8_index]!='\0')&&(u8_str[u8_index]!='\r')&&(u8_str[u8_index]!='\n'))
	{
		UART_sendChar(u8_str[u8_index]);
		u8_index++;
	}
}
void UART_receiveString(uint8_t* u8_retStr)
{
	uint8_t u8_index=0;
	while(u8_index<255)
	{
		UART_receiveChar(&u8_retStr[u8_index]);
		if('\0'==u8_retStr[u8_index] ||'\n'==u8_retStr[u8_index] ||'\r'==u8_retStr[u8_index])
		{
			u8_retStr[u8_index]='\0';
			break;
		}
		else
		{
			u8_index++;
		}
	}
}