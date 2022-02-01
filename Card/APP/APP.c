/*
 * Sprint6_COMM.c
 *
 * Created: 1/24/2022 8:04:48 PM
 * Author : No. 01
 */
#include <string.h>
#include "../LIB/STD_types.h"
#include "../HAL/EEPROM/EEPROM.h"
#include "../HAL/Terminal/Terminal.h"
//#include "../MCAL/SPI/SPI_interface.h"
#include "APP_private.h"

static void delay(uint16_t max);
/*******************************************************************************
 *                     Function Implementation                                 *
 *******************************************************************************/
void APP_vidInit(void)
{
  TERMINAL_init();
  EEPROM_init();
  // SPI_SLVinit();
}
void APP_vidStart(void)
{
  uint8_t u8_mode[MAX_TERMINAL_CHAR];
  while (1)
  {

    TERMINAL_write("ENTER MODE :");
    TERMINAL_newLine();
    TERMINAL_read(u8_mode);

    if (compare(u8_mode, "ADMIN") == 0)
    {
      CARD_admin();
    }
    else if (compare(u8_mode, "USER") == 0)
    {
      CARD_user();
    }
    else
    {
      TERMINAL_write("INVALID MODE");
      TERMINAL_newLine();
    }
  }
}

/*******************************************************************************
 *                     Private Function Implementation                         *
 *******************************************************************************/
void CARD_admin(void)
{

  uint8_t u8_validityFlag = LOW, u8_index = 0;
  uint8_t u8_val[MAX_TERMINAL_CHAR];
  uint8_t u8_dataFlag = LOW;
  ST_card_t st_myCard;
  TERMINAL_write("HELLO ADMIN");
  TERMINAL_newLine();

  while (!u8_validityFlag)
  {
    TERMINAL_write("Please enter a valid card holder name");
    TERMINAL_newLine();
    TERMINAL_read(u8_val);
    TERMINAL_write(u8_val);
    TERMINAL_newLine();
    for (u8_index = 0; u8_val[u8_index] != '\0'; u8_index++)
    {
      if (u8_index >= 9)
      {
        TERMINAL_write("MAX length of name is 9 characters long");
        TERMINAL_newLine();
        u8_validityFlag = LOW;
        break;
      }
      else if (!((u8_val[u8_index] >= 'A') && (u8_val[u8_index] <= 'z')))
      {
        TERMINAL_write("Enter only alphabetic characters");
        TERMINAL_newLine();
        u8_validityFlag = LOW;
        break;
      }
      else
      {
        u8_validityFlag = HIGH;
      }
    }
  }
  strncpy(st_myCard.s8_cardHolderName, u8_val, NAME_SIZE);
  TERMINAL_write("THE CARD NAME ENTERED");
  TERMINAL_newLine();
  TERMINAL_write(st_myCard.s8_cardHolderName);
  TERMINAL_newLine();
  EEPROM_write_bytes(NAME_STARTING_ADDRESS, st_myCard.s8_cardHolderName, NAME_SIZE);
  delay(65000);
  delay(65000);
  delay(65000);
  delay(65000);
  delay(65000);
  delay(65000);
  delay(65000);
  u8_validityFlag = LOW;

  while (!u8_validityFlag)
  {
    TERMINAL_write("Please enter a valid PAN");
    TERMINAL_newLine();
    TERMINAL_read(u8_val);
    TERMINAL_write(u8_val);
    TERMINAL_newLine();
    for (u8_index = 0; u8_val[u8_index] != '\0'; u8_index++)
    {
      if (u8_index >= 9)
      {
        TERMINAL_write("MAX length of PAN is 9 characters long");
        TERMINAL_newLine();
        u8_validityFlag = LOW;
        break;
      }
      else if (!((u8_val[u8_index] >= '0') && (u8_val[u8_index] <= '9')))
      {
        TERMINAL_write("Enter only numeric characters");
        TERMINAL_newLine();
        u8_validityFlag = LOW;
        break;
      }
      else
      {
        u8_validityFlag = HIGH;
      }
    }
  }
  strncpy(st_myCard.s8_PAN, u8_val, PAN_SIZE);
  TERMINAL_write("THE PAN ENTERED");
  TERMINAL_newLine();
  TERMINAL_write(st_myCard.s8_PAN);
  TERMINAL_newLine();
  EEPROM_write_bytes(PAN_STARTING_ADDRESS, st_myCard.s8_PAN, PAN_SIZE);
  delay(65000);
  delay(65000);
  delay(65000);
  delay(65000);
  delay(65000);
  delay(65000);
  delay(65000);
  u8_validityFlag = LOW;

  while (!u8_validityFlag)
  {
    TERMINAL_write("Please enter a valid PIN");
    TERMINAL_newLine();
    TERMINAL_read(u8_val);
    TERMINAL_write(u8_val);
    TERMINAL_newLine();
    for (u8_index = 0; u8_val[u8_index] != '\0'; u8_index++)
    {
      if (u8_index >= 4)
      {
        TERMINAL_write("MAX length of PIN is 4 characters long");
        TERMINAL_newLine();
        u8_validityFlag = LOW;
        break;
      }
      else if (!((u8_val[u8_index] >= '0') && (u8_val[u8_index] <= '9')))
      {
        TERMINAL_write("Enter only numeric characters");
        TERMINAL_newLine();
        u8_validityFlag = LOW;
        break;
      }
      else
      {
        u8_validityFlag = HIGH;
      }
    }
  }
  strncpy(st_myCard.s8_pin, u8_val, PIN_SIZE);
  TERMINAL_write("THE PIN ENTERED");
  TERMINAL_newLine();
  TERMINAL_write(st_myCard.s8_pin);
  TERMINAL_newLine();
  EEPROM_write_bytes(PIN_STARTING_ADDRESS, st_myCard.s8_pin, PIN_SIZE);
  u8_dataFlag = HIGH;
  EEPROM_write_bytes(WRITTEN_FLAG_ADDRESS, u8_dataFlag, 1);
  delay(65000);
  delay(65000);
  delay(65000);
  delay(65000);
}

void CARD_user(void)
{
  ST_card_t st_myCard;
  EEPROM_read_bytes(NAME_STARTING_ADDRESS, st_myCard.s8_cardHolderName, NAME_SIZE);
  EEPROM_read_bytes(PAN_STARTING_ADDRESS, st_myCard.s8_PAN, PAN_SIZE);
  EEPROM_read_bytes(PIN_STARTING_ADDRESS, st_myCard.s8_pin, PIN_SIZE);

  TERMINAL_write(st_myCard.s8_cardHolderName);
  TERMINAL_newLine();
  TERMINAL_write(st_myCard.s8_PAN);
  TERMINAL_newLine();
  TERMINAL_write(st_myCard.s8_pin);
  TERMINAL_newLine();
}

// Comparing both the strings.
uint8_t compare(uint8_t a[], uint8_t b[])
{
  uint8_t flag = 0, i = 0;             // integer variables declaration
  while (a[i] != '\0' && b[i] != '\0') // while loop
  {
    if (a[i] != b[i])
    {
      flag = 1;
      break;
    }
    i++;
  }
  if (flag == 0)
    return 0;
  else
    return 1;
}

static void delay(uint16_t max)
{
  uint16_t counter = 0;
  while (counter < max) // loop to perform a delay
  {
    counter++;
  }
}
