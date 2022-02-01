#include "../../01-LIB/BIT_MATH.h"
#include "../../01-LIB/STD_TYPES.h"

#include "../DIO/DIO_register.h"

#include "ADC_register.h"
#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_interface.h"

uint16_t* gu8_Reading;
uint8_t gu8_State=IDLE;
void(*CallbackNotification)(void);

void ADC_init(void)
{
	CLR_BIT(DDRA,0);
	/*Select Ref.*/
#if ADC_REF_SEL == ADC_AREF
	CLR_BIT(ADC_ADMUX,ADMUX_REFS0);
	CLR_BIT(ADC_ADMUX,ADMUX_REFS1);
#elif ADC_REF_SEL == ADC_AVCC
	SET_BIT(ADC_ADMUX,ADMUX_REFS0);
	CLR_BIT(ADC_ADMUX,ADMUX_REFS1);
#endif

	/*Select ADC Left Adjust Result*/
#if ADC_ADLAR_SEL == LEFT_ADJUST
	SET_BIT(ADC_ADMUX,ADMUX_ADLAR);
#elif ADC_ADLAR_SEL == RIGHT_ADJUST
	CLR_BIT(ADC_ADMUX,ADMUX_ADLAR);
#endif

	/*Select Prescalar*/
	ADC_ADCSRA&=PRESC_BIT_MASK;
	ADC_ADCSRA|=ADC_PRESCLAR_SEL;

	/*Enable ADC*/
	SET_BIT(ADC_ADCSRA,ADCSRA_ADEN);
}

uint8_t ADC_u8StartConversionSynch(uint8_t ADC_Channel,uint16_t* u8_Reading)
{
	uint8_t local_u8Error=OK;
	uint32_t local_u8Counter=0;
	if(gu8_State == IDLE)
	{
		gu8_State=BUSY;
		/*Select Channel*/
		ADC_ADMUX&=MUX_BIT_MASK;
		ADC_ADMUX|=ADC_Channel;

		/*Start Conversion*/
		SET_BIT(ADC_ADCSRA,ADCSRA_ADSC);

		/*Make sure that the conversion time has finished*/
		while((GET_BIT(ADC_ADCSRA,ADCSRA_ADIF)==0) && (local_u8Counter != ADC_TIMEOUT))
		{
			local_u8Counter++;
		}

		if(local_u8Counter == ADC_TIMEOUT)
		{
			local_u8Error=NOK;
		}
		else
		{
			/*Clear the ADC flag*/
			SET_BIT(ADC_ADCSRA,ADCSRA_ADIF);

			/*Read the ADC value*/
			if(ADC_ADLAR_SEL == LEFT_ADJUST)
			{
				*u8_Reading=ADC_ADCH;
				gu8_State=IDLE;
			}
			else if(ADC_ADLAR_SEL == RIGHT_ADJUST)
			{
				*u8_Reading=ADC_ADCL;
				gu8_State=IDLE;
			}
		}
	}
	else
	{
		local_u8Error=BUSY;
	}
	return local_u8Error;
}

uint8_t ADC_u8StartConversionASynch(uint8_t ADC_Channel,uint8_t* u8_Reading,void(*NotificFunc)(void))
{
	uint8_t local_u8Error=OK;
	if(gu8_State==IDLE)
	{
		if((u8_Reading==NULL) || (NotificFunc == NULL))
		{
			local_u8Error=NOK;
		}
		else
		{
			gu8_State=BUSY;

			/*Select Channel*/
			ADC_ADMUX&=MUX_BIT_MASK;
			ADC_ADMUX|=ADC_Channel;

			/*Start Conversion*/
			SET_BIT(ADC_ADCSRA,ADCSRA_ADSC);

			/*Enable Interrupt*/
			SET_BIT(ADC_ADCSRA,ADCSRA_ADIE);

			gu8_Reading=u8_Reading;
			CallbackNotification=NotificFunc;
		}
	}
	else
	{
		local_u8Error=BUSY;
	}
	return local_u8Error;
}

void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	/*Read ADC*/
	if(ADC_ADLAR_SEL == LEFT_ADJUST)
	{
		*gu8_Reading=ADC_ADCH;
	}
	else if(ADC_ADLAR_SEL == RIGHT_ADJUST)
	{
		*gu8_Reading=ADC_ADCL;
	}

	/*ADC state IDLE*/
	gu8_State=IDLE;

	/*Call callback notification func*/
	CallbackNotification();

	/*Disable the interrupt*/
	CLR_BIT(ADC_ADCSRA,ADCSRA_ADIE);

}
