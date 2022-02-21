/*
 * Team 2
 *
 * ATM Terminal
 */
#include "APP.h"

#include <util/delay.h>

/**
 * Global varibale
 */
uint8_t Card_Data =NOT_FOUND;
uint8_t	PIN_Card[PIN_SIZE];
uint8_t Card_Pan[PAN_SIZE];

uint8_t CardData_flag=E_NOK;

void EXTI_ISR(void)
{
	uint8_t local_u8Counter;
	for(local_u8Counter=Init_BY_ZERO;local_u8Counter<2;local_u8Counter++)
	{
		if(local_u8Counter==FirstRound)
		{
			SPI_ReceiveStr(Card_Pan);
		}
		else if(local_u8Counter==SecRound)
		{
			SPI_ReceiveStr(PIN_Card);
			CardData_flag=E_OK;
		}
	}
}

void ATM_Init(void)
{
	/*Terminal initialization "UART"*/
	TERMINAL_init();
	/*Timer2 initialization "dalay"*/
	Timer2_Init();
	/*Temperature sensor initialization*/
	TEMP_init();
	/*Button initialization*/
	BTN_vidInit(BTN_1);
	/*EEPROM initialization*/
	EEPROM_init();
	/*Motor initialization*/
	MOTOR_init(MOTOR_1);
	/*LCD initialization*/
	LCD_init();
	/*KEYPAD initialization*/
	KPD_init();
	/*SPI slave initialization*/
	SPI_SLVinit();
	/*External interrupt initialization*/
	EXTI_init(INT2);
	/*EXTI callback*/
	EXTI_CallBack(&EXTI_ISR);
	/*Global interrupt initialization*/
	GlobalInerruptEnable();
}

void ATM_Prog_Mode(void)
{
	uint8_t local_u8KPDRead=KPD_NOT_PRESSED;
	LCD_CLR();
	LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
	LCD_sendStrData("1-Program. mode");
	LCD_GoToXY(LCD_X_SecLine,LCD_Y_initialPos);
	LCD_sendStrData("2-Operating mode");
	local_u8KPDRead=KPD_u8GetPressedKey();
	/*Wait for key pressed*/
	while(local_u8KPDRead == KPD_NOT_PRESSED)
	{
		local_u8KPDRead=KPD_u8GetPressedKey();
	}
	/*If pressed 1 */
	if(local_u8KPDRead == ProgMode)
	{
		LCD_CLR();
		LCD_WriteNumber(local_u8KPDRead);
		/*Start programmable mode*/
		Programable_mode();
	}
	/*If pressed 2*/
	else if (local_u8KPDRead == OperRound)
	{
		LCD_CLR();
		LCD_WriteNumber(local_u8KPDRead);
		/*Start operating mode*/
		OperatingHomePage();
	}
	else
	{
		LCD_CLR();
		LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
		LCD_sendStrData("Wrong Selection");
	}
}


/* Initialization Operating Mode ATM*/
void OperatingHomePage()
{
	uint8_t Temp_KBTN=Init_BY_ZERO;
	LCD_CLR();
	LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
	LCD_sendStrData("1-Insert Card");
	LCD_GoToXY(LCD_X_SecLine,LCD_Y_initialPos);
	LCD_sendStrData("2-Display Temp");

	/*	wait for key pressed */
	Temp_KBTN = KPD_u8GetPressedKey();

	while(Temp_KBTN != INSERT_CARD && Temp_KBTN != DSIPLAY_TEMP)
	{
		if(Temp_KBTN != KPD_NOT_PRESSED){
			LCD_GoToXY(LCD_X_initialPos,LCD_POS13);
			/*display the key pressed*/
			LCD_WriteNumber(Temp_KBTN);
		}

		Temp_KBTN = KPD_u8GetPressedKey();
	}

	/*if pressed key is 1*/
	if(Temp_KBTN == INSERT_CARD)
	{
		Check_CardPAN();
	}
	/*if pressed key is 2*/
	else if (Temp_KBTN == DSIPLAY_TEMP)
	{
		DisplayTemp();
	}
	else if (Temp_KBTN == HOME_KEY)
	{
		ATM_Prog_Mode();
	}

}

