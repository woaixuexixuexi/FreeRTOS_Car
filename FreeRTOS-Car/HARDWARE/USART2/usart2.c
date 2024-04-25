#include "delay.h"
#include "usart2.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"
#include "usart.h"
#include "lcd.h"
#include "my_task.h"

// 串口接收缓存区
u8 USART2_RX_BUF[USART2_MAX_RECV_LEN]; // 接收缓冲,最大USART3_MAX_RECV_LEN个字节.
u8 USART2_TX_BUF[USART2_MAX_SEND_LEN]; // 发送缓冲,最大USART3_MAX_SEND_LEN字节

// 接收到的数据状态
//[15]:0,没有接收到数据;1,接收到了一批数据.
//[14:0]:接收到的数据长度
vu16 USART2_RX_STA = 0;
u8 i=0;
u8 WF_Data1=0;
// 串口3接收中断服务函数
void USART2_IRQHandler(void)
{
    u8 res;
    
		BaseType_t xHigherPriorityTaskWoken;
	  xHigherPriorityTaskWoken = pdFALSE;
	  //printf("串口2头");
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) // 接收到数据
    {
        res = USART_ReceiveData(USART2);
		
        USART_SendData(DEBUG_USARTx, res); // 这里是把ESP8266发送到串口3的消息发送到电脑端串口调试助手，便于调试

        if (res != 'A') // 以‘A’为结束位，收到‘A’表示一次接收消息完成
        {
            if ((USART2_RX_STA & (1 << 15)) == 0) // 接收完的一批数据,还没有被处理,则不再接收其他数据
            {
                USART2_RX_BUF[USART2_RX_STA++] = res; // 记录接收到的值
            }
            else
            {
                USART2_RX_STA |= 1 << 15; // 没有收到结束符‘A’，收到的字节数>=0x80,强制标记接收完成
            }
        }
        else
        {

            USART2_RX_STA |= 1 << 15; // 接收消息完成
        }
	
				//printf("串口中断");
			
			if(BinarySemaphore!=NULL){
				
				i++;
					//printf("信号量不为0");
				if(i==2){
				xSemaphoreGiveFromISR( BinarySemaphore, &xHigherPriorityTaskWoken );
		 /* 根据xHigherPriorityTaskWoken 判断是否需要执行调度 */
				 portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
					//printf("释放信号量");
				i=0;}
			
			}
//			


    }
	}

	
	void USART2_WIFI_CTRL(void)
	{
	
	       if (USART2_RX_STA & 0x8000) // 如果消息接收完成，则处理
        {
            if (strstr((const char *)USART2_RX_BUF, "stop"))
						{							// 这里是看接收到的消息中有没有自己设置的命令“on”，strstr()函数不会用的可以搜一下

                GPIO_ResetBits(GPIOA, GPIO_Pin_8);
                WF_Data1=0x01;

            }
            if (strstr((const char *)USART2_RX_BUF, "go"))
            {

                GPIO_SetBits(GPIOA, GPIO_Pin_8);
                 WF_Data1=0x02;
            }
            if (strstr((const char *)USART2_RX_BUF, "back"))
            {

                GPIO_SetBits(GPIOA, GPIO_Pin_8);
                 WF_Data1=0x03;
            }			

            if (strstr((const char *)USART2_RX_BUF, "left"))
            {

                 WF_Data1=0x04;
            }			
            if (strstr((const char *)USART2_RX_BUF, "right"))
            {

                 WF_Data1=0x05;
            }			




						

            USART2_RX_STA = 0;             // 消息处理完成，开始重新接收
            memset(USART2_RX_BUF, 0, 600); // 将接收区清0

        }
	
	
	
	}		
	
	
	
// 初始化IO 串口3
// pclk1:PCLK1时钟频率(Mhz)
// bound:波特率
void usart2_init(u32 bound)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // GPIOB时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); // 串口3时钟使能

    USART_DeInit(USART2); // 复位串口3
                          // USART3_TX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // PA2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);          // 初始化PB10

    // USART3_RX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);                // 初始化PB11

    USART_InitStructure.USART_BaudRate = bound;                                     // 波特率一般设置为9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     // 字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          // 一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             // 无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 // 收发模式

    USART_Init(USART2, &USART_InitStructure); // 初始化串口	3

    USART_Cmd(USART2, ENABLE); // 使能串口

    // 使能接收中断
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // 开启中断

    // 设置中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5; // 抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        // 子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                           // 根据指定的参数初始化VIC寄存器

    USART2_RX_STA = 0; // 清零
}

// 串口3,printf 函数
// 确保一次发送数据不超过USART3_MAX_SEND_LEN字节
void u2_printf(char *fmt, ...)
{
    u16 i, j;
    va_list ap;
    va_start(ap, fmt);
    vsprintf((char *)USART2_TX_BUF, fmt, ap);
    va_end(ap);
    i = strlen((const char *)USART2_TX_BUF); // 此次发送数据的长度
    for (j = 0; j < i; j++)                  // 循环发送数据
    {
        while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
            ; // 循环发送,直到发送完毕
        USART_SendData(USART2, USART2_TX_BUF[j]);
    }
}
