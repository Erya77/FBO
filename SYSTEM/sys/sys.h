#ifndef __SYS_H
#define __SYS_H	
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/8/18
//版本：V1.7
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	 

//0,不支持ucos
//1,支持ucos
#define SYSTEM_SUPPORT_UCOS		0		//定义系统文件夹是否支持UCOS
																	    
	 
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

////led defines
//#define LED_1V8  PBout(12)//DC
//#define LED_2V5  PBout(13)//SCL
//#define LED_3V3  PBout(14)//SDA
//#define LED_PDM  PBout(10)//CS
//#define LED_IIS  PBout(11)//RES
//													//BLK A3

///********************************通道1前置输出************************************/

//#define AU1_N10DB_GAIN PEout(12)      //通道1前置一输出
//#define AU1_Z0DB_GAIN  PEout(13)      //通道1前置二输出
//#define AU1_P10DB_GAIN PEout(14)      //通道1前置三输出

///********************************通道2前置输出************************************/

//#define AU2_N10DB_GAIN PEout(15)      //通道2前置一输出
//#define AU2_Z0DB_GAIN  PBout(11)      //通道2前置二输出
//#define AU2_P10DB_GAIN PBout(10)      //通道2前置三输出

///********************************通道3前置输出************************************/

//#define AU3_N10DB_GAIN PDout(12)      //通道3前置一输出
//#define AU3_Z0DB_GAIN  PDout(14)      //通道3前置二输出
//#define AU3_P10DB_GAIN PDout(13)      //通道3前置三输出

///********************************通道1功放输出************************************/

//#define AMP1_0DB_GAIN  PBout(1)       //通道1功放1输出
//#define AMP1_20DB_GAIN PBout(0)       //通道1功放2输出

///********************************通道2功放输出************************************/

//#define AMP2_0DB_GAIN   PCout(4)       //通道2功放1输出
//#define AMP2_20DB_GAIN  PAout(7)      //通道2功放2输出


/********************************功能按键选择************************************/
#define KEY1  PDin(2)
#define KEY2  PDin(3)
#define KEY3  PDin(4)
#define KEY4  PDin(5)
#define KEY5  PDin(6)
#define KEY6  PDin(7)

///***********************************蜂鸣器***************************************/

//#define KEY_BUZ  PDout(1)             //蜂鸣器

//sda pb7
//scl pb6
#define CLK_9M_CTL PCout(0)
#define CLK_12M_CTL PCout(1)
#define CLK_24M_CTL PCout(2)
void NVIC_Configuration(void);



#endif
