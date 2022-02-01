/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 8/1/2022            */
/* Version  : V01                 */
/**********************************/
#ifndef TIMER_H_
#define TIMER_H_

void TIMER_vidTimer0Init  (void);                          // initalize timer 0 configration
void TIMER_vidTimer0Start(uint8_t intial_value);           // starts the timer with the intial required value
void TIMER_vidTimer0Stop  (void);                          // stops the timer
void TIMER_vidTimer0SetInitValue(uint8_t intial_value);    // function that sets the intial value
uint8_t TIMER_u8Timer0_OVFflag(void);                      // function to get the ovf flag
uint8_t TIMER_u8Timer0_CTCflag(void);                      // function to get CTC flag
 

void SetCallBack_Timer0CTC(void(*func)(void));             // setting the callback function for CTC interrupt
void SetCallBack_Timer0OVF(void(*func)(void));             // setting the callback function for OVF interrupt

#endif
