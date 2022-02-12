/*
 * IncFile1.h
 *
 * Created: 10/12/2021 2:01:58 PM
 *  Author: win7
 */ 


#ifndef ECU_BUZZER_BUZZER_H_
#define ECU_BUZZER_BUZZER_H_

#include "../../Common/DataType.h"
#include "../../MCAL/DIO/DIO.h"

/*typedef enum{
	BUZZER,
	
}BUZZER_en;*/

void BUZZER_Init();
void BUZZER_ON();
void BUZZER_OFF();


#endif /* ECU_BUZZER_BUZZER_H_ */