#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f10x.h"
 
#define KEY1 	 	GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)//�궨���ȡPA1����
#define KEY2  	GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)//�궨���ȡPA2����
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//�궨���ȡPA3����
 
#define KEY2_PRES 	3
#define KEY1_PRES	  2
#define WKUP_PRES   1
#define WKUP_PRES_long 4
 
void KEY_Init(void);//��ʼ����������
u8 KEY_Scan(u8);//����ɨ�躯������
void key_sta_chage(void);
 
 
#endif 
