
#include "ADC.h"
#include <stdio.h>


ptrFunction ADC_INT_ISR = NULL;

void SET_ADC_INT_ISR_Handler( ptrFunction handler)
{
	if(handler != NULL)
	{
		ADC_INT_ISR = handler;
	}
}

void ADC_Init(ADC_Vref_type vref,ADC_scallertype scaller)
{

	// select voltage refrence
	switch(vref)
	{
		case VREF_AREF:
		clr_bit(ADMUX,REFS1);
		clr_bit(ADMUX,REFS0);
		break;
		case VREF_AVCC:
		clr_bit(ADMUX,REFS1);
		set_bit(ADMUX,REFS0);
		break;
		case VREF_256V:
		set_bit(ADMUX,REFS1);
		set_bit(ADMUX,REFS0);
		break;
	}

	 // set adjustment
	clr_bit(ADMUX,ADLAR);

	// set prescaller
	ADCSRA |= scaller;

	//ADC_Enable
	set_bit(ADCSRA,ADEN);
}


uint16 ADC_ReadChannel_Block(ADC_channel_type channel)
{

	// set read channel as input
	clr_bit(DDRA,channel);

	// select read channel.
	ADMUX |=channel;

	// start manual conversion
	set_bit(ADCSRA,ADSC);

	// polling wait for complete conversion "Blocking"
	while(!get_bit(ADCSRA,ADIF));

	//adc_val=((uint16)ADCH<<8)|ADCL;
	return ADC;
	//return adc_val;
}

void ADC_InterruptEnable(void)
{
	// Set ADC interrupt enable
	set_bit(ADCSRA,ADIE);
	// Set Global interrupt enable
	set_bit(SREG, 7);
}

void ADC_InterruptDisable(void)
{
	// Set ADC interrupt enable
	clr_bit(ADCSRA,ADIE);
}

void ADC_StartConversion(ADC_channel_type ch)
{

	// set read channel as input
	clr_bit(DDRA,ch);

	// select read channel.
	ADMUX |=ch;

	// start manual conversion
	set_bit(ADCSRA,ADSC);



}

uint16 ADC_ReadValue_NotBlock(void)
{
	uint16 ADCValue = 2000;
	if(get_bit(ADCSRA,ADIF))
	{
		ADCValue = ADC;
		//ADCValue=((uint16)ADCH<<8)|ADCL;
	}

	return ADCValue;
}

//ISR(ADC_vect)
//{
//	if(ADC_INT_ISR != NULL)
//	{
//		ADC_INT_ISR();
//	}
//}


void ADC_TriggerByPeripheral(Trigger_t source)
{
	// set enable trigger source
	SFIOR |= 5<<source;

	// set enable trigger source
	set_bit(ADCSRA,ADATE);

}




