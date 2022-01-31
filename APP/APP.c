/*
 * Abdelrahman
 *
 * ATM Operating mode
 */

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../LIB/DET/Det.h"

#include "../MCAL/TIMER/Timer.h"

#include "../HAL/LCD/LCD.h"
#include "../HAL/KEYPAD/KEYPAD_interface.h"
#include "../HAL/BUTTON/Button.h"
#include "../HAL/EEPROM/EEPROM.h"
#include "../HAL/TEMP/TEMP_interface.h"
#include "../HAL/motor/Motor.h"

#include "APP.h"


/* Initialization Operating Mode ATM*/
void ATM_OperatingInit()
{
	Timer2_Init();
	LCD_vidInit();
	KPD_init();
	TEMP_init();
	BTN_vidInit(BTN_1);
	EEPROM_init();
	MOTOR_init(MOTOR_1);
}

void ATM_OperatingMode()
{
	OperatingHomePage();

	/*if(Check_CardPAN()== NOT_APPROVED)
	{
	while(KPD_u8GetPressedKey()!=HOMEPAGE)
		{
			LCD_vidClear();
			LCD_vidSetPosition(0,0);
			LCD_vidWriteString("Invalid User PAN");
			LCD_vidSetPosition(1,0);
			LCD_vidWriteString("Exit: Home button :");
		}
	OperatingHomePage();
	}
	else
	{
		if(Check_PINCard()== NOT_APPROVED)
		{
			Check_PINCard();
		}
	}*/

}



void OperatingHomePage()
{
	uint8_t Temp_KBTN=0;
	LCD_vidSetPosition(0,0);
	LCD_vidWriteString("1-Insert Card");
	LCD_vidSetPosition(1,0);
	LCD_vidWriteString("2-Display Temp");

	/*	polling */
	Temp_KBTN = KPD_u8GetPressedKey();
	while(Temp_KBTN != INSERT_CARD && Temp_KBTN != DSIPLAY_TEMP)
	{
		Temp_KBTN = KPD_u8GetPressedKey();
	}


	if(Temp_KBTN == INSERT_CARD)
	{
		Check_CardPAN();
	}
	else if (Temp_KBTN == DSIPLAY_TEMP)
	{
		DisplayTemp();
	}

}


void DisplayTemp(void)
{


	while(KPD_u8GetPressedKey()!=HOMEPAGE)
	{
				LCD_vidClear();
				LCD_vidSetPosition(0,0);
				LCD_vidWriteString("ATM Temp :");
				LCD_vidSetPosition(0,12);
				LCD_vidWriteNumber(TEMP_u8GetReading());
				LCD_vidSetPosition(1,0);
				LCD_vidWriteString("Exit: Home button :");

	}

	OperatingHomePage();
}




/* Need to check in data base too*/
void Check_CardPAN()
{
	uint8_t	PAN_ATM_index =0;
	uint8_t PAN_Temp =0;
	uint8_t Card_Pan[PAN_SIZE]= {0};
	uint8_t Card_Check = NOT_APPROVED;
			/*Scanning the card data*/

/****************öADVANCED ***************************************************/
		/*LCD_vidClear();
		LCD_vidWriteString("Scanning");
		Timer2_SetBusyWait(9375);
		LCD_vidWriteString(" .");
		Timer2_SetBusyWait(9375);
		LCD_vidWriteString(" .");
		Timer2_SetBusyWait(9375);
		LCD_vidWriteString(" .");
		Timer2_SetBusyWait(9375);*/
/****************ö END ADVANCED ***************************************************/

			/*Scanning the card data with ATM data*/
			SPI_ReceiveStr(Card_Pan);
			for(PAN_ATM_index = 0; PAN_ATM_index < NUM_ATM_ACCOUNTS ;PAN_ATM_index ++)
			{
				EEPROM_read_bytes ( PAN_ADDRESS,  &PAN_Temp,  PAN_SIZE);
				if(strcmp(PAN_Temp , Card_Pan) == 0)
				{
					Check_CardPIN();

				}
				else
				{
					while(KPD_u8GetPressedKey()!=HOMEPAGE)
					{
						LCD_vidClear();
						LCD_vidSetPosition(0,0);
						LCD_vidWriteString("Invalid User PAN");
						LCD_vidSetPosition(1,0);
						LCD_vidWriteString("Exit: Home button :");
					}
					ATM_OperatingMode();

				}
			}
}


