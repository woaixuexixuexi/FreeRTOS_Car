#include "begstp.h"

/* 1.0�汾�ĵ�·������������ӳ������
 *���    ����������     ��������ʱ��   ��������������   ����:EN    DIR_1   DIR_2  ��ʱ��ͨ��
 *  A       B6,B7          TIM4          Encoder_Date[2]   PA8      PB0   PB1    TIM1->CH1
 *  B       A6 ,A7         TIM3          Encoder_Date[1]   PA9      PB10   PB11    TIM1->CH2*/

/*�ĸ��ܽ����ò�ͬ�ĵ�ƽ(1Ϊ�ߵ�ƽ0Ϊ�͵�ƽ)����ΪTB6612���߼����룬���Կ��Ƶ��ת��״̬�� 
����ȷ����ĸ��ܽ�IO�ֱ����ó�0 1 0 1�������ת����ô���������ó�1 0 1 0ʱ�������ת*/
	
	
    /*������ֵ��AIN1  0   0   1
                 AIN2  0   1   0
                     ֹͣ��ת ��ת*/
 
 
 
 
  void begstp_Init(void)
 {
 
  GPIO_InitTypeDef GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_SetBits(GPIOB,GPIO_Pin_3);//PB3�ߵ�ƽ	   1
 
 
 }
 void backforward(void)//С�����������ת����ΪԽ���յ���ʱ������ֹͣ���������С������Ϊ����ͣ�����������Զ�ʱ��ķ�ת���ܵ������ԣ��Ӷ�ʹС��Ѹ��ͣ����
{
	 

	  GPIO_SetBits(GPIOB,GPIO_Pin_12);   //PB12�ߵ�ƽ	     1
		GPIO_ResetBits(GPIOB,GPIO_Pin_13); //PB13�͵�ƽ   		 0
		GPIO_SetBits(GPIOB,GPIO_Pin_14);   //PB14�ߵ�ƽ	     1
		GPIO_ResetBits(GPIOB,GPIO_Pin_15); //PB15�͵�ƽ   		 0

        
}
void forward(void)//С�����������ת
{


	

		GPIO_ResetBits(GPIOB,GPIO_Pin_12);//PB12�͵�ƽ   0
		GPIO_SetBits(GPIOB,GPIO_Pin_13);  //PB13�ߵ�ƽ	  1
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);//PB14�͵�ƽ   0
		GPIO_SetBits(GPIOB,GPIO_Pin_15);  //PB15�ߵ�ƽ	  1
	

}
void stop(void)//STBY���㣬���ֹͣ  pc2  pc3
{

	
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);//PB3�͵�ƽ	   0
	
}
void motor1_forward (void)
{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);//PB12�͵�ƽ   0
		GPIO_SetBits(GPIOB,GPIO_Pin_13);  //PB13�ߵ�ƽ	  1/////���AC��ת
	



}

void motor1_backfoward (void)
{
	

		GPIO_SetBits(GPIOB,GPIO_Pin_12);   //PB12�ߵ�ƽ	  1   
		GPIO_ResetBits(GPIOB,GPIO_Pin_13); //PB13�͵�ƽ   0////���AC��ת
	

}




void motor2_forward (void)
{

		GPIO_ResetBits(GPIOB,GPIO_Pin_14);//PB14�͵�ƽ 0 
		GPIO_SetBits(GPIOB,GPIO_Pin_15);  //PB15�ߵ�ƽ	 1////���BD��ת
	
	


}

void motor2_backfoward (void)
{
	
	
		GPIO_SetBits(GPIOB,GPIO_Pin_14);   //PB14�ߵ�ƽ	 1
		GPIO_ResetBits(GPIOB,GPIO_Pin_15); //PB15�͵�ƽ   0////���BD��ת

}
 
