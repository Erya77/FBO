
/*
  ******************************************************************************
	* @file      adc.c
	* @company   FBO
	* @project   P632
  * @author    zhirui fan
  * @version   V0.0
  * @date      2019-9-15
  * @brief     Computer test coordination control
  ******************************************************************************
*/

#include "main.h"
#include "adc.h"
#include "delay.h"

u16 Pre1_Voltage;
u16 Pre2_Voltage;
u16 Pre3_Voltage;
u16 Amp1_Voltage;
u16 Amp2_Voltage;
float Pre1_AD_Result;
float Pre2_AD_Result;
float Pre3_AD_Result;
float Amp1_AD_Result;
float Amp2_AD_Result;



extern u8 cursor_1_num;
extern u8 cursor_2_num;
extern u8 cursor_3_num;
extern u8 cursor_4_num;
extern u8 cursor_5_num;
extern u8 cursor_6_num;
extern u8 cursor_7_num;
extern u8 cursor_8_num;



u16 AD_Value[6]; // 定义缓冲区数组，类型和大小应与 ADC 分辨率匹配

void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PC0,1,2 作为模拟通道输入引脚         ADC对应通道为10-13                
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//PA1,2 作为模拟通道输入引脚         ADC对应通道为1，2              
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);

//	NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn; // ADC1和ADC2共用同一个中断线
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // 抢占优先级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; // 子优先级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

	ADC_DeInit(ADC1);  //复位ADC1 
  
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
  
	//ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE); // 启用ADC1的转换完成中断
	
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}		


//获得ADC值
//ch:通道值 0~3
u16 Get_Adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

// void AD_GetValue(void)
// {
//	 DMA_Cmd(DMA1_Channel1,DISABLE);
//	DMA_SetCurrDataCounter(DMA1_Channel1,6);
//	DMA_Cmd(DMA1_Channel1,ENABLE);
//	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET)
//	DMA_ClearFlag(DMA1_FLAG_TC1);
// }

u8 adc_average_val[100]={0};

float Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
		for(t=0;t<times;t++)
		{
		temp_val+=Get_Adc(ch);
//		delay_ms(1);
		}
	return (float)temp_val/times/4096*3.3;
}


float average1;
char count=0;







