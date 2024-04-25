

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

//********************ESP8266相关******************************
#include "usart2.h"
#include "esp8266.h"
//*********************ESP8266相关******************************

//********************MPU6050陀螺仪相关******************************
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"

//********************MPU6050陀螺仪相关******************************

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
//    char yaw_str[20];	// 欧拉角
	SystemInit();
	my_mem_init(SRAMIN);            	//初始化内部内存池
	time7_init();         // 定时器4初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);                                              //2位响应优先级,优先级数字越小，优先级越高
	USART_Config();
	usart2_init(115200);     //初始化串口二
	delay_init(); // 延时函数初始化
	LED_Init();   // 初始化与LED连接的硬件接口
	LCD_Init();
	LCD_Clear(WHITE);
	
	
	esp8266_start_trans();
	
	
	Encoder_Count_Init(); // 编码器初始化
	
	MPU_Init(); // 初始化MPU6050
	while (mpu_dmp_init())
	{
		delay_ms(20);
		printf("初始化失败");
	}

	USART2_RX_STA = 0;

	LCD_Clear(BLACK);
	begstp_Init();
	forward();	
	TIM1_PWM_Init();
	//time6_init();         // 定时器2初始化  

    
	FreeRTOS_Task_Start(); //操作系统开始运行
}

