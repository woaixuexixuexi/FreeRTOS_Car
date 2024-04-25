#ifndef __ESP8266_H
#define __ESP8266_H
#include "stdio.h"	
#include "stm32f10x.h"



//º¯Êý
void esp8266_send_cmd1(u8 *cmd);

void esp8266_start_trans(void);


#endif
