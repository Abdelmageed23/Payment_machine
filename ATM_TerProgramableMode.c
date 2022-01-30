#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "UART_interface.h"
#include "I2C.h"

#include "LCD.h"
#include "KEYPAD_interface.h"
#include "EEPROM.h"
#include "Terminal.h"

//#include <util/delay.h>

#define EEPROM_MAX_AMOUNT_ADDRESS	0x10
#define Balance_ADDRESS		0x30
#define MaxAmountSize		9
#define PAN					9
#define KPD_NOT_PRESSED		255
#define Init_BY_ZERO		0
#define LCD_X_initialPos	0
#define LCD_Y_initialPos	0
#define LCD_X_SecLine		1
#define LCD_Y_SecLine		1
#define LCD_Y_elenPos		11
#define LCD_Line_Size		16
#define CustomerData_mode	1
#define MaxAmount_mode		2
#define Exit_mode			3
#define Enter_Button		12
#define KPD_Min_Button		0
#define KPD_Max_Button		9
#define LCD_Y_SixLine		6
#define Balance_intNum		4
#define BalanceSize			7

uint8_t Check_sentData(uint8_t* data,uint8_t* Order);
void Customer_data(void);
void Max_Balance(void);
void Exit(void);

void main(void)
{
	uint8_t local_u8KPDread;

	LCD_vidInit();
	TERMINAL_init();
	EEPROM_init();
	KPD_init();
	while(1)
	{
		LCD_vidClear();
		LCD_vidSetPosition(LCD_X_initialPos,LCD_Y_initialPos);
		LCD_vidWriteString("1-Customer data");
		LCD_vidSetPosition(LCD_X_SecLine,LCD_Y_initialPos);
		LCD_vidWriteString("2-MaxAmount");
		LCD_vidSetPosition(LCD_X_SecLine,LCD_Y_elenPos);
		LCD_vidWriteString("3-Exit");
		local_u8KPDread=KPD_u8GetPressedKey();
		while(local_u8KPDread==KPD_NOT_PRESSED)
		{
			local_u8KPDread=KPD_u8GetPressedKey();
		}
		if(local_u8KPDread==CustomerData_mode)
		{
			Customer_data();
		}

		else if(local_u8KPDread==MaxAmount_mode)
		{
			Max_Balance();
		}

		else if(local_u8KPDread==Exit_mode)
		{
			Exit();
		}
		else
		{
			LCD_vidClear();
			LCD_vidSetPosition(LCD_X_initialPos,LCD_Y_initialPos);
			LCD_vidWriteString("Wrong Number.");
			LCD_vidSetPosition(LCD_X_SecLine,LCD_Y_initialPos);
			LCD_vidWriteString("Try again.");
		//	_delay_ms(1000);/*Delaaaaaaaaaaaaaaaaaaay*/
		}
	}
}

uint8_t Check_sentData(uint8_t* data,uint8_t* Order)
{
	uint8_t local_u8Return=NOK;
	uint8_t local_u8counter=Init_BY_ZERO;
	while(*(Order+local_u8counter) != '\0')
	{
		if(*(Order+local_u8counter) == *(data+local_u8counter))
		{
			local_u8Return=OK;
		}
		else
		{
			local_u8Return=NOK;
			break;
		}
		local_u8counter++;
	}
	return local_u8Return;
}

