#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 

//IO方向设置
//#define SDA_IN()  	IIC_SDA_in()
//#define SDA_OUT() 	IIC_SDA_out()


//IIC  PCA9554     IIC  ---------------------------------------------------------
//IO操作函数	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define IIC_READ_SDA   PBin(7)  //输入SDA 

//IIC  PCA9554  所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8   IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8   IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号
void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8   IIC_Read_One_Byte(u8 daddr,u8 addr);	  

//IIC2  TCA6424A-1   IIC  ---------------------------------------------------------

//IO操作函数	 
#define IIC2_SCL    PCout(9) //SCL
#define IIC2_SDA    PCout(8) //SDA	 
#define IIC2_READ_SDA   PCin(8)  //输入SDA 

//IIC2  PCA9554  所有操作函数
void IIC2_Init(void);                //初始化IIC2的IO口				 
void IIC2_Start(void);				//发送IIC2开始信号
void IIC2_Stop(void);	  			//发送IIC2停止信号
void IIC2_Send_Byte(u8 txd);			//IIC2发送一个字节
u8   IIC2_Read_Byte(unsigned char ack);//IIC2读取一个字节
u8   IIC2_Wait_Ack(void); 				//IIC2等待ACK信号
void IIC2_Ack(void);					//IIC2发送ACK信号
void IIC2_NAck(void);				//IIC2不发送ACK信号
void IIC2_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8   IIC2_Read_One_Byte(u8 daddr,u8 addr);	

//IIC3  TCA6424A-2   IIC  ---------------------------------------------------------

//IO操作函数	 
#define IIC3_SCL    PEout(4) //SCL
#define IIC3_SDA    PEout(3) //SDA	 
#define IIC3_READ_SDA   PEin(3)  //输入SDA 

//IIC3  PCA9554  所有操作函数
void IIC3_Init(void);                //初始化IIC3的IO口				 
void IIC3_Start(void);				//发送IIC3开始信号
void IIC3_Stop(void);	  			//发送IIC3停止信号
void IIC3_Send_Byte(u8 txd);			//IIC3发送一个字节
u8   IIC3_Read_Byte(unsigned char ack);//IIC3读取一个字节
u8   IIC3_Wait_Ack(void); 				//IIC3等待ACK信号
void IIC3_Ack(void);					//IIC3发送ACK信号
void IIC3_NAck(void);				//IIC3不发送ACK信号
void IIC3_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8   IIC3_Read_One_Byte(u8 daddr,u8 addr);	


//IIC4  XM_ADC   IIC  ---------------------------------------------------------

//IO操作函数	 
#define IIC4_SCL    PBout(6) //SCL
#define IIC4_SDA    PBout(7) //SDA	 
#define IIC4_READ_SDA   PBin(7)  //输入SDA 

//IIC4  PCA9554  所有操作函数
void IIC4_Init(void);                //初始化IIC4的IO口				 
void IIC4_Start(void);				//发送IIC4开始信号
void IIC4_Stop(void);	  			//发送IIC4停止信号
void IIC4_Send_Byte(u8 txd);			//IIC4发送一个字节
u8   IIC4_Read_Byte(unsigned char ack);//IIC4读取一个字节
u8   IIC4_Wait_Ack(void); 				//IIC4等待ACK信号
void IIC4_Ack(void);					//IIC4发送ACK信号
void IIC4_NAck(void);				//IIC4不发送ACK信号
void IIC4_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8   IIC4_Read_One_Byte(u8 daddr,u8 addr);	

#endif



