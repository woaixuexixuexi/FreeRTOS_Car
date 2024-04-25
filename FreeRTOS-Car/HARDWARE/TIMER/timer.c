#include "time.h" 
#include "motor.h"
#include "led.h"

u16 time6=0;          //��׼��ʱ��λ
u16 time7=0;          //��׼��ʱ��λ


//**********************����ϵͳʱ��*********************************
void TIM6_RCC_Configuration(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);  //��time6���ж�ʱ��
}
//**********************����ϵͳʱ��*********************************
void TIM7_RCC_Configuration(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);  //��time7���ж�ʱ��
}
//**********************ʱ���ж����ú���*********************************
void TIM6_Configuration(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ClearITPendingBit(TIM6,TIM_IT_Update); 	                //�����ʱ���ж�
  TIM_TimeBaseStructure.TIM_Period=3599;                      //����3600,1����  
  TIM_TimeBaseStructure.TIM_Prescaler=19;                     //20��Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision=0;                  //���˲�
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;   //���ϼ���ģʽ
  TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);              //��ʼ��
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);                    //�򿪶�ʱ���ж�
	TIM_Cmd(TIM6,ENABLE);                                       //�򿪶�ʱ������
}

//**********************ʱ���ж����ú���*********************************
void TIM7_Configuration(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ClearITPendingBit(TIM7,TIM_IT_Update); 	                //�����ʱ���ж�
  TIM_TimeBaseStructure.TIM_Period=36;                        //����36,10uS
  TIM_TimeBaseStructure.TIM_Prescaler=20;                     //20��Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision=0;                  //���˲�
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;   //���ϼ���ģʽ
  TIM_TimeBaseInit(TIM7,&TIM_TimeBaseStructure);              //��ʼ��
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);                    //�򿪶�ʱ���ж�
	TIM_Cmd(TIM7,ENABLE);                                       //�򿪶�ʱ������
}
//**************************�������ȼ�***********************************
void TIM6_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;                        //Ϊ�ṹ�嶨��ṹ�����
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);             //�����ȼ����з���
  NVIC_InitStructure.NVIC_IRQChannel =TIM6_IRQn;              //�ⲿ�ж�5����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //��ռ���ȼ�Ϊ3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //��Ӧ���ȼ�Ϊ0         
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //ʹ��
  NVIC_Init(&NVIC_InitStructure);                             //��ʼ��
}
//**************************�������ȼ�***********************************
void TIM7_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;                        //Ϊ�ṹ�嶨��ṹ�����
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);             //�����ȼ����з���
  NVIC_InitStructure.NVIC_IRQChannel =TIM7_IRQn;              //�ⲿ�ж�5����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;   //��ռ���ȼ�Ϊ4
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //��Ӧ���ȼ�Ϊ0         
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //ʹ��
  NVIC_Init(&NVIC_InitStructure);                             //��ʼ��
}
//*********************��ʱ����ʼ��********************************************
void time6_init(void)
{
  TIM6_RCC_Configuration();
	TIM6_Configuration();
  TIM6_NVIC_Configuration();
}
//*********************��ʱ����ʼ��********************************************
void time7_init(void)
{
  TIM7_RCC_Configuration();
	TIM7_Configuration();
  TIM7_NVIC_Configuration();
}


//FreeRTOSʱ��ͳ�����õĽ��ļ�����
volatile unsigned long long FreeRTOSRunTimeTicks;
//��ʼ����ʱ��ר��
void ConfigureTimeForRunTimeStats(void)
{
	FreeRTOSRunTimeTicks=0;
	time7_init();
}

//*************************************�жϺ������� ***************************
void TIM6_IRQHandler(void)
{
	time6++;	
  MPU6050_Data_read();	//��ȡ����������	
	if(time6>=5)
	{
		time6=0;  
	  Moto_Speed_Read(1); //��ȡ�ٶ�
	  Moto_Speed_Read(2);	//��ȡ�ٶ�
	  
	}
  Smart_Car_Task();     //ƽ�⳵�˶�����	
  TIM_ClearITPendingBit(TIM6,TIM_IT_Update); 	         //�����ʱ���ж�	
}
//*************************************�жϺ������� ***************************
void TIM7_IRQHandler(void)
{
	//time7++;		
	FreeRTOSRunTimeTicks++;   //10uSһ��
  TIM_ClearITPendingBit(TIM7,TIM_IT_Update); 	         //�����ʱ���ж�	
}















