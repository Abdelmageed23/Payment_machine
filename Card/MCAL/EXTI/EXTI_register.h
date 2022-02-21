/**********************************************************************/
/**********************************************************************/
/*****************		Author: Mohamed Alaa	***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	EXTI			***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/
/**********************************************************************/

#ifndef _EXTI_REGISTER_H_
#define _EXTI_REGISTER_H_

#define EXTI_MCUCR		*((volatile uint8_t*)0x55) /*MCU control register*/
#define MCUCR_ISC11		3
#define MCUCR_ISC10		2
#define MCUCR_ISC01		1
#define MCUCR_ISC00		0

#define EXTI_MCUCSR		*((volatile uint8_t*)0x54) /*MCU control ans status register*/
#define MCUSCR_ISC2		6

#define EXTI_GICR		*((volatile uint8_t*)0x5B) /*General interrupt control register*/
#define GICR_INT1		7
#define GICR_INT0		6
#define GICR_INT2		5

#define EXTI_GIFR		*((volatile uint8_t*)0x5A) /*General interrupt flag register*/
#define GIFR_INT1		7
#define GIFR_INT0		6
#define GIFR_INT2		5

#endif