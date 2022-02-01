/***********************************************************/
/***********************************************************/
/******************** Author : Mohamed Alaa ****************/
/******************** Layer : HAL **************************/
/******************** Driver : KEYPAD **********************/
/***********************************************************/
/***********************************************************/
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "KEYPAD_config.h"
#include "KEYPAD_private.h"
#include "KEYPAD_interface.h"

void KPD_init(void)
{
#if KEYPAD_T == KEYPAD3_3
	/*Set columns & Rows Direction*/
	DIO_SETpinDir(KPD_PORT,KPD_COLUMN0_PIN,DIO_OUTPUT);
	DIO_SETpinDir(KPD_PORT,KPD_COLUMN1_PIN,DIO_OUTPUT);
	DIO_SETpinDir(KPD_PORT,KPD_COLUMN2_PIN,DIO_OUTPUT);
	DIO_SETpinDir(KPD_PORT,KPD_ROW0_PIN,DIO_INPUT);
	DIO_SETpinDir(KPD_PORT,KPD_ROW1_PIN,DIO_INPUT);
	DIO_SETpinDir(KPD_PORT,KPD_ROW2_PIN,DIO_INPUT);

	/*Set Rows to work in pull up mode*/
	DIO_SETpinVal(KPD_PORT,KPD_ROW0_PIN,DIO_HIGH);
	DIO_SETpinVal(KPD_PORT,KPD_ROW1_PIN,DIO_HIGH);
	DIO_SETpinVal(KPD_PORT,KPD_ROW2_PIN,DIO_HIGH);

	/*Deactivate columns by setting them high*/
	DIO_SETpinVal(KPD_PORT,KPD_COLUMN0_PIN,DIO_HIGH);
	DIO_SETpinVal(KPD_PORT,KPD_COLUMN1_PIN,DIO_HIGH);
	DIO_SETpinVal(KPD_PORT,KPD_COLUMN2_PIN,DIO_HIGH);

#elif KEYPAD_T == KEYPAD4_3
	/*Set columns & Rows Direction*/
	DIO_SETpinDir(KPD_PORT,KPD_COLUMN0_PIN,DIO_OUTPUT);
	DIO_SETpinDir(KPD_PORT,KPD_COLUMN1_PIN,DIO_OUTPUT);
	DIO_SETpinDir(KPD_PORT,KPD_COLUMN2_PIN,DIO_OUTPUT);
	DIO_SETpinDir(KPD_PORT,KPD_ROW0_PIN,DIO_INPUT);
	DIO_SETpinDir(KPD_PORT,KPD_ROW1_PIN,DIO_INPUT);
	DIO_SETpinDir(KPD_PORT,KPD_ROW2_PIN,DIO_INPUT);
	DIO_SETpinDir(KPD_PORT,KPD_ROW3_PIN,DIO_INPUT);

	/*Set Rows to work in pull up mode*/
	DIO_SETpinVal(KPD_PORT,KPD_ROW0_PIN,DIO_HIGH);
	DIO_SETpinVal(KPD_PORT,KPD_ROW1_PIN,DIO_HIGH);
	DIO_SETpinVal(KPD_PORT,KPD_ROW2_PIN,DIO_HIGH);
	DIO_SETpinVal(KPD_PORT,KPD_ROW3_PIN,DIO_HIGH);

	/*Deactivate columns by setting them high*/
	DIO_SETpinVal(KPD_PORT,KPD_COLUMN0_PIN,DIO_HIGH);
	DIO_SETpinVal(KPD_PORT,KPD_COLUMN1_PIN,DIO_HIGH);
	DIO_SETpinVal(KPD_PORT,KPD_COLUMN2_PIN,DIO_HIGH);
#endif
}

uint8_t KPD_u8GetPressedKey(void)
{
#if KEYPAD_T == KEYPAD3_3
	uint8_t local_u8Pressed=KPD_NO_Pressed;//The initial value of the key is not pressed
	static uint8_t KPD_Arr[Row_num][Column_num]=KPD_Arr_Val;//arrays of keypad
	static uint8_t KPD_ROWS[Row_num]={KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN};//array of rows
	static uint8_t KPD_COLUMNS[Column_num]={KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN};//array of columns
	uint8_t KPD_ROWS_Index,KPD_COLUMNS_Index,ROW_PIN_State;//local variables of rows and colum index and row state

	/*Interate to active each column and check the row's value*/
	for(KPD_COLUMNS_Index=0;KPD_COLUMNS_Index<Column_num;KPD_COLUMNS_Index++)
	{
		/*Activate Columns*/
		DIO_SETpinVal(KPD_PORT,KPD_COLUMNS[KPD_COLUMNS_Index],DIO_LOW);
		/*Iterate to check row's values*/
		for(KPD_ROWS_Index=0;KPD_ROWS_Index<Row_num;KPD_ROWS_Index++)
		{
			/*get the row state*/
			DIO_GETpinVal(KPD_PORT,KPD_ROWS[KPD_ROWS_Index],&ROW_PIN_State);
			/*if button pressed*/
			if(DIO_LOW==ROW_PIN_State)
			{
				/*put the button number in key value*/
				local_u8Pressed=KPD_Arr[KPD_ROWS_Index][KPD_COLUMNS_Index];
				/*If user want to keep the key value*/
				if(KPD_STATE == POOLING)
				{
					/*Polling until key released*/
					while(DIO_LOW==ROW_PIN_State)
					{
						DIO_GETpinVal(KPD_PORT,KPD_ROWS[KPD_ROWS_Index],&ROW_PIN_State);
					}
				}
				else
				{
					//do nothing
				}
				/*deactivate the column*/
				DIO_SETpinVal(KPD_PORT,KPD_COLUMNS[KPD_COLUMNS_Index],DIO_HIGH);
				return local_u8Pressed;
			}
		}
		/*Deactivate current column*/
		DIO_SETpinVal(KPD_PORT,KPD_COLUMNS[KPD_COLUMNS_Index],DIO_HIGH);
	}

	return local_u8Pressed;

#elif KEYPAD_T == KEYPAD4_3
	uint8_t local_u8Pressed=KPD_NO_Pressed;//The initial value of the key is not pressed
	static uint8_t KPD_Arr[Row_num4_3][Column_num4_3]=KPD_Arr_Val4_3;//arrays of keypad
	static uint8_t KPD_ROWS[Row_num4_3]={KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};//array of rows
	static uint8_t KPD_COLUMNS[Column_num4_3]={KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN};//array of columns
	uint8_t KPD_ROWS_Index,KPD_COLUMNS_Index,ROW_PIN_State;//local variables of rows and colum index and row state

	/*Interate to active each column and check the row's value*/
	for(KPD_COLUMNS_Index=0;KPD_COLUMNS_Index<Column_num4_3;KPD_COLUMNS_Index++)
	{
		/*Activate Columns*/
		DIO_SETpinVal(KPD_PORT,KPD_COLUMNS[KPD_COLUMNS_Index],DIO_LOW);
		/*Iterate to check row's values*/
		for(KPD_ROWS_Index=0;KPD_ROWS_Index<Row_num4_3;KPD_ROWS_Index++)
		{
			/*get the row state*/
			DIO_GETpinVal(KPD_PORT,KPD_ROWS[KPD_ROWS_Index],&ROW_PIN_State);

			/*if button pressed*/
			if(DIO_LOW==ROW_PIN_State)
			{
				/*put the button number in key value*/
				local_u8Pressed=KPD_Arr[KPD_ROWS_Index][KPD_COLUMNS_Index];
				/*If user want to keep the key value*/
				if(KPD_STATE == POOLING)
				{
					/*Polling until key released*/
					while(DIO_LOW==ROW_PIN_State)
					{
						DIO_GETpinVal(KPD_PORT,KPD_ROWS[KPD_ROWS_Index],&ROW_PIN_State);
					}
				}
				else
				{
					//do nothing
				}
				/*deactivate the column*/
				DIO_SETpinVal(KPD_PORT,KPD_COLUMNS[KPD_COLUMNS_Index],DIO_HIGH);
				return local_u8Pressed;
			}
		}
		/*Deactivate current column*/
		DIO_SETpinVal(KPD_PORT,KPD_COLUMNS[KPD_COLUMNS_Index],DIO_HIGH);
	}

	return local_u8Pressed;
#endif
}
