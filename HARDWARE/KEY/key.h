#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
								  
//////////////////////////////////////////////////////////////////////////////////   	 

	 
 

///********************************���ܰ���ѡ��************************************/

//#define KEY1           GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)        //����***
//#define KEY2           GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)        //����***
//#define KEY3           GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)        //����***
//#define KEY4           GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)        //����***
//#define KEY5           GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)        //����***
//#define KEY6           GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)        //����***
 

#define KEY1_PRES	1		//KEY1  
#define KEY2_PRES	2		//KEY2
#define KEY3_PRES	3		//KEY3  
#define KEY4_PRES	4		//KEY4 
#define KEY5_PRES	5		//KEY5  
#define KEY6_PRES	6		//KEY6

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8 mode);  	//����ɨ�躯��					    
#endif
