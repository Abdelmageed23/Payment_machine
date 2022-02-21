/**********************************************************************/
/**********************************************************************/
/*****************		Author: Mohamed Alaa	***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	EXTI			***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/
/**********************************************************************/

#ifndef _EXTI_INTERFACE_H_
#define _EXTI_INTERFACE_H_

#define INT0		6
#define INT1		7
#define INT2		5

#define RISING		1
#define FALLING		2

ERROR_STATUS_t EXTI_init(uint8_t u8_INT);

ERROR_STATUS_t EXTI_EdgeTrig(uint8_t u8_INT,uint8_t u8_State);

ERROR_STATUS_t EXTI_Disable(uint8_t u8_INT);

void EXTI_CallBack(void (*ISR)(void));

#endif
