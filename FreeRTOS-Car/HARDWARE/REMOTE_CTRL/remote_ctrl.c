#include "remote_ctrl.h"
#include "usart2.h"
#include "motor.h"

u8 front_flag=0;      //ǰ������
u8 back_flag=0;       //��������
u8 turn_left_flag=0;  //��ת����
u8 turn_right_flag=0; //��ת����
u8 stop_flag=0;       //ֹͣ����
u8 voice_flag=0;      //��Ƶ��������
int turnmentleft=0;
int turnmentright=0;

//*******���ݷ���*************************************
void MSG_Analyze_BT(void)
{

	//******ͣ��**********
	if(WF_Data1==0x01)
	{
		WF_Data1=0;
		stop_flag=1;	
		//USART3_Count=0;
	}
	//******ǰ��*********
	if(WF_Data1==0x02)
	{
		WF_Data1=0;
		front_flag=1;
		
		//USART3_Count=0;
	}
	//******����*******
	if(WF_Data1==0x03)
	{
		WF_Data1=0;
		back_flag=1;
		//USART3_Count=0;
	}
	//******��ת*********
	if(WF_Data1==0x04)
	{
		WF_Data1=0;
		turn_left_flag=1;
		//USART3_Count=0;
	}
	//*****��ת********
	if(WF_Data1==0x05)
	{
		WF_Data1=0;
		turn_right_flag=1;
		//USART3_Count=0;
	}

}
//*********UI����*********************************
void UI(void)
{
	 MSG_Analyze_BT();			//���ݽ���
  //*****ͣ��************
	if(stop_flag==1)
	{
	  stop_flag=0;
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		turnment=0;
    zhuan_Kp=0;   //����С��ת��������
    zhuan_Kd=0;
		Car_zero_offset=0;
		return;
	}
  //****ǰ��************
	if(front_flag==1)
	{
	  front_flag=0;
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		Car_zero_offset=Car_zero_offset+1.6;
		turnment=0;
    zhuan_Kp=1;   //����С��ת��������
    zhuan_Kd=0;
		return;
	}
  //****����**********
	if(back_flag==1)
	{
	  back_flag=0;
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		Car_zero_offset=Car_zero_offset-1.67;;
		turnment=0;

    zhuan_Kp=1;   //����С��ת��������
    zhuan_Kd=0;
		return;
	}
  //****��ת*********
	if(turn_left_flag==1)
	{
	  turn_left_flag=0;
    turnment=turnmentleft-400;
		zhuan_Kp=1;
		zhuan_Kd=0;
		return;
	}
  //***��ת*********
	if(turn_right_flag==1)
	{
	  turn_right_flag=0;
   turnment=turnmentright+400;
		zhuan_Kp=1;
		zhuan_Kd=0;
		return;
	}

}
	

	


