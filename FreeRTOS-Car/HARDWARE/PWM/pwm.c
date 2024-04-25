#include "pwm.h"

void TIM1_PWM_Init() //  �����PWM�źų�ʼ������
{

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    GPIO_InitTypeDef GPIO_InitStruct;								//GPIO��ʼ�� �ṹ�����
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    

	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; //GPIO���ø����������ģʽ
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; //TIM1ͬʱ������·PWM�� �ڹܽ�a8 a11
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  //GPIO�ٶ�50MHZ
    GPIO_Init(GPIOA,&GPIO_InitStruct);  //��ʼ������ �øո����õĲ��� ���뵽��Ӧ�Ĵ�������
     




    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

	
    TIM_TimeBaseStructure.TIM_Period = 7200;							//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ 80K
    TIM_TimeBaseStructure.TIM_Prescaler =0;						//����������Ϊ TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ ����Ƶ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//���ϼ���
    TIM_TimeBaseStructure.TIM_RepetitionCounter=0;					//�ظ��Ĵ����������Զ�����
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 				//�ڳ�ʼ�� TIMx

	 TIM_ARRPreloadConfig(TIM1, ENABLE);   //������ֹ�ڶ�ʱ������ʱ��ARR�Ļ�������д����ֵ���Ա��ڸ����¼�����ʱ���븲����ǰ��ֵ��
	       //�������ȼ�

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //�������ģʽ ͨ��1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Disable;//ʹ�ܻ��������
    TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset; //���������״̬
    TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;//�����󻥲������״̬
    TIM_OCInitStructure.TIM_Pulse = 0; 							//���ô�װ�벶��ȽϼĴ���������ֵ
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //������Ը�
    TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High; //���û������������
                               //û�б�д�жϷ������������жϷ������и�����û�и�ARR����������д����ֵ����



    TIM_OC3Init(TIM1, &TIM_OCInitStructure); 			//�۳�ʼ������ TIMx
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable); 	//CH3 Ԥװ��ʹ��

   TIM_OC4Init(TIM1, &TIM_OCInitStructure); 			//�۳�ʼ������ TIMx
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable); 	//CH4 Ԥװ��ʹ��

    TIM_SetAutoreload(TIM1, 7200);//���ö�ʱ��1��װ��ֵ

    TIM_SetCompare3(TIM1,1000);
    TIM_SetCompare4(TIM1,1000);

    TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE); //ʹ�ܵ�TIM1�����ж�


    TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1

    TIM_CtrlPWMOutputs(TIM1,ENABLE); //��PWM���ʹ��
    //return;
}



















































