#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h"
#include "main.h"

#define USART_REC_LEN  		20 	//�����������ֽ��� 20
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

#define USART_Need_Line   0
#define COM_NUM 50//���ܱ�ʵ������������
extern unsigned char comd_flag;

uint8_t cmh_strcmp(uint8_t *str1,uint8_t *str2,uint8_t number);
void cmh_memcpyn(uint8_t *buffer1, uint8_t *buffer2,uint8_t number);
void USART_CMD(void);

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
extern u16 USART_RX_CNT;				//���յ��ֽ���	
//����봮���жϽ��գ��벻Ҫע�����º궨��

void uart4_init(u32 bound);
void PC_CMD_CTL(void);
void PC_CMD_PRO(void);
void uart4_send_str(char* pbuf);
void Get_state(void);
#endif


