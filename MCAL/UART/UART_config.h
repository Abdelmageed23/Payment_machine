/*
 * UART_config.h
 *
 * Created: 1/24/2022 8:21:04 PM
 *  Author: No. 01
 */ 


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/*
BAUD RATE OPTIONS: *(DOUBLE SPEED Ux2 turned off)*
BAUD     NUMBER
2400     207
4800     103
9600     51
14.4k    34
19.2k    25
28.8k    16
38.4k    12
*/

#define BAUD_RATE 51  //9600 default

/*
PARITY OPTIONS
DISABLED -> 0
EVEN -> 2
ODD -> 3 
*/

#define PARITY_MODE 0 //disabled by default

/*
STOP BIT OPTIONS
1Bit -> 0
2Bits -> 1
*/

#define STOP_MODE 0  //1 Bit by default



#endif /* UART_CONFIG_H_ */