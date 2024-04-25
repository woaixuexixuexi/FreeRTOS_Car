#ifndef __PWM_H
#define __PWM_H
#include "stm32f10x.h"
#include "sys.h"

void TIM1_PWM_Init(void);


void PWM_RCC(void);                  //时钟配置   
void PWM_GPIO(void);                 //管脚配置
void PWM_TIM3_Configuration(void);   //占空比时钟控制
void TIM3_NVIC_Configuration(void);  //优先级
void PWM_Init(void);                 //初始化 



#endif
