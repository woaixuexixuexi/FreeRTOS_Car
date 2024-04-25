#include "encoder.h"


//这里采用TIM2和TIM3的CH1和CH2通道进行编码器的接口输入
//定时器				CH1					CH2
//TIM2				PA0					PA1
//TIM3				PA6					PA7

//这里的定时器2、3挂载在APB1上
//**********************编码器时钟初始化*********************
void Encoder_Count_RCC(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
}
//**********************编码器引脚初始化*********************
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
//**********************编码器功能初始化*********************
void Encoder_Count_Configuration(void)
{
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	//**********TIM2,PA0,PA1***********************************
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter=0xF;  //滤波
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
//**********************编码器初始化*********************
void Encoder_Count_Init(void)
{
  Encoder_Count_RCC();
	Encoder_Count_GPIO();
	Encoder_Count_Configuration();
}
//******************编码器数据读取********************************
int Encoder_Value(TIM_TypeDef* TIMx)
{ 
	int channal_val=0;
	
	channal_val = TIMx ->CNT;
	if(channal_val>>15)//  channal_val 的最高位（即符号位）移到最低位，然后判断该最低位是否为 1。
										//  如果是1那么证明从0开始反转，65535开始减，那么第十六这时候就是1
	
	{			
		channal_val =  (channal_val&0x7FFF)-32767;//通过 channal_val & 0x7FFF 将 channal_val 的最高位清零，保留其他位的值
	}	
  return channal_val;
}
//****************编码器清零*************************************
void Encoder_Count_Clear(TIM_TypeDef* TIMx)
{
  TIMx ->CNT = 0;
}










