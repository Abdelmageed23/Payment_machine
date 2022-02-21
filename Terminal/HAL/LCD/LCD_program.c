#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"


#include<util/delay.h>

void LCD_sendComd(uint8_t u8_Data)
{
#if LCD_MODE == LCD_8bitMODE
	/*Set Rs by 0 to send command*/
	DIO_SETpinVal(LCD_Ctrl,LCD_Rs,DIO_LOW);

	/*Set Rw by 0 to select write*/
	DIO_SETpinVal(LCD_Ctrl,LCD_Rw,DIO_LOW);
	/*Send command*/
	DIO_SETportVal(LCD_DataPort,u8_Data);
	/*Activate enable*/
	DIO_SETpinVal(LCD_Ctrl,LCD_E,DIO_HIGH);
	_delay_ms(2);
	DIO_SETpinVal(LCD_Ctrl,LCD_E,DIO_LOW);
#elif LCD_MODE == LCD_4bitMODE
	//LCD_4bitDataPort=(LCD_4bitDataPort & 0x0f)|(u8_Data & 0xf0);
	DIO_SETportVal(LCD_DataPort,(LCD_4bitDataPort & 0x0f)|(u8_Data & 0xf0));
	/*Set Rs by 0 to send command*/
	DIO_SETpinVal(LCD_Ctrl,LCD_Rs,DIO_LOW);
	/*Send Enable pulse*/
	DIO_SETpinVal(LCD_Ctrl,LCD_E,DIO_HIGH);
	_delay_us(1);
	DIO_SETpinVal(LCD_Ctrl,LCD_E,DIO_LOW);

	_delay_ms(2);

	//LCD_4bitDataPort=(LCD_4bitDataPort & 0x0f)|(u8_Data << 4);
	DIO_SETportVal(LCD_DataPort,(LCD_4bitDataPort & 0x0f)|(u8_Data << 4));
	/*Send Enable pulse*/
	DIO_SETpinVal(LCD_Ctrl,LCD_E,DIO_HIGH);
	_delay_us(1);
	DIO_SETpinVal(LCD_Ctrl,LCD_E,DIO_LOW);

	_delay_ms(2);
#endif

}

void LCD_sendData(uint8_t u8_Data)
{
#if LCD_MODE == LCD_8bitMODE
	/*Set Rs by 1 to send data*/
	DIO_SETpinVal(LCD_Ctrl,LCD_Rs,DIO_HIGH);

	/*Set Rw by 0 to select write*/
	DIO_SETpinVal(LCD_Ctrl,LCD_Rw,DIO_LOW);

	/*Send command*/
	DIO_SETportVal(LCD_DataPort,u8_Data);

	/*Activate enable*/
	DIO_SETpinVal(LCD_Ctrl,LCD_E,DIO_HIGH);
	_delay_ms(2);
	DIO_SETpinVal(LCD_Ctrl,LCD_E,DIO_LOW);
#elif LCD_MODE == LCD_4bitMODE
	//LCD_4bitDataPort=(LCD_4bitDataPort & 0x0f)|(u8_Data & 0xf0);
	DIO_SETportVal(LCD_DataPort,(LCD_4bitDataPort & 0x0f)|(u8_Data & 0xf0));
	/*Set Rs by 1 to send command*/
	DIO_SETpinVal(LCD_Ctrl,LCD_Rs,DIO_HIGH);
	/*Send Enable pulse*/
	DIO_SETpinVal(LCD_Ctrl,LCD_E,DIO_HIGH);
	_delay_us(1);
	DIO_SETpinVal(LCD_Ctrl,LCD_E,DIO_LOW);

	_delay_ms(2);

	//LCD_4bitDataPort=(LCD_4bitDataPort & 0x0f)|(u8_Data << 4);
	DIO_SETportVal(LCD_DataPort,(LCD_4bitDataPort & 0x0f)|(u8_Data << 4));
	/*Send Enable pulse*/
	DIO_SETpinVal(LCD_Ctrl,LCD_E,DIO_HIGH);
	_delay_us(1);
	DIO_SETpinVal(LCD_Ctrl,LCD_E,DIO_LOW);

	_delay_ms(2);
#endif

}

void LCD_sendStrData(uint8_t* pu8_Data)
{
	/*local variable to count iterations initialized by 0*/
	uint8_t localu8_counter=0;
	/*Check if the counter reach the end of string*/
	while(*(pu8_Data+localu8_counter)!='\0')
	{
		/*Send string to LCD*/
		LCD_sendData(*(pu8_Data+localu8_counter));
		localu8_counter++;//increament local counter
	}
}

void LCD_GoToXY(uint8_t u8_Xpos,uint8_t u8_Ypos)
{
	uint8_t local_u8Address;
	/*Check if user want first or second line*/
	if(u8_Xpos==0)
	{
		/*Calculate target address*/
		local_u8Address=u8_Ypos;
	}
	else if(u8_Xpos==1)
	{
		/*Calculate target address*/
		local_u8Address=u8_Ypos+0x40;
	}
	/*Set D7 by 1 upon datasheet*/
	local_u8Address=local_u8Address+128;
	/*Send command*/
	LCD_sendComd(local_u8Address);
}

void LCD_CLR(void)
{
	/*Clear data from LCD*/
	LCD_sendComd(0x01);
}

void LCD_WriteNumber(uint32_t u32_NUM)
{
	/*Some local variables that help to convert number to char data*/
	uint32_t local_u32Reminder,local_u32copyNum,local_u32Reverse=1;
	local_u32copyNum=u32_NUM;//take a copy of the number
	/*a while that reverse the number*/
	while(local_u32copyNum!=0)
	{
		local_u32Reminder=local_u32copyNum%10;//get reminder
		local_u32copyNum=local_u32copyNum/10;//divide by 10
		local_u32Reverse=local_u32Reverse*10;
		local_u32Reverse=local_u32Reminder+local_u32Reverse;
	}
	/*send the number element by element to LCD*/
	while(local_u32Reverse!=1)
	{
		local_u32Reminder=local_u32Reverse%10;
		switch(local_u32Reminder)
		{
		case 0:LCD_sendData('0');break;
		case 1:LCD_sendData('1');break;
		case 2:LCD_sendData('2');break;
		case 3:LCD_sendData('3');break;
		case 4:LCD_sendData('4');break;
		case 5:LCD_sendData('5');break;
		case 6:LCD_sendData('6');break;
		case 7:LCD_sendData('7');break;
		case 8:LCD_sendData('8');break;
		case 9:LCD_sendData('9');break;
		}
		local_u32Reverse=local_u32Reverse/10;
	}
}

void LCD_init(void)
{
	DIO_SETportDir(DIO_PORTA,DIO_portOUTPUT);
#if LCD_MODE == LCD_8bitMODE
	_delay_ms(40);
	/*Function set N=1 (Teo lines), F=5*8 Font*/
	LCD_sendComd(0b00111000);
	/*Display control D=1 for enable screening, C=1 for show cursor, B=1 for blinking cursor*/
	LCD_sendComd(0b00001111);
	/*Clear screen*/
	LCD_sendComd(0b00000001);
#elif LCD_MODE == LCD_4bitMODE
	_delay_ms(40);
	/*4 bit mode activate*/
	LCD_sendComd(0x02);
	/*Select N=1 for 2 lines, F= 5*8 Font*/
	LCD_sendComd(0x28);
	/*Display control cursor off*/
	LCD_sendComd(0x0c);
	/*Increament cursor (Shift cursor to right)*/
	LCD_sendComd(0x06);
	/*Clear screen*/
	LCD_sendComd(0x01);
#endif
}
