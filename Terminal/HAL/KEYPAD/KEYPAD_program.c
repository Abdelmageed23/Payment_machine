#include "../../01-LIB/STD_TYPES.h"

#include "../../02-MCAL/DIO/DIO_interface.h"

#include "KEYPAD_config.h"
#include "KEYPAD_private.h"
#include "KEYPAD_interface.h"
//#include<util/delay.h>

void KPD_init(void)
{
	/*Set columns & Rows Direction*/
	DIO_SETpinDir(KPD_PORT,KPD_COLUMN0_PIN,DIO_OUTPUT);
	DIO_SETpinDir(KPD_PORT,KPD_COLUMN1_PIN,DIO_OUTPUT);
	DIO_SETpinDir(KPD_PORT,KPD_COLUMN2_PIN,DIO_OUTPUT);
	//DIO_SETpinDir(KPD_PORT,KPD_COLUMN3_PIN,DIO_OUTPUT);
	DIO_SETpinDir(KPD_PORT,KPD_ROW0_PIN,DIO_INPUT);
	DIO_SETpinDir(KPD_PORT,KPD_ROW1_PIN,DIO_INPUT);
	DIO_SETpinDir(KPD_PORT,KPD_ROW2_PIN,DIO_INPUT);
	//DIO_SETpinDir(KPD_PORT,KPD_ROW3_PIN,DIO_INPUT);

	/*Set Rows to work in pull up mode*/
	DIO_SETpinVal(KPD_PORT,KPD_ROW0_PIN,DIO_HIGH);
	DIO_SETpinVal(KPD_PORT,KPD_ROW1_PIN,DIO_HIGH);
	DIO_SETpinVal(KPD_PORT,KPD_ROW2_PIN,DIO_HIGH);
	//DIO_SETpinVal(KPD_PORT,KPD_ROW3_PIN,DIO_HIGH);

	/*Deactivate columns by setting them high*/
	DIO_SETpinVal(KPD_PORT,KPD_COLUMN0_PIN,DIO_HIGH);
	DIO_SETpinVal(KPD_PORT,KPD_COLUMN1_PIN,DIO_HIGH);
	DIO_SETpinVal(KPD_PORT,KPD_COLUMN2_PIN,DIO_HIGH);
	//DIO_SETpinVal(KPD_PORT,KPD_COLUMN3_PIN,DIO_HIGH);
}

uint8_t KPD_u8GetPressedKey(void)
{
	uint8_t local_u8Pressed=KPD_NO_Pressed;
	static uint8_t KPD_Arr[Row_num][Column_num]=KPD_Arr_Val;
	static uint8_t KPD_ROWS[Row_num]={KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN};
	static uint8_t KPD_COLUMNS[Column_num]={KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN};
	uint8_t KPD_ROWS_Index,KPD_COLUMNS_Index,ROW_PIN_State;

	for(KPD_COLUMNS_Index=0;KPD_COLUMNS_Index<Column_num;KPD_COLUMNS_Index++)
	{
		/*Activate Columns*/
		DIO_SETpinVal(KPD_PORT,KPD_COLUMNS[KPD_COLUMNS_Index],DIO_LOW);
		for(KPD_ROWS_Index=0;KPD_ROWS_Index<Row_num;KPD_ROWS_Index++)
		{
			DIO_GETpinVal(KPD_PORT,KPD_ROWS[KPD_ROWS_Index],&ROW_PIN_State);
			if(DIO_LOW==ROW_PIN_State)
			{
				local_u8Pressed=KPD_Arr[KPD_ROWS_Index][KPD_COLUMNS_Index];
				/*Polling until key released*/
				while(DIO_LOW==ROW_PIN_State)
				{
					DIO_GETpinVal(KPD_PORT,KPD_ROWS[KPD_ROWS_Index],&ROW_PIN_State);
				}
				//_delay_ms(25);
				DIO_SETpinVal(KPD_PORT,KPD_COLUMNS[KPD_COLUMNS_Index],DIO_HIGH);
				return local_u8Pressed;
			}
		}
		/*Deactivate current column*/
		DIO_SETpinVal(KPD_PORT,KPD_COLUMNS[KPD_COLUMNS_Index],DIO_HIGH);
	}

	return local_u8Pressed;
}
