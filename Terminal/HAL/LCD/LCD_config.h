#ifndef _LCD_CONFIG_H_
#define _LCD_CONFIG_H_

/*Select LCD data port*/
#define LCD_DataPort	DIO_PORTA
#define LCD_4bitDataPort	PORTA

/*Select LCD data port*/
#define LCD_Ctrl		DIO_PORTA
#define LCD_Rs			DIO_PIN1
#define LCD_Rw			DIO_PIN2
#define LCD_E			DIO_PIN3

/*Select:1-LCD_4bitMODE
 	 	 2-LCD_8bitMODE*/
#define LCD_MODE	LCD_4bitMODE


#endif
