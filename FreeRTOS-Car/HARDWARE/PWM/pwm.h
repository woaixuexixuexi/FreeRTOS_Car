#ifndef __PWM_H
#define __PWM_H
#include "stm32f10x.h"
#include "sys.h"

void TIM1_PWM_Init(void);


void PWM_RCC(void);                  //ʱ������   
void PWM_GPIO(void);                 //�ܽ�����
void PWM_TIM3_Configuration(void);   //ռ�ձ�ʱ�ӿ���
void TIM3_NVIC_Configuration(void);  //���ȼ�
void PWM_Init(void);                 //��ʼ�� 



#endif
