/*
 * Terminal.c
 *
 * Created: 1/29/2022 2:04:24 AM
 *  Author: No. 01
 */ 

#include "../../LIB/STD_types.h"
#include "../../MCAL/UART/UART_config.h"
#include "../../MCAL/UART/UART_interface.h"
#include "Terminal.h"

void TERMINAL_init(void)
{
	UART_init();
}
void TERMINAL_read(uint8_t* u8_retStr)
{
	UART_receiveString(u8_retStr);
}
void TERMINAL_write(uint8_t* u8_str)
{
	UART_sendString(u8_str);
}
void TERMINAL_newLine(void)
{
	UART_sendChar('\n');
	UART_sendChar('\r');
}