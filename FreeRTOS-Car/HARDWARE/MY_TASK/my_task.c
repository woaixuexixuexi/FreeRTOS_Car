
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

//****��ѯ����״̬****************
char task_buff[500];         //�洢�����Ϣ
char task_time_buff[500];    //�洢�����Ϣ
//******����������***************
TaskHandle_t StartTask_Handler;   //��ʼ����  
TaskHandle_t LEDTask_Handler;     //LED����
TaskHandle_t UITask_Handler;      //UI����
TaskHandle_t SPEEDTask_Handler;   //��������
TaskHandle_t MOTOTask_Handler;    //�������
TaskHandle_t USART2Task_Handler;     //���ڶ�����
TaskHandle_t LCDTask_Handler;     //LCD����
//��ֵ�ź������
SemaphoreHandle_t BinarySemaphore;	//��ֵ�ź������

//******************************************
//�������֣���ʼ�����ʼ��
//�������ܣ���ʼ������ϵͳ�ĵ�һ�������������ڳ�ʼ����������
//******************************************
void FreeRTOS_Task_Start(void)
{
  xTaskCreate(
							(TaskFunction_t )start_task,            //������ Ҫ�ͺ��涨��ĺ���������һ��
							(const char*    )"start_task",          //�������� �ͺ�������һ������
							(uint16_t       )START_STK_SIZE,        //�����ջ��С
							(void*          )NULL,                  //���ݸ��������Ĳ���
							(UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
							(TaskHandle_t*  )&StartTask_Handler     //���������Լ�����ľ������һ��
				     );                
   vTaskStartScheduler();          //����������� ��ʱֻ�п�ʼ����ֻ��ִ����1������
}	
//******************************************
//�������֣���ʼ����
//�������ܣ����ڳ�ʼ����������
//******************************************
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ��� �ٽ��������������жϣ�����Ĳ������ᱻ��Ϸ����ڴ����Ĺ����оͻῪʼִ��������
   //������ֵ�ź���
	  BinarySemaphore=xSemaphoreCreateBinary();	
	 xSemaphoreTake(BinarySemaphore, 0); // �����ź���
	//����LED����
    xTaskCreate(
								(TaskFunction_t )led_task,     	
								(const char*    )"led_task",   	
								(uint16_t       )LED_STK_SIZE, 
								(void*          )NULL,				
								(UBaseType_t    )LED_TASK_PRIO,	
								(TaskHandle_t*  )&LEDTask_Handler
							 );   
    //����UI����
    xTaskCreate(
								(TaskFunction_t )ui_task,     
								(const char*    )"ui_task",   
								(uint16_t       )UI_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )UI_TASK_PRIO,
								(TaskHandle_t*  )&UITask_Handler
							 );
    //����SPEED����
    xTaskCreate(
								(TaskFunction_t )speed_task,     
								(const char*    )"speed_task",   
								(uint16_t       )SPEED_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )SPEED_TASK_PRIO,
								(TaskHandle_t*  )&SPEEDTask_Handler
							 );  	 																
    //�����������
    xTaskCreate(
								(TaskFunction_t )moto_task,     
								(const char*    )"moto_task",   
								(uint16_t       )MOTO_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )MOTO_TASK_PRIO,
								(TaskHandle_t*  )&MOTOTask_Handler
							 );
    //����wifi��������
    xTaskCreate(
								(TaskFunction_t )usart2_task,
								(const char*    )"usart2_task",
								(uint16_t       )USART2_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )USART2_TASK_PRIO,
								(TaskHandle_t*  )&USART2Task_Handler
							 ); 
    //����LCD��ʾ����
    xTaskCreate(
								(TaskFunction_t )lcd_task,
								(const char*    )"lcd_task",
								(uint16_t       )LCD_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )LCD_TASK_PRIO,
								(TaskHandle_t*  )&LCDTask_Handler
							 ); 																		
																	
		vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

//******************************************
//�������֣�LED����
//�������ܣ�ʵ�������ƹ��ܣ����ϵͳ�Ƿ�����
//******************************************
void usart2_task(void *pvParameters)
{
    while(1)
    {
					/* ��ȡ�ź���������ź��������ã��������ȴ� */
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
      	sprintf(pitch_str, "pitch��%.2f", pitch);
        sprintf(roll_str, "roll��%.2f", roll);
        sprintf(yaw_str, "yaw��%.2f", yaw);
        LCD_DrawFont_GBK24(0, 10, BLACK, WHITE, (u8 *)pitch_str);
        LCD_DrawFont_GBK24(0, 40, BLACK, WHITE, (u8 *)roll_str);
        LCD_DrawFont_GBK24(0, 70, BLACK, WHITE, (u8 *)yaw_str);
			vTaskDelay(1);   	
    }




}

//******************************************
//�������֣�LED����
//�������ܣ�ʵ�������ƹ��ܣ����ϵͳ�Ƿ�����
//******************************************
void led_task(void *pvParameters)
{
    while(1)
    {
      //LED0=~LED0;	    //������
			//Feed_dog();   //ι��
			//ADC_Check1();
			vTaskDelay(1);   	
    }
}   
  u8 u=0;
//******************************************
//�������֣�UI����
//�������ܣ�ʵ�ֲ���1���ܣ�ʵʱ��������ٶ�
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
//�������֣�SPEED����
//�������ܣ�ʵ�ֲ��ٹ��ܣ�ʵʱ��������ٶ�
//******************************************
u8 times = 0;
void speed_task(void *pvParameters)
{
	while(1)
   {
    
  times++;
  MPU6050_Data_read();	//��ȡ����������	
	if(times>=5)
	{
		times=0;  
	  Moto_Speed_Read(1); //��ȡ�ٶ�
	  Moto_Speed_Read(2);	//��ȡ�ٶ�
	  
	}
  Smart_Car_Task();     //ƽ�⳵�˶�����	
		  vTaskDelay(1);   
    }
	
	 
	
}
//******************************************
//�������֣�MOTO����
//�������ܣ�
//******************************************
void moto_task(void *pvParameters)
{
    while(1)
    {    

			vTaskDelay(10); 	
    }
}




























