#include <avr/io.h>
#include "ECU/LED/LED.h"
#include "ECU/LCD/LCD.h"
#include "ECU/BUZZER/BUZZER.h"
#include "Common/BitMath.h"
#include "Common/DataType.h"
#include "MCAL/ADC/ADC.h"
#include "MCAL/DIO/DIO.h"
#include "MCAL/PWM/PWM.h"
#include "MCAL/EEPROM/EEPROM.h"
#include "MCAL/TWI/TWI.h"
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>

void alarm(){
	while (1)
	{
		BUZZER_ON();
		_delay_ms(500);
		BUZZER_OFF();
		_delay_ms(500);
	}
	
}
void control()
{
	int dutyCycle;
	for(dutyCycle=0;dutyCycle<100;dutyCycle++) /* Increase the Brightness of the Leds */
	{
		PWM_SetDutyCycle(3,10);
		PWM_SetDutyCycle(3,50);
		PWM_SetDutyCycle(3,100);
		_delay_ms(10);
	}

	for(dutyCycle=100;dutyCycle>0;dutyCycle--) /* Decrease the Brightness of the Leds */
	{
		PWM_SetDutyCycle(3,100);
		PWM_SetDutyCycle(3,50);
		PWM_SetDutyCycle(3,10);
		_delay_ms(10);
	}
}

	char user = 'a';
	char password = 'a';
	char x;
void main()
{
	eeprom_init();
	UART_INIT();
	PWM_Init(3);
	PWM_Start(3);
	BUZZER_Init();
	ADC_Init(VREF_AVCC,ADC_SCALLER_8);
	int TEMP_counter,trial;
	char lamp;
	LCD_Init();
	LED_Init(LED_0);
	LED_Init(LED_1);
	LED_Init(LED_2);
	trial=0;
	eeprom_write(0x00,user);
	eeprom_write(0x01,password);
	char checkuser = eeprom_read(0x00);
	char checkpass = eeprom_read(0x01);
	while (1)
	{
		LCD_Clear();
		_delay_ms(1000);
		LCD_WriteString("Please enter the username and pass");
		LCD_WriteAtPosition(2,1);
		LCD_WriteString("username and pass");
		user = UART_Rx();
		password = UART_Rx();
		if(trial<2)
		{

			if(user == checkuser && password == checkpass)
			{
				while(1)
				{
				TEMP_counter=ADC_ReadChannel_Block(CH_1);
				if (TEMP_counter>512)
				{
					LED_ON(LED_0);//ac on
				}
				else if (TEMP_counter<200)
				{
					LED_OFF(LED_0);//ac off
				}
			
				LCD_Clear();
				_delay_ms(1000);
				LCD_WriteAtPosition(1,5);
				_delay_ms(1000);

				LCD_WriteString("TEMP=");
				_delay_ms(1000);

				LCD_WriteNumbers(TEMP_counter);
			
				_delay_ms(1000);
				control();
				}

			}
			else
			{
				LCD_Clear();
				LCD_WriteString("enter them again");
				trial++;
			}
		}
		else
		{
		LCD_Clear();
		LCD_WriteString("trials exceeded");
		alarm();
		}

	}
	
}

ISR(USART_RXC_vect)
{
	x = UDR;
}