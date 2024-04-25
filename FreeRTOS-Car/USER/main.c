

#include "stm32f10x.h"
#include "stdio.h"


#include "malloc.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "my_task.h"

#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "usart.h"

//********************ESP8266���******************************
#include "usart2.h"
#include "esp8266.h"
//*********************ESP8266���******************************

//********************MPU6050���������******************************
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"

//********************MPU6050���������******************************

#include "encoder.h"
#include "pwm.h"
#include "time.h"

#include "begstp.h"
#include "motor.h"

#include "remote_ctrl.h"



int main(void)
{
  
//	  float pitch, roll, yaw;
//    char pitch_str[20];
//    char roll_str[20];
//    char yaw_str[20];	// ŷ����
	SystemInit();
	my_mem_init(SRAMIN);            	//��ʼ���ڲ��ڴ��
	time7_init();         // ��ʱ��4��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);                                              //2λ��Ӧ���ȼ�,���ȼ�����ԽС�����ȼ�Խ��
	USART_Config();
	usart2_init(115200);     //��ʼ�����ڶ�
	delay_init(); // ��ʱ������ʼ��
	LED_Init();   // ��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();
	LCD_Clear(WHITE);
	
	
	esp8266_start_trans();
	
	
	Encoder_Count_Init(); // ��������ʼ��
	
	MPU_Init(); // ��ʼ��MPU6050
	while (mpu_dmp_init())
	{
		delay_ms(20);
		printf("��ʼ��ʧ��");
	}

	USART2_RX_STA = 0;

	LCD_Clear(BLACK);
	begstp_Init();
	forward();	
	TIM1_PWM_Init();
	//time6_init();         // ��ʱ��2��ʼ��  

    
	FreeRTOS_Task_Start(); //����ϵͳ��ʼ����
}

