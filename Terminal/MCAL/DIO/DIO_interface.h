#ifndef _DIO_INTERFACE_H_
#define _DIO_INTERFACE_H_

#define DIO_INPUT	0 //Define pin as an input pin
#define DIO_OUTPUT	1//Define pin as an output pin

#define DIO_portINPUT		0//Define all pins of the port as an input
#define DIO_portOUTPUT		0xff//Define all pins of the port as an output

#define DIO_LOW		0//Set low to a pin
#define DIO_HIGH	1//Set high to a pin

#define DIO_PortLOW			0//Set low to all port pins
#define DIO_PortHIGH		0xff//Set High to all port pins

/*Define some macros of ports to select a suitable one*/
#define DIO_PORTA	0
#define DIO_PORTB	1
#define DIO_PORTC	2
#define DIO_PORTD	3

/*Define some macros of pins to select a suitable one*/
#define DIO_PIN0	0
#define DIO_PIN1	1
#define DIO_PIN2	2
#define DIO_PIN3	3
#define DIO_PIN4	4
#define DIO_PIN5	5
#define DIO_PIN6	6
#define DIO_PIN7	7


/*Declaration of function which sets pin's direction*/
/*The function takes 3 unsigned chars "PORT, PIN and Status" and return an unsigned char*/
uint8_t DIO_SETpinDir(uint8_t u8_PORT,uint8_t u8_PIN,uint8_t u8_STAT);

/*Declaration of function which sets port's direction*/
/*The function takes 3 unsigned chars "PORT and Status" and return an unsigned char*/
uint8_t DIO_SETportDir(uint8_t u8_PORT,uint8_t u8_STAT);

/*Declaration of function which sets pin's value*/
/*The function takes 3 unsigned chars "PORT, PIN and Value" and return an unsigned char*/
uint8_t DIO_SETpinVal(uint8_t u8_PORT,uint8_t u8_PIN,uint8_t u8_VAL);

/*Declaration of function which sets port's value*/
/*The function takes 3 unsigned chars "PORT and Value" and return an unsigned char*/
uint8_t DIO_SETportVal(uint8_t u8_PORT,uint8_t u8_VAL);

/*Declaration of function which gets pin's value*/
/*The function takes 2 unsigned chars "PORT & PIN" + 1 pointer to unsigned char "return value"*/
/*The function returns an unsigned char*/
uint8_t DIO_GETpinVal(uint8_t PORT,uint8_t PIN, uint8_t *RetVal);


#endif
