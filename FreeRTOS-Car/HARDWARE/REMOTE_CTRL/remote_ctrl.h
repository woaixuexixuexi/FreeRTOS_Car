#ifndef __REMOTE_CTRL_H
#define __REMOTE_CTRL_H
#include "stdio.h"	
#include "stm32f10x.h"


extern u8 front_flag;      //ǰ������
extern u8 back_flag;       //��������
extern u8 turn_left_flag;  //��ת����
extern u8 turn_right_flag; //��ת����
extern u8 stop_flag;       //ֹͣ����
extern u8 voice_flag;      //��Ƶ��������
void MSG_Analyze_BT(void);
void UI(void);


#endif
