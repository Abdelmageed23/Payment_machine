/*
 * Sprint6_COMM.c
 *
 * Created: 1/24/2022 8:04:48 PM
 * Author : No. 01
 */
#include <string.h>
#include "../LIB/STD_types.h"
#include "../MCAL/UART/UART_regs.h"
#include "../HAL/EEPROM/EEPROM.h"
#include "../HAL/Terminal/Terminal.h"
#include "../MCAL/UART/UART_interface.h"
#include "../MCAL/SPI/SPI_interface.h"
#include "APP_private.h"

/*******************************************************************************
 *                     Function Implementation                                 *
 *******************************************************************************/
void APP_vidInit(void)
{
	TERMINAL_init();
	EEPROM_init();
	SPI_SLVinit();
}
void APP_vidStart(void)
{

	uint8_t u8_eeprom_written_flag = 0;
	uint8_t u8_signal[MAX_TERMINAL_CHAR];
	ST_card_t st_myCard;
	while (1)
	{

		u8_eeprom_written_flag = EEPROM_read_byte(WRITTEN_FLAG_ADDRESS);
		if (u8_eeprom_written_flag == 0XFF)
		{
			TERMINAL_write((uint8_t *)"FLAG HIGH");
			TERMINAL_newLine();
			EEPROM_read_bytes(NAME_STARTING_ADDRESS,
							  st_myCard.s8_cardHolderName, NAME_SIZE);
			EEPROM_read_bytes(PAN_STARTING_ADDRESS, st_myCard.s8_PAN, PAN_SIZE);
			EEPROM_read_bytes(PIN_STARTING_ADDRESS, st_myCard.s8_pin, PIN_SIZE);
			TERMINAL_write("Card's data is loaded");
			TERMINAL_newLine();
			while (1)
			{
				if (UART_returnRxStatus() == STD_HIGH)
				{

					TERMINAL_read(u8_signal);
					TERMINAL_write(u8_signal);
								TERMINAL_newLine();
					if (compare(u8_signal, "ADMIN") == STD_LOW)
					{
						CARD_admin();
						u8_signal[0] = '\0';
						break;
					}
					else
					{
						continue;
					}
				}

				else if (SPI_flagComplete() == STD_HIGH)
				{SPI_ReceiveStr(u8_signal);
					if (compare(u8_signal, "SEND") == 0)
					
					{
						TERMINAL_write("Sending data to the terminal..");
						TERMINAL_newLine();
						SPI_TransmitStr(st_myCard.s8_cardHolderName);
						SPI_TransmitStr(st_myCard.s8_PAN);
						SPI_TransmitStr(st_myCard.s8_pin);
						u8_signal[0] = '\0';
						break;
					}
				}
				else{  /* do nothing */}
			}
				}
		else
		{
			TERMINAL_write("FLAG LOW");
			TERMINAL_newLine();
			CARD_admin();
		}
	}
}

/*******************************************************************************
 *                     Private Function Implementation                         *
 *******************************************************************************/
