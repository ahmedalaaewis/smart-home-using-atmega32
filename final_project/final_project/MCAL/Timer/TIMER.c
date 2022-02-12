/*
 * TIMER.c
 *
 *  Created on: Dec 3, 2021
 *      Author: user
 */

#include "TIMER.h"

ptrFunction TMR0_OVF_INT_ISR = NULL, TMR0_OC_INT_ISR = NULL;


void TIMER_Init(TIMER_Paramter_t timerCfgParamter)
{
	switch(timerCfgParamter.Timer_Channel)
	{
		case TIMER0:
		{

			// set prescale , operation mode ,and wave generation
			TCCR0 |= ( timerCfgParamter.Timer_Prescale << CS00 ) |
					 ( timerCfgParamter.COM_Pin << COM00);

			// set interrupt
			TIMSK |= (timerCfgParamter.Timer_OVF_Interrupt << TOIE0) |
					(timerCfgParamter.Timer_OCR_Interrupt << OCIE0);

			// enable global interrupt
			if( timerCfgParamter.Timer_OVF_Interrupt || timerCfgParamter.Timer_OCR_Interrupt)
			{
				set_bit(SREG, 7);
			}
			switch(timerCfgParamter.Timer_Mode)
			{
				case NORMAL:
				{
					// set wave generation
					TCCR0 |=(0 << WGM00) | (0 << WGM01);

					break;
				}

				case CTC:
				{
					// set wave generation
					TCCR0 |=(0 << WGM00) | (1 << WGM01);
					break;
				}

			}

			break;
		}

		case TIMER1:
		{

			break;
		}

		case TIMER2:
		{

			break;
		}
	}




}

uint16 TIMER_Read_Counter_Value( TMR_Channel_t timerChannel )
{
	uint16 value =0;

	switch(timerChannel)
	{

		case TIMER0 :
		{
			value = TCNT0;
			break;
		}

		case TIMER1 :
		{

			break;
		}

		case TIMER2 :
		{

			break;
		}
	}

	return value;

}

void TIMER_Set_Counter_Value( TMR_Channel_t timerChannel , uint16 value)
{
	switch(timerChannel)
	{

		case TIMER0 :
		{
			TCNT0 =(uint8)value ;
			break;
		}

		case TIMER1 :
		{

			break;
		}

		case TIMER2 :
		{

			break;
		}
	}
}

void TIMER_Set_OCR_Value( TMR_Channel_t timerChannel , uint16 value)
{
	switch(timerChannel)
	{

		case TIMER0 :
		{
			OCR0 =(uint8)value ;
			break;
		}

		case TIMER1 :
		{

			break;
		}

		case TIMER2 :
		{

			break;
		}
	}
}


void SET_TMR0_OVF_INT_ISR_Handler( ptrFunction handler)
{
	if(handler != NULL)
	{
		TMR0_OVF_INT_ISR = handler;
	}
}

ISR(TIMER0_OVF_vect)
{
	if(TMR0_OVF_INT_ISR != NULL)
	{
		TMR0_OVF_INT_ISR();
	}
}

void SET_TMR0_OC_INT_ISR_Handler( ptrFunction handler)
{
	if(handler != NULL)
	{
		TMR0_OC_INT_ISR = handler;
	}
}

ISR(TIMER0_COMP_vect)
{
	if(TMR0_OC_INT_ISR != NULL)
	{
		TMR0_OC_INT_ISR();
	}
}