void Check_CardPIN()
{
	uint8_t PIN_Index =0;
	uint8_t PIN_Check[PIN_SIZE]={0};
	uint8_t	PIN_Card[PIN_SIZE]={0};

			/* Checking Card PIN*/
			LCD_vidClear();
			LCD_vidWriteString("Enter PIN");
			LCD_vidSetPosition(1,5);
			EEPROM_read_bytes( PIN_ADDRESS, &PIN_Card[PIN_Index], PIN_SIZE);
			for(PIN_Index =0;PIN_Index<PIN_SIZE;PIN_Index++)
			{
				while(KPD_u8GetPressedKey()== KPD_NO_Pressed);
				PIN_Check[PIN_Index] = KPD_u8GetPressedKey();
				LCD_vidWriteString('*');
			}
			/***************************************Strcmp********************/
				if(strcmp(PIN_Check,PIN_Card)==0)
				{
					Check_Transaction();

				}
				else
				{
		/******************** adding home option later*********************************/
					while(KPD_u8GetPressedKey()!= 1)
					{
						LCD_vidClear();
						LCD_vidSetPosition(0,0);
						LCD_vidWriteString("Invalid PIN");
						LCD_vidSetPosition(1,0);
						LCD_vidWriteString("Again:Press 1");
					}
					Check_CardPIN();

				}
}

void Check_Transaction()
	{
		uint8_t Trans_index=0;
		uint32_t AMOUNT_Check=0;
		uint32_t Account_Balance =0;
		uint8_t Balance_Str[BALANCE_SIZE] ={0};
		uint8_t balance_temp=0;
		uint8_t balance_address = BALANCE_ADDRESS;

		EEPROM_read_bytes ( BALANCE_ADDRESS,  &Balance_Str,  BALANC_ADDRESS_COUNT);
		LCD_vidClear();
		LCD_vidWriteString("Enter Amount");
		LCD_vidSetPosition(1,3);
		LCD_vidWriteString("0000.00");
		LCD_vidSetPosition(1,3);

		for(Trans_index =0;Trans_index<AMOUT_SIZE - AMOUT_DEICMAL_SIZE;Trans_index++)
		{
			balance_temp = KPD_u8GetPressedKey();
			LCD_vidWriteNumber(balance_temp);
			AMOUNT_Check = AMOUNT_Check +10 * balance_temp;
		}
		LCD_vidWriteString('.');
		for(Trans_index =AMOUT_SIZE - AMOUT_DEICMAL_SIZE;Trans_index<AMOUT_SIZE;Trans_index++)
		{
			balance_temp = KPD_u8GetPressedKey();
			LCD_vidWriteNumber(balance_temp);
			AMOUNT_Check = AMOUNT_Check +10 * balance_temp;
		}

		/***************** ***************************************/
		/*
		 * convert string to integer
		 */
		Account_Balance = strtoint(Balance_Str);

		/****************** To be implemented ******************/
		if(CheckMaxAmount(AMOUNT_Check)==ABOVE_MAX)
		{
			while(KPD_u8GetPressedKey()!= 1)
			{
				LCD_vidClear();
				LCD_vidSetPosition(0,0);
				LCD_vidWriteString("Max Amount Exceeded");
				LCD_vidSetPosition(1,0);
				LCD_vidWriteString("Home :Press 1");
			}

			OperatingHomePage();
		}
		else
		{
			if(AMOUNT_Check>Account_Balance)
			{
				while(KPD_u8GetPressedKey()!= 1)
				{
					LCD_vidClear();
					LCD_vidSetPosition(0,0);
					LCD_vidWriteString("Insufficient Fund");
					LCD_vidSetPosition(1,0);
					LCD_vidWriteString("Home :Press 1");
				}

				OperatingHomePage();
			}
			else
			{

				Account_Balance = Account_Balance -AMOUNT_Check;


		/* Need to check the address to be stored*/
				StoreNewBalance(Account_Balance,BALANCE_ADDRESS);
				TransactionApproved();
			}
		}
	}
	/*******************To be implemented******************************/
			/*
			 * Pushing new balance to EEPROM
			 */

void TransactionApproved()
{
		LCD_vidClear();
		LCD_vidWriteString("APPROVED");
		MOTOR_direction(MOTOR_1,FWD);
		MOTOR_speed(50);
		Timer2_SetBusyWait(ONE_SECOND);
		MOTOR_off(MOTOR_1);
		OperatingHomePage();
}





uint8_t CheckMaxAmount(uint32_t Amount)
{
	if (Amount> MAX_AMOUNT * AMOUNT_FLOAT)
	{
		return ABOVE_MAX;
	}
	else
	{
		return BELOW_MAX;
	}
}



uint32_t strtoint(uint8_t *str)
{
	uint32_t Result =0;
    uint8_t i=0;
        for(i=0;str[i]!='\0';i++)
        {
        	if(str[i]=='.')
			{
				continue;
			}
        	Result = Result*10+str[i]-'0';
        }
        return Result;
}

void StoreNewBalance(uint32_t num , uint8_t balance_address)
{
	uint32_t reversed = 1;
	uint8_t index =0;
		if (num == 0)
		{
			EEPROM_write_byte(balance_address,'0');
			balance_address++;
			index++;
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
				if(index == AMOUT_DEICMAL_SIZE)
				{
					continue ;
				}
				EEPROM_write_byte(BALANCE_ADDRESS,((reversed % 10) + '0'));
				reversed /= 10;
				balance_address++;
				index++;
			}
		}
}

