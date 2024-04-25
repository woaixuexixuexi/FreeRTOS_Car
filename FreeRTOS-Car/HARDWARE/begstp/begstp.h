#ifndef __BEGSTP_H
#define __BEGSTP_H	 
#include "stm32f10x.h"


#define C_DIR_1 PBout(12);
#define C_DIR_2 PBout(13);
#define D_DIR_1 PBout(14);
#define D_DIR_2 PBout(15);


 
void backforward(void);
void forward(void);
void stop(void);
void right (void);
void left (void);
void begstp_Init(void);


void motor1_forward (void);
void motor1_backfoward (void);
void motor2_forward (void);	
void motor2_backfoward (void);
 
#endif 
