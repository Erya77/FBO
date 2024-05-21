/**
  ******************************************************************************
  * @file    main.c
  * @author  Fan zhirui
  * @version V0.1
  * @date    2019-8-15
  * @brief   Computer test coordination control
  ******************************************************************************
  * @attention
  ******************************************************************************
  */
#include "main.h"
#include "myexti.h"
#include "delay.h"
#include "usart.h"

unsigned char Key_Up_Flag      =0;
unsigned char Key_Down_Flag    =0;
unsigned char Key_Left_Flag    =0;
unsigned char Key_Right_Flag   =0;
unsigned char Key_Confirm_Flag =0;
unsigned char Key_Menu_Flag    =0;
		
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;  
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //使能复用时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);  //使能GPIOF时钟
	
	Deploy_Init();
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource2); 
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt; 
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;  //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource3); 
	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt; 
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;  //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource4); 
	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt; 
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;  //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource5); 
	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt; 
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;  //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource6); 
	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt; 
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;  //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource7); 
	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt; 
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;  //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;   
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI3_IRQn;   
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI4_IRQn;   
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;   
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

 
void EXTI2_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line2) != RESET) 
	{
		EXTI_ClearITPendingBit(EXTI_Line2);
		if(KEY1==RESET)
		{
			delay_ms(10);
			if(KEY1==RESET)
			{
			  Key_Up_Flag=1;
				Key_Down_Flag=0;
				Key_Left_Flag=0;
				Key_Right_Flag=0;
				Key_Confirm_Flag=0;
				Key_Menu_Flag=0;
			}
		}

		
		
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
}

void EXTI3_IRQHandler(void)
{
	
  if(EXTI_GetITStatus(EXTI_Line3) != RESET) 
	{
		EXTI_ClearITPendingBit(EXTI_Line3);
		if(KEY2==RESET)
		{
			delay_ms(10);
			if(KEY2==RESET)
			{
			  Key_Up_Flag=0;
				Key_Down_Flag=1;
				Key_Left_Flag=0;
				Key_Right_Flag=0;
				Key_Confirm_Flag=0;
				Key_Menu_Flag=0;
			}
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
}

void EXTI4_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line4) != RESET) 
	{
		EXTI_ClearITPendingBit(EXTI_Line4);
		if(KEY3==RESET)
		{
			delay_ms(10);
			if(KEY3==RESET)
			{
			  Key_Up_Flag=0;
				Key_Down_Flag=0;
				Key_Left_Flag=1;
				Key_Right_Flag=0;
				Key_Confirm_Flag=0;
				Key_Menu_Flag=0;
			}
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}


void EXTI9_5_IRQHandler(void)
{			 		 
	if(EXTI_GetITStatus(EXTI_Line5) != RESET) 
	{
		EXTI_ClearITPendingBit(EXTI_Line5);
		if(KEY4==RESET)
		{
			delay_ms(10);
			if(KEY4==RESET)
			{
			  Key_Up_Flag=0;
				Key_Down_Flag=0;
				Key_Left_Flag=0;
				Key_Right_Flag=1;
				Key_Confirm_Flag=0;
				Key_Menu_Flag=0;
			}
		}
	}
  if(EXTI_GetITStatus(EXTI_Line6) != RESET) 
	{
		EXTI_ClearITPendingBit(EXTI_Line6);
		if(KEY5==RESET)
		{
			delay_ms(10);
			if(KEY5==RESET)
			{
			  Key_Up_Flag=0;
				Key_Down_Flag=0;
				Key_Left_Flag=0;
				Key_Right_Flag=0;
				Key_Confirm_Flag=1;
				Key_Menu_Flag=0;

			}
		}
	}
  if(EXTI_GetITStatus(EXTI_Line7) != RESET) 
	{
		EXTI_ClearITPendingBit(EXTI_Line7);
		if(KEY6==RESET)
		{
			delay_ms(10);
			if(KEY6==RESET)
			{
			  Key_Up_Flag=0;
				Key_Down_Flag=0;
				Key_Left_Flag=0;
				Key_Right_Flag=0;
				Key_Confirm_Flag=0;
				Key_Menu_Flag=1;
				
			}
		}
	}
  EXTI_ClearITPendingBit(EXTI_Line5);
  EXTI_ClearITPendingBit(EXTI_Line6);
  EXTI_ClearITPendingBit(EXTI_Line7);
}


void EXTI15_10_IRQHandler(void)
{
	
	if(EXTI_GetITStatus(EXTI_Line10) != RESET)
	{		
		EXTI_ClearITPendingBit(EXTI_Line10);
		//捕获输入电平
	}
	
	if(EXTI_GetITStatus(EXTI_Line11) != RESET)
	{		
		EXTI_ClearITPendingBit(EXTI_Line11);
   //捕获输入电平
	}
	
	if(EXTI_GetITStatus(EXTI_Line12) != RESET)
	{		
		EXTI_ClearITPendingBit(EXTI_Line12);
		//捕获输入电平
	}
	
}