/*Display temperature function*/
void DisplayTemp(void)
{
	LCD_CLR();
	LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
	LCD_sendStrData("ATM Temp :");
	/*Display temperature until home key pressed "#"*/
	while(KPD_u8GetPressedKey()!=HOME_KEY)
	{

		LCD_GoToXY(LCD_X_initialPos,LCD_POS12);
		/*Get temperature reading and display*/
		LCD_WriteNumber(TEMP_u8GetReading());
		LCD_GoToXY(LCD_X_SecLine,LCD_Y_initialPos);
		LCD_sendStrData("Back: Home  ");

	}

	OperatingHomePage();
}

/* Need to check in data base too*/
void Check_CardPAN()
{
	uint8_t	PAN_ATM_index ;
	uint8_t PAN_Temp[PAN_SIZE];

	uint8_t Card_Check = NOT_APPROVED;

	/*Scanning the card data*/
	LCD_CLR();
	LCD_sendStrData("Scanning");

	LCD_sendStrData(" .");

	LCD_sendStrData(" .");

	LCD_sendStrData(" .");

	while(CardData_flag==E_NOK);
	/*loop for searching for PAN*/
	for(PAN_ATM_index = PAN_INITAL_ADDRESS; PAN_ATM_index < (NUM_ATM_ACCOUNTS * ACCOUNT_SIZE) ;PAN_ATM_index += ACCOUNT_SIZE)
	{
		/*READ EEPROM Saved PANs*/
		EEPROM_read_bytes ( PAN_ATM_index,  PAN_Temp,  PAN_SIZE);
		/*Compare the entered pan with the saved*/
		if(strcmp(PAN_Temp , Card_Pan) == Identical)
		{
			/*if identical*/
			Card_Data = PAN_Temp;
			/*Go to Check the PIN*/
			Check_CardPIN();
		}
		else
		{
			/*do nothing*/
		}
	}
	TERMINAL_write("PAN is not found");
	TERMINAL_newLine();
	OperatingHomePage();
}


void Check_CardPIN()
{
	uint8_t PIN_Index =Init_BY_ZERO;
	uint8_t Temp_key = KPD_NO_Pressed;
	uint8_t PIN_Check[PIN_SIZE]={0};


	uint32_t PIN_Numeric =Init_BY_ZERO;
	uint32_t PIN_INPUT_Numeric =Init_BY_ZERO;

	/* Checking Card PIN*/
	LCD_CLR();
	LCD_sendStrData("Enter PIN");
	LCD_GoToXY(LCD_X_SecLine,LCD_POS5);

	PIN_Numeric = strtoint(PIN_Card);
	for(PIN_Index =Init_BY_ZERO;PIN_Index<4;PIN_Index++)
	{
		Temp_key =KPD_u8GetPressedKey();
		while(Temp_key== KPD_NO_Pressed)
		{
			Temp_key =KPD_u8GetPressedKey();
		}
		PIN_INPUT_Numeric =PIN_INPUT_Numeric *10 + Temp_key;
		LCD_sendStrData("*");
	}
	LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
	LCD_WriteNumber(PIN_INPUT_Numeric);
	if(PIN_Numeric == PIN_INPUT_Numeric)
	{
		Check_Transaction();
	}
	else
	{
		LCD_CLR();
		LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
		LCD_sendStrData("Invalid PIN");
		LCD_GoToXY(LCD_X_SecLine,LCD_Y_initialPos);
		LCD_sendStrData("1-Again     Home");

		Temp_key =KPD_u8GetPressedKey();
		while(Temp_key!= HOME_KEY && Temp_key!= AGAIN_KEY)
		{
			Temp_key =KPD_u8GetPressedKey();

		}
		if(Temp_key == HOME_KEY)
		{
			OperatingHomePage();
		}
		else
		{
			Check_CardPIN();
		}
	}
}

