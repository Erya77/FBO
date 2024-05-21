
/*
  ******************************************************************************
	* @file      deploy.c
	* @company   FBO
	* @project   P632
  * @author    zhirui fan
  * @version   V0.0
  * @date      2019-9-15
  * @brief     Computer test coordination control
  ******************************************************************************
*/

//#include "main.h"
#include "deploy.h"

u16 current_tca1_reg0;
u16 current_tca1_reg1;
u16 current_tca1_reg2;
u16 current_tca2_reg0;
u16 current_tca2_reg1;
u16 current_tca2_reg2;


void Deploy_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);
	
	//A
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	              //前置1-4 bias输出24V
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 
	GPIO_ResetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	            
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;	              //前置1-5 MIC检测
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 			
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 	
	
	
	//B
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_10;	              //PB10  AU4_0DB_GAIN；PB0  ISEN2_IN_EN
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 
	GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_10);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	            //IO2_SCL,IO2_INIT
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_11;	              //前置6 MIC检测
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 			
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	
	//C
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	              //IO_SCL,IO_INIT
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 
	GPIO_SetBits(GPIOC,GPIO_Pin_6|GPIO_Pin_7);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;	          		  //前置5，6 bias输出24V
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 
	GPIO_ResetBits(GPIOC,GPIO_Pin_4|GPIO_Pin_5);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	              //前置6 MIC检测
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 			
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	
	//D	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;	     //前置1-6 输入保护继电器控制
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 
	GPIO_ResetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	  //前置5，6  bias输出2V
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	GPIO_ResetBits(GPIOD,GPIO_Pin_0|GPIO_Pin_1);	
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	     		//PD12   PORT_AMP1_OUT
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	     		//PD15   PORT_AMP2_OUT
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	
	//E
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	            //PE6   ISEN1_IN_EN
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOE, &GPIO_InitStructure);					 
	GPIO_ResetBits(GPIOE,GPIO_Pin_6);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_5;	            //IO2_SCL,IO2_INIT
	GPIO_Init(GPIOE, &GPIO_InitStructure);					 
	GPIO_SetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_5);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;	            //前置5，6 bias输出2.7V
	GPIO_Init(GPIOE, &GPIO_InitStructure);					 
	GPIO_ResetBits(GPIOE,GPIO_Pin_9|GPIO_Pin_10);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	  //前置5，6，1-3增益
	GPIO_Init(GPIOE, &GPIO_InitStructure);					 
	GPIO_SetBits(GPIOE,GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

}




void TCA6424_Port(u8 reg,u8 port,u8 tca,u8 state)
{
	u16 temp=0;
	
	if(tca==1)
	temp = tca6424a_1_read(reg);//读寄存器状态
	else if(tca==2)
	temp = tca6424a_2_read(reg);
	
	if(state==1)		
	temp |= (1 << port);//置位对应脚
	else
	temp &= ~(1 << port);//复位对应脚
	
	if(tca==1)
	tca6424a_1_Write_Process(reg, temp);
	else if(tca==2)
	tca6424a_2_Write_Process(reg, temp);
	
	
	switch(reg)//存储当前寄存器状态	
	{
			 case Output_Port0:
		{
			if(tca==1)
			{current_tca1_reg0 = temp;}//STMFLASH_Write(TCA1_REG0_ADDR,&temp,1);STMFLASH_Read(TCA1_REG0_ADDR,&current_tca1_reg0,1);}
			else if(tca==2)
			{current_tca2_reg0 = temp;}//STMFLASH_Write(TCA2_REG0_ADDR,&temp,1);STMFLASH_Read(TCA2_REG0_ADDR,&current_tca2_reg0,1);}
		}break;
		
				case Output_Port1:
		{
			if(tca==1)
			{current_tca1_reg1 = temp;}//STMFLASH_Write(TCA1_REG1_ADDR,&temp,1);STMFLASH_Read(TCA1_REG1_ADDR,&current_tca1_reg1,1);}
			else if(tca==2)
			{current_tca2_reg1 = temp;}//STMFLASH_Write(TCA2_REG1_ADDR,&temp,1);STMFLASH_Read(TCA2_REG1_ADDR,&current_tca2_reg1,1);}
		}break;
		
				case Output_Port2:
		{
			if(tca==1)
			{current_tca1_reg2 = temp;}//STMFLASH_Write(TCA1_REG2_ADDR,&temp,1);STMFLASH_Read(TCA1_REG2_ADDR,&current_tca1_reg2,1);}
			else if(tca==2)
			{current_tca2_reg2 = temp;}//STMFLASH_Write(TCA2_REG2_ADDR,&temp,1);STMFLASH_Read(TCA2_REG2_ADDR,&current_tca2_reg2,1);}
		}break;
	}
	
}


