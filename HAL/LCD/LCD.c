/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 18/1/2022           */
/* Version  : V01                 */
/**********************************/
#include "../../01-LIB/STD_TYPES.h"
#include "../../01-LIB/BIT_MATH.h"
#include "../../01-LIB/DET/Det.h"
#include "../../02-MCAL/DIO/DIO_interface.h"
#include "LCD_cfg.h"
#include "LCD.h"

static uint8_t LCD_Status = LCD_NOT_INITIALIZED;

// ********* PRIVATE FUNCTIONS PROTOTYPE *********

static void delay(uint16_t max);

// ********* FUNCTIONS IMPLMENTATION **********

// function to intialize the LCD with the configured pins
void LCD_vidInit(void)
{
	if (LCD_Status == LCD_NOT_INITIALIZED)
	{
		// setting the pins direction
		DIO_SETpinDir(LCD_Port, LCD_RS, DIO_OUTPUT);
		DIO_SETpinDir(LCD_Port, LCD_RW, DIO_OUTPUT);
		DIO_SETpinDir(LCD_Port, LCD_E, DIO_OUTPUT);
		DIO_SETpinDir(LCD_Port, LCD_D4, DIO_OUTPUT);
		DIO_SETpinDir(LCD_Port, LCD_D5, DIO_OUTPUT);
		DIO_SETpinDir(LCD_Port, LCD_D6, DIO_OUTPUT);
		DIO_SETpinDir(LCD_Port, LCD_D7, DIO_OUTPUT);
		delay(65000);
		LCD_Status = LCD_INITIALIZED;

		LCD_vidWriteCommand(0b00101000);
		delay(5000);
		LCD_vidWriteCommand(0b00001100);
		delay(5000);
		LCD_vidWriteCommand(0b00000001);
		delay(5000);

	}
	else
	{
		// do nothing
	}
}

// function to send a command to LCD
void LCD_vidWriteCommand(uint8_t command)
{
	if (LCD_Status == LCD_NOT_INITIALIZED)
	{
		Det_ReportError(LCD_MODULE_ID, LCD_WRITE_COMMAND_SID);
	}
	else
	{
		DIO_SETpinVal(LCD_Port, LCD_RS, 0);
		DIO_SETpinVal(LCD_Port, LCD_RW, 0);
		DIO_SETpinVal(LCD_Port, LCD_D4, GET_BIT(command, 4));
		DIO_SETpinVal(LCD_Port, LCD_D5, GET_BIT(command, 5));
		DIO_SETpinVal(LCD_Port, LCD_D6, GET_BIT(command, 6));
		DIO_SETpinVal(LCD_Port, LCD_D7, GET_BIT(command, 7));

		DIO_SETpinVal(LCD_Port, LCD_E, STD_HIGH);
		delay(5000);
		DIO_SETpinVal(LCD_Port, LCD_E, STD_LOW);

		DIO_SETpinVal(LCD_Port, LCD_RS, 0);
		DIO_SETpinVal(LCD_Port, LCD_RW, 0);
		DIO_SETpinVal(LCD_Port, LCD_D4, GET_BIT(command, 0));
		DIO_SETpinVal(LCD_Port, LCD_D5, GET_BIT(command, 1));
		DIO_SETpinVal(LCD_Port, LCD_D6, GET_BIT(command, 2));
		DIO_SETpinVal(LCD_Port, LCD_D7, GET_BIT(command, 3));

		DIO_SETpinVal(LCD_Port, LCD_E, STD_HIGH);
		delay(5000);
		DIO_SETpinVal(LCD_Port, LCD_E, STD_LOW);
	}
}

// function that writes  one element on the LCD
void LCD_vidWriteData(uint8_t data)
{
	if (LCD_Status == LCD_NOT_INITIALIZED)
	{
		Det_ReportError(LCD_MODULE_ID, LCD_WRITE_DATA_SID);
	}
	else
	{
		DIO_SETpinVal(LCD_Port, LCD_RS, 1);
		DIO_SETpinVal(LCD_Port, LCD_RW, 0);
		DIO_SETpinVal(LCD_Port, LCD_D4, GET_BIT(data, 4));
		DIO_SETpinVal(LCD_Port, LCD_D5, GET_BIT(data, 5));
		DIO_SETpinVal(LCD_Port, LCD_D6, GET_BIT(data, 6));
		DIO_SETpinVal(LCD_Port, LCD_D7, GET_BIT(data, 7));

		DIO_SETpinVal(LCD_Port, LCD_E, STD_HIGH);
		delay(5000);
		DIO_SETpinVal(LCD_Port, LCD_E, STD_LOW);

		DIO_SETpinVal(LCD_Port, LCD_RS, 1);
		DIO_SETpinVal(LCD_Port, LCD_RW, 0);
		DIO_SETpinVal(LCD_Port, LCD_D4, GET_BIT(data, 0));
		DIO_SETpinVal(LCD_Port, LCD_D5, GET_BIT(data, 1));
		DIO_SETpinVal(LCD_Port, LCD_D6, GET_BIT(data, 2));
		DIO_SETpinVal(LCD_Port, LCD_D7, GET_BIT(data, 3));

		DIO_SETpinVal(LCD_Port, LCD_E, STD_HIGH);
		delay(5000);
		DIO_SETpinVal(LCD_Port, LCD_E, STD_LOW);
	}
}
// function to write string on the LCD
void LCD_vidWriteString(uint8_t *string)
{
	if (string == NULL_PTR)
	{
		Det_ReportError(LCD_MODULE_ID, LCD_WRITE_STRING_SID);
	}
	else if (LCD_Status == LCD_NOT_INITIALIZED)
	{
		Det_ReportError(LCD_MODULE_ID, LCD_WRITE_STRING_SID);
	}
	else
	{
		uint8_t index = 0;
		while (string[index] != 0)
		{
			LCD_vidWriteData(string[index]);
			index++;
		}
	}
}

// function to write a number on the LCD
void LCD_vidWriteNumber(uint32_t num)
{
	if (LCD_Status == LCD_NOT_INITIALIZED)
	{
		Det_ReportError(LCD_MODULE_ID, LCD_WRITE_NUMBER_SID);
	}
	else
	{
	uint32_t reversed = 1;
	if (num == 0)
	{
		LCD_vidWriteData('0');
	}
	else
	{
		while (num != 0)
		{
			reversed = (reversed * 10) + (num % 10);
			num /= 10;
		}
		while (reversed != 1)
		{
			LCD_vidWriteData(((reversed % 10) + '0'));
			reversed /= 10;
		}
	}
	}
}

// function that sets the postion that u want to write in
void LCD_vidSetPosition(uint8_t row, uint8_t col)
{
	if (LCD_Status == LCD_NOT_INITIALIZED)
	{
		Det_ReportError(LCD_MODULE_ID, LCD_SET_POSTION_SID);
	}
	else
	{
	uint8_t adrs = 128;
	switch (row)
	{
	case 0:
		adrs += col;
		break;
	case 1:
		adrs += (64 + col);
		break;
	}
	LCD_vidWriteCommand(adrs);
	}
}

// function to clear the LCD
void LCD_vidClear(void)
{   if (LCD_Status == LCD_NOT_INITIALIZED)
	{
		Det_ReportError(LCD_MODULE_ID, LCD_CLEAR_SID);
	}
	else
	{
	LCD_vidWriteCommand(0b00000001);
	delay(8000);
}
}

//*******  PRIVATE FUNCTIONS IMPLMENTATION ********
static void delay(uint16_t max)
{
	uint16_t counter = 0;
	while (counter < max) // loop to perform a delay
	{
		counter++;
	}
}