void CARD_admin(void)
{

	uint8_t u8_validityFlag = LOW, u8_index = 0;
	uint8_t u8_val[MAX_TERMINAL_CHAR];
	ST_card_t st_myCard;
	TERMINAL_write("HELLO ADMIN");
	TERMINAL_newLine();

	while (!u8_validityFlag)
	{
		TERMINAL_write("Please enter a valid card holder name");
		TERMINAL_newLine();
		TERMINAL_read(u8_val);
		TERMINAL_write(u8_val);
		TERMINAL_newLine();
		for (u8_index = 0; u8_val[u8_index] != '\0'; u8_index++)
		{
			if (u8_index >= 9)
			{
				TERMINAL_write("MAX length of name is 9 characters long");
				TERMINAL_newLine();
				u8_validityFlag = LOW;
				break;
			}
			else if (!((u8_val[u8_index] >= 'A') && (u8_val[u8_index] <= 'z')))
			{
				TERMINAL_write("Enter only alphabetic characters");
				TERMINAL_newLine();
				u8_validityFlag = LOW;
				break;
			}
			else
			{
				u8_validityFlag = HIGH;
			}
		}
	}
	strncpy(st_myCard.s8_cardHolderName, u8_val, NAME_SIZE);
	TERMINAL_write("THE CARD NAME ENTERED");
	TERMINAL_newLine();
	TERMINAL_write(st_myCard.s8_cardHolderName);
	TERMINAL_newLine();
	EEPROM_write_bytes(NAME_STARTING_ADDRESS, st_myCard.s8_cardHolderName,
					   NAME_SIZE);
	delay(65000);
	u8_validityFlag = LOW;

	while (!u8_validityFlag)
	{
		TERMINAL_write("Please enter a valid PAN");
		TERMINAL_newLine();
		TERMINAL_read(u8_val);
		TERMINAL_write(u8_val);
		TERMINAL_newLine();
		for (u8_index = 0; u8_val[u8_index] != '\0'; u8_index++)
		{
			if (u8_index >= 9)
			{
				TERMINAL_write("MAX length of PAN is 9 characters long");
				TERMINAL_newLine();
				u8_validityFlag = LOW;
				break;
			}
			else if (!((u8_val[u8_index] >= '0') && (u8_val[u8_index] <= '9')))
			{
				TERMINAL_write("Enter only numeric characters");
				TERMINAL_newLine();
				u8_validityFlag = LOW;
				break;
			}
			else
			{
				u8_validityFlag = HIGH;
			}
		}
	}
	strncpy(st_myCard.s8_PAN, u8_val, PAN_SIZE);
	TERMINAL_write("THE PAN ENTERED");
	TERMINAL_newLine();
	TERMINAL_write(st_myCard.s8_PAN);
	TERMINAL_newLine();
	EEPROM_write_bytes(PAN_STARTING_ADDRESS, st_myCard.s8_PAN, PAN_SIZE);
	delay(65000);
	u8_validityFlag = LOW;

	while (!u8_validityFlag)
	{
		TERMINAL_write("Please enter a valid PIN");
		TERMINAL_newLine();
		TERMINAL_read(u8_val);
		TERMINAL_write(u8_val);
		TERMINAL_newLine();
		for (u8_index = 0; u8_val[u8_index] != '\0'; u8_index++)
		{
			if (u8_index >= 4)
			{
				TERMINAL_write("MAX length of PIN is 4 characters long");
				TERMINAL_newLine();
				u8_validityFlag = LOW;
				break;
			}
			else if (!((u8_val[u8_index] >= '0') && (u8_val[u8_index] <= '9')))
			{
				TERMINAL_write("Enter only numeric characters");
				TERMINAL_newLine();
				u8_validityFlag = LOW;
				break;
			}
			else
			{
				u8_validityFlag = HIGH;
			}
		}
	}
	strncpy(st_myCard.s8_pin, u8_val, PIN_SIZE);
	TERMINAL_write("THE PIN ENTERED");
	TERMINAL_newLine();
	TERMINAL_write(st_myCard.s8_pin);
	TERMINAL_newLine();
	EEPROM_write_bytes(PIN_STARTING_ADDRESS, st_myCard.s8_pin, PIN_SIZE);
	delay(65000);
	EEPROM_write_byte(WRITTEN_FLAG_ADDRESS, 0XFF);
	TERMINAL_write("FLAG WRITTIN HIGH");
	TERMINAL_newLine();
	delay(65000);
}

// Comparing both the strings.
uint8_t compare(uint8_t a[], uint8_t b[])
{
	uint8_t flag = 0, i = 0;			 // integer variables declaration
	while (a[i] != '\0' && b[i] != '\0') // while loop
	{
		if (a[i] != b[i])
		{
			flag = 1;
			break;
		}
		i++;
	}
	if (flag == 0)
		return STD_LOW;
	else
		return STD_HIGH;
}

static void delay(uint16_t max)
{
	uint16_t counter = 0;
	while (counter < max) // loop to perform a delay
	{
		counter++;
	}
}
