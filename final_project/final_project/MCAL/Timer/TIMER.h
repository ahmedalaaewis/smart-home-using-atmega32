/*
 * TIMER.h
 *
 *  Created on: Dec 3, 2021
 *      Author: user
 */

#ifndef MCAL_TIMER_TIMER_H_
#define MCAL_TIMER_TIMER_H_

#include "TIMER_CONFIG.h"
#include "../../Common/BitMath.h"
#include "../../Common/DataType.h"
#include <avr/interrupt.h>
#include <stdio.h>

typedef enum
{
	TIMER0,
	TIMER1,
	TIMER2
}TMR_Channel_t;


typedef enum
{
	CTC,
	NORMAL
}TMR_Mode_t ;

typedef enum
{
	Disconnected,
	Toggle,
	Clear,
	Set
}TMR_OutComparePin_t ;

typedef enum
{
	NO_CLK_SRC = 0, //Timer Disable
	NO_PRESCALING = 1,
	PRESCALING_CLK8 = 2,
	PRESCALING_CLK64 = 3,
	PRESCALING_CLK256 = 4,
	PRESCALING_CLK1024 = 5,
	EXT_CLK_FALLING=6,
	EXT_CLK_RISING = 7
}TMR_Prescale_t;



typedef enum
{
	TOVF_disable,
	TOVF_enable,

}TMR_OVF_INT_t;

typedef enum    //Timer/Counter0 Output Compare Match Interrupt Enable
{
	OCR_disable,
	OCR_enable ,

}TMR_OCR_INT_t;




typedef struct
{
	TMR_Channel_t Timer_Channel;
	TMR_Mode_t    Timer_Mode;
	TMR_OutComparePin_t COM_Pin;
	TMR_Prescale_t Timer_Prescale;
	TMR_OVF_INT_t Timer_OVF_Interrupt;
	TMR_OCR_INT_t Timer_OCR_Interrupt;

}TIMER_Paramter_t;



typedef void(*ptrFunction)(void);


 void TIMER_Init(TIMER_Paramter_t timerCfgParamter);
 uint16 TIMER_Read_Counter_Value( TMR_Channel_t timerChannel );
 void TIMER_Set_Counter_Value( TMR_Channel_t timerChannel , uint16 value);
 void TIMER_Set_OCR_Value( TMR_Channel_t timerChannel , uint16 value);
 void SET_TMR0_OVF_INT_ISR_Handler( ptrFunction handler);
 void SET_TMR0_OC_INT_ISR_Handler( ptrFunction handler);



#endif /* MCAL_TIMER_TIMER_H_ */
