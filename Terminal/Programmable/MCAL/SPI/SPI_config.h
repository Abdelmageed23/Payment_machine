/**********************************************************************/
/**********************************************************************/
/*****************		Author: Mohamed Alaa	***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	SPI				***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/
/**********************************************************************/
#ifndef _SPI_CONFIG_H_
#define _SPI_CONFIG_H_

/*Select the interrupt state ENABLE or DISABLE*/
#define SPI_INTERR		DISABLE

/*Select Data order:
 	 	 	 	 	 1- LSB_FIRST
 	 	 	 	 	 2- MSB_FIRST*/
#define SPI_DataORD		MSB_FIRST

/*Select the clock polarity:
 	 	 	 	 	 	 	 1- RISING
 	 	 	 	 	 	 	 2- FALLING*/
#define SPI_CLK_POLARITY	RISING

/*Select clock phase:
 	 	 	 	 	 1- SAMPLE
 	 	 	 	 	 2- SETUP*/
#define SPI_CLK_PHASE	SAMPLE

/*Select clock rate:
 	 	 	 	 	 1- DIV_BY_4
 	 	 	 	 	 2- DIV_BY_16
 	 	 	 	 	 3- DIV_BY_64
 	 	 	 	 	 4- DIV_BY_128
 	 	 	 	 	 5- DIV_BY_D2
 	 	 	 	 	 6- DIV_BY_D8
 	 	 	 	 	 7- DIV_BY_D32
 	 	 	 	 	 8- DIV_BY_D64*/
#define SPI_CLK_RATE	DIV_BY_16

#endif
