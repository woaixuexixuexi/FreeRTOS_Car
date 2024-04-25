#include "time.h" 
#include "motor.h"
#include "led.h"

u16 time6=0;          //基准定时单位
u16 time7=0;          //基准定时单位


//**********************配置系统时钟*********************************
void TIM6_RCC_Configuration(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);  //打开time6的中断时钟
}
//**********************配置系统时钟*********************************
void TIM7_RCC_Configuration(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);  //打开time7的中断时钟
}
//**********************时钟中断配置函数*********************************
void TIM6_Configuration(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ClearITPendingBit(TIM6,TIM_IT_Update); 	                //清除定时器中断
  TIM_TimeBaseStructure.TIM_Period=3599;                      //计数3600,1毫秒  
  TIM_TimeBaseStructure.TIM_Prescaler=19;                     //20分频
  TIM_TimeBaseStructure.TIM_ClockDivision=0;                  //不滤波
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;   //向上计数模式
  TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);              //初始化
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);                    //打开定时器中断
	TIM_Cmd(TIM6,ENABLE);                                       //打开定时器外设
}

//**********************时钟中断配置函数*********************************
void TIM7_Configuration(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ClearITPendingBit(TIM7,TIM_IT_Update); 	                //清除定时器中断
  TIM_TimeBaseStructure.TIM_Period=36;                        //计数36,10uS
  TIM_TimeBaseStructure.TIM_Prescaler=20;                     //20分频
  TIM_TimeBaseStructure.TIM_ClockDivision=0;                  //不滤波
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;   //向上计数模式
  TIM_TimeBaseInit(TIM7,&TIM_TimeBaseStructure);              //初始化
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);                    //打开定时器中断
	TIM_Cmd(TIM7,ENABLE);                                       //打开定时器外设
}
//**************************配置优先级***********************************
void TIM6_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;                        //为结构体定义结构体变量
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);             //对优先级进行分组
  NVIC_InitStructure.NVIC_IRQChannel =TIM6_IRQn;              //外部中断5引脚
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //抢占优先级为3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //响应优先级为0         
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能
  NVIC_Init(&NVIC_InitStructure);                             //初始化
}
//**************************配置优先级***********************************
void TIM7_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;                        //为结构体定义结构体变量
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);             //对优先级进行分组
  NVIC_InitStructure.NVIC_IRQChannel =TIM7_IRQn;              //外部中断5引脚
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;   //抢占优先级为4
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //响应优先级为0         
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能
  NVIC_Init(&NVIC_InitStructure);                             //初始化
}
//*********************定时器初始化********************************************
void time6_init(void)
{
  TIM6_RCC_Configuration();
	TIM6_Configuration();
  TIM6_NVIC_Configuration();
}
//*********************定时器初始化********************************************
void time7_init(void)
{
  TIM7_RCC_Configuration();
	TIM7_Configuration();
  TIM7_NVIC_Configuration();
}


//FreeRTOS时间统计所用的节拍计数器
volatile unsigned long long FreeRTOSRunTimeTicks;
//初始化定时器专用
void ConfigureTimeForRunTimeStats(void)
{
	FreeRTOSRunTimeTicks=0;
	time7_init();
}

//*************************************中断函数配置 ***************************
void TIM6_IRQHandler(void)
{
	time6++;	
  MPU6050_Data_read();	//获取陀螺仪数据	
	if(time6>=5)
	{
		time6=0;  
	  Moto_Speed_Read(1); //读取速度
	  Moto_Speed_Read(2);	//读取速度
	  
	}
  Smart_Car_Task();     //平衡车运动任务	
  TIM_ClearITPendingBit(TIM6,TIM_IT_Update); 	         //清除定时器中断	
}
//*************************************中断函数配置 ***************************
void TIM7_IRQHandler(void)
{
	//time7++;		
	FreeRTOSRunTimeTicks++;   //10uS一次
  TIM_ClearITPendingBit(TIM7,TIM_IT_Update); 	         //清除定时器中断	
}















