/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 27/1/2022           */
/* Version  : V01                 */
/**********************************/
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/I2C/I2C.h"
#include "EEPROM.h"

#define EEPROM_ADDRESS 0b01010000

void EEPROM_init(void)
{
	I2C_init_master();
}

void EEPROM_write_byte(unint16_t address, uint8_t data)
{
	I2C_start();
	I2C_send_slave_address_with_write_req(EEPROM_ADDRESS);
	I2C_write_byte((address >> 8));
	I2C_write_byte((uint8_t)address);
	I2C_write_byte(data);
	I2C_stop();
}

uint8_t EEPROM_read_byte(unint16_t address)
{
	uint8_t data;
	I2C_start();
	I2C_send_slave_address_with_write_req(EEPROM_ADDRESS);
	I2C_write_byte((address >> 8));
	I2C_write_byte((uint8_t)address);
	I2C_repeated_start();
	I2C_send_slave_address_with_read_req(EEPROM_ADDRESS);
	data = I2C_read_byte();
	I2C_stop();
	return data;
}
void EEPROM_write_bytes(unint16_t address, const uint8_t *data, uint8_t byte_count)
{
	uint8_t index = 0;
	I2C_start();
	I2C_send_slave_address_with_write_req(EEPROM_ADDRESS);
	I2C_write_byte((address >> 8));
	I2C_write_byte((uint8_t)address);
	for (index = 0; index < byte_count; index++)
	{
		I2C_write_byte(data[index]);
	}
	I2C_stop();
}
void EEPROM_read_bytes(unint16_t address, uint8_t *return_var, uint8_t byte_count)
{
	uint8_t index = 0;
	I2C_start();
	I2C_send_slave_address_with_write_req(EEPROM_ADDRESS);
	I2C_write_byte((address >> 8));
	I2C_write_byte((uint8_t)address);
	I2C_repeated_start();
	I2C_send_slave_address_with_read_req(EEPROM_ADDRESS);
	for (index = 0; index < byte_count; index++)
	{
		return_var[index] = I2C_read_byte();
	}
	I2C_stop();
}
