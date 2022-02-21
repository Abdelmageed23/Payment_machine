/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 8/1/2022            */
/* Version  : V01                 */
/**********************************/

#ifndef TIMER_CONFIG_H
#define TIMER_CONFIG_H

//options:  NORMAL
//          CTC
#define TIMER_0_MODE    NORMAL

//options:  from 0 to 255
#define TIMER_0_COMPARE_VALUE   0

/*Options:  0b001  -> no prescaler 
            0b010  -> /8
            0b011  ->/64
            0b100  ->/256
            0b101  ->/1024 */
#define TIMER_0_PRESCALER    0b011

/* Options: STD_ON
            STD_OFF  */
#define TIMER_0_OVF_INT   STD_ON

/* Options: STD_ON
            STD_OFF  */
#define TIMER_0_CTC_INT   STD_OFF





/***********************************************TIMER2********************************/

/*	NORMAL
 * 	CTC
 * 	PWM_PHASE_CORRECT
 * 	FAST_PWM
 */
#define  Timer2_Mode NORMAL

/*
 * NO_CLOCK        	// STOP
 * NO_PRESCALLER
 * CLK_8
 * CLK_32
 * CLK_64
 * CLK_128
 * CLK_256
 * CLK_1024
 */
#define Timer2_prescaler NO_PRESCALLER


/*
 * NO_INTERRUPT
 * NORMAL
 * CTC
 */
#define TIMER2_INTERRUPT	NO_INTERRUPT

#endif
