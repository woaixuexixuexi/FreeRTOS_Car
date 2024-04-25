#include "begstp.h"

/* 1.0版本的电路板电机驱动部分映射如下
 *电机    编码器引脚     编码器定时器   编码器数组数据   引脚:EN    DIR_1   DIR_2  定时器通道
 *  A       B6,B7          TIM4          Encoder_Date[2]   PA8      PB0   PB1    TIM1->CH1
 *  B       A6 ,A7         TIM3          Encoder_Date[1]   PA9      PB10   PB11    TIM1->CH2*/

/*四个管脚设置不同的电平(1为高电平0为低电平)，作为TB6612的逻辑输入，用以控制电机转动状态。 
打个比方，四个管脚IO分别设置成0 1 0 1，电机反转，那么反过来设置成1 0 1 0时，电机正转*/
	
	
    /*查阅真值表，AIN1  0   0   1
                 AIN2  0   1   0
                     停止正转 反转*/
 
 
 
 
  void begstp_Init(void)
 {
 
  GPIO_InitTypeDef GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_SetBits(GPIOB,GPIO_Pin_3);//PB3高电平	   1
 
 
 }
 void backforward(void)//小车两个电机反转，因为越过终点线时，单纯停止电机工作，小车会因为惯性停不下来，所以短时间的反转，能抵消惯性，从而使小车迅速停下来
{
	 

	  GPIO_SetBits(GPIOB,GPIO_Pin_12);   //PB12高电平	     1
		GPIO_ResetBits(GPIOB,GPIO_Pin_13); //PB13低电平   		 0
		GPIO_SetBits(GPIOB,GPIO_Pin_14);   //PB14高电平	     1
		GPIO_ResetBits(GPIOB,GPIO_Pin_15); //PB15低电平   		 0

        
}
void forward(void)//小车两个电机正转
{


	

		GPIO_ResetBits(GPIOB,GPIO_Pin_12);//PB12低电平   0
		GPIO_SetBits(GPIOB,GPIO_Pin_13);  //PB13高电平	  1
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);//PB14低电平   0
		GPIO_SetBits(GPIOB,GPIO_Pin_15);  //PB15高电平	  1
	

}
void stop(void)//STBY置零，电机停止  pc2  pc3
{

	
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);//PB3低电平	   0
	
}
void motor1_forward (void)
{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);//PB12低电平   0
		GPIO_SetBits(GPIOB,GPIO_Pin_13);  //PB13高电平	  1/////电机AC正转
	



}

void motor1_backfoward (void)
{
	

		GPIO_SetBits(GPIOB,GPIO_Pin_12);   //PB12高电平	  1   
		GPIO_ResetBits(GPIOB,GPIO_Pin_13); //PB13低电平   0////电机AC反转
	

}




void motor2_forward (void)
{

		GPIO_ResetBits(GPIOB,GPIO_Pin_14);//PB14低电平 0 
		GPIO_SetBits(GPIOB,GPIO_Pin_15);  //PB15高电平	 1////电机BD正转
	
	


}

void motor2_backfoward (void)
{
	
	
		GPIO_SetBits(GPIOB,GPIO_Pin_14);   //PB14高电平	 1
		GPIO_ResetBits(GPIOB,GPIO_Pin_15); //PB15低电平   0////电机BD反转

}
 
