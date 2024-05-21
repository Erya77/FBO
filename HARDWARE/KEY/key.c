
/*
  ******************************************************************************
	* @file      key.c
	* @company   FBO
	* @project   P632
  * @author    zhirui fan
  * @version   V0.0
  * @date      2019-9-15
  * @brief     Computer test coordination control
  ******************************************************************************
*/

#include "key.h"
#include "delay.h"
 	    
//按键初始化函数 
//void KEY_Init(void)
//{
//	
//	GPIO_InitTypeDef GPIO_InitStructure;
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//使能PORTD,PORTC时钟

//	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
// 	GPIO_Init(GPIOD, &GPIO_InitStructure);	
//} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0||KEY6==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY1==0)     return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(KEY3==0)return KEY3_PRES;
		else if(KEY4==0)return KEY4_PRES;
		else if(KEY5==0)return KEY5_PRES;
		else if(KEY6==0)return KEY6_PRES;
	}
	else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1&&KEY5==1&&KEY6==1)key_up=1; 	     
	return 0;// 无按键按下
}
