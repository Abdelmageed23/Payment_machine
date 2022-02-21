/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 8/1/2022            */
/* Version  : V01                 */
/**********************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
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



void Timer2_Init()
{
#if Timer2_Mode == NORMAL
	CLR_BIT(TCCR2,3);
	CLR_BIT(TCCR2,6);

#elif Timer2_Mode == PWM_PHASE_CORRECT
	CLR_BIT(TCCR2,3);
	SET_BIT(TCCR2,6);

#elif Timer2_Mode == CTC
	CLR_BIT(TCCR2,6);
	SET_BIT(TCCR2,3);

#elif Timer2_Mode == FAST_PWM
	SET_BIT(TCCR2,3);
	SET_BIT(TCCR2,6);
#else
			#error("You chose Wrong clock type")
#endif


#if Timer2_prescaler == NO_CLOCK
		CLR_BIT(TCCR2,0);
		CLR_BIT(TCCR2,1);
		CLR_BIT(TCCR2,2);
#elif Timer2_prescaler == NO_PRESCALLER
		SET_BIT(TCCR2,0);
		CLR_BIT(TCCR2,1);
		CLR_BIT(TCCR2,2);
#elif Timer2_prescaler == CLK_8
		CLR_BIT(TCCR2,0);
		SET_BIT(TCCR2,1);
		CLR_BIT(TCCR2,2);
#elif Timer2_prescaler == CLK_32
		SET_BIT(TCCR2,0);
		SET_BIT(TCCR2,1);
		CLR_BIT(TCCR2,2);
#elif Timer2_prescaler == CLK_64
		CLR_BIT(TCCR2,0);
		CLR_BIT(TCCR2,1);
		SET_BIT(TCCR2,2);
#elif Timer2_prescaler == CLK_128
		SET_BIT(TCCR2,0);
		CLR_BIT(TCCR2,1);
		SET_BIT(TCCR2,2);
#elif Timer2_prescaler == CLK_256
		CLR_BIT(TCCR2,0);
		SET_BIT(TCCR2,1);
		SET_BIT(TCCR2,2);
#elif Timer2_prescaler == CLK_1024
		SET_BIT(TCCR2,0);
		SET_BIT(TCCR2,1);
		SET_BIT(TCCR2,2);
#else
			#error("You chose Wrong clock type")
#endif


#if TIMER2_INTERRUPT ==	NO_INTERRUPT
		CLR_BIT(TIMSK,6);
		CLR_BIT(TIMSK,7);

#elif TIMER2_INTERRUPT == NORMAL
		SET_BIT(TIMSK,6);
		CLR_BIT(TIMSK,7);

#elif TIMER2_INTERRUPT == CTC
		CLR_BIT(TIMSK,6);
		SET_BIT(TIMSK,7);

#else
			#error("You chose Wrong clock type")
#endif


}


uint8_t Timer2_GetValue(uint8_t *getvalue)
{
	*getvalue = TCNT2;
	return TCNT2;
}


void Timer2_Stop()
{
			CLR_BIT(TCCR2,0);
			CLR_BIT(TCCR2,1);
			CLR_BIT(TCCR2,2);
}

void Timer2_SetCTC(uint8_t CompareValue)
{
	OCR2 = CompareValue;
}

void Timer2_SetovfFlag(void)
{
	SET_BIT(TIFR,6);
}


void Timer2_CheckovfFlag(uint8_t *OverflowFlag)
{
	*OverflowFlag = GET_BIT(TIFR,6);
}

void Timer2_SetCTCFlag(void)
{
	SET_BIT(TIFR,7);
}

void Timer2_CheckCTCFlag(uint8_t *OverflowFlag)
{
	*OverflowFlag = GET_BIT(TIFR,7);
}


void Timer2_Start(uint8_t InitalTick)
{
	TCNT2 = InitalTick;
}


void Timer2_SetBusyWait(unint16_t Ticks)
{
	uint8_t Overflow_Number = Ticks / Timer2_OVF;
	uint8_t inital_Tick_value = Timer2_OVF - (Ticks % Timer2_OVF);
	uint8_t ovf_flag=0;
	uint8_t i;
	Timer2_Start(inital_Tick_value);
	for(i=0;i<=Overflow_Number;i++)
			 {
				 Timer2_CheckovfFlag(&ovf_flag);
				 while(ovf_flag==0)
				 {
					 Timer2_CheckovfFlag(&ovf_flag);
				 }
				 Timer2_SetovfFlag();
			 }
}



void Timer2_OvfISR(void (*Timer2_Callback)(void))
{
	Timer2_ovfCallback = Timer2_Callback;
}

/* Timer0 Overflow ISR*/
void __vector_5(void)__attribute__((signal));
void __vector_5(void)
{
	Timer2_ovfCallback();
}



void Timer2_CTCISR(void (*Timer2_Callback)(void))
{
	Timer2_CTCCallback = Timer2_Callback;
}


/* Timer0 CTC ISR*/
void __vector_4(void)__attribute__((signal));
void __vector_4(void)
{
	Timer2_CTCCallback();
}

