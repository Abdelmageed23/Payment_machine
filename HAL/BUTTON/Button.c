/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 5/1/2022            */
/* Version  : V01                 */
/**********************************/
#include "../../01-LIB/STD_TYPES.h"
#include "../../01-LIB/BIT_MATH.h"
#include "../../02-MCAL/DIO/DIO_interface.h"
#include "Button.h"
#include "ButtonConfig.h"

void BTN_vidInit(BTN_Num_t btn)
{
    switch (btn)
    {
    case BTN_0:
        DIO_SETpinDir(BTN_0_PORT, BTN_0_PIN, DIO_INPUT);
        if (BTN_0_RESISTOR == BTN_PULL_UP_INTERNAL)
        {
            DIO_SETpinVal(BTN_0_PORT, BTN_0_PIN, STD_HIGH);
        }
        else
        {
            // do nothing
        }
        break;
    case BTN_1:
        DIO_SETpinDir(BTN_1_PORT, BTN_1_PIN, DIO_INPUT);
        if (BTN_1_RESISTOR == BTN_PULL_UP_INTERNAL)
        {
            DIO_SETpinVal(BTN_1_PORT, BTN_1_PIN, STD_HIGH);
        }
        else
        {
            // do nothing
        }
        break;
    default:
        break;
    }
}

uint8_t BTN_u8IsPressed(BTN_Num_t btn)
{   uint16_t counter= 0;
    uint8_t prev_status = 0;
    uint8_t status = 1;

    switch (btn)
    {
    case BTN_0:
        while (1)
        {
            DIO_GETpinVal(BTN_0_PORT, BTN_0_PIN,&prev_status);
            while (counter < 42000)  //loop to perform a delay
            {
                counter++;    
            }
            DIO_GETpinVal(BTN_0_PORT, BTN_0_PIN,&status);
            
            if (status == prev_status)
            {
                break;
            }
        }
        
        if (BTN_0_RESISTOR == BTN_PULL_DOWN_EXT)
        {
            return status;
        }
        else if ((BTN_0_RESISTOR == BTN_PULL_UP_EXT) || (BTN_0_RESISTOR == BTN_PULL_UP_INTERNAL))
        {

            return (!status);
        }

        else
        {
            // do nothing
        }

    case BTN_1:
        while (1)
        {
            DIO_GETpinVal(BTN_1_PORT, BTN_1_PIN,&prev_status);
            while (counter < 42000)  //loop to perform a delay
            {
                counter++;    
            }
            DIO_GETpinVal(BTN_1_PORT, BTN_1_PIN,&status);
            
            if (status == prev_status)
            {
                break;
            }
        }
        if (BTN_1_RESISTOR == BTN_PULL_DOWN_EXT)
        {
            return status;
        }
        else if ((BTN_1_RESISTOR == BTN_PULL_UP_EXT) || (BTN_1_RESISTOR == BTN_PULL_UP_INTERNAL))
        {

            return (!status);
        }

        else
        {
            // do nothing
        }
        break;
    default:
        break;
    }
    return status;
}