void MICX_PRT_ON(struct _AU *au)
{
		if (au == &AU1)
				MIC1_PRT_ON; 
		else if (au == &AU2)
				MIC2_PRT_ON;
		else if (au == &AU3)
				MIC3_PRT_ON;
		else if (au == &AU4)
				MIC4_PRT_ON;
		else if (au == &AU5)
				MIC5_PRT_ON;
		else if (au == &AU6)
				MIC6_PRT_ON;	
}
void MICX_PRT_OFF(struct _AU *au)
{
		if (au == &AU1)
				MIC1_PRT_OFF; 
		else if (au == &AU2)
				MIC2_PRT_OFF;
		else if (au == &AU3)
				MIC3_PRT_OFF;
		else if (au == &AU4)
				MIC4_PRT_OFF;
		else if (au == &AU5)
				MIC5_PRT_OFF;
		else if (au == &AU6)
				MIC6_PRT_OFF;	
}
void AUX_0DB_GAIN(struct _AU *au)
{
		if (au == &AU1)
				AU1_0DB_GAIN ;
		else if (au == &AU2)
				AU2_0DB_GAIN ;
		else if (au == &AU3)
				AU3_0DB_GAIN ;
		else if (au == &AU4)
				AU4_0DB_GAIN ;
		else if (au == &AU5)
				AU5_0DB_GAIN ;
		else if (au == &AU6)
				AU6_0DB_GAIN ;
}
void AUX_20DB_GAIN(struct _AU *au)
{
			if (au == &AU1)
				AU1_20DB_GAIN ;
		else if (au == &AU2)
				AU2_20DB_GAIN ;
		else if (au == &AU3)
				AU3_20DB_GAIN ;
		else if (au == &AU4)
				AU4_20DB_GAIN ;
		else if (au == &AU5)
				AU5_20DB_GAIN ;
		else if (au == &AU6)
				AU6_20DB_GAIN ;
}
void MICX_CON_ON(struct _AU *au)
{
			if (au == &AU1)
				MIC1_CON_ON;
		else if (au == &AU2)
				MIC2_CON_ON;
		else if (au == &AU3)
				MIC3_CON_ON;
		else if (au == &AU4)
				MIC4_CON_ON;
		else if (au == &AU5)
				MIC5_CON_ON;
		else if (au == &AU6)
				MIC6_CON_ON;
}
void MICX_CON_OFF(struct _AU *au)
{
			if (au == &AU1)
				MIC1_CON_OFF;
		else if (au == &AU2)
				MIC2_CON_OFF;
		else if (au == &AU3)
				MIC3_CON_OFF;
		else if (au == &AU4)
				MIC4_CON_OFF;
		else if (au == &AU5)
				MIC5_CON_OFF;
		else if (au == &AU6)
				MIC6_CON_OFF;
}
void ISENX_IN_ON(struct _AU *au)
{
			if(au == &AU5)
		ISEN1_IN_EN=1;
			else if(au == &AU6)
		ISEN2_IN_EN=1;
}
void ISENX_IN_OFF(struct _AU *au)
{
				if(au == &AU5)
		ISEN1_IN_EN=0;
			else if(au == &AU6)
		ISEN2_IN_EN=0;
}
void AUX_2V7_ON(struct _AU *au)
{
	if (au == &AU1)
	{
			AU1_2V0_OFF;
			AU1_2V7_ON;
			AU1_ICP_OFF;}
	else if (au == &AU2)
	{
			AU2_2V0_OFF;
			AU2_2V7_ON;
			AU2_ICP_OFF;}
	else if (au == &AU3)
	{
			AU3_2V0_OFF;
			AU3_2V7_ON;
			AU3_ICP_OFF;}
	else if (au == &AU4)
	{
			AU4_2V0_OFF;
			AU4_2V7_ON;
			AU4_ICP_OFF;}
	else if (au == &AU5)
	{
			AU5_2V0_OFF;
			AU5_2V7_ON;
			AU5_ICP_OFF;}
	else if (au == &AU6)
	{
			AU6_2V0_OFF;
			AU6_2V7_ON;
			AU6_ICP_OFF;}
	
}
void AUX_2V0_ON(struct _AU *au)
{
	if (au == &AU1)
	{
			AU1_2V0_ON;
			AU1_2V7_OFF;
			AU1_ICP_OFF;}
	else if (au == &AU2)
	{
			AU2_2V0_ON;
			AU2_2V7_OFF;
			AU2_ICP_OFF;}
	else if (au == &AU3)
	{
			AU3_2V0_ON;
			AU3_2V7_OFF;
			AU3_ICP_OFF;}
	else if (au == &AU4)
	{
			AU4_2V0_ON;
			AU4_2V7_OFF;
			AU4_ICP_OFF;}
	else if (au == &AU5)
	{
			AU5_2V0_ON;
			AU5_2V7_OFF;
			AU5_ICP_OFF;}
	else if (au == &AU6)
	{
			AU6_2V0_ON;
			AU6_2V7_OFF;
			AU6_ICP_OFF;}
	
}
void AUX_ICP_ON(struct _AU *au)
{
			if (au == &AU1)
	{
			AU1_2V0_OFF;
			AU1_2V7_OFF;
			AU1_ICP_ON;}
	else if (au == &AU2)
	{
			AU2_2V0_OFF;
			AU2_2V7_OFF;
			AU2_ICP_ON;}
	else if (au == &AU3)
	{
			AU3_2V0_OFF;
			AU3_2V7_OFF;
			AU3_ICP_ON;}
	else if (au == &AU4)
	{
			AU4_2V0_OFF;
			AU4_2V7_OFF;
			AU4_ICP_ON;}
	else if (au == &AU5)
	{
			AU5_2V0_OFF;
			AU5_2V7_OFF;
			AU5_ICP_ON;}
	else if (au == &AU6)
	{
			AU6_2V0_OFF;
			AU6_2V7_OFF;
			AU6_ICP_ON;}
	
}
void AUX_NONE_ON(struct _AU *au)
{
		if (au == &AU1)
	{
			AU1_2V0_OFF;
			AU1_2V7_OFF;
			AU1_ICP_OFF;}
	else if (au == &AU2)
	{
			AU2_2V0_OFF;
			AU2_2V7_OFF;
			AU2_ICP_OFF;}
	else if (au == &AU3)
	{
			AU3_2V0_OFF;
			AU3_2V7_OFF;
			AU3_ICP_OFF;}
	else if (au == &AU4)
	{
			AU4_2V0_OFF;
			AU4_2V7_OFF;
			AU4_ICP_OFF;}
	else if (au == &AU5)
	{
			AU5_2V0_OFF;
			AU5_2V7_OFF;
			AU5_ICP_OFF;}
	else if (au == &AU6)
	{
			AU6_2V0_OFF;
			AU6_2V7_OFF;
			AU6_ICP_OFF;}
	
}
void AMPX_OVER_ON(struct _AMP *amp)
{
	if(amp == &AMP1)
	AMP1_OVER_ON;
	else if(amp == &AMP2)
	AMP2_OVER_ON;
}
void AMPX_OVER_OFF(struct _AMP *amp)
{
	if(amp == &AMP1)
	AMP1_OVER_OFF;
	else if(amp == &AMP2)
	AMP2_OVER_OFF;
}
void AMPX_20DB_GAIN(struct _AMP *amp)
{
		if(amp == &AMP1)
	AMP1_20DB_GAIN;
	else if(amp == &AMP2)
	AMP2_20DB_GAIN;
	
}
void AMPX_0DB_GAIN(struct _AMP *amp)	
{
			if(amp == &AMP1)
	AMP1_0DB_GAIN;
	else if(amp == &AMP2)
	AMP2_0DB_GAIN;
}

