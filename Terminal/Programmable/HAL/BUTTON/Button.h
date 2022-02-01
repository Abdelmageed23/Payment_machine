/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 5/1/2022            */
/* Version  : V01                 */
/**********************************/
#ifndef BUTTON_H_
#define BUTTON_H_

/* Description: Enum to hold configured leds */
typedef enum
{
    BTN_0,
    BTN_1
} BTN_Num_t;

/* Description: Enum to hold internal resistor type for Button */
typedef enum
{
    BTN_PULL_UP_EXT,
    BTN_PULL_DOWN_EXT,
    BTN_PULL_UP_INTERNAL
}BTN_Resistor;

void BTN_vidInit(BTN_Num_t btn);
uint8_t BTN_u8IsPressed(BTN_Num_t btn);

#endif