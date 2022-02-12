

#ifndef ADC_H_
#define ADC_H_

#include "ADC_CONFIG.h"

#include "../../Common/BitMath.h"
#include "../../Common/DataType.h"
#include <avr/io.h>
#include <avr/interrupt.h>

typedef enum
{
	VREF_AREF,
	VREF_AVCC,
	VREF_256V
}ADC_Vref_type;

typedef enum
{
	ADC_SCALLER_0 = 0,
	ADC_SCALLER_2=1,
	ADC_SCALLER_4,
	ADC_SCALLER_8,
	ADC_SCALLER_16,
	ADC_SCALLER_32,
	ADC_SCALLER_64,
	ADC_SCALLER_128
}ADC_scallertype;


typedef enum
{
	CH_0=0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
}ADC_channel_type;

typedef enum
{
	Free_Running_mode=0,
	Analog_Comparator,
	External_Interrupt_Request_0,
	TimerCounter0_Compare_Match,
	TimerCounter0_Overflow,
	TimerCounter1_CompareMatch_B,
	TimerCounter1_Overflow,
	TimerCounter1_CaptureEvent
}Trigger_t;


typedef void(*ptrFunction)(void);


void		ADC_Init(ADC_Vref_type vref,ADC_scallertype scaller);
uint16		ADC_ReadChannel_Block(ADC_channel_type channel);
void		ADC_InterruptEnable(void);
void		ADC_InterruptDisable(void);
void 		ADC_StartConversion(ADC_channel_type ch);
uint16      ADC_ReadValue_NotBlock(void);
void        SET_ADC_INT_ISR_Handler( ptrFunction handler);
void        ADC_TriggerByPeripheral(Trigger_t source);
#endif /* ADC_H_ */
