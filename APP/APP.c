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
void ATM_OperatingInit()
{
	LCD_vidInit();
	KPD_init();
	TEMP_init();
	BTN_vidInit();
	EEPROM_init();
	MOTOR_init();
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

	OperatingHomePage();

}

void Check_Card()
{

		uint8_t Temp_loop=0;
		uint8_t PIN[PIN_SIZE]={0};
		uint8_t PIN_Check[PIN_SIZE]=0;
		uint8_t PIN_Resut=0;
			PIN_Resut =0;
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
					Check_Card();
				}
				else
				{
					Chcek_Transaction();
				}


			}
}

void Chcek_Transaction()
	{
		uint8_t Temp_loop=0;
		uint8_t AMOUNT_Check[AMOUT_SIZE]=0;
		uint32_t Nmeric_amount =0;

		LCD_vidClear();
		LCD_vidWriteString("Enter Amount");
		LCD_vidSetPosition(1,3);

		/********** DOT NOTED NEEDED*********/
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

		/***************** ***************************************/
		/*
		 * convert string to integer
		 */
		Nmeric_amount = strtoint(AMOUNT_Check);

		/****************** To be implemented ******************/
		if(CheckMaxAmount(Nmeric_amount)==ABOVE_MAX)
		{
			LCD_vidClear();
			LCD_vidWriteString("Max Amount Exceeded");
			OperatingHomePage();
		}
		else
		{
			if(check_balance(Nmeric_amount)==0)
			{
				LCD_vidClear();
				LCD_vidWriteString("Insufficient Fund");
				OperatingHomePage();
			}
			else
			{
				Balance -=Nmeric_amount;
				LCD_vidClear();
				LCD_vidWriteString("APPROVED");
				MOTOR_direction(MOTOR_1,FWD);
				MOTOR_speed(50);

			}

		}
	}






void OperatingHomePage()
	{
	uint8_t Temp_KBTN=0;
	LCD_vidSetPosition(0,0);
	LCD_vidWriteString("1-Insert Card");
	LCD_vidSetPosition(1,0);
	LCD_vidWriteString("2-Display Temp");


	Temp_KBTN = KPD_u8GetPressedKey();

	if(Temp_KBTN == INSERT_CARD)
	{
		Check_Card();
	}
	else if (Temp_KBTN == DSIPLAY_TEMP)
	{
		DisplayTemp();
	}

	}

void DisplayTemp(void)
		{
		LCD_vidClear();
		LCD_vidSetPosition(0,0);
		LCD_vidWriteString("ATM Temp :");
		LCD_vidSetPosition(1,5);

		LCD_vidWriteNumber(TEMP_u8GetReading());

		while(BTN_u8IsPressed()==0);

		OperatingHomePage();
		}


uint8_t CheckMaxAmount(uint32_t Amount)
{
	if (Amount> MAX_AMOUNT*AMOUNT_FLOAT)
	{
		return ABOVE_MAX;
	}
	else
	{
		return BELOW_MAX;
	}
}



uint32_t strtoint(char *str)
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


uint8_t check_balance(uint32 Nmeric_amount)
{
	if(Nmeric_amount>Balance)
	{
		Return 1;
	}
	else
		Return 0;
}
