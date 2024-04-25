#ifndef __ENCODER_H
#define __ENCODER_H	 
#include "stm32f10x.h"

void Encoder_Count_RCC(void);
void Encoder_Count_GPIO(void);
void Encoder_Count_Configuration(void);
void Encoder_Count_Init(void);
int Encoder_Value(TIM_TypeDef* TIMx);
void Encoder_Count_Clear(TIM_TypeDef* TIMx);


#endif 
