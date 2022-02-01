/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 27/1/2022           */
/* Version  : V01                 */
/**********************************/
#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_


/**********************************/
/*           REGISTERS            */
/**********************************/
#define  TWBR     *((volatile uint8_t*)0x20)
#define  TWSR     *((volatile uint8_t*)0x21)
#define  TWAR     *((volatile uint8_t*)0x22)
#define  TWDR     *((volatile uint8_t*)0x23)
#define  TWCR     *((volatile uint8_t*)0x56)

//TWCR BITS
#define TWINT  7 
#define TWEA   6
#define TWSTA  5
#define TWSTO  4
#define TWWC   3
#define TWEN   2
#define TWIE   0
//TWSR BITS
#define TWPS0   0
#define TWPS1   1

//macros
#define START_ACK                0x08 // start has been sent
#define REP_START_ACK            0x10 // repeated start
#define SLAVE_ADD_AND_WR_ACK     0x18 // Master transmit ( slave address + Write request ) ACK
#define SLAVE_ADD_AND_RD_ACK     0x40 // Master transmit ( slave address + Read request ) ACK
#define WR_BYTE_ACK              0x28 // Master transmit data ACK
#define RD_BYTE_WITH_NACK        0x58 // Master received data with not ACK
#define SLAVE_ADD_RCVD_RD_REQ    0xA8 // means that slave address is received with write req
#define SLAVE_ADD_RCVD_WR_REQ    0x60 // means that slave address is received with read req
#define SLAVE_DATA_RECEIVED      0x80 // means that read byte req is received
#define SLAVE_BYTE_TRANSMITTED   0xC0 // means that write byte req is received

#define BIT_RATE_DIVISION_FACTOR   0x02
#define STATUS_BITS_MASK           0xF8
#define MY_SLAVE_ADDRESS           1
 
      

#endif
