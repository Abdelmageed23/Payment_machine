/*
 * Motor.c
 *
 * Created: 1/9/2022 5:56:57 PM
 *  Author: No. 01
 */ 
#include "../../01-LIB/STD_TYPES.h"
#include "../../02-MCAL/DIO/DIO_interface.h"
#include "../../02-MCAL/PWM/PWM.h"
#include "MOTOR_CONFIG.h"
#include "Motor.h"



void MOTOR_init(uint8_t numMotor)// numMotor (initialize Direction pins only (PWM initializes enable pins inside them))
{
	PWM_vidInit();
	if(MOTOR_1==numMotor)
	{
		DIO_SETpinDir(MOTOR_PORT,MOTOR_DIR_1A,DIO_OUTPUT);
		DIO_SETpinDir(MOTOR_PORT,MOTOR_DIR_1B,DIO_OUTPUT);
	}
	else if(MOTOR_2==numMotor)
	{
		DIO_SETpinDir(MOTOR_PORT,MOTOR_DIR_2A,DIO_OUTPUT);
		DIO_SETpinDir(MOTOR_PORT,MOTOR_DIR_2B,DIO_OUTPUT);
	}
}

void MOTOR_speed(uint8_t dutyCycle)//  30/60/90 (Start PWM and initialize duty cycle)
{
	PWM_SetDutyCycle(dutyCycle);
}
void MOTOR_direction(uint8_t numMotor, uint8_t DIR)//  numMotor/(FWD,REV) (Set direction of specified motor) i.e (MOTOR_1, FWD) meaning motor 1, move forward
{
	if(MOTOR_1==numMotor)
	{
		if(FWD==DIR)
		{
			DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_1A,DIO_HIGH);
			DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_1B,DIO_LOW);
		}
		else if(REV==DIR)
		{
			DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_1A,DIO_LOW);
			DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_1B,DIO_HIGH);
		}
	}
	else if(MOTOR_2==numMotor)
	{
		if(FWD==DIR)
		{
			DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_2A,DIO_HIGH);
			DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_2B,DIO_LOW);
		}
		else if(REV==DIR)
		{
			DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_2A,DIO_LOW);
			DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_2B,DIO_HIGH);
		}
	}
	
	
}
void MOTOR_off(uint8_t numMotor)// stop specified motor (writes LOW on DIR data pins)
{
	if(MOTOR_1==numMotor)
	{
		DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_1A,DIO_LOW);
		DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_1B,DIO_LOW);
	}
	else if(MOTOR_2==numMotor)
	{
		DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_2A,DIO_LOW);
		DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_2B,DIO_LOW);
	}
}