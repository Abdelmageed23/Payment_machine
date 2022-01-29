/*
 * Sprint6_COMM.c
 *
 * Created: 1/24/2022 8:04:48 PM
 * Author : No. 01
 */ 

#include "./01-LIB/STD_types.h"
#include "./01-LIB/Registers.h"
#include "./03-HAL/Terminal/Terminal.h"
#include <string.h>

typedef struct card_t
{
	sint8_t s8_cardHolderName[10];
	sint8_t s8_PAN[10];
	sint8_t s8_pin[5];
	}ST_card_t;

void CARD_admin(void)
{
	uint8_t u8_validityFlag=0,u8_index=0;
	uint8_t u8_val[255];
	TERMINAL_init();
	//I2C initialization
	//EEPROM initialization
   
	ST_card_t st_myCard;
	TERMINAL_write("HELLO ADMIN");
	TERMINAL_newLine();
		
	while(!u8_validityFlag)
	{
		TERMINAL_write("Please enter a valid card holder name");
		TERMINAL_newLine();
		TERMINAL_read(u8_val);
		TERMINAL_write(u8_val);
		TERMINAL_newLine();
		for(u8_index=0;u8_val[u8_index]!='\0';u8_index++)
		{
			if(u8_index>=9)
			{
				TERMINAL_write("MAX length of name is 9 characters long");
				TERMINAL_newLine();
				u8_validityFlag=0;
				break;
			}
			else if (!((u8_val[u8_index]>='A') && (u8_val[u8_index]<='z')))
			{
				TERMINAL_write("Enter only alphabetic characters");
				TERMINAL_newLine();
				u8_validityFlag=0;
				break;
			}
			else
			{
				u8_validityFlag=1;
			}
		}
	}
	strncpy(st_myCard.s8_cardHolderName,u8_val,10);
	TERMINAL_write("THE CARD NAME ENTERED");
	TERMINAL_newLine();
	TERMINAL_write(st_myCard.s8_cardHolderName);
	TERMINAL_newLine();
	u8_validityFlag=0;
		
	while(!u8_validityFlag)
	{
		TERMINAL_write("Please enter a valid PAN");
		TERMINAL_newLine();
		TERMINAL_read(u8_val);
		TERMINAL_write(u8_val);
		TERMINAL_newLine();
		for(u8_index=0;u8_val[u8_index]!='\0';u8_index++)
		{
			if(u8_index>=9)
			{
				TERMINAL_write("MAX length of PAN is 9 characters long");
				TERMINAL_newLine();
				u8_validityFlag=0;
				break;
			}
			else if (!((u8_val[u8_index]>='0') && (u8_val[u8_index]<='9')))
			{
				TERMINAL_write("Enter only numeric characters");
				TERMINAL_newLine();
				u8_validityFlag=0;
				break;
			}
			else
			{
				u8_validityFlag=1;
			}
		}
	}
	strncpy(st_myCard.s8_PAN,u8_val,10);
	TERMINAL_write("THE PAN ENTERED");
	TERMINAL_newLine();
	TERMINAL_write(st_myCard.s8_PAN);
	TERMINAL_newLine();
	u8_validityFlag=0;
		
	while(!u8_validityFlag)
	{
		TERMINAL_write("Please enter a valid PIN");
		TERMINAL_newLine();
		TERMINAL_read(u8_val);
		TERMINAL_write(u8_val);
		TERMINAL_newLine();
		for(u8_index=0;u8_val[u8_index]!='\0';u8_index++)
		{
			if(u8_index>=4)
			{
				TERMINAL_write("MAX length of PIN is 4 characters long");
				TERMINAL_newLine();
				u8_validityFlag=0;
				break;
			}
			else if (!((u8_val[u8_index]>='0') && (u8_val[u8_index]<='9')))
			{
				TERMINAL_write("Enter only numeric characters");
				TERMINAL_newLine();
				u8_validityFlag=0;
				break;
			}
			else
			{
				u8_validityFlag=1;
			}
		}
	}
	strncpy(st_myCard.s8_pin,u8_val,5);
	TERMINAL_write("THE PIN ENTERED");
	TERMINAL_newLine();
	TERMINAL_write(st_myCard.s8_pin);
	TERMINAL_newLine();
	//WRITE DATA IN EEPROM
}

