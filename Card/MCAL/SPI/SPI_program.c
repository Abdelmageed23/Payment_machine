#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "SPI_register.h"
#include "SPI_private.h"
#include "SPI_config.h"
#include "SPI_interface.h"

void SPI_MASTinit(void)
{
	/*Select Data order*/
#if SPI_DataORD == LSB_FIRST
	SET_BIT(SPI_SPCR,SPCR_DORD);
#elif SPI_DataORD == MSB_FIRST
	CLR_BIT(SPI_SPCR,SPCR_DORD);
#endif

	/*Set SPI as Master*/
	SET_BIT(SPI_SPCR,SPCR_MSTR);

	/*select clock parity*/
#if SPI_CLK_POLARITY == RISING
	CLR_BIT(SPI_SPCR,SPCR_CPOL);
#elif SPI_CLK_POLARITY == FALLING
	SET_BIT(SPI_SPCR,SPCR_CPOL);
#endif

	/*Select Clock phase*/
#if SPI_CLK_PHASE == SETUP
	SET_BIT(SPI_SPCR,SPCR_CPHA);
#elif SPI_CLK_PHASE == SAMPLE
	CLR_BIT(SPI_SPCR,SPCR_CPHA);
#endif

	/*Set clock rate*/
#if SPI_CLK_RATE == DIV_BY_4
	CLR_BIT(SPI_SPCR,SPCR_SPR0);
	CLR_BIT(SPI_SPCR,SPCR_SPR1);
	CLR_BIT(SPI_SPSR,SPSR_SPI2X);
#elif SPI_CLK_RATE == DIV_BY_16
	SET_BIT(SPI_SPCR,SPCR_SPR0);
	CLR_BIT(SPI_SPCR,SPCR_SPR1);
	CLR_BIT(SPI_SPSR,SPSR_SPI2X);
#elif SPI_CLK_RATE == DIV_BY_64
	CLR_BIT(SPI_SPCR,SPCR_SPR0);
	SET_BIT(SPI_SPCR,SPCR_SPR1);
	CLR_BIT(SPI_SPSR,SPSR_SPI2X);
#endif

	/*SPI Interrupt Mode*/
#if SPI_INTERR == ENABLE
	SET_BIT(SPI_SPCR,SPCR_SPIE);
#elif SPI_INTERR == DISABLE
	CLR_BIT(SPI_SPCR,SPCR_SPIE);
#endif

	/*SPI Activation*/
	SET_BIT(SPI_SPCR,SPCR_SPE);
}

void SPI_SLVinit(void)
{
	/*Set SPI as a slave*/
	CLR_BIT(SPI_SPCR,SPCR_MSTR);

	/*SPI Interrupt Mode*/
#if SPI_INTERR == ENABLE
	SET_BIT(SPI_SPCR,SPCR_SPIE);
#elif SPI_INTERR == DISABLE
	CLR_BIT(SPI_SPCR,SPCR_SPIE);
#endif

	/*SPI Activation*/
	SET_BIT(SPI_SPCR,SPCR_SPE);
}

void SPI_Transmit_char(uint8_t u8_SData)
{
	/*Transmit data*/
	SPI_SPDR=u8_SData;

	/*Wait until transmit is complete*/
	while(SPI_flagComplete() == 0);

}
void SPI_Receive_char(uint8_t* u8_Rdata)
{

	/*Wait until transmit is complete*/
	while(SPI_flagComplete() == 0);

	/*save the data value*/
	*u8_Rdata=SPI_SPDR;
}

void SPI_TransmitStr(uint8_t* u8_Sdata)
{
	/*A local variable to count*/
	uint8_t local_u8Counter=0;
	/*Iterate until null*/
	while(u8_Sdata[local_u8Counter] != '\0')
	{
		/*Transmit character by character*/
		SPI_Transmit_char(u8_Sdata[local_u8Counter]);
		local_u8Counter++;//counter increment
	}
	SPI_Transmit_char('\0');//save the last value of the string as null
}

void SPI_ReceiveStr(uint8_t* u8_Rdata)
{
	/*A local variable to count*/
	uint8_t local_u8Counter=0;
	uint8_t local_u8Temp;/*A local variable to save the received data*/
	do
	{
		/*Receive data element by element*/
		SPI_Receive_char(&local_u8Temp);
		/*Save the received data into an array*/
		u8_Rdata[local_u8Counter]=local_u8Temp;
		local_u8Counter++;//counter increment
	}while(local_u8Temp != '\0');//iterate until null
	u8_Rdata[local_u8Counter]=local_u8Temp;//save the last elemr=ent in string by null
}

uint8_t SPI_flagComplete(void)
{
	uint8_t local_u8FlagRead;
	local_u8FlagRead=GET_BIT(SPI_SPSR,SPSR_SPIF);
	return local_u8FlagRead;
}