void Check_Transaction()
{
	uint8_t Temp_Key = KPD_NO_Pressed;
	uint8_t Trans_index=Init_BY_ZERO;
	uint32_t AMOUNT_Check=Init_BY_ZERO;
	uint32_t Account_Balance =Init_BY_ZERO;
	uint8_t Balance_Str[BALANCE_SIZE] ={0};
	uint8_t balance_temp=Init_BY_ZERO;
	uint8_t balance_address = BALANCE_ADDRESS;

	EEPROM_read_bytes ( Card_Data+PAN_SIZE,  &Balance_Str,  BALANC_ADDRESS_COUNT);
	LCD_CLR();
	LCD_sendStrData("Enter Amount");
	LCD_GoToXY(LCD_X_SecLine,LCD_POS3);
	LCD_sendStrData("0000.00");
	LCD_GoToXY(LCD_X_SecLine,LCD_POS3);

	for(Trans_index =Init_BY_ZERO;Trans_index<AMOUT_SIZE - AMOUT_DEICMAL_SIZE;Trans_index++)
	{
		Temp_Key =KPD_u8GetPressedKey();
		while(Temp_Key== KPD_NO_Pressed)
		{
			Temp_Key =KPD_u8GetPressedKey();
		}
		balance_temp = Temp_Key;
		LCD_WriteNumber(balance_temp);
		AMOUNT_Check = AMOUNT_Check *10+ balance_temp;
	}
	LCD_sendStrData(".");
	for(Trans_index =AMOUT_SIZE - AMOUT_DEICMAL_SIZE;Trans_index<AMOUT_SIZE;Trans_index++)
	{
		Temp_Key =KPD_u8GetPressedKey();
		while(Temp_Key== KPD_NO_Pressed)
		{
			Temp_Key =KPD_u8GetPressedKey();
		}
		balance_temp = Temp_Key;
		LCD_WriteNumber(balance_temp);
		AMOUNT_Check = AMOUNT_Check *10+ balance_temp;
	}


	/*
	 * convert string to integer
	 */
	Account_Balance = strtoint(Balance_Str);

	/****************** To be implemented ******************/

	if(CheckMaxAmount(AMOUNT_Check)==ABOVE_MAX)
	{
		LCD_CLR();
		LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
		LCD_sendStrData("Max Amount Exceeded");
		LCD_GoToXY(LCD_X_SecLine,LCD_Y_initialPos);
		LCD_sendStrData("1-Again     Home");

		Temp_Key =KPD_u8GetPressedKey();
		while(Temp_Key!= HOME_KEY && Temp_Key!= AGAIN_KEY)
		{
			Temp_Key =KPD_u8GetPressedKey();

		}
		if(Temp_Key == HOME_KEY)
		{
			OperatingHomePage();
		}
		else
		{
			Check_Transaction();
		}
	}
	else
	{
		if(AMOUNT_Check>Account_Balance)
		{
			LCD_CLR();
			LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
			LCD_sendStrData("Insufficient Fund");
			LCD_GoToXY(LCD_X_SecLine,LCD_Y_initialPos);
			LCD_sendStrData("1-Again     Home");

			Temp_Key =KPD_u8GetPressedKey();
			while(Temp_Key!= HOME_KEY && Temp_Key!= AGAIN_KEY)
			{
				Temp_Key =KPD_u8GetPressedKey();

			}
			if(Temp_Key == HOME_KEY)
			{
				OperatingHomePage();
			}
			else
			{
				Check_Transaction();
			}

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


void TransactionApproved()
{
	LCD_CLR();
	LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
	LCD_sendStrData("APPROVED");
	MOTOR_direction(MOTOR_1,FWD);
	MOTOR_speed(Motor_SPEED);
	_delay_ms(Delay_1SEC);
	MOTOR_off(MOTOR_1);
	OperatingHomePage();
}





uint8_t CheckMaxAmount(uint32_t Amount)
{
	if (Amount> MAX_AMOUNT )
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
	uint32_t Result =Init_BY_ZERO;
	uint8_t i=Init_BY_ZERO;
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

void StoreNewBalance(uint32_t num , unint16_t balance_address)
{
	uint32_t reversed = 1;
	uint8_t index =Init_BY_ZERO;
	uint8_t local_u8NewBalance[BALANCE_SIZE]={0};
	if (num == Init_BY_ZERO)
	{
		for(index=Init_BY_ZERO;index<6;index++)
		{
			local_u8NewBalance[index]='0';
		}
	}
	else
	{
		while (num != Init_BY_ZERO)
		{
			reversed = (reversed * 10) + (num % 10);
			num /= 10;
		}
		while (reversed != 1 && index<6)
		{
			local_u8NewBalance[index]=(reversed % 10) + '0';
			reversed /= 10;
			index++;
		}
		EEPROM_write_bytes(balance_address,local_u8NewBalance,BALANCE_SIZE);
		_delay_ms(Delay_1SEC);
	}
}

/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
void Programable_mode(void)
{
	uint8_t local_u8KPDread;
	LCD_CLR();
	LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
	LCD_sendStrData("1-Customer data");
	LCD_GoToXY(LCD_X_SecLine,LCD_Y_initialPos);
	LCD_sendStrData("2-MaxAmount");
	LCD_GoToXY(LCD_X_SecLine,LCD_Y_elenPos);
	LCD_sendStrData("3-Exit");
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
	else if(local_u8KPDread==HOME_KEY)
	{
		ATM_Prog_Mode();
	}
	else
	{
		LCD_CLR();
		LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
		LCD_sendStrData("Wrong Number.");
		LCD_GoToXY(LCD_X_SecLine,LCD_Y_initialPos);
		LCD_sendStrData("Try again.");
		_delay_ms(Delay_1SEC);
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
	uint8_t local_u8PassState=NOK;
	uint8_t local_u8AdminArr[]="ADMIN";
	uint8_t local_u8PassArr[]={4,5,6,7};
	uint8_t local_u8AdminRead[LCD_Line_Size];
	uint8_t local_u8PassRead[LCD_Line_Size];
	uint8_t local_u8PAN[PAN_SIZE];
	uint8_t local_u8BALANCE[BalanceSize];

	LCD_CLR();
	LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
	LCD_sendStrData("Enter UserName:");
	_delay_ms(Delay_1SEC);
	TERMINAL_read(&local_u8AdminRead);
	if(Check_sentData(&local_u8AdminRead,&local_u8AdminArr))
	{
		LCD_CLR();
		LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
		LCD_sendStrData("Enter Password:");
		LCD_GoToXY(LCD_X_SecLine,LCD_Y_initialPos);
		for(local_u8indexI=Init_BY_ZERO;local_u8indexI<LCD_Line_Size;local_u8indexI++)
		{
			local_u8KPDread=KPD_u8GetPressedKey();
			while(local_u8KPDread==KPD_NOT_PRESSED)
			{
				local_u8KPDread=KPD_u8GetPressedKey();
			}
			if(local_u8KPDread>=KPD_Min_Button && local_u8KPDread<=KPD_Max_Button)
			{
				local_u8PassRead[local_u8indexI]=local_u8KPDread;
				LCD_WriteNumber(local_u8PassRead[local_u8indexI]);
				if(local_u8PassRead[local_u8indexI]==local_u8PassArr[local_u8indexI])
				{
					local_u8PassState=OK;
				}
				else
				{
					local_u8PassState=NOK;
					break;
				}
			}
			else if(local_u8KPDread==Enter_Button)
			{
				if(local_u8indexI==4)
				{
					local_u8PassState=OK;
				}
				else
				{
					local_u8PassState=NOK;
				}
				local_u8PassRead[local_u8indexI]='\0';
				break;
			}
			else
			{
				local_u8indexI--;
			}
		}
		if(local_u8PassState==OK)
		{
			PAN_BALANCE();
		}
		else
		{
			LCD_CLR();
			LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
			LCD_sendStrData("Wrong Password");
			_delay_ms(Delay_1SEC);
		}
	}
	else
	{
		LCD_CLR();
		LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
		LCD_sendStrData("Wrong User name");
		_delay_ms(Delay_1SEC);
	}
	Programable_mode();
}

void Max_Balance(void)
{
	uint8_t local_u8MaxAmountArr[MaxAmountSize];
	uint8_t local_u8indexI;
	uint8_t local_u8KPDread;

	LCD_CLR();
	LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
	LCD_sendStrData("Enter MaxAmount:");
	LCD_GoToXY(LCD_X_SecLine,LCD_Y_initialPos);
	for(local_u8indexI=Init_BY_ZERO;local_u8indexI<10;local_u8indexI++)
	{
		local_u8KPDread=KPD_u8GetPressedKey();
		while(local_u8KPDread==KPD_NOT_PRESSED)
		{
			local_u8KPDread=KPD_u8GetPressedKey();
		}
		if(local_u8KPDread>=KPD_Min_Button && local_u8KPDread<=KPD_Max_Button)
		{
			LCD_WriteNumber(local_u8KPDread);
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
	_delay_ms(Delay_1SEC);
	LCD_CLR();
	LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
	LCD_sendStrData("AmountConfirmed");
	_delay_ms(Delay_1SEC);
	Programable_mode();
}

void Exit(void)
{
	//do nothing
}

void PAN_BALANCE(void)
{
	uint8_t PAN_Temp[PAN_SIZE];
	uint8_t local_u8KPDread;
	uint8_t local_u8indexI;
	uint8_t local_u8indexII;
	uint8_t local_u8PAN[PAN_SIZE];
	uint8_t local_u8BALANCE[BalanceSize];
	static uint8_t PANADDRESS=PAN_INITAL_ADDRESS;
	uint8_t BalanceADDRESS=BALANCE_ADDRESS;
	static uint8_t FirstTimeFlag=NOK;

	LCD_CLR();
	LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
	LCD_sendStrData("Enter PAN:");
	LCD_GoToXY(LCD_X_SecLine,LCD_Y_initialPos);
	for(local_u8indexI=Init_BY_ZERO;local_u8indexI<9;local_u8indexI++)
	{
		local_u8KPDread=KPD_u8GetPressedKey();
		while(local_u8KPDread==KPD_NOT_PRESSED)
		{
			local_u8KPDread=KPD_u8GetPressedKey();
		}
		if(local_u8KPDread>=KPD_Min_Button && local_u8KPDread<=KPD_Max_Button)
		{
			LCD_WriteNumber(local_u8KPDread);
			switch(local_u8KPDread)
			{
			case 0:local_u8PAN[local_u8indexI]='0';break;
			case 1:local_u8PAN[local_u8indexI]='1';break;
			case 2:local_u8PAN[local_u8indexI]='2';break;
			case 3:local_u8PAN[local_u8indexI]='3';break;
			case 4:local_u8PAN[local_u8indexI]='4';break;
			case 5:local_u8PAN[local_u8indexI]='5';break;
			case 6:local_u8PAN[local_u8indexI]='6';break;
			case 7:local_u8PAN[local_u8indexI]='7';break;
			case 8:local_u8PAN[local_u8indexI]='8';break;
			case 9:local_u8PAN[local_u8indexI]='9';break;
			}
		}
		else if(local_u8KPDread==Enter_Button)
		{
			if(local_u8indexI==9)
			{
				local_u8PAN[local_u8indexI]='\0';
				break;
			}
			else
			{
				LCD_CLR();
				LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
				LCD_sendStrData("Wrong PAN");
				LCD_CLR();
				LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
				LCD_sendStrData("Enter PAN:");
				LCD_GoToXY(LCD_X_SecLine,LCD_Y_initialPos);
				local_u8indexI=Init_BY_ZERO;
			}
		}
		else
		{
			local_u8indexI--;
		}
	}
	local_u8PAN[local_u8indexI]='\0';
	TERMINAL_write("pan= ");
	TERMINAL_write(local_u8PAN);
	TERMINAL_newLine();
	if(FirstTimeFlag==NOK)
	{
		EEPROM_write_bytes(PANADDRESS,&local_u8PAN,PAN_SIZE);
		_delay_ms(Delay_1SEC);
	}
	else
	{
		PANADDRESS=PANADDRESS+(PAN_SIZE+6);
		EEPROM_write_bytes(PANADDRESS,&local_u8PAN,PAN_SIZE);
		_delay_ms(Delay_1SEC);
	}

	EEPROM_read_bytes ( PANADDRESS,  PAN_Temp,  PAN_SIZE);
	TERMINAL_write(PAN_Temp);
	TERMINAL_newLine();

	LCD_CLR();
	LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
	LCD_sendStrData("Enter Balance:");
	LCD_GoToXY(LCD_X_SecLine,LCD_Y_initialPos);
	LCD_sendStrData("0000.00");
	LCD_GoToXY(LCD_X_SecLine,LCD_Y_initialPos);
	for(local_u8indexI=Init_BY_ZERO;local_u8indexI<7;local_u8indexI++)
	{
		if(local_u8indexI==Balance_intNum)
		{
			LCD_sendStrData(".");
		}
		else
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
					LCD_WriteNumber(local_u8KPDread);
					local_u8BALANCE[local_u8indexI]=local_u8KPDread;
				}
				else if(local_u8indexI>Balance_intNum)
				{
					LCD_WriteNumber(local_u8KPDread);
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
	}
	if(FirstTimeFlag==NOK)
	{
		EEPROM_write_bytes(BalanceADDRESS,&local_u8BALANCE,BalanceSize);
		_delay_ms(Delay_1SEC);
		FirstTimeFlag=OK;
	}
	else
	{
		BalanceADDRESS=PANADDRESS+PAN_SIZE;
		EEPROM_write_bytes(BalanceADDRESS,&local_u8BALANCE,BalanceSize);
		_delay_ms(Delay_1SEC);
	}

	LCD_CLR();
	LCD_GoToXY(LCD_X_initialPos,LCD_Y_initialPos);
	LCD_sendStrData("Confirm");
	_delay_ms(Delay_1SEC);
}
