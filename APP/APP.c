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

#include "APP.h"
void ATM_OperatingInit()
{
	LCD_vidInit();
	KPD_init();
	TEMP_init();
	BTN_vidInit();
	EEPROM_init();
}

void ATM_OperatingMode()
{
	uint8_t Temp_KBTN=0;
	uint8_t Temp_BTN=0;
	uint8_t Temp_loop=0;
	uint8_t PIN[PIN_SIZE]={0};
	uint8_t PIN_Check[PIN_SIZE]=0;
	uint8_t PIN_Resut=0;
	uint8_t AMOUNT_Check[AMOUT_SIZE]=0;
	LCD_vidSetPosition(0,0);
	LCD_vidWriteString("1-Insert Card");
	LCD_vidSetPosition(1,0);
	LCD_vidWriteString("2-Display Temp");


	Temp_KBTN = KPD_u8GetPressedKey();

	switch(Temp_KBTN)
	{
	case INSERT_CARD:
		PIN_Resut =0;
		Temp_KBTN =0;
		LCD_vidClear();
		LCD_vidWriteString("Enter PIN");
		LCD_vidSetPosition(1,5);
		for(Temp_loop =0;Temp_loop<PIN_SIZE;Temp_loop++)
		{
			PIN[Temp_loop] = KPD_u8GetPressedKey();
			LCD_vidWriteString('*');
			EEPROM_read_bytes( PIN_ADDRESS, &PIN_Check[Temp_loop], PIN_SIZE);
			if(PIN_Check[Temp_loop] == PIN[Temp_loop])
			{
				PIN_Resut++;
			}
			if(PIN_Resut != SUCESS)
			{
				Temp_KBTN = INSERT_CARD;
				break;
			}
			else
			{
				LCD_vidClear();
				LCD_vidWriteString("Enter Amount");
				LCD_vidSetPosition(1,3);
				for(Temp_loop =0;Temp_loop<AMOUT_SIZE - AMOUT_DEICMAL_SIZE;Temp_loop++)
				{
					AMOUNT_Check[Temp_loop] = KPD_u8GetPressedKey();
					LCD_vidWriteNumber(AMOUNT_Check[Temp_loop]);
				}
				LCD_vidWriteString('.');
				for(Temp_loop =AMOUT_SIZE - AMOUT_DEICMAL_SIZE;Temp_loop<AMOUT_SIZE;Temp_loop++)
				{
					AMOUNT_Check[Temp_loop] = KPD_u8GetPressedKey();
					LCD_vidWriteNumber(AMOUNT_Check[Temp_loop]);
				}


				/****************** To be implemented ******************/
				if(CheckMaxAmount()==ABOVE_MAX)
				{
					LCD_vidClear();
					LCD_vidWriteString("Max Amount Exceeded");
					Temp_KBTN = INSERT_CARD;
					break;
				}

			}
		}



		break;

	case DSIPLAY_TEMP:
		LCD_vidClear();
		LCD_vidSetPosition(0,0);
		LCD_vidWriteString("ATM Temp :");
		LCD_vidSetPosition(1,5);

		LCD_vidWriteNumber(TEMP_u8GetReading());

		while(BTN_u8IsPressed()==0);

		ATM_OperatingMode();

		break;
	default:
		break;
	}


}
