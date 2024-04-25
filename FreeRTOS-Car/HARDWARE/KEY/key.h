#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f10x.h"
 
#define KEY1 	 	GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)//宏定义读取PA1引脚
#define KEY2  	GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)//宏定义读取PA2引脚
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//宏定义读取PA3引脚
 
#define KEY2_PRES 	3
#define KEY1_PRES	  2
#define WKUP_PRES   1
#define WKUP_PRES_long 4
 
void KEY_Init(void);//初始化函数声明
u8 KEY_Scan(u8);//按键扫描函数声明
void key_sta_chage(void);
 
 
#endif 
