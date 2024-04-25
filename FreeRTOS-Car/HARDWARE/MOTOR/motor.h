#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "stm32f10x.h"

//*************��ر���***********************
extern u8 mpu6050_data_flag;  //�Ƿ�������ȡ����
extern int bianma1;         //������1������
extern int bianma2;         //������2������
extern float pitch,roll,yaw;  //ŷ����
extern short aacx,aacy,aacz;	 //���ٶȴ�����ԭʼ����
extern short gyrox,gyroy,gyroz;//������ԭʼ����
extern short mpu6050_temp;		 //�¶�	
extern int bianma1_num;     //��¼1�ű�������ֵ���ڲ���
extern int bianma2_num;     //��¼2�ű�������ֵ���ڲ���
extern int speed_num1;      //1�ŵ���ٶ� 
extern int speed_num2;      //2�ŵ���ٶ� 
extern int PID_temp;        //PID��������ֵ
extern int bianma_cnt1;     //���������1��ת����
extern int bianma_cnt2;     //���������2��ת����
extern int speed_avr1;      //�����ٶ�1   
extern int	speed_last_avr1; //�ϴβ������ٶ�1
extern int speed_avr1_num;  //�ٶ�1�������м�ֵ
extern int speed_bga1[10];    //�ٶ�1�������ݰ�
extern int speed_cnt1;      //�ٶ�1�˲��������
extern int speed_avr2;      //�����ٶ�2  
extern int	speed_last_avr2; //�ϴβ������ٶ�2
extern int speed_avr2_num;  //�ٶ�2�������м�ֵ
extern int speed_bga2[10];    //�ٶ�2�������ݰ�
extern int speed_cnt2;      //�ٶ�2�˲��������
extern int sudu_out;     //�ٶȻ����
extern int zhili_out;       //ֱ�������
extern int zhuan_out;        //ת�����
extern int PWM_OUT1;        //�������������
extern int PWM_OUT2;        //����������ҵ��
extern int Movement;
extern int turnment;

extern char pitch_str[20];
extern char roll_str[20];
extern char yaw_str[20];	// ŷ����
//****************С����е���***************
extern  float Car_zero;
//****************С����е���ƫ��ֵ***************
extern float Car_zero_offset;
//*************PID�����궨��*****************
//ֱ����
extern float zhili_Kp;  //���ִ���ȵ�Ƶ�� -500
extern float zhili_Kd;      //����С���ȸ�Ƶ�� 1.8
//�ٶȻ�
extern float sudu_Kp;  //����200
extern float sudu_Ki;
//ת��
extern float zhuan_Kp;
extern float zhuan_Kd;
//*****************��������************************
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
