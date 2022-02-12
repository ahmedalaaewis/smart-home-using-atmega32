/*
 * I2C.c
 *
 *  Created on: Dec 23, 2021
 *      Author: user
 */

#include "TWI.h"
#define F_CPU 16000000
#include <util/delay.h>

#define NULL (void*)(0)
void (*p1)(uint8 *) = NULL;
void (*p2)(void) = NULL;

uint8 ss1[] = "TW_Start";
uint8 ss2[] = "TW_MT_SLA_W_ACK";
uint8 ss3[] = "TW_MT_DATA_ACK_W";
uint8 ss4[] = "TW_MT_DATA_N_ACK";
uint8 ss5[] = "TW_MR_DATA_ACK_R";
uint8 ss6[] = "TW_REP_START";
uint8 ss7[] = "TW_MT_SLA_R_ACK";


void Call_Back_LCD_Write_String(void (*p)(uint8 *))
{
	p1 = p;
}
void Call_Back_LCD_Clear(void (*p)(void))
{
	p2 = p;
}

void TWI_MASTER_INIT(void)
{
	TWBR = 0x0C;
	set_bit(TWCR,2);
}
void TWI_SLAVE_INIT(void)
{
	TWAR = (1<<1)|0x01;
	set_bit(TWCR,2);
}
void TWI_START_CONDITION(void)
{
// 	set_bit(TWCR,5);
// 	set_bit(TWCR,7);
// 	set_bit(TWCR,2);
	TWCR = (1 << 5) | (1 << 2) | (1 << 7);
	while((TWSR&0xF8) != TW_START);
 	_delay_ms(100);
// 	(*p2)();
// 	(*p1)(ss1);
// 	_delay_ms(2000);
	
	

}
void TWI_REPEATED_START(void)
{
	TWCR = (1 << 5) | (1 << 2) | (1 << 7);
	while((TWSR&0xF8) != TW_REP_START);
 	_delay_ms(100);
// 	(*p2)();
// 	(*p1)(ss6);
// 	_delay_ms(2000);	
}
void TWI_SEND_SLAVE_ADDRESS_WRITE(uint8 address)
{
		TWDR = (address << 1);
		TWCR = (1 << 2) | (1 << 7);
		while((TWSR&0xF8) != TW_MT_SLA_W_ACK);
 		_delay_ms(100);
// 		(*p2)();
// 		(*p1)(ss2);
// 		_delay_ms(2000);
		
}
void TWI_SEND_SLAVE_ADDRESS_READ(uint8 address)
{
		TWDR = ((address << 1) | 1);
		TWCR = (1 << 2) | (1 << 7);
		while((TWSR&0xF8) != TW_MT_SLA_R_ACK);
 		_delay_ms(100);
// 		(*p2)();
// 		(*p1)(ss7);
// 		_delay_ms(2000);		
}
void TWI_SEND_DATA(uint8 data)
{
		TWDR = data;
		TWCR = (1 << 2) | (1 << 7);
		while((TWSR&0xF8) != TW_MT_DATA_ACK);
 		_delay_ms(100);
// 		(*p2)();
// 		(*p1)(ss3);
// 		_delay_ms(2000);
		
}
uint8 TWI_READ_DATA(void)
{
		TWCR = (1 << 2) | (1 << 7);
		while((TWSR&0xF8) != TW_MR_DATA_NACK);
 		_delay_ms(100);
// 		(*p2)();
// 		(*p1)(ss5);
// 		_delay_ms(2000);	
		return TWDR;
}
void TWI_STOP_CONDITION(void)
{
	TWCR = (1 << 4) | (1 << 2) | (1 << 7);
	//while(!(TWCR & (1 << 7)));
		//while((TWSR&0xF8) != TW_START);
}