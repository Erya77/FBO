#include "tca6424a.h"
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

//u8 current_status;
//u8 new_status;
//new_status = current_status ^ 0x01;


void TCA6424_Init(void)
{
	tca6424a_1_init();
	tca6424a_2_init();	
	tca6424a_1_Write_Process(0x0c, 0x00);	//配置TCA6424A_1的port0.0-0.7为output
	tca6424a_1_Write_Process(0x0d, 0x00);	//配置TCA6424A_1的port1.0-1.7为output
	tca6424a_1_Write_Process(0x0e, 0x00);	//配置TCA6424A_1的port2.0-2.7为output
	tca6424a_2_Write_Process(0x0c, 0x00);	//配置TCA6424A_2的port0.0-0.7为output
	tca6424a_2_Write_Process(0x0d, 0x00);	//配置TCA6424A_2的port1.0-1.7为output
	tca6424a_2_Write_Process(0x0e, 0x00);	//配置TCA6424A_2的port2.0-2.7为output
	

	
	tca6424a_1_Write_Process(0x04, current_tca1_reg0);
	tca6424a_1_Write_Process(0x05, current_tca1_reg1);
	tca6424a_1_Write_Process(0x06, current_tca1_reg2);	
	tca6424a_2_Write_Process(0x04, current_tca2_reg0);
	tca6424a_2_Write_Process(0x05, current_tca2_reg1);
	tca6424a_2_Write_Process(0x06, current_tca2_reg2);	
}


void tca6424a_1_init(void)//PC8 SDA  PC9  SCL 
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );	//使能GPIOB时钟
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_8|GPIO_Pin_9); 	//PB6,PB7 输出高
	
}


int tca6424a_1_Cmd(u8 cmd)
{
	IIC2_Start();
	IIC2_Send_Byte(0x44);	//地址:0x20
	if(IIC2_Wait_Ack())
		return 1;
	//delay_ms(2);
	IIC2_Send_Byte(cmd); 
	if(IIC2_Wait_Ack())
		return 2;
	return 0;
}

int tca6424a_1_Read(u8 *buf)
{
	IIC2_Start();
	IIC2_Send_Byte(0x45); //地址
	if(IIC2_Wait_Ack())
		return -1;
	*buf=IIC2_Read_Byte(0);
	IIC2_Stop();
	return 0;
	
}


int tca6424a_1_Write_Process(u8 cmd, u8 data)
{
//	u8 temp=0;
//	temp=tca6424a_1_Cmd(cmd);
//	if(temp)
//		printf("write cmd:%d\r\n",temp);
//	IIC2_Send_Byte(data);
//	if(IIC2_Wait_Ack())
//		printf("write error\r\n");
//	IIC2_Stop();
		IIC2_Start();
	IIC2_Send_Byte(0x44);	//地址:0x20
	IIC2_Wait_Ack();
		IIC2_Send_Byte(cmd);	//地址:0x20
	IIC2_Wait_Ack();
		IIC2_Send_Byte(data);	//地址:0x20
	IIC2_Wait_Ack();

	IIC2_Stop();
	return 0;
}

int tca6424a_1_Read_Process(u8 cmd)
{
	u8 temp=0;
	temp=tca6424a_1_Cmd(cmd);
	if(temp)
		printf("write cmd:%d\r\n",temp);
	delay_ms(10);
	temp=tca6424a_1_Read(0x00);		//！！！
	if(temp)
		printf("read:%d\r\n",temp);
	return 0;
}

void tca6424a_2_init(void)//PE3 SDA  PE4  SCL 
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOE, ENABLE );	//使能GPIOB时钟
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE,GPIO_Pin_3|GPIO_Pin_4); 	//PB6,PB7 输出高
}

int tca6424a_2_Cmd(u8 cmd)
{
	IIC3_Start();
	IIC3_Send_Byte(0x44);	//地址:0x20
	if(IIC3_Wait_Ack())
		return 1;
	//delay_ms(2);
	IIC3_Send_Byte(cmd); 
	if(IIC3_Wait_Ack())
		return 2;
	return 0;
}

