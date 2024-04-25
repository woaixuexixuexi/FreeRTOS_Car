 
#include "stm32f10x.h"
#include "key.h"
#include "delay.h"
unsigned int k;						    
void KEY_Init(void)  //��ʼ��
{
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA,ENABLE);//ʱ��ʹ�� 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9;//KEY0,KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������ģʽ(��������ʱ ɨ����Ǹߵ�ƽ)
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
	

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//KEY0,KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//��������ģʽ(��������ʱ ɨ����Ǹߵ�ƽ)
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
 
}
//u8 c=0;
//����ɨ�躯��,������ģʽ(1.֧��������(��ס�������ɿ�) 2.��֧��������)
u8 KEY_Scan(u8 mode)//mode ģʽѡ��:1Ϊ֧�������� 0Ϊ��֧��������
{	
	static u8 key_up=1;
	if(mode)key_up=1;	  
	if(key_up&&(KEY1==0|| KEY2==0||WK_UP==1))
	{
		key_up=0;
		delay_xms(10);//��ʱ��������
		if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(WK_UP==1)
	
		return WKUP_PRES;

	}else if(WK_UP==0&&KEY1==1&&KEY2==1)key_up=1; 	    
 	return 0;
}

void key_sta_chage(void)
{
  if(KEY1==0)
	{
		delay_xms(5);
		if(KEY1==0)
		{
			k++;
			delay_xms(5);
			if(k>2)
			k=1;
		}
	}
}

