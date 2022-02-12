/*
 * EEPROM.c
 *
 * Created: 25/12/2021 11:43:04 AM
 *  Author: ahmed
 */ 
#include "EEPROM.h"
#define F_CPU 16000000
#include <util/delay.h>


void eeprom_init()
{
	TWI_MASTER_INIT();
}

void eeprom_write(uint8 byte_address,uint8 data)
{
	TWI_START_CONDITION();
	TWI_SEND_SLAVE_ADDRESS_WRITE(0X51);
	TWI_SEND_DATA(byte_address);
	TWI_SEND_DATA(data);
	TWI_STOP_CONDITION();
	_delay_ms(10);
}

uint8 eeprom_read(uint8 byte_address)
{
	uint8 data = 0;
	TWI_START_CONDITION();
	TWI_SEND_SLAVE_ADDRESS_WRITE(0X51);
	TWI_SEND_DATA(byte_address);
	TWI_REPEATED_START();
	TWI_SEND_SLAVE_ADDRESS_READ(0X51);
	data = TWI_READ_DATA();
	TWI_STOP_CONDITION();
	return data;
}