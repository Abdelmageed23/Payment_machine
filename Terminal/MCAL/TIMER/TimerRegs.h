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
#define Timer0_OVF			256






/* Timer Modes */
#define 	NORMAL				1
#define  	PWM_PHASE_CORRECT	2
#define	 	CTC					3
#define 	FAST_PWM			4

/* PreScaller*/
#define    NO_CLOCK        		0	// STOP
#define    NO_PRESCALLER		1
#define    CLK_8				2
#define    CLK_64				3
#define    CLK_256				4
#define    CLK_1024				5


/* Overflow Ticks*/
#define Timer0_OVF			256
#define Timer2_OVF			256


/************** TIMER 2 ***************/
#define TCCR2		(*(volatile uint8_t* )(0x45))  //Timer/Counter2 Control Reg
#define TCNT2		(*(volatile uint8_t* )(0x44))
#define OCR2		(*(volatile uint8_t* )(0x43))




#endif
