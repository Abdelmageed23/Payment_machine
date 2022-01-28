/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 27/1/2022           */
/* Version  : V01                 */
/**********************************/
#include "../../01-LIB/01-STD_TYPES/STD_TYPES.h"
#include "../../02-MCAL/I2C/I2C.h"
#include "eeprom.h"

#define EEPROM_ADDRESS  0b01010000

void EEPROM_init(void)
{
	I2C_init_master();
}

u8_t EEPROM_write_byte(u16_t address, u8_t data)
{
    I2C_start();
	I2C_send_slave_address_with_write_req(EEPROM_ADDRESS);
	I2C_write_byte((address>>8));
    I2C_write_byte((u8_t)address);
	I2C_write_byte(data);
	I2C_stop();
    return 1;
}

u8_t EEPROM_read_byte(u16_t address)
{
	u8_t data;
	I2C_start();
	I2C_send_slave_address_with_write_req(EEPROM_ADDRESS);
	I2C_write_byte((address>>8));
	I2C_write_byte((u8_t)address);
	I2C_repeated_start();
	I2C_send_slave_address_with_read_req(EEPROM_ADDRESS);
	data = I2C_read_byte();
	I2C_stop();
    return data;
}
u8_t EEPROM_write_25byte(u16_t address, u8_t* data)
{
	u8_t index=0;
    I2C_start();
	I2C_send_slave_address_with_write_req(EEPROM_ADDRESS);
	I2C_write_byte((address>>8));
    I2C_write_byte((u8_t)address);
	for (index = 0; i < 25; index++)
	{
		I2C_write_byte(data[index]);
	}
	
	
	I2C_stop();
    return 1;
}
