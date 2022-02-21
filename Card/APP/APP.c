/*
 * Sprint6_COMM.c
 *
 * Created: 1/24/2022 8:04:48 PM
 * Author : Team2
 */
#include <string.h>
#include "../LIB/STD_types.h"
#include "../MCAL/UART/UART_regs.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/UART/UART_interface.h"
#include "../MCAL/SPI/SPI_interface.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include "../MCAL/Interrupt/Interrupt_interface.h"

#include "../HAL/EEPROM/EEPROM.h"
#include "../HAL/Terminal/Terminal.h"
#include "../HAL/BUTTON/Button.h"

#include "APP_private.h"

#include <util/delay.h>

ST_card_t st_myCard;
/*******************************************************************************
 *                     Function Implementation                                 *
 *******************************************************************************/
void EXTI_ISR(void)
{
	TERMINAL_write("Sending data...");
	TERMINAL_newLine();
	/*Send PAN to terminal*/
	SPI_TransmitStr(st_myCard.s8_PAN);
	_delay_ms(350);
	/*send PIN to terminal*/
	SPI_TransmitStr(st_myCard.s8_pin);
}

void APP_vidInit(void)
{
	/*Button initialization "Card Entered"*/
	BTN_vidInit(BTN_1);
	/*Virtual terminal initialization "UART"*/
	TERMINAL_init();
	/*EEPROM initialization "TWI"*/
	EEPROM_init();
	/*SPI Master initialization*/
	SPI_MASTinit();
	/*External interrupt initialization*/
	EXTI_init(INT2);
	/*EXTI callback*/
	EXTI_CallBack(&EXTI_ISR);
	/*Global interrupt enable*/
	GlobalInerruptEnable();
}
void APP_vidStart(void)
{
	/*some local variables to go through the code states*/
	uint8_t u8_eeprom_written_flag = Initial_by_Zero;
	uint8_t u8_signal[MAX_TERMINAL_CHAR];

	while (InfiniteLoop)
	{
		/*read if any saved numbers in EEprom*/
		u8_eeprom_written_flag = EEPROM_read_byte(WRITTEN_FLAG_ADDRESS);
		/*if yes*/
		if (u8_eeprom_written_flag == 0XFF)
		{
			/*Read name saved*/
			EEPROM_read_bytes(NAME_STARTING_ADDRESS,
					st_myCard.s8_cardHolderName, NAME_SIZE);
			/*Read PAN saved*/
			EEPROM_read_bytes(PAN_STARTING_ADDRESS, st_myCard.s8_PAN, PAN_SIZE);
			/*Read PIN saved*/
			EEPROM_read_bytes(PIN_STARTING_ADDRESS, st_myCard.s8_pin, PIN_SIZE);
			TERMINAL_write("Card's data is loaded");
			TERMINAL_newLine();
			while (InfiniteLoop)
			{
				/*Check if UART sent any data*/
				if (UART_returnRxStatus() == STD_HIGH)
				{
					/*Read the data sent*/
					TERMINAL_read(u8_signal);
					/*If sent data us "ADMIN"*/
					if (compare(u8_signal, "ADMIN") == STD_LOW)
					{
						/*Go to Admin mode*/
						CARD_admin();
						u8_signal[Loop_FirstElement] = '\0';
						break;
					}
					else
					{
						continue;
					}
				}
				else{  /* do nothing */}
			}
		}
		/*If no*/
		else
		{
			/*Go to admin mode*/
			CARD_admin();
		}
	}
}

/*******************************************************************************
 *                     Private Function Implementation                         *
 *******************************************************************************/
