#ifndef _ADC_INTERFACE_H_
#define _ADC_INTERFACE_H_

void ADC_init(void);

uint8_t ADC_u8StartConversionSynch(uint8_t ADC_Channel,uint16_t* u8_Reading);

uint8_t ADC_u8StartConversionASynch(uint8_t ADC_Channel,uint8_t* u8_Reading,void(*NotificFunc)(void));

#endif
