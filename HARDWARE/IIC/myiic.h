#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 

//IO��������
//#define SDA_IN()  	IIC_SDA_in()
//#define SDA_OUT() 	IIC_SDA_out()


//IIC  PCA9554     IIC  ---------------------------------------------------------
//IO��������	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define IIC_READ_SDA   PBin(7)  //����SDA 

//IIC  PCA9554  ���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8   IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8   IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�
void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8   IIC_Read_One_Byte(u8 daddr,u8 addr);	  

//IIC2  TCA6424A-1   IIC  ---------------------------------------------------------

//IO��������	 
#define IIC2_SCL    PCout(9) //SCL
#define IIC2_SDA    PCout(8) //SDA	 
#define IIC2_READ_SDA   PCin(8)  //����SDA 

//IIC2  PCA9554  ���в�������
void IIC2_Init(void);                //��ʼ��IIC2��IO��				 
void IIC2_Start(void);				//����IIC2��ʼ�ź�
void IIC2_Stop(void);	  			//����IIC2ֹͣ�ź�
void IIC2_Send_Byte(u8 txd);			//IIC2����һ���ֽ�
u8   IIC2_Read_Byte(unsigned char ack);//IIC2��ȡһ���ֽ�
u8   IIC2_Wait_Ack(void); 				//IIC2�ȴ�ACK�ź�
void IIC2_Ack(void);					//IIC2����ACK�ź�
void IIC2_NAck(void);				//IIC2������ACK�ź�
void IIC2_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8   IIC2_Read_One_Byte(u8 daddr,u8 addr);	

//IIC3  TCA6424A-2   IIC  ---------------------------------------------------------

//IO��������	 
#define IIC3_SCL    PEout(4) //SCL
#define IIC3_SDA    PEout(3) //SDA	 
#define IIC3_READ_SDA   PEin(3)  //����SDA 

//IIC3  PCA9554  ���в�������
void IIC3_Init(void);                //��ʼ��IIC3��IO��				 
void IIC3_Start(void);				//����IIC3��ʼ�ź�
void IIC3_Stop(void);	  			//����IIC3ֹͣ�ź�
void IIC3_Send_Byte(u8 txd);			//IIC3����һ���ֽ�
u8   IIC3_Read_Byte(unsigned char ack);//IIC3��ȡһ���ֽ�
u8   IIC3_Wait_Ack(void); 				//IIC3�ȴ�ACK�ź�
void IIC3_Ack(void);					//IIC3����ACK�ź�
void IIC3_NAck(void);				//IIC3������ACK�ź�
void IIC3_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8   IIC3_Read_One_Byte(u8 daddr,u8 addr);	


//IIC4  XM_ADC   IIC  ---------------------------------------------------------

//IO��������	 
#define IIC4_SCL    PBout(6) //SCL
#define IIC4_SDA    PBout(7) //SDA	 
#define IIC4_READ_SDA   PBin(7)  //����SDA 

//IIC4  PCA9554  ���в�������
void IIC4_Init(void);                //��ʼ��IIC4��IO��				 
void IIC4_Start(void);				//����IIC4��ʼ�ź�
void IIC4_Stop(void);	  			//����IIC4ֹͣ�ź�
void IIC4_Send_Byte(u8 txd);			//IIC4����һ���ֽ�
u8   IIC4_Read_Byte(unsigned char ack);//IIC4��ȡһ���ֽ�
u8   IIC4_Wait_Ack(void); 				//IIC4�ȴ�ACK�ź�
void IIC4_Ack(void);					//IIC4����ACK�ź�
void IIC4_NAck(void);				//IIC4������ACK�ź�
void IIC4_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8   IIC4_Read_One_Byte(u8 daddr,u8 addr);	

#endif



