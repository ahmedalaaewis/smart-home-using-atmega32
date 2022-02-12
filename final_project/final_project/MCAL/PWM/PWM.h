/*
 * PWM.h
 *
 * Created: 17/12/2021 11:18:57 PM
 *  Author: ahmed
 */ 


#ifndef PWM_H_
#define PWM_H_
#include "../../Common/BitMath.h"
#include "../../Common/DataType.h"


void PWM_Init(uint8 channel);
void PWM_SetDutyCycle(uint8 channel,uint8 dutyCycle);
void PWM_Start(uint8 channel);
void PWM_Stop(uint8 channel);


#endif /* PWM_H_ */