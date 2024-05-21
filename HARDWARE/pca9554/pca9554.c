#include "myiic.h"
#include "delay.h"
#include "usart.h"
#include "pca9554.h"

/*
地址:0x20
寄存器地址(cmd)：	0x00	Input Port Register
					0x01	Output Port Register
					0x02	Polarity Inversion Register
					0x03	Configuration Register

*/

u8 IIC_BUF[4]={0};

int pca9554_Cmd(u8 cmd)
{
	IIC_Start();
	IIC_Send_Byte(0x40);	//地址:0x20
	if(IIC_Wait_Ack())
		return 1;
	//delay_ms(2);
	IIC_Send_Byte(cmd); 
	if(IIC_Wait_Ack())
		return 2;
	return 0;
}

int pca9554_Read(u8 *buf)
{
	IIC_Start();
	IIC_Send_Byte(0x41); //地址
	if(IIC_Wait_Ack())
		return -1;
	*buf=IIC_Read_Byte(0);
	IIC_Stop();
	return 0;
	
}


int pca9554_Write_Process(u8 cmd, u8 data)
{
	u8 temp=0;
	temp=pca9554_Cmd(cmd);
	if(temp)
		printf("write cmd:%d\r\n",temp);
	IIC_Send_Byte(data);
	if(IIC_Wait_Ack())
		printf("write error\r\n");
	IIC_Stop();
	return 0;
}

int pca9554_Read_Process(u8 cmd)
{
	u8 temp=0;
	temp=pca9554_Cmd(cmd);
	if(temp)
		printf("write cmd:%d\r\n",temp);
	delay_ms(10);
	temp=pca9554_Read(IIC_BUF);
	if(temp)
		printf("read:%d\r\n",temp);
	return 0;
}


void pca9554_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7); 	//PB6,PB7 输出高
}





