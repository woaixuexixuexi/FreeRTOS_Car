#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x.h"
//#include "timer.h"
//#include "lcd.h"
#include "stdio.h"
#include "delay.h"
#include "sys.h"
//#include "pwm.h"
#include "key.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PAout(8)// PA8
	

void LED_Init(void);//��ʼ��
void LED_GPIO_High(void);
void LED_GPIO_low(void);

		 				    
#endif
