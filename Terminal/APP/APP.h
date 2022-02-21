/*
 * **** Account 16
 * PAN 			9 char
 * Balance		7 char
 */
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../LIB/DET/Det.h"

#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/UART/UART_interface.h"
#include "../MCAL/I2C/I2C.h"
#include "../MCAL/TIMER/Timer.h"
#include "../MCAL/SPI/SPI_interface.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include "../MCAL/Interrupt/Interrupt_interface.h"

#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/KEYPAD/KEYPAD_interface.h"
#include "../HAL/BUTTON/Button.h"
#include "../HAL/EEPROM/EEPROM.h"
#include "../HAL/TEMP/TEMP_interface.h"
#include "../HAL/motor/Motor.h"
#include "../HAL/Terminal/Terminal.h"
/* Configuration*/

#define ACCOUNT_SIZE	16

#define PAN_INITAL_ADDRESS		0x01
#define PAN_SIZE	10

#define PIN_SIZE	5
#define NUM_ATM_ACCOUNTS		10


#define BALANCE_ADDRESS	0x10
#define BALANC_ADDRESS_COUNT	8
#define BALANCE_SIZE	7

#define FirstRound		0
#define SecRound		1

#define ProgMode		1
#define OperRound		2

#define LCD_POS3		3
#define LCD_POS5		5
#define LCD_POS13		13
#define LCD_POS12		12

#define Identical		0

#define Motor_SPEED		50

#define Delay_1SEC		1000

#define MAX_AMOUNT 500000
/**********************************/
#define EEPROM_MAX_AMOUNT_ADDRESS	0xF5
//#define Balance_ADDRESS		0x10
//#define PAN_ADDRESS			0x01
#define MaxAmountSize		9
//#define PAN					10
#define KPD_NOT_PRESSED		255
#define Init_BY_ZERO		0
#define LCD_X_initialPos	0
#define LCD_Y_initialPos	0
#define LCD_X_SecLine		1
#define LCD_Y_SecLine		1
#define LCD_Y_elenPos		11
#define LCD_Line_Size		16
#define CustomerData_mode	1
#define MaxAmount_mode		2
#define Exit_mode			3
#define Enter_Button		12
#define KPD_Min_Button		0
#define KPD_Max_Button		9
#define LCD_Y_SixLine		6
#define Balance_intNum		4
#define BalanceSize			7
/*************************************/


/* MACROS*/
										/* To be configurable */
#define HOME_KEY	12				// Press '#' IN CASE OF Keypad 4x3
#define AGAIN_KEY	10				// Press '*' IN CASE OF KEYPAD 4x3

#define INSERT_CARD		1
#define DSIPLAY_TEMP	2

#define NOT_FOUND 0

#define APPROVED	1
#define NOT_APPROVED 0

#define SUCESS			4
#define AMOUT_SIZE	6
#define AMOUT_DEICMAL_SIZE	2

#define KPD_NO_Pressed	0xff
#define ABOVE_MAX	1
#define BELOW_MAX	0

#define AMOUNT_FLOAT 100



void ATM_OperatingInit();
void ATM_OperatingMode();
void OperatingHomePage();
void DisplayTemp(void);
void Check_CardPAN();
void Check_CardPIN();
void Check_Transaction();
void TransactionApproved();
void TransactionApproved();
uint8_t CheckMaxAmount(uint32_t Amount);
uint32_t strtoint(uint8_t *str);
void StoreNewBalance(uint32_t num , unint16_t balance_address);

void Programable_mode(void);
uint8_t Check_sentData(uint8_t* data,uint8_t* Order);
void Customer_data(void);
void Max_Balance(void);
void PAN_BALANCE(void);

