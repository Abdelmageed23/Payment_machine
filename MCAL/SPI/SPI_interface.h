/**********************************************************************/
/**********************************************************************/
/*****************		Author: Mohamed Alaa	***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	SPI				***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/
/**********************************************************************/
#ifndef _SPI_INTERFACE_H_
#define _SPI_INTERFACE_H_

void SPI_MASTinit(void);

void SPI_SLVinit(void);

void SPI_Transmit_char(uint8_t u8_SData);

void SPI_Receive_char(uint8_t* u8_Rdata);

void SPI_TransmitStr(uint8_t* u8_Sdata);

void SPI_ReceiveStr(uint8_t* u8_Rdata);

#endif
