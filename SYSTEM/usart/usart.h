#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h"
#include "main.h"

#define USART_REC_LEN  		20 	//定义最大接收字节数 20
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

#define USART_Need_Line   0
#define COM_NUM 50//不能比实际命令数量大
extern unsigned char comd_flag;

uint8_t cmh_strcmp(uint8_t *str1,uint8_t *str2,uint8_t number);
void cmh_memcpyn(uint8_t *buffer1, uint8_t *buffer2,uint8_t number);
void USART_CMD(void);

extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
extern u16 USART_RX_CNT;				//接收的字节数	
//如果想串口中断接收，请不要注释以下宏定义

void uart4_init(u32 bound);
void PC_CMD_CTL(void);
void PC_CMD_PRO(void);
void uart4_send_str(char* pbuf);
void Get_state(void);
#endif


