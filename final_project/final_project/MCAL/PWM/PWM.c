/*
 * PWM.c
 *
 * Created: 17/12/2021 11:18:48 PM
 *  Author: ahmed
 */ 
#include "pwm.h"
#include "../../Common/BitMath.h"
#include "../../Common/DataType.h"
#include <avr/io.h>
#include <stdio.h>

void PWM_Init(uint8 channel)
{
	switch (channel)
	{
		case 0 :
		TCNT0 = 0x00;
		set_bit(DDRB,3); // Make the PWM pin Output
		break;

		case 1 :
		TCNT1 = 0x00;
		set_bit(DDRD,5); // Make the PWM pin Output
		break;

		case 2 :
		TCNT1 = 0x00;
		set_bit(DDRD,4); // Make the PWM pin Output
		break;

		case 3 :
		TCNT2 = 0x00;
		set_bit(DDRD,7); // Make the PWM pin Output
		break;
	}
}

void PWM_SetDutyCycle(uint8 channel,uint8 dutyCycle)
{
	dutyCycle *= 2.55;

	switch (channel)
	{
		case 0 :
		OCR0 = dutyCycle;    //Set the Duty Cycle between 0-100
		break;

		case 1 :
		OCR1A = dutyCycle;    //Set the Duty Cycle between 0-100
		break;

		case 2 :
		OCR1B = dutyCycle;    //Set the Duty Cycle between 0-100
		break;

		case 3 :
		OCR2 = dutyCycle;    //Set the Duty Cycle between 0-100
		break;
	}
}

void PWM_Start(uint8 channel)
{
	switch (channel)
	{
		case 0 :
		TCCR0 = (1<<WGM00)|(1<<COM01)|(1<<CS00);
		break;

		case 1 :
		set_bit(TCCR1A, COM1A1);   //Start the PWM Generation
		set_bit(TCCR1A, WGM10);   //Start the PWM Generation
		set_bit(TCCR1B, CS10);   //Start the PWM Generation
		break;

		case 2 :
		set_bit(TCCR1A, COM1B1);   //Start the PWM Generation
		set_bit(TCCR1B, CS10);   //Start the PWM Generation
		break;

		case 3 :
		TCCR2 = (1<<WGM20)|(1<<COM21)|(1<<CS20);
		break;
	}
}

void PWM_Stop(uint8 channel)
{
	switch (channel)
	{
		case 0 :
		clr_bit(TCCR0, COM00);   //Stop the PWM Generation
		break;

		case 1 :
		clr_bit(TCCR1A, COM1A1);   //Stop the PWM Generation
		break;

		case 2 :
		clr_bit(TCCR1A, COM1B1);   //Stop the PWM Generation
		break;

		case 3 :
		clr_bit(TCCR2, COM21);    //Stop the PWM Generation
		break;
	}

}