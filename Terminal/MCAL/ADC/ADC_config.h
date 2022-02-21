#ifndef _ADC_CONFIG_H_
#define _ADC_CONFIG_H_

/*Select Reference Selection:
 	 	 	 	 	 	 	 1- ADC_AREF
 	 	 	 	 	 	 	 2- ADC_AVCC*/
#define ADC_REF_SEL			ADC_AVCC

/*Select ADLAR:
 	 	 	 	 1- LEFT_ADJUST
 	 	 	 	 2- RIGHT_ADJUST*/
#define ADC_ADLAR_SEL		RIGHT_ADJUST

/*Select Analog Channel:
 	 	 	 	 	 	 1- ADC0
 	 	 	 	 	 	 2- ADC1
 	 	 	 	 	 	 3- ADC2
 	 	 	 	 	 	 4- ADC3
 	 	 	 	 	 	 5- ADC4
 	 	 	 	 	 	 6- ADC5
 	 	 	 	 	 	 7- ADC6
 	 	 	 	 	 	 8- ADC7*/
#define ADC_CHANNEL_SEL		ADC0

/*Select PRESCALAR:
 	 	 	 	 	1- DIV_2
 	 	 	 	 	1- DIV_4
 	 	 	 	 	1- DIV_8
 	 	 	 	 	1- DIV_16
 	 	 	 	 	1- DIV_32
 	 	 	 	 	1- DIV_64
 	 	 	 	 	1- DIV_128*/
#define ADC_PRESCLAR_SEL	DIV_128

/*Select ADC time out if mode is synch*/
#define ADC_TIMEOUT	50000 //Random number
#endif
