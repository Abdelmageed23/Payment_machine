/*
 * UART_interface.h
 *
 * Created: 1/24/2022 8:20:49 PM
 *  Author: No. 01
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/*UCSRC BITS*/
#define URSEL 7
#define UMSEL 6
#define UPM1 5
#define UPM0 4
#define USBS 3
#define UCSZ1 2
#define UCSZ0 1
#define UCPOL 0

/*UCSRB BITS*/
#define RXCIE 7
#define TXCIE 6
#define UDRIE 5
#define RXEN 4
#define TXEN 3
#define UCSZ2 2
#define RXB8 1
#define TXB8 0

/*UCSRA BITS*/
#define RXC 7
#define TXC 6
#define UDRE 5
#define FE 4
#define DOR 3
#define PE 2
#define U2X 1
#define MPCM 0

/*UBRR Register shift helper*/
#define REG_SIZE 8

void static (*RxCompleteCallback)(void);
void UART_init(void);
void setRxCompleteCallback(void (*callback)(void));
void UART_sendChar(uint8_t u8_char);
void UART_receiveChar(uint8_t* u8_val);
void UART_sendString(uint8_t* u8_str);
void UART_receiveString(uint8_t* u8_retStr);
//void UART_sendBytes(uint8_t u8_numBytes);
//void UART_receiveBytes(uint8_t numBytes,uint8_t* u8_val);
void __vector_13(void) __attribute__ ((signal,used));




#endif /* UART_INTERFACE_H_ */