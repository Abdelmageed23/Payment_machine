/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 8/1/2022            */
/* Version  : V01                 */
/**********************************/
#ifndef TIMER_REGS_H
#define TIMER_REGS_H


#define TIMSK    *((volatile uint8_t*)0x59)
#define TCCR0    *((volatile uint8_t*)0x53)
#define TCNT0    *((volatile uint8_t*)0x52)
#define OCR0     *((volatile uint8_t*)0x5C)
#define TIFR     *((volatile uint8_t*)0x58)


#endif
