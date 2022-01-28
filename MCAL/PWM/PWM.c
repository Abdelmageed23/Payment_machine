/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 10/1/2022            */
/* Version  : V01                 */
/**********************************/
#include "../../01-LIB/STD_TYPES.h"
#include "../../01-LIB/BIT_MATH.h"
#include "../TIMER/Timer.h"
#include "../DIO/DIO_interface.h"
#include "PWM.h"
#include "PWMconfig.h"


static uint8_t PWM_timer_count = 0;
static uint8_t PWM_dutyCycle=0;

void PWM_vidInit(void){
    SetCallBack_Timer0OVF(PWM_vidstart);
    TIMER_vidTimer0Init();
    DIO_SETpinDir(PWM_PORT1 , PWM_PIN1 , DIO_OUTPUT );
    DIO_SETpinDir(PWM_PORT2 , PWM_PIN2 , DIO_OUTPUT );
   // DIO_vidSetPinDirection(PWM_PORT3 , PWM_PIN3 , OUTPUT );
    TIMER_vidTimer0Start(PWM_INTIAL_TIMER_VALUE);
}

// the callback function when the timer overflow 
void PWM_vidstart(void)
{
    PWM_timer_count++;
    if (PWM_timer_count == PWM_dutyCycle)
    {
        DIO_SETpinVal(PWM_PORT1 , PWM_PIN1 , STD_LOW);
        DIO_SETpinVal(PWM_PORT2 , PWM_PIN2 , STD_LOW);
       // DIO_vidSetPinValue(PWM_PORT3 , PWM_PIN3 , STD_LOW);
        
    }
    else if(PWM_timer_count >= 100)
    {
        PWM_timer_count = 0;
        DIO_SETpinVal(PWM_PORT1 , PWM_PIN1 , STD_HIGH);
        DIO_SETpinVal(PWM_PORT2 , PWM_PIN2 , STD_HIGH);
       // DIO_vidSetPinValue(PWM_PORT3 , PWM_PIN3 , STD_HIGH);
        
    }
    else
    {
        // do nothing
    }
}

//function to change dutycycle
void PWM_SetDutyCycle(uint8_t dutyc){
    PWM_dutyCycle = dutyc;
}