void Customer_data(void)
{
	uint8_t local_u8KPDread;
	uint8_t local_u8indexI;
	uint8_t local_u8AdminArr[]="ADMIN";
	uint8_t local_u8PassArr[]="1234";
	uint8_t local_u8AdminRead[LCD_Line_Size];
	uint8_t local_u8PassRead[LCD_Line_Size];
	uint8_t local_u8PAN[PAN];
	uint8_t local_u8BALANCE[BalanceSize];

	LCD_vidClear();
	LCD_vidSetPosition(LCD_X_initialPos,LCD_Y_initialPos);
	LCD_vidWriteString("Enter UserName:");
	TERMINAL_read(&local_u8AdminRead);
	if(Check_sentData(&local_u8AdminRead,&local_u8AdminArr))
	{
		LCD_vidClear();
		LCD_vidSetPosition(LCD_X_initialPos,LCD_Y_initialPos);
		LCD_vidWriteString("Enter Password:");
		LCD_vidSetPosition(LCD_X_SecLine,LCD_Y_initialPos);
		for(local_u8indexI=Init_BY_ZERO;local_u8indexI<LCD_Line_Size;local_u8indexI++)
		{
			local_u8KPDread=KPD_u8GetPressedKey();
			while(local_u8KPDread==KPD_NOT_PRESSED)
			{
				local_u8KPDread=KPD_u8GetPressedKey();
			}
			if(local_u8KPDread>=KPD_Min_Button && local_u8KPDread<=KPD_Max_Button)
			{
				LCD_vidWriteCommand('*');
				local_u8PassRead[local_u8indexI]=local_u8KPDread;
			}
			else if(local_u8KPDread==Enter_Button)
			{
				local_u8PassRead[local_u8indexI]='\0';
				break;
			}
			else
			{
				local_u8indexI--;
			}
		}
		if(Check_sentData(&local_u8PassRead,&local_u8PassArr))
		{
			LCD_vidClear();
			LCD_vidSetPosition(LCD_X_initialPos,LCD_Y_initialPos);
			LCD_vidWriteString("Enter PAN:");
			LCD_vidSetPosition(LCD_X_SecLine,LCD_Y_initialPos);
			for(local_u8indexI=Init_BY_ZERO;local_u8indexI<PAN;local_u8indexI++)
			{
				local_u8KPDread=KPD_u8GetPressedKey();
				while(local_u8KPDread==KPD_NOT_PRESSED)
				{
					local_u8KPDread=KPD_u8GetPressedKey();
				}
				if(local_u8KPDread>=KPD_Min_Button && local_u8KPDread<=KPD_Max_Button)
				{
					LCD_vidWriteCommand(local_u8KPDread);
					local_u8PAN[local_u8indexI]=local_u8KPDread;
				}
				else if(local_u8KPDread==Enter_Button)
				{
					local_u8PAN[local_u8indexI]='\0';
					break;
				}
				else
				{
					local_u8indexI--;
				}
			}
			EEPROM_write_bytes(0x20,&local_u8PAN,PAN);
			//_delay_ms(1000);/*Delaaaaaaaaaaaaaaaaaaay*/

			LCD_vidClear();
			LCD_vidSetPosition(LCD_X_initialPos,LCD_Y_initialPos);
			LCD_vidWriteString("Enter Balance:");
			LCD_vidSetPosition(LCD_X_SecLine,LCD_Y_initialPos);
			LCD_vidWriteString("0000.00");
			LCD_vidSetPosition(LCD_X_SecLine,LCD_Y_initialPos);
			for(local_u8indexI=Init_BY_ZERO;local_u8indexI<7;local_u8indexI++)
			{
				local_u8KPDread=KPD_u8GetPressedKey();
				while(local_u8KPDread==KPD_NOT_PRESSED)
				{
					local_u8KPDread=KPD_u8GetPressedKey();
				}
				if(local_u8KPDread>=KPD_Min_Button && local_u8KPDread<=KPD_Max_Button)
				{
					if(local_u8indexI<Balance_intNum)
					{
						LCD_vidWriteCommand(local_u8KPDread);
						local_u8BALANCE[local_u8indexI]=local_u8KPDread;
					}
					else if(local_u8indexI>=Balance_intNum)
					{
						LCD_vidSetPosition(LCD_X_SecLine,LCD_Y_SixLine);
						LCD_vidWriteCommand(local_u8KPDread);
						local_u8BALANCE[local_u8indexI]=local_u8KPDread;
					}
				}
				else if(local_u8KPDread==Enter_Button)
				{
					local_u8BALANCE[local_u8indexI]='\0';
					break;
				}
				else
				{
					local_u8indexI--;
				}
			}
			EEPROM_write_bytes(Balance_ADDRESS,&local_u8BALANCE,PAN);
			//_delay_ms(1000);/*Delaaaaaaaaaaaaaaaaaaay*/
			LCD_vidClear();
			LCD_vidSetPosition(LCD_X_initialPos,LCD_Y_initialPos);
			LCD_vidWriteString("Confirm");
		}
		else
		{
			LCD_vidClear();
			LCD_vidSetPosition(LCD_X_initialPos,LCD_Y_initialPos);
			LCD_vidWriteString("Wrong Password");
		//	_delay_ms(1000);/*Delaaaaaaaaaaaaaaaaaaay*/
		}
	}
	else
	{
		LCD_vidClear();
		LCD_vidSetPosition(LCD_X_initialPos,LCD_Y_initialPos);
		LCD_vidWriteString("Wrong User name");
	//	_delay_ms(1000);/*Delaaaaaaaaaaaaaaaaaaay*/
	}
}

void Max_Balance(void)
{
	uint8_t local_u8MaxAmountArr[MaxAmountSize];
	uint8_t local_u8indexI;
	uint8_t local_u8KPDread;

	LCD_vidClear();
	LCD_vidSetPosition(LCD_X_initialPos,LCD_Y_initialPos);
	LCD_vidWriteString("Enter MaxAmount:");
	LCD_vidSetPosition(LCD_X_SecLine,LCD_Y_initialPos);
	for(local_u8indexI=Init_BY_ZERO;local_u8indexI<10;local_u8indexI++)
	{
		local_u8KPDread=KPD_u8GetPressedKey();
		while(local_u8KPDread==KPD_NOT_PRESSED)
		{
			local_u8KPDread=KPD_u8GetPressedKey();
		}
		if(local_u8KPDread>=KPD_Min_Button && local_u8KPDread<=KPD_Max_Button)
		{
			LCD_vidWriteNumber(local_u8KPDread);
			local_u8MaxAmountArr[local_u8indexI]=local_u8KPDread;
		}
		else if(local_u8KPDread==Enter_Button)
		{
			local_u8MaxAmountArr[local_u8indexI]='\0';
			break;
		}
		else
		{
			local_u8indexI--;
		}
	}
	EEPROM_write_bytes(EEPROM_MAX_AMOUNT_ADDRESS,&local_u8MaxAmountArr,MaxAmountSize);
	//_delay_ms(1000);/*Delaaaaaaaaaaaaaaaaaaay*/
	LCD_vidClear();
	LCD_vidSetPosition(LCD_X_initialPos,LCD_Y_initialPos);
	LCD_vidWriteString("AmountConfirmed");
	//_delay_ms(1000);/*Delaaaaaaaaaaaaaaaaaaay*/
}

void Exit(void)
{
	//do nothing
}
