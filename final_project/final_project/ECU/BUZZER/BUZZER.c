/*
 * CFile1.c
 *
 * Created: 10/12/2021 1:59:39 PM
 *  Author: win7
 */ 
#include "BUZZER.h"
void BUZZER_Init(){
	DIO_SetDir(PORT_A,PIN_3,OUTPUT);
}
void BUZZER_ON(){
	DIO_SetHigh(PORT_A,PIN_3);
}
void BUZZER_OFF(){
	DIO_SetLow(PORT_A,PIN_3);
}