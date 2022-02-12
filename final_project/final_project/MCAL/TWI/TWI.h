/*
 * I2C.h
 *
 *  Created on: Dec 23, 2021
 *      Author: user
 */

#ifndef MCAL_TWI_TWI_H_
#define MCAL_TWI_TWI_H_

#include "../../Common/BitMath.h"
#include "../../Common/DataType.h"
#include <avr/io.h>

#define  TW_START 			 0x08U  // start has been sent
#define  TW_REP_START 		 0x10U  // repeated start
#define  TW_MT_SLA_W_ACK 	 0x18U  // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define  TW_MT_SLA_W_NACK 	 0x20   // Master transmit ( slave address + Write request ) to slave + No Ack received from slave
#define  TW_MT_SLA_R_ACK 	 0x40U  // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define  TW_MT_SLA_R_NACK    0x48U  // Master transmit ( slave address + Read request ) to slave + No Ack received from slave
#define  TW_MT_DATA_ACK 	 0x28U  // Master transmit data and ACK has been received from Slave.
#define  TW_MT_DATA_W_NACK 	 0x30   // Master transmit data and No ACK has been received from Slave.
#define  TW_MR_DATA_ACK 	 0x50U  // Master received data and send ACK to slave
#define  TW_MR_DATA_NACK     0x58U   // Master received data but doesn't send ACK to slave

void TWI_MASTER_INIT(void);
void TWI_SLAVE_INIT(void);
void TWI_START_CONDITION(void);
void TWI_REPEATED_START(void);
void TWI_SEND_SLAVE_ADDRESS_WRITE(uint8 address);
void TWI_SEND_SLAVE_ADDRESS_READ(uint8 address);
void TWI_SEND_DATA(uint8 data);
uint8 TWI_READ_DATA(void);
void TWI_STOP_CONDITION(void);

void Call_Back_LCD_Write_String(void (*p)(uint8 *));
void Call_Back_LCD_Clear(void (*p)(void));


#endif /* MCAL_TWI_TWI_H_ */
