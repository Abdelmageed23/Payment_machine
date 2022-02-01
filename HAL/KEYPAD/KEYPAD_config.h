/***********************************************************/
/***********************************************************/
/******************** Author : Mohamed Alaa ****************/
/******************** Layer : HAL **************************/
/******************** Driver : KEYPAD **********************/
/***********************************************************/
/***********************************************************/
#ifndef _KEYPAD_CONFIG_H_
#define _KEYPAD_CONFIG_H_

/*Select the KEYPAD type:
 	 	 	 	 	 	 1- KEYPAD3_3
 	 	 	 	 	 	 2- KEYPAD4_3*/
#define KEYPAD_T		KEYPAD3_3

/*Select the Keypad Port:
						 1- DIO_PORTA
						 2- DIO_PORTB
						 3- DIO_PORTC
						 4- DIO_PORTD*/
#define KPD_PORT		DIO_PORTC

/*Select Rows and coulumns pins:
								1-DIO_PIN0
								2-DIO_PIN1
								3-DIO_PIN2
								4-DIO_PIN3
								5-DIO_PIN4
								6-DIO_PIN5
								7-DIO_PIN6
								8-DIO_PIN7*/
#define KPD_ROW0_PIN	DIO_PIN2
#define KPD_ROW1_PIN	DIO_PIN3
#define KPD_ROW2_PIN	DIO_PIN4
//#define KPD_ROW3_PIN	DIO_PIN7

#define KPD_COLUMN0_PIN	DIO_PIN5
#define KPD_COLUMN1_PIN	DIO_PIN6
#define KPD_COLUMN2_PIN	DIO_PIN7

/*Put 0xff if key not pressed*/
#define KPD_NO_Pressed	0xff

/*KeyPad Array*/
#define KPD_Arr_Val		{{1,2,3},{4,5,6},{7,8,9}}

#define KPD_Arr_Val4_3		{{1,2,3},{4,5,6},{7,8,9},{10,0,12}}

/*Control Pooling:
				  1- POOLING
				  2- NO_POOLING*/

#define KPD_STATE	POOLING
#endif
