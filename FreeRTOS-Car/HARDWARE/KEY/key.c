 
#include "stm32f10x.h"
#include "key.h"
#include "delay.h"
unsigned int k;						    
void KEY_Init(void)  //初始化
{
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA,ENABLE);//时钟使能 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9;//KEY0,KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//输入上拉模式(不按按键时 扫描的是高电平)
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
	

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//KEY0,KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//输入上拉模式(不按按键时 扫描的是高电平)
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
 
}
//u8 c=0;
//按键扫描函数,有两种模式(1.支持连续按(按住按键不松开) 2.不支持连续按)
u8 KEY_Scan(u8 mode)//mode 模式选择:1为支持连续按 0为不支持连续按
{	
	static u8 key_up=1;
	if(mode)key_up=1;	  
	if(key_up&&(KEY1==0|| KEY2==0||WK_UP==1))
	{
		key_up=0;
		delay_xms(10);//延时函数消抖
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

