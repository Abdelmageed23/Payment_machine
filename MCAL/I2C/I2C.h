/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 27/1/2022           */
/* Version  : V01                 */
/**********************************/
#ifndef I2C_H_
#define I2C_H_

void I2C_init_master(void);
void I2C_init_slave(void);
void I2C_start(void);
void I2C_repeated_start(void);
void I2C_send_slave_address_with_write_req(uint8_t slave_address);
void I2C_send_slave_address_with_read_req(uint8_t slave_address);
void I2C_write_byte(uint8_t byte);
uint8_t I2C_read_byte_NACK(void);
uint8_t I2C_read_byte_ACK(void);
void I2C_stop(void);
void I2C_slave_check_slave_address_received_with_write_req(void);
void I2C_slave_check_slave_address_received_with_read_req(void);
uint8_t I2C_slave_read_byte(void);
void I2C_slave_write_byte(uint8_t byte);


#endif
