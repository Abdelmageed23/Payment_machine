/*
 * **** Account 16
 * PAN 			9 char
 * Balance		7 char
 */

/* Configuration*/

#define ACCOUNT_SIZE	16

#define PAN_INITAL_ADDRESS		0x01
#define PAN_SIZE	9
#define CARD_NAME_SIZE	9

#define PIN_SIZE	4
#define NUM_ATM_ACCOUNTS		10


#define BALANCE_ADDRESS	0x10
#define BALANC_ADDRESS_COUNT	8
#define BALANCE_SIZE	6


//#define PAN_CARD


#define MAX_AMOUNT 500000




/* MACROS*/
										/* To be configurable */
#define HOME_KEY	9				// Press '*' IN CASE OF Keypad 4x3
#define AGAIN_KEY	1				// Press '#' IN CASE OF KEYPAD 4x3

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

#define ONE_SECOND	31250UL


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
void StoreNewBalance(uint32_t num , uint8_t balance_address);
