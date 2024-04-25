#include "encoder.h"


//�������TIM2��TIM3��CH1��CH2ͨ�����б������Ľӿ�����
//��ʱ��				CH1					CH2
//TIM2				PA0					PA1
//TIM3				PA6					PA7

//����Ķ�ʱ��2��3������APB1��
//**********************������ʱ�ӳ�ʼ��*********************
void Encoder_Count_RCC(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
}
//**********************���������ų�ʼ��*********************
void Encoder_Count_GPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//**********TIM2,PA0,PA1****************
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//**********TIM3,PA6,PA7****************
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

}
//**********************���������ܳ�ʼ��*********************
void Encoder_Count_Configuration(void)
{
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	//**********TIM2,PA0,PA1***********************************
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter=0xF;  //�˲�
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInit(TIM2, &TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICFilter=0xF;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInit(TIM2, &TIM_ICInitStruct);	
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_Period=65535;    //65536-1
	TIM_TimeBaseInitStruct.TIM_Prescaler=0;     //1-1
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	TIM_Cmd(TIM2,ENABLE);  
	//**********TIM3,PA6,PA7***********************************
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter=0xF;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInit(TIM3, &TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICFilter=0xF;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInit(TIM3, &TIM_ICInitStruct);	
	
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_Period=65535;    //65536-1
	TIM_TimeBaseInitStruct.TIM_Prescaler=0;     //1-1
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	TIM_Cmd(TIM3,ENABLE);  
}
//**********************��������ʼ��*********************
void Encoder_Count_Init(void)
{
  Encoder_Count_RCC();
	Encoder_Count_GPIO();
	Encoder_Count_Configuration();
}
//******************���������ݶ�ȡ********************************
int Encoder_Value(TIM_TypeDef* TIMx)
{ 
	int channal_val=0;
	
	channal_val = TIMx ->CNT;
	if(channal_val>>15)//  channal_val �����λ��������λ���Ƶ����λ��Ȼ���жϸ����λ�Ƿ�Ϊ 1��
										//  �����1��ô֤����0��ʼ��ת��65535��ʼ������ô��ʮ����ʱ�����1
	
	{			
		channal_val =  (channal_val&0x7FFF)-32767;//ͨ�� channal_val & 0x7FFF �� channal_val �����λ���㣬��������λ��ֵ
	}	
  return channal_val;
}
//****************����������*************************************
void Encoder_Count_Clear(TIM_TypeDef* TIMx)
{
  TIMx ->CNT = 0;
}










