/*
 * Sprint6_COMM.c
 *
 * Created: 1/24/2022 8:04:48 PM
 * Author : No. 01
 */ 

#include "./LIB/STD_types.h"
#include "./HAL/EEPROM/EEPROM.h"
#include "./HAL/Terminal/Terminal.h"
#include <string.h>

#define HIGH 1
#define LOW 0

#define NAME_SIZE 10   //9 characters + 1 NULL
#define PAN_SIZE 10   //9 characters + 1 NULL
#define PIN_SIZE 5   //4 characters +1 NULL
#define MAX_TERMINAL_CHAR 255   // Max size of terminal buffer

#define NAME_STARTING_ADDRESS 0x00   //start at 0 it will take 10 bytes so ending address -> 0xA
#define PAN_STARTING_ADDRESS 0x14    //start at 0xA+10 bytes(A) = 0x14 and it will end at 0x1E (+10) 
#define PIN_STARTING_ADDRESS 0x28	 //leave 10 bytes after ending (0x1E) so it will start at 0x28

typedef struct card_t
{
	sint8_t s8_cardHolderName[NAME_SIZE];
	sint8_t s8_PAN[PAN_SIZE];
	sint8_t s8_pin[PIN_SIZE];
	}ST_card_t;

void CARD_admin(void)
{
	uint8_t u8_validityFlag=LOW,u8_index=0;
	uint8_t u8_val[MAX_TERMINAL_CHAR];
	TERMINAL_init();
	//I2C initialization
	EEPROM_init();
   
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
				u8_validityFlag=LOW;
				break;
			}
			else if (!((u8_val[u8_index]>='A') && (u8_val[u8_index]<='z')))
			{
				TERMINAL_write("Enter only alphabetic characters");
				TERMINAL_newLine();
				u8_validityFlag=LOW;
				break;
			}
			else
			{
				u8_validityFlag=HIGH;
			}
		}
	}
	strncpy(st_myCard.s8_cardHolderName,u8_val,NAME_SIZE);
	TERMINAL_write("THE CARD NAME ENTERED");
	TERMINAL_newLine();
	TERMINAL_write(st_myCard.s8_cardHolderName);
	TERMINAL_newLine();
	EEPROM_write_bytes(NAME_STARTING_ADDRESS,st_myCard.s8_cardHolderName,NAME_SIZE);
	u8_validityFlag=LOW;
		
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
				u8_validityFlag=LOW;
				break;
			}
			else if (!((u8_val[u8_index]>='0') && (u8_val[u8_index]<='9')))
			{
				TERMINAL_write("Enter only numeric characters");
				TERMINAL_newLine();
				u8_validityFlag=LOW;
				break;
			}
			else
			{
				u8_validityFlag=HIGH;
			}
		}
	}
	strncpy(st_myCard.s8_PAN,u8_val,PAN_SIZE);
	TERMINAL_write("THE PAN ENTERED");
	TERMINAL_newLine();
	TERMINAL_write(st_myCard.s8_PAN);
	TERMINAL_newLine();
	EEPROM_write_bytes(PAN_STARTING_ADDRESS,st_myCard.s8_PAN,PAN_SIZE);
	u8_validityFlag=LOW;
		
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
				u8_validityFlag=LOW;
				break;
			}
			else if (!((u8_val[u8_index]>='0') && (u8_val[u8_index]<='9')))
			{
				TERMINAL_write("Enter only numeric characters");
				TERMINAL_newLine();
				u8_validityFlag=LOW;
				break;
			}
			else
			{
				u8_validityFlag=HIGH;
			}
		}
	}
	strncpy(st_myCard.s8_pin,u8_val,PIN_SIZE);
	TERMINAL_write("THE PIN ENTERED");
	TERMINAL_newLine();
	TERMINAL_write(st_myCard.s8_pin);
	TERMINAL_newLine();
	EEPROM_write_bytes(PIN_STARTING_ADDRESS,st_myCard.s8_pin,PIN_SIZE);
}

