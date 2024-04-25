#include "pwm.h"

void TIM1_PWM_Init() //  电机的PWM信号初始化函数
{

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    GPIO_InitTypeDef GPIO_InitStruct;								//GPIO初始化 结构体变量
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    

	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; //GPIO采用复用推挽输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; //TIM1同时产生两路PWM波 在管脚a8 a11
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  //GPIO速度50MHZ
    GPIO_Init(GPIOA,&GPIO_InitStruct);  //初始化函数 让刚刚配置的参数 输入到对应寄存器里面
     




    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

	
    TIM_TimeBaseStructure.TIM_Period = 7200;							//设置在下一个更新事件装入活动的自动重装载寄存器周期的值 80K
    TIM_TimeBaseStructure.TIM_Prescaler =0;						//设置用来作为 TIMx 时钟频率除数的预分频值 不分频
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//向上计数
    TIM_TimeBaseStructure.TIM_RepetitionCounter=0;					//重复寄存器，用于自动更新
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 				//②初始化 TIMx

	 TIM_ARRPreloadConfig(TIM1, ENABLE);   //允许或禁止在定时器工作时向ARR的缓冲器中写入新值，以便在更新事件发生时载入覆盖以前的值。
	       //设置优先级

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //脉宽调制模式 通道1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Disable;//使能互补端输出
    TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset; //死区后输出状态
    TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;//死区后互补端输出状态
    TIM_OCInitStructure.TIM_Pulse = 0; 							//设置待装入捕获比较寄存器的脉冲值
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性高
    TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High; //设置互补端输出极性
                               //没有编写中断服务函数或者在中断服务函数中根本就没有给ARR缓冲器重新写入新值警告



    TIM_OC3Init(TIM1, &TIM_OCInitStructure); 			//③初始化外设 TIMx
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable); 	//CH3 预装载使能

   TIM_OC4Init(TIM1, &TIM_OCInitStructure); 			//③初始化外设 TIMx
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable); 	//CH4 预装载使能

    TIM_SetAutoreload(TIM1, 7200);//设置定时器1重装载值

    TIM_SetCompare3(TIM1,1000);
    TIM_SetCompare4(TIM1,1000);

    TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE); //使能的TIM1更新中断


    TIM_Cmd(TIM1, ENABLE);  //使能TIM1

    TIM_CtrlPWMOutputs(TIM1,ENABLE); //⑤PWM输出使能
    //return;
}



















































