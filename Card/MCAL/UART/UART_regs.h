/*
 * UART_regs.h
 *
 * Created: 1/29/2022 9:39:34 PM
 *  Author: No. 01
 */ 


#ifndef UART_REGS_H_
#define UART_REGS_H_


#define UBRRH_UCSRC (*((volatile uint8_t *)(0x40)))
#define UBRRL (*((volatile uint8_t *)(0x29)))
#define UCSRB (*((volatile uint8_t *)(0x2A)))
#define UCSRA (*((volatile uint8_t *)(0x2B)))
#define UDR (*((volatile uint8_t *)(0x2C)))


#endif /* UART_REGS_H_ */