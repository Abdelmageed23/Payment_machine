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

/*Declaration of master initialization function*/
void SPI_MASTinit(void);

/*Declaration of slave initialization function*/
void SPI_SLVinit(void);

/*Declaration of transmit character*/
void SPI_Transmit_char(uint8_t u8_SData);

/*Declaration of receive character*/
void SPI_Receive_char(uint8_t* u8_Rdata);

/*Declaration of transmit string*/
void SPI_TransmitStr(uint8_t* u8_Sdata);

/*Declaration of receive string*/
void SPI_ReceiveStr(uint8_t* u8_Rdata);

/*Get flag of completion function*/
uint8_t SPI_flagComplete(void);

#endif
