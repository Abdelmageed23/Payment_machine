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

#endif
