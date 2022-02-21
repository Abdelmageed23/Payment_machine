/**********************************************************************/
/**********************************************************************/
/*****************		Author: Mohamed Alaa	***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	EXTI			***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/
/**********************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "EXTI_register.h"
#include "EXTI_private.h"
#include "EXTI_config.h"
#include "EXTI_interface.h"

void (*CALL_BACK)(void);

ERROR_STATUS_t EXTI_init(uint8_t u8_INT)
{
	uint8_t local_u8Error=E_NOK;

	if(u8_INT == INT0)
	{
#if INT_MODE == RISING
		SET_BIT(EXTI_MCUCR,MCUCR_ISC00);
		SET_BIT(EXTI_MCUCR,MCUCR_ISC01);
#elif INT_MODE == FALLING
		CLR_BIT(EXTI_MCUCR,MCUCR_ISC00);
		SET_BIT(EXTI_MCUCR,MCUCR_ISC01);
#elif INT_MODE == LOWLEVEL
		CLR_BIT(EXTI_MCUCR,MCUCR_ISC00);
		CLR_BIT(EXTI_MCUCR,MCUCR_ISC01);
#elif INT_MODE == ANYLOGIC
		SET_BIT(EXTI_MCUCR,MCUCR_ISC00);
		CLR_BIT(EXTI_MCUCR,MCUCR_ISC01);
#else
#error "Please select between previous choises"
#endif

		local_u8Error = E_OK;
	}

	else if(u8_INT == INT1)
	{
#if INT_MODE == RISING
		SET_BIT(EXTI_MCUCR,MCUCR_ISC10);
		SET_BIT(EXTI_MCUCR,MCUCR_ISC11);
#elif INT_MODE == FALLING
		CLR_BIT(EXTI_MCUCR,MCUCR_ISC10);
		SET_BIT(EXTI_MCUCR,MCUCR_ISC11);
#elif INT_MODE == LOWLEVEL
		CLR_BIT(EXTI_MCUCR,MCUCR_ISC10);
		CLR_BIT(EXTI_MCUCR,MCUCR_ISC11);
#elif INT_MODE == ANYLOGIC
		SET_BIT(EXTI_MCUCR,MCUCR_ISC10);
		CLR_BIT(EXTI_MCUCR,MCUCR_ISC11);
#else
#error "Please select between previous choises"
#endif

		local_u8Error = E_OK;
	}

	else if(u8_INT == INT2)
	{
#if INT_MODE == RISING
		SET_BIT(EXTI_MCUCSR,MCUSCR_ISC2);
#elif INT_MODE == FALLING
		CLR_BIT(EXTI_MCUCSR,MCUSCR_ISC2);
#else
#error "Please select between previous choises"
#endif

		local_u8Error = E_OK;
	}

	else
	{
		//do nothing
	}

	/*Enable the interrupt*/
	SET_BIT(EXTI_GICR,u8_INT);

	return local_u8Error;
}


ERROR_STATUS_t EXTI_EdgeTrig(uint8_t u8_INT,uint8_t u8_State)
{
	if(u8_INT == INT0)
	{
		if(u8_State == RISING)
		{
			SET_BIT(EXTI_MCUCR,MCUCR_ISC00);
			SET_BIT(EXTI_MCUCR,MCUCR_ISC01);
		}
		else if(u8_State == FALLING)
		{
			CLR_BIT(EXTI_MCUCR,MCUCR_ISC00);
			SET_BIT(EXTI_MCUCR,MCUCR_ISC01);
		}
		else if(u8_State == LOWLEVEL)
		{
			CLR_BIT(EXTI_MCUCR,MCUCR_ISC00);
			CLR_BIT(EXTI_MCUCR,MCUCR_ISC01);
		}
		else if(u8_State == ANYLOGIC)
		{
			SET_BIT(EXTI_MCUCR,MCUCR_ISC00);
			CLR_BIT(EXTI_MCUCR,MCUCR_ISC01);
		}
		else
		{
			return E_NOK;
		}
		return E_OK;
	}
	else if(u8_INT == INT1)
	{
		if(u8_State == RISING)
		{
			SET_BIT(EXTI_MCUCR,MCUCR_ISC10);
			SET_BIT(EXTI_MCUCR,MCUCR_ISC11);
		}
		else if(u8_State == FALLING)
		{
			CLR_BIT(EXTI_MCUCR,MCUCR_ISC10);
			SET_BIT(EXTI_MCUCR,MCUCR_ISC11);
		}
		else if(u8_State == LOWLEVEL)
		{
			CLR_BIT(EXTI_MCUCR,MCUCR_ISC10);
			CLR_BIT(EXTI_MCUCR,MCUCR_ISC11);
		}
		else if(u8_State == ANYLOGIC)
		{
			SET_BIT(EXTI_MCUCR,MCUCR_ISC10);
			CLR_BIT(EXTI_MCUCR,MCUCR_ISC11);
		}
		else
		{
			return E_NOK;
		}
		return E_OK;
	}
	else if(u8_INT == INT2)
	{
		if(u8_State == RISING)
		{
			SET_BIT(EXTI_MCUCSR,MCUSCR_ISC2);
		}
		else if(u8_State == FALLING)
		{
			CLR_BIT(EXTI_MCUCSR,MCUSCR_ISC2);
		}
		else
		{
			return E_NOK;
		}
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

ERROR_STATUS_t EXTI_Disable(uint8_t u8_INT)
{
	if(u8_INT == INT0)
	{
		CLR_BIT(EXTI_GICR,GICR_INT0);
		return E_OK;
	}
	else if(u8_INT == INT1)
	{
		CLR_BIT(EXTI_GICR,GICR_INT1);
		return E_OK;
	}
	else if(u8_INT == INT2)
	{
		CLR_BIT(EXTI_GICR,GICR_INT2);
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

void EXTI_CallBack(void (*ISR)(void))
{
		CALL_BACK=ISR;
}

void __vector_1(void)	__attribute__((signal));
void __vector_1(void)
{
	if(CALL_BACK != NULL)
	{
		CALL_BACK();
	}
	else
	{

	}
}

void __vector_2(void)	__attribute__((signal));
void __vector_2(void)
{
	if(CALL_BACK != NULL)
	{
		CALL_BACK();
	}
	else
	{

	}
}

void __vector_3(void)	__attribute__((signal));
void __vector_3(void)
{
	if(CALL_BACK != NULL)
	{
		CALL_BACK();
	}
	else
	{

	}
}
