/*
 * UART.c
 *
 * Created: 6/25/2021 1:28:22 PM
 *  Author: ahmed
 */ 

#include "UART.h"

void UART_INIT(void)
{
	/*Set pin Directions*/
	/*pin_0 input*/
	clr_bit(DDRD, 0);
	/*pin_1 output*/
	set_bit(DDRD, 1);
	
	/* Transmitter/ Receiver Enable */
	UCSRB = 0x18;
	
	/*Parity Bit Selection*/
	/*Data Size Selection*/
	/*Stop Bit Selection*/
	UCSRC = (PARITY_MODE << 4) | (DATA_SIZE << 1) | (STOP_BIT << 3) | (1 << 7);
	
	/*Baud Rate Selection*/
	UBRRL = BAUD_RATE;
	
	
}
void UART_Tx(uint8 chr)
{
	UDR = chr;
	while(get_bit(UCSRA, 5) == 0);	
}
void UART_Tx_String(uint8* str)
{
	
}
uint8 UART_Rx(void)
{
	uint8 received_data = 0;
	while(get_bit(UCSRA, 7) == 0);
	received_data = UDR;
	return received_data;
}
