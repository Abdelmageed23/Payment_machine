#ifndef _ADC_REGISTER_H_
#define _ADC_REGISTER_H_

#define	ADC_ADMUX		*((volatile char*)0x27)
#define ADMUX_REFS1		7
#define ADMUX_REFS0		6
#define ADMUX_ADLAR		5

#define	ADC_ADCSRA      *((volatile char*)0x26)
#define ADCSRA_ADEN		7
#define ADCSRA_ADSC		6
#define ADCSRA_ADATE    5
#define ADCSRA_ADIF     4
#define ADCSRA_ADIE     3
#define ADCSRA_ADPS2    2
#define ADCSRA_ADPS1    1
#define ADCSRA_ADPS0	0

#define	ADC_ADCL        *((volatile uint16_t*)0x24)
#define	ADC_ADCH        *((volatile char*)0x25)

#define	ADC_SFIOR       *((volatile char*)0x50)


#endif
