#include "esp8266.h"
#include "string.h"
#include "usart.h"
#include "usart2.h"
#include "delay.h"

char a[]="AT+CWMODE=1";
char b[]="AT+RST";
char c[]="AT+CWJAP=\"lfh\",\"81009738\"";                
char d[]="AT+CIPMUX=1";
char e[]="AT+CIPSTART=0,\"TCP\",\"115.29.109.104\",6552";
char f[]="AT+CWLAP";

void esp8266_start_trans(void)
{
		//重启
	esp8266_send_cmd1((u8 *)b);
  delay_xms(1000);
	delay_xms(1000);
	delay_xms(1000);
	delay_xms(1000);


	//设置工作模式 1：station模式   2：AP模式  3：兼容 AP+station模式
	esp8266_send_cmd1((u8 *)a);
	delay_xms(1000);
	delay_xms(1000);
	
	//重启
	esp8266_send_cmd1((u8 *)b);
  delay_xms(1000);
	delay_xms(1000);
	delay_xms(1000);
	delay_xms(1000);

	//连接WIFI
	esp8266_send_cmd1((u8 *)c);
  delay_xms(1000);
	delay_xms(1000);
	delay_xms(1000);
	delay_xms(1000);
	delay_xms(1000);
	delay_xms(1000);
	delay_xms(1000);
	delay_xms(1000);

	
	esp8266_send_cmd1((u8 *)d);
  delay_xms(1000);
	delay_xms(1000);

	esp8266_send_cmd1((u8 *)e);
  delay_xms(1000);
	delay_xms(1000);

}

void esp8266_send_cmd1(u8 *cmd)
{
  u2_printf("%s\r\n",cmd);	//发送命令，需要加换行符

}
 

