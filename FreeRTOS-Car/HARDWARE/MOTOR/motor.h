#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "stm32f10x.h"

//*************相关变量***********************
extern u8 mpu6050_data_flag;  //是否正常读取数据
extern int bianma1;         //编码器1的数据
extern int bianma2;         //编码器2的数据
extern float pitch,roll,yaw;  //欧拉角
extern short aacx,aacy,aacz;	 //加速度传感器原始数据
extern short gyrox,gyroy,gyroz;//陀螺仪原始数据
extern short mpu6050_temp;		 //温度	
extern int bianma1_num;     //记录1号编码器数值用于测速
extern int bianma2_num;     //记录2号编码器数值用于测速
extern int speed_num1;      //1号电机速度 
extern int speed_num2;      //2号电机速度 
extern int PID_temp;        //PID计算后输出值
extern int bianma_cnt1;     //保存编码器1旋转总数
extern int bianma_cnt2;     //保存编码器2旋转总数
extern int speed_avr1;      //测量速度1   
extern int	speed_last_avr1; //上次测量的速度1
extern int speed_avr1_num;  //速度1计算用中间值
extern int speed_bga1[10];    //速度1缓存数据包
extern int speed_cnt1;      //速度1滤波数组计数
extern int speed_avr2;      //测量速度2  
extern int	speed_last_avr2; //上次测量的速度2
extern int speed_avr2_num;  //速度2计算用中间值
extern int speed_bga2[10];    //速度2缓存数据包
extern int speed_cnt2;      //速度2滤波数组计数
extern int sudu_out;     //速度环输出
extern int zhili_out;       //直立环输出
extern int zhuan_out;        //转向换输出
extern int PWM_OUT1;        //最终输出到左电机
extern int PWM_OUT2;        //最终输出到右电机
extern int Movement;
extern int turnment;

extern char pitch_str[20];
extern char roll_str[20];
extern char yaw_str[20];	// 欧拉角
//****************小车机械零点***************
extern  float Car_zero;
//****************小车机械零点偏移值***************
extern float Car_zero_offset;
//*************PID参数宏定义*****************
//直立环
extern float zhili_Kp;  //出现大幅度低频振荡 -500
extern float zhili_Kd;      //出现小幅度高频振荡 1.8
//速度环
extern float sudu_Kp;  //除以200
extern float sudu_Ki;
//转向环
extern float zhuan_Kp;
extern float zhuan_Kd;
//*****************函数申明************************
void Encoder_Count_read(void);  
void MPU6050_Data_read(void);
void Moto_Speed_Read(u8 n);
int my_abs(int n);
void Moto_Ctrl(int pwm,u8 n);
void Speed1_Read(void);
void Speed2_Read(void);
void Smart_Car_Task(void);
void Moto_Task(void);


#endif 
