#include "xmos_adc.h"
#include "myiic.h"
#include "delay.h"
#include "usart.h"

/*
地址:ADDR:0/1   0x44/0x46
寄存器地址(cmd)：
					PORT 0/1/2
					0x00/01/02	Input Port Register
					0x04/05/06	Output Port Register
					0x08/09/0A	Polarity Inversion Register
					0x0C/0D/0E	Configuration Register
*/



void xmos_adc_init(void)//PB7 SDA  PB6  SCL 
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );	//使能GPIOB时钟
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7); 	//PB6,PB7 输出高	
}

int MCU_Write_ADC1_Process(u8 address,u8 cmd, u8 data)
{
	IIC4_Start();

	IIC4_Send_Byte(address);	//设备地址
	IIC4_Wait_Ack();	
	IIC4_Send_Byte(cmd);	//地址:0x20
	IIC4_Wait_Ack();
	IIC4_Send_Byte(data);	//地址:0x20
	IIC4_Wait_Ack();

	IIC4_Stop();
	return 0;
}