void CARD_admin(void)
{
	/*some local variables to go through the code states*/
	uint8_t u8_validityFlag = LOW, u8_index = Initial_by_Zero;
	uint8_t u8_val[MAX_TERMINAL_CHAR];

	TERMINAL_write("HELLO ADMIN");
	TERMINAL_newLine();
	/*loop until flag low*/
	while (!u8_validityFlag)
	{
		/*Enter card owner name*/
		TERMINAL_write("Please enter a valid card holder name");
		TERMINAL_newLine();
		TERMINAL_read(u8_val);
		/*Check card name validity*/
		for (u8_index = Initial_by_Zero; u8_val[u8_index] != '\0'; u8_index++)
		{
			/*If more than 9 char*/
			if (u8_index >= MAX_PAN_Num)
			{
				TERMINAL_write("MAX length of name is 9 characters long");
				TERMINAL_newLine();
				u8_validityFlag = LOW;
				break;
			}
			/*If not alphabetic*/
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
	/*Display card name on terminal*/
	TERMINAL_write(st_myCard.s8_cardHolderName);
	TERMINAL_newLine();
	/*Save it to EEPROM*/
	EEPROM_write_bytes(NAME_STARTING_ADDRESS, st_myCard.s8_cardHolderName,
			NAME_SIZE);
	delay(delay_OneSec);
	u8_validityFlag = LOW;

	while (!u8_validityFlag)
	{
		TERMINAL_write("Please enter a valid PAN");
		TERMINAL_newLine();
		/*Read PAN from terminal*/
		TERMINAL_read(u8_val);
		/*Check PAN validity*/
		for (u8_index = Initial_by_Zero; u8_val[u8_index] != '\0'; u8_index++)
		{
			/*If entered PAN more than 9*/
			if (u8_index >= MAX_PAN_Num)
			{
				TERMINAL_write("MAX length of PAN is 9 characters long");
				TERMINAL_newLine();
				u8_validityFlag = LOW;
				break;
			}
			/*If not numeric*/
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
	/*Display PAN*/
	TERMINAL_write(st_myCard.s8_PAN);
	TERMINAL_newLine();
	/*Save PAN in EEPROM*/
	EEPROM_write_bytes(PAN_STARTING_ADDRESS, st_myCard.s8_PAN, PAN_SIZE);
	delay(delay_OneSec);
	u8_validityFlag = LOW;

	while (!u8_validityFlag)
	{
		TERMINAL_write("Please enter a valid PIN");
		TERMINAL_newLine();
		/*Read PIN entered*/
		TERMINAL_read(u8_val);
		/*Check PIN validity*/
		for (u8_index = Initial_by_Zero; u8_val[u8_index] != '\0'; u8_index++)
		{
			/*if PIN entered mare than 4*/
			if (u8_index >= MAX_PIN_Num)
			{
				TERMINAL_write("MAX length of PIN is 4 characters long");
				TERMINAL_newLine();
				u8_validityFlag = LOW;
				break;
			}
			/*If not numeric*/
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
	/*Display Card PIN*/
	TERMINAL_write(st_myCard.s8_pin);
	TERMINAL_newLine();
	/*Save PIN to EEPROM*/
	EEPROM_write_bytes(PIN_STARTING_ADDRESS, st_myCard.s8_pin, PIN_SIZE);
	delay(delay_OneSec);
	/*Save flag State*/
	EEPROM_write_byte(WRITTEN_FLAG_ADDRESS, 0XFF);
	delay(delay_OneSec);
}

// Comparing both the strings.
uint8_t compare(uint8_t a[], uint8_t b[])
{
	uint8_t flag = NOK, local_u8Index = Initial_by_Zero;			 // integer variables declaration
	while (a[local_u8Index] != '\0' && b[local_u8Index] != '\0') // while loop
	{
		if (a[local_u8Index] != b[local_u8Index])
		{
			flag = OK;
			break;
		}
		local_u8Index++;
	}
	if (flag == NOK)
		return STD_LOW;
	else
		return STD_HIGH;
}

static void delay(unint16_t max)
{
	unint16_t counter = Initial_by_Zero;
	while (counter < max) // loop to perform a delay
	{
		counter++;
	}
}
