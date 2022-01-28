/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 27/1/2022           */
/* Version  : V01                 */
/**********************************/
#ifndef EEPROM_H_
#define EEPROM_H_


void EEPROM_init(void);
u8_t EEPROM_write_byte(u16_t address, u8_t data);
u8_t EEPROM_read_byte(u16_t address);
u8_t EEPROM_write_25byte(u16_t address, u8_t* data);
u8_t EEPROM_read_25byte(u16_t address );
#endif /* EEPROM_H_ */
