#include "../../01-LIB/STD_TYPES.h"

#include "../../02-MCAL/ADC/ADC_interface.h"
#include "TEMP_private.h"
#include "TEMP_config.h"
#include "TEMP_interface.h"

void TEMP_init(void)
{
	DIO_SETpinDir(DIO_PORTA,ADC_Channel,DIO_INPUT);
	ADC_init();
}

uint8_t TEMP_u8GetReading(void)
{
	uint8_t local_u8TEMP;
	uint16_t local_u16MiliVolt;
	uint16_t local_u8ADC_Read;
	ADC_u8StartConversionSynch(ADC_Channel,&local_u8ADC_Read);
	local_u16MiliVolt=(uint16_t)(((uint32_t)local_u8ADC_Read*Vref)/TWO_P_RESOLUTION);
	local_u8TEMP=local_u16MiliVolt/10;
	return local_u8TEMP;

}
