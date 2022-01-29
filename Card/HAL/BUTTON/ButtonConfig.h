/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 5/1/2022            */
/* Version  : V01                 */
/**********************************/

#ifndef BUTTON_CONFIG_H
#define BUTTON_CONFIG_H

//BUTTON 0 Config
/*options :  DIO_PORTA
             DIO_PORTB
             DIO_PORTC
             DIO_PORTD   */
#define   BTN_0_PORT        DIO_PORTC

/*options : DIO_PIN0
            DIO_PIN1
            DIO_PIN2
            DIO_PIN3
            DIO_PIN4
            DIO_PIN5 
            DIO_PIN6
            DIO_PIN7    */
#define   BTN_0_PIN         DIO_PIN4

/*options:  BTN_PULL_UP_EXT
            BTN_PULL_DOWN_EXT 
            BTN_PULL_UP_INTERNAL */
#define   BTN_0_RESISTOR     BTN_PULL_DOWN_EXT

//BUTTON 1 Config
/*options :  DIO_PORTA
             DIO_PORTB
             DIO_PORTC
             DIO_PORTD   */
#define   BTN_1_PORT        DIO_PORTB

/*options : DIO_PIN0
            DIO_PIN1
            DIO_PIN2
            DIO_PIN3
            DIO_PIN4
            DIO_PIN5
            DIO_PIN6
            DIO_PIN7    */
#define   BTN_1_PIN         DIO_PIN2 

/*options:  BTN_PULL_UP_EXT
            BTN_PULL_DOWN_EXT 
            BTN_BTN_PULL_UP_INTERNAL  */
#define   BTN_1_RESISTOR     BTN_PULL_DOWN_EXT

#endif