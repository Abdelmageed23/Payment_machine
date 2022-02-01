/*
 * Terminal.h
 *
 * Created: 1/29/2022 2:04:09 AM
 *  Author: No. 01
 */ 


#ifndef TERMINAL_H_
#define TERMINAL_H_

void TERMINAL_init(void);
void TERMINAL_read(uint8_t* u8_retStr);
void TERMINAL_write(uint8_t* u8_str);
void TERMINAL_newLine(void);



#endif /* TERMINAL_H_ */