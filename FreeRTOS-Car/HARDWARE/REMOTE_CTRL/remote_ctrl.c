#include "remote_ctrl.h"
#include "usart2.h"
#include "motor.h"

u8 front_flag=0;      //前进命令
u8 back_flag=0;       //后退命令
u8 turn_left_flag=0;  //左转命令
u8 turn_right_flag=0; //右转命令
u8 stop_flag=0;       //停止命令
u8 voice_flag=0;      //音频播放命令
int turnmentleft=0;
int turnmentright=0;

//*******数据分析*************************************
void MSG_Analyze_BT(void)
{

	//******停车**********
	if(WF_Data1==0x01)
	{
		WF_Data1=0;
		stop_flag=1;	
		//USART3_Count=0;
	}
	//******前进*********
	if(WF_Data1==0x02)
	{
		WF_Data1=0;
		front_flag=1;
		
		//USART3_Count=0;
	}
	//******后退*******
	if(WF_Data1==0x03)
	{
		WF_Data1=0;
		back_flag=1;
		//USART3_Count=0;
	}
	//******左转*********
	if(WF_Data1==0x04)
	{
		WF_Data1=0;
		turn_left_flag=1;
		//USART3_Count=0;
	}
	//*****右转********
	if(WF_Data1==0x05)
	{
		WF_Data1=0;
		turn_right_flag=1;
		//USART3_Count=0;
	}

}
//*********UI交互*********************************
void UI(void)
{
	 MSG_Analyze_BT();			//数据解码
  //*****停车************
	if(stop_flag==1)
	{
	  stop_flag=0;
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		turnment=0;
    zhuan_Kp=0;   //期望小车转向，正反馈
    zhuan_Kd=0;
		Car_zero_offset=0;
		return;
	}
  //****前进************
	if(front_flag==1)
	{
	  front_flag=0;
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		Car_zero_offset=Car_zero_offset+1.6;
		turnment=0;
    zhuan_Kp=1;   //期望小车转向，正反馈
    zhuan_Kd=0;
		return;
	}
  //****后退**********
	if(back_flag==1)
	{
	  back_flag=0;
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		Car_zero_offset=Car_zero_offset-1.67;;
		turnment=0;

    zhuan_Kp=1;   //期望小车转向，正反馈
    zhuan_Kd=0;
		return;
	}
  //****左转*********
	if(turn_left_flag==1)
	{
	  turn_left_flag=0;
    turnment=turnmentleft-400;
		zhuan_Kp=1;
		zhuan_Kd=0;
		return;
	}
  //***右转*********
	if(turn_right_flag==1)
	{
	  turn_right_flag=0;
   turnment=turnmentright+400;
		zhuan_Kp=1;
		zhuan_Kd=0;
		return;
	}

}
	

	


