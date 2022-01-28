/*Include all header files needed to implement the driver*/
#include "../../01-LIB/BIT_MATH.h"
#include "../../01-LIB/STD_TYPES.h"
#include "DIO_register.h"
#include "DIO_interface.h"

uint8_t DIO_SETpinDir(uint8_t u8_PORT,uint8_t u8_PIN,uint8_t u8_STAT){
	uint8_t Local_u8Error=OK;//variable using in Error check
	if(u8_PIN<=DIO_PIN7)//check if the chosen is correct or not
	{
		/*If the direction of the pin is output*/
		if(u8_STAT==DIO_OUTPUT)
		{
			/*Choose which port*/
			switch(u8_PORT)
			{
			case DIO_PORTA: SET_BIT(DDRA,u8_PIN);break;
			case DIO_PORTB: SET_BIT(DDRB,u8_PIN);break;
			case DIO_PORTC: SET_BIT(DDRC,u8_PIN);break;
			case DIO_PORTD: SET_BIT(DDRD,u8_PIN);break;
			default:Local_u8Error=NOK;
			}
		}
		/*If the direction of the pin is input*/
		else if(u8_STAT==DIO_INPUT)
		{
			/*Choose which port*/
			switch(u8_PORT)
			{
			case DIO_PORTA: CLR_BIT(DDRA,u8_PIN);break;
			case DIO_PORTB: CLR_BIT(DDRB,u8_PIN);break;
			case DIO_PORTC: CLR_BIT(DDRC,u8_PIN);break;
			case DIO_PORTD: CLR_BIT(DDRD,u8_PIN);break;
			default:Local_u8Error=NOK;break;
			}
		}
		else
		{
			Local_u8Error=NOK;
		}
	}
	else
	{
		Local_u8Error=NOK;
	}
	return Local_u8Error;
}

uint8_t DIO_SETportDir(uint8_t u8_PORT,uint8_t u8_STAT)
{
	uint8_t local_u8Error=OK;
	switch(u8_PORT)
	{
		case DIO_PORTA: DDRA=u8_STAT;break;
		case DIO_PORTB: DDRB=u8_STAT;break;
		case DIO_PORTC: DDRC=u8_STAT;break;
		case DIO_PORTD: DDRD=u8_STAT;break;
		default:local_u8Error=NOK;break;
	}

	return local_u8Error;
}

uint8_t DIO_SETpinVal(uint8_t u8_PORT,uint8_t u8_PIN,uint8_t u8_VAL){
	uint8_t Local_u8Error=OK;//variable using in Error check
	if(u8_PIN<=DIO_PIN7)//check if the chosen is correct or not
	{
		/*If the chosen value is high*/
		if(u8_VAL==DIO_HIGH)
		{
			/*Choose which port*/
			switch(u8_PORT)
			{
			case DIO_PORTA: SET_BIT(PORTA,u8_PIN);break;
			case DIO_PORTB: SET_BIT(PORTB,u8_PIN);break;
			case DIO_PORTC: SET_BIT(PORTC,u8_PIN);break;
			case DIO_PORTD: SET_BIT(PORTD,u8_PIN);break;
			default:Local_u8Error=NOK;break;
			}
		}
		/*If the chosen value is low*/
		else if(u8_VAL==DIO_LOW)
		{
			/*Choose which port*/
			switch(u8_PORT)
			{
			case DIO_PORTA: CLR_BIT(PORTA,u8_PIN);break;
			case DIO_PORTB: CLR_BIT(PORTB,u8_PIN);break;
			case DIO_PORTC: CLR_BIT(PORTC,u8_PIN);break;
			case DIO_PORTD: CLR_BIT(PORTD,u8_PIN);break;
			default:Local_u8Error=NOK;break;
			}
		}
		else
		{
			Local_u8Error=NOK;
		}
	}
	else
	{
		Local_u8Error=NOK;
	}
	return Local_u8Error;
}

uint8_t DIO_SETportVal(uint8_t u8_PORT,uint8_t u8_VAL)
{
	uint8_t local_u8Error=OK;
	switch(u8_PORT)
	{
		case DIO_PORTA: PORTA=u8_VAL;break;
		case DIO_PORTB: PORTB=u8_VAL;break;
		case DIO_PORTC: PORTC=u8_VAL;break;
		case DIO_PORTD: PORTD=u8_VAL;break;
		default:local_u8Error=NOK;break;
	}

	return local_u8Error;
}

uint8_t DIO_GETpinVal(uint8_t u8_PORT,uint8_t u8_PIN, uint8_t *u8p_RetVal){
	uint8_t Local_u8Error=OK;//variable using in Error check
	if(u8_PIN<=DIO_PIN7)
	{
		switch(u8_PORT)
		{
		/*Choose which port*/
		case DIO_PORTA: *u8p_RetVal=GET_BIT(PINA,u8_PIN);break;
		case DIO_PORTB: *u8p_RetVal=GET_BIT(PINB,u8_PIN);break;
		case DIO_PORTC: *u8p_RetVal=GET_BIT(PINC,u8_PIN);break;
		case DIO_PORTD: *u8p_RetVal=GET_BIT(PIND,u8_PIN);break;
		default: Local_u8Error=NOK;break;
		}
	}
	else
	{
		Local_u8Error=NOK;
	}
	return Local_u8Error;
}
