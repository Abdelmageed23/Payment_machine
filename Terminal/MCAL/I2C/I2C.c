/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 27/1/2022           */
/* Version  : V01                 */
/**********************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "I2C.h"
#include "I2C_private.h"



void I2C_init_master(void)
{
	TWBR = BIT_RATE_DIVISION_FACTOR ; // bit rate = 400.000 kbps, F_CPU = 8M   SCL freq= F_CPU/(16+2(TWBR).4^TWPS)
    //prescaler 0b00 -> 4^0 -> 1
	CLR_BIT(TWSR,TWPS1);
	CLR_BIT(TWSR,TWPS0);

	TWCR = (1<<TWEN);           //enable I2C
	
}

void I2C_init_slave(void)
{
	TWAR = (1<<MY_SLAVE_ADDRESS);    // my address = MY_SLAVE_ADDRESS
	TWCR = (1<<TWEN);                //enable I2C
}

void I2C_start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);         // Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	while((GET_BIT(TWCR,TWINT)) == 0 );                        // Wait till start condition is transmitted
	while((TWSR & STATUS_BITS_MASK) != START_ACK);           // Check for the acknowledgment
}

void I2C_repeated_start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);         // Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	while((GET_BIT(TWCR,TWINT)) == 0 );                   // wait till restart condition is transmitted
	while((TWSR & STATUS_BITS_MASK) != REP_START_ACK);  // Check for the acknowledgment
}

void I2C_send_slave_address_with_write_req(uint8_t slave_address)
{
	TWDR = (slave_address<<1);                     //Address and write instruction
	TWCR = (1<<TWINT) | (1<<TWEN);                 // Clear TWI interrupt flag, Enable TWI
	while((GET_BIT(TWCR,TWINT)) == 0 );                  // Wait till complete TWDR byte transmitted
	while((TWSR & STATUS_BITS_MASK) != SLAVE_ADD_AND_WR_ACK);  // Check for the acknowledgment
}

void I2C_send_slave_address_with_read_req(uint8_t slave_address)
{
	TWDR = (slave_address<<1);                     //Address
	SET_BIT(TWDR,0) ;                               // read instruction
	TWCR = (1<<TWINT) | (1<<TWEN);                 // Clear TWI interrupt flag,Enable TWI
	while((GET_BIT(TWCR,TWINT)) == 0 );                  // Wait till complete TWDR byte received
	while((TWSR & STATUS_BITS_MASK) != SLAVE_ADD_AND_RD_ACK);  // Check for the acknowledgment
}

void I2C_write_byte(uint8_t byte)
{
	TWDR = byte;                         // put data in TWDR
	TWCR = (1<<TWINT) | (1<<TWEN);       // Clear TWI interrupt flag,Enable TWI
	while((GET_BIT(TWCR,TWINT)) == 0 );        // Wait till complete TWDR byte transmitted
	while((TWSR & STATUS_BITS_MASK) != WR_BYTE_ACK); // Check for the acknowledgment
}

uint8_t I2C_read_byte_NACK(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);             // Clear TWI interrupt flag,Enable TWI
	while((GET_BIT(TWCR,TWINT)) == 0 );               // Wait till complete TWDR byte transmitted
	while((TWSR & STATUS_BITS_MASK) != RD_BYTE_WITH_NACK); // Check for the acknowledgment
	return TWDR;
}

uint8_t I2C_read_byte_ACK(void)
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA); /* Enable TWI, generation of ack */
    while(GET_BIT(TWCR,TWINT) == 0);	/* Wait until TWI finish its current job */
	while((TWSR & STATUS_BITS_MASK) != RD_BYTE_WITH_ACK); // Check for the acknowledgment
    return TWDR;
}

void I2C_stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO); // Clear TWI interrupt flag, Put stop condition on SDA,Enable TWI
}

void I2C_slave_check_slave_address_received_with_write_req(void)
{
	TWCR = (1<<TWEA) | (1<<TWEN) | (1<<TWINT);       // enable acknowledgment after receive, Enable TWI, Clear TWI interrupt flag
	while((GET_BIT(TWCR,TWINT)) == 0 );                    // Wait for TWINT flag
	while((TWSR & STATUS_BITS_MASK) != SLAVE_ADD_RCVD_WR_REQ) ;  
}

void I2C_slave_check_slave_address_received_with_read_req(void)
{
	TWCR = (1<<TWEA) | (1<<TWEN) | (1<<TWINT); // enable acknowledgment after receive, Enable TWI, Clear TWI interrupt flag
	while((GET_BIT(TWCR,TWINT)) == 0 );             // Wait for TWINT flag
	while((TWSR & STATUS_BITS_MASK) != SLAVE_ADD_RCVD_RD_REQ);
}

uint8_t I2C_slave_read_byte(void)
{
	TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);     // Clear TWI interrupt flag,Get enable acknowledgment, Enable TWI
	while((GET_BIT(TWCR,TWINT))== 0 );                   // Wait for TWINT flag
	while((TWSR & STATUS_BITS_MASK) != SLAVE_DATA_RECEIVED);
	return TWDR;
}

void I2C_slave_write_byte(uint8_t byte)
{
	TWDR = byte;
	TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);         // Clear TWI interrupt flag,Get enable acknowledgment, Enable TWI
	while((GET_BIT(TWCR,TWINT)) == 0 );                     // Wait for TWINT flag
	while((TWSR & STATUS_BITS_MASK) != SLAVE_BYTE_TRANSMITTED);    // Data byte in TWDR has been transmitted
	return;
}

