#ifndef __REMOTE_CTRL_H
#define __REMOTE_CTRL_H
#include "stdio.h"	
#include "stm32f10x.h"


extern u8 front_flag;      //Ç°½øÃüÁî
extern u8 back_flag;       //ºóÍËÃüÁî
extern u8 turn_left_flag;  //×ó×ªÃüÁî
extern u8 turn_right_flag; //ÓÒ×ªÃüÁî
extern u8 stop_flag;       //Í£Ö¹ÃüÁî
extern u8 voice_flag;      //ÒôÆµ²¥·ÅÃüÁî
void MSG_Analyze_BT(void);
void UI(void);


#endif
