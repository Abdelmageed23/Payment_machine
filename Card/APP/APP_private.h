#ifndef APP_PRIVATE_H_
#define APP_PRIVATE_H_

// APPLICATION'S MACROS
#define HIGH 1
#define LOW 0

#define NAME_SIZE 10          // 9 characters + 1 NULL
#define PAN_SIZE 10           // 9 characters + 1 NULL
#define PIN_SIZE 5            // 4 characters +1 NULL
#define MAX_TERMINAL_CHAR 255 // Max size of terminal buffer

#define NAME_STARTING_ADDRESS 0x00 // start at 0 it will take 10 bytes so ending address -> 0xA
#define PAN_STARTING_ADDRESS 0x14  // start at 0xA+10 bytes(A) = 0x14 and it will end at 0x1E (+10)
#define PIN_STARTING_ADDRESS 0x28  // leave 10 bytes after ending (0x1E) so it will start at 0x28

//  DATATYPES 
typedef struct card_t
{
  sint8_t s8_cardHolderName[NAME_SIZE];
  sint8_t s8_PAN[PAN_SIZE];
  sint8_t s8_pin[PIN_SIZE];
} ST_card_t;

/*******************************************************************************
 *                     Private Function Prototypes                             *
 *******************************************************************************/
void CARD_user(void);
void CARD_admin(void);
uint8_t compare(uint8_t a[], uint8_t b[]);

#endif