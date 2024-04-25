
#include "stm32f10x.h"
#include "string.h"
#include "stdio.h"
#include "key.h"

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

//****查询任务状态****************
char task_buff[500];         //存储表格信息
char task_time_buff[500];    //存储表格信息
//******定义任务句柄***************
TaskHandle_t StartTask_Handler;   //开始任务  
TaskHandle_t LEDTask_Handler;     //LED任务
TaskHandle_t UITask_Handler;      //UI任务
TaskHandle_t SPEEDTask_Handler;   //测速任务
TaskHandle_t MOTOTask_Handler;    //电机任务
TaskHandle_t USART2Task_Handler;     //串口二任务
TaskHandle_t LCDTask_Handler;     //LCD任务
//二值信号量句柄
SemaphoreHandle_t BinarySemaphore;	//二值信号量句柄

//******************************************
//函数名字：开始任务初始化
//函数功能：初始化操作系统的第一个任务函数，用于初始化其他任务
//******************************************
void FreeRTOS_Task_Start(void)
{
  xTaskCreate(
							(TaskFunction_t )start_task,            //任务函数 要和后面定义的函数的名字一样
							(const char*    )"start_task",          //任务名称 和函数名字一样就行
							(uint16_t       )START_STK_SIZE,        //任务堆栈大小
							(void*          )NULL,                  //传递给任务函数的参数
							(UBaseType_t    )START_TASK_PRIO,       //任务优先级
							(TaskHandle_t*  )&StartTask_Handler     //任务句柄和自己定义的句柄名字一样
				     );                
   vTaskStartScheduler();          //开启任务调度 此时只有开始任务，只会执行这1个任务
}	
//******************************************
//函数名字：开始任务
//函数功能：用于初始化其他任务
//******************************************
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区 临界区屏蔽了所有中断，这里的操作不会被打断否则在创建的过程中就会开始执行任务了
   //创建二值信号量
	  BinarySemaphore=xSemaphoreCreateBinary();	
	 xSemaphoreTake(BinarySemaphore, 0); // 清零信号量
	//创建LED任务
    xTaskCreate(
								(TaskFunction_t )led_task,     	
								(const char*    )"led_task",   	
								(uint16_t       )LED_STK_SIZE, 
								(void*          )NULL,				
								(UBaseType_t    )LED_TASK_PRIO,	
								(TaskHandle_t*  )&LEDTask_Handler
							 );   
    //创建UI任务
    xTaskCreate(
								(TaskFunction_t )ui_task,     
								(const char*    )"ui_task",   
								(uint16_t       )UI_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )UI_TASK_PRIO,
								(TaskHandle_t*  )&UITask_Handler
							 );
    //创建SPEED任务
    xTaskCreate(
								(TaskFunction_t )speed_task,     
								(const char*    )"speed_task",   
								(uint16_t       )SPEED_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )SPEED_TASK_PRIO,
								(TaskHandle_t*  )&SPEEDTask_Handler
							 );  	 																
    //创建电机任务
    xTaskCreate(
								(TaskFunction_t )moto_task,     
								(const char*    )"moto_task",   
								(uint16_t       )MOTO_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )MOTO_TASK_PRIO,
								(TaskHandle_t*  )&MOTOTask_Handler
							 );
    //创建wifi控制任务
    xTaskCreate(
								(TaskFunction_t )usart2_task,
								(const char*    )"usart2_task",
								(uint16_t       )USART2_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )USART2_TASK_PRIO,
								(TaskHandle_t*  )&USART2Task_Handler
							 ); 
    //创建LCD显示任务
    xTaskCreate(
								(TaskFunction_t )lcd_task,
								(const char*    )"lcd_task",
								(uint16_t       )LCD_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )LCD_TASK_PRIO,
								(TaskHandle_t*  )&LCDTask_Handler
							 ); 																		
																	
		vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

//******************************************
//函数名字：LED任务
//函数功能：实现心跳灯功能，检测系统是否正常
//******************************************
void usart2_task(void *pvParameters)
{
    while(1)
    {
					/* 获取信号量，如果信号量不可用，则阻塞等待 */
		xSemaphoreTake(  BinarySemaphore, portMAX_DELAY );
//			LCD_Clear(WHITE);
//			delay_xms(2);
//			LCD_Clear(BLACK);
      USART2_WIFI_CTRL();
			vTaskDelay(1);   	
    }
}   



void lcd_task(void *pvParameters)
{
     while(1)
    {
      	sprintf(pitch_str, "pitch：%.2f", pitch);
        sprintf(roll_str, "roll：%.2f", roll);
        sprintf(yaw_str, "yaw：%.2f", yaw);
        LCD_DrawFont_GBK24(0, 10, BLACK, WHITE, (u8 *)pitch_str);
        LCD_DrawFont_GBK24(0, 40, BLACK, WHITE, (u8 *)roll_str);
        LCD_DrawFont_GBK24(0, 70, BLACK, WHITE, (u8 *)yaw_str);
			vTaskDelay(1);   	
    }




}

//******************************************
//函数名字：LED任务
//函数功能：实现心跳灯功能，检测系统是否正常
//******************************************
void led_task(void *pvParameters)
{
    while(1)
    {
      //LED0=~LED0;	    //心跳灯
			//Feed_dog();   //喂狗
			//ADC_Check1();
			vTaskDelay(1);   	
    }
}   
  u8 u=0;
//******************************************
//函数名字：UI任务
//函数功能：实现测速1功能，实时检测轮子速度
//******************************************
void ui_task(void *pvParameters)
{
	 while(1)
    { 
			  //LCD_Clear(WHITE);
			LED0=!LED0;
			UI();
     	

			vTaskDelay(2); 
		
    
    }
}
//******************************************
//函数名字：SPEED任务
//函数功能：实现测速功能，实时检测轮子速度
//******************************************
u8 times = 0;
void speed_task(void *pvParameters)
{
	while(1)
   {
    
  times++;
  MPU6050_Data_read();	//获取陀螺仪数据	
	if(times>=5)
	{
		times=0;  
	  Moto_Speed_Read(1); //读取速度
	  Moto_Speed_Read(2);	//读取速度
	  
	}
  Smart_Car_Task();     //平衡车运动任务	
		  vTaskDelay(1);   
    }
	
	 
	
}
//******************************************
//函数名字：MOTO任务
//函数功能：
//******************************************
void moto_task(void *pvParameters)
{
    while(1)
    {    

			vTaskDelay(10); 	
    }
}




























