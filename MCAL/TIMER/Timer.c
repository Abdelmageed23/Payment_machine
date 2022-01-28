/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 8/1/2022            */
/* Version  : V01                 */
/**********************************/
#include "../../01-LIB/STD_TYPES.h"
#include "../../01-LIB/BIT_MATH.h"
#include "TimerRegs.h"
#include "Timer.h"
#include "TimerConfig.h"

#define __INTR_ATTRS used,externally_visible

void static (*CallBack_Timer0CTC)(void) = NULL_PTR;
void static (*CallBack_Timer0OVF)(void) = NULL_PTR;

static uint8_t gu8_intial_value = 0;

void TIMER_vidTimer0Init(void)
{


    // setting waveform generation mode  ctc or normal
#if ( TIMER_0_MODE == NORMAL)
    TCCR0 = 0;
    if( TIMER_0_OVF_INT == STD_ON){
        TIMSK |= 1;
    }
    else
    {
        //do nothing
    }
#elif (TIMER_0_MODE == CTC)
    TCCR0 = 8;
    OCR0  = TIMER_0_COMPARE_VALUE; // setting the compare value
    if( TIMER_0_CTC_INT == STD_ON){
        TIMSK |= 2;
    }
    else
    {
        //do nothing
    }
#endif

}


void TIMER_vidTimer0Start(uint8_t intial_value){
    TIMER_vidTimer0SetInitValue(intial_value);           // setting intial value
    TCCR0 |= TIMER_0_PRESCALER;    // setting the prescaler
}

void TIMER_vidTimer0Stop(void){
    TCCR0 &= ~(0b111);  // clearing the prescaler bits 
}

uint8_t TIMER_u8Timer0_OVFflag(void){
return GET_BIT(TIFR,0);
}

uint8_t TIMER_u8Timer0_CTCflag(void){
return GET_BIT(TIFR,1);
}

void TIMER_vidTimer0SetInitValue(uint8_t intial_value){
    gu8_intial_value = intial_value ;
    TCNT0  = gu8_intial_value; 
}


void SetCallBack_Timer0CTC(void(*func)(void)){
	CallBack_Timer0CTC=func;
}


void SetCallBack_Timer0OVF(void(*func)(void)){
	CallBack_Timer0OVF=func;
}


void __vector_10(void)__attribute__((signal,__INTR_ATTRS));
void  __vector_10(void){
    if (CallBack_Timer0CTC != NULL_PTR)
    {
        CallBack_Timer0CTC();
    }
    

}

void __vector_11(void)__attribute__((signal,__INTR_ATTRS));
void  __vector_11(void){
    TCNT0  = gu8_intial_value;
 if (CallBack_Timer0OVF != NULL_PTR)
    {
        CallBack_Timer0OVF();
    }

}
