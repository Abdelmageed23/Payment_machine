/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 27/1/2022           */
/* Version  : V01                 */
/**********************************/
#ifndef EEPROM_H_
#define EEPROM_H_


void EEPROM_init(void);
void EEPROM_write_byte (uint16_t address, uint8_t data);
uint8_t EEPROM_read_byte  (uint16_t address);
void EEPROM_write_bytes(uint16_t address, const uint8_t *data, uint8_t byte_count);
void EEPROM_read_bytes (uint16_t address, uint8_t *return_var, uint8_t byte_count);
#endif /* EEPROM_H_ */