int tca6424a_2_Read(u8 *buf)
{
	IIC3_Start();
	IIC3_Send_Byte(0x45); //地址
	if(IIC3_Wait_Ack())
		return -1;
	*buf=IIC3_Read_Byte(0);
	IIC3_Stop();
	return 0;
	
}


int tca6424a_2_Write_Process(u8 cmd, u8 data)
{
//	u8 temp=0;
//	temp=tca6424a_1_Cmd(cmd);
//	if(temp)
//		printf("write cmd:%d\r\n",temp);
//	IIC3_Send_Byte(data);
//	if(IIC3_Wait_Ack())
//		printf("write error\r\n");
//	IIC3_Stop();
//	return 0;
			IIC3_Start();
	IIC3_Send_Byte(0x44);	//地址:0x20
	IIC3_Wait_Ack();
		IIC3_Send_Byte(cmd);	//地址:0x20
	IIC3_Wait_Ack();
		IIC3_Send_Byte(data);	//地址:0x20
	IIC3_Wait_Ack();

	IIC3_Stop();
	return 0;
}

int tca6424a_2_Read_Process(u8 cmd)
{
	u8 temp=0;
	temp=tca6424a_2_Cmd(cmd);
	if(temp)
		printf("write cmd:%d\r\n",temp);
	delay_ms(10);
	temp=tca6424a_2_Read(0x00);		//！！！
	if(temp)
		printf("read:%d\r\n",temp);
	return 0;
}

uint8_t tca6424a_1_read(uint8_t reg)
{
    uint8_t temp = 0;
    IIC2_Start();
    IIC2_Send_Byte(0x44);
    IIC2_Wait_Ack();
    IIC2_Send_Byte(reg);
    IIC2_Wait_Ack();
    IIC2_Start();
    IIC2_Send_Byte(0x45);
    IIC2_Wait_Ack();
    temp = IIC2_Read_Byte(0);
    // IIC_NAck();//发送nACK
    IIC2_Stop();
    return temp;
}

uint8_t tca6424a_2_read(uint8_t reg)
{
    uint8_t temp = 0;
    IIC3_Start();
    IIC3_Send_Byte(0x44);
    IIC3_Wait_Ack();
    IIC3_Send_Byte(reg);
    IIC3_Wait_Ack();
    IIC3_Start();
    IIC3_Send_Byte(0x45);
    IIC3_Wait_Ack();
    temp = IIC3_Read_Byte(0);
    // IIC_NAck();//发送nACK
    IIC3_Stop();
    return temp;
}

//void TCA6424_Port_val(u8 port,u8 pin,u8 state)//port：端口号，pin：每个端口的0~7，state：1拉高，0拉低
//{
//	static u8 tca6462_port1_val;
//	static u8 tca6462_port2_val;
//	static u8 tca6462_port3_val;
//	switch(port)
//	{
//		case 0:
//		{
//			if(state)
//			{
//				tca6462_port1_val=tca6462_port1_val|(0x01<<pin);
//			}else                                
//			{                                    
//				tca6462_port1_val=tca6462_port1_val|(0xFE<<pin);
//			}
//			//sand0x04
//		}			break;
//			 case 1:
//     {
//			 if(state)
//			{
//				tca6462_port2_val=tca6462_port1_val|(0x01<<pin);
//			}else                                
//			{                                    
//				tca6462_port2_val=tca6462_port1_val|(0xFE<<pin);
//			}
//			//sand0x05
//		 } break;
//		 case 2: 
//					{
//			 if(state)
//			{
//				tca6462_port3_val=tca6462_port1_val|(0x01<<pin);
//			}else
//			{
//				tca6462_port3_val=tca6462_port1_val|(0xFE<<pin);
//			}
//			//sand0x06
//		 }break;
//	}
//}
