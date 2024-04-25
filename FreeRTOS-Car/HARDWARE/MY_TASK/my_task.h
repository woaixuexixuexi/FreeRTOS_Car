#ifndef __MY_TASK_H
#define __MY_TASK_H	 
//#include "pbdata.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
//*******�������ȼ�0-31,Խ��Խ����*******************
#define START_TASK_PRIO		  1
#define LED_TASK_PRIO		  2
#define MOTO_TASK_PRIO		  2
#define LCD_TASK_PRIO         3
#define UI_TASK_PRIO		  4
#define USART2_TASK_PRIO      4
#define SPEED_TASK_PRIO		  5

//*******�����ջ��С	��λ�� *4�ĵ�λΪ�ֽ� 1024�ֽ�Ϊ1KB**********
#define START_STK_SIZE 		 100     
#define LED_STK_SIZE 		 500  
#define UI_STK_SIZE          500  
#define SPEED_STK_SIZE       1000 
#define MOTO_STK_SIZE 	     500
#define USART2_STK_SIZE      500
#define LCD_STK_SIZE         500


//****��ѯ����״̬****************
extern char task_buff[500];    //�洢�����Ϣ
extern char task_time_buff[500];
//********������*******************
extern TaskHandle_t StartTask_Handler;     
extern TaskHandle_t LEDTask_Handler;
extern TaskHandle_t UITask_Handler;
extern TaskHandle_t SPEEDTask_Handler;
extern TaskHandle_t MOTOTask_Handler;


extern SemaphoreHandle_t BinarySemaphore;	//��ֵ�ź������
//********������*******************
void FreeRTOS_Task_Start(void);
void start_task(void *pvParameters);
void led_task(void *pvParameters);
void ui_task(void *pvParameters);	
void speed_task(void *pvParameters);	
void moto_task(void *pvParameters);
void usart2_task(void *pvParameters);	
void lcd_task(void *pvParameters);	
void api_task(void *pvParameters);
void apitime_task(void *pvParameters);
#endif
