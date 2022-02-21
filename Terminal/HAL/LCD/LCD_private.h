#ifndef _LCD_PRIVATE_H_
#define _LCD_PRIVATE_H_

#define LCD_8bitMODE	1 //8 bit mode: send data to LCD by 8 bits (D0 to D7)
#define LCD_4bitMODE	2 //4 bit mode: send data to LCD by 4 bits (D4 to D7)

#define PORTA	*((volatile char*)0x3B)//LCD_PORT register
#endif
