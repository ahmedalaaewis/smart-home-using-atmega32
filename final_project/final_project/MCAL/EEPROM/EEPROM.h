/*
 * EEPROM.h
 *
 * Created: 25/12/2021 11:43:20 AM
 *  Author: ahmed
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "../../Common/BitMath.h"
#include "../../Common/DataType.h"
#include <avr/io.h>
#include "../TWI/TWI.h"

void eeprom_init();
void eeprom_write(uint8 byte_address,uint8 data);
uint8 eeprom_read(uint8 byte_address);

#endif /* EEPROM_H_ */