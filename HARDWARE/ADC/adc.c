
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



u16 AD_Value[6]; // ���建�������飬���ͺʹ�СӦ�� ADC �ֱ���ƥ��

void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PC0,1,2 ��Ϊģ��ͨ����������         ADC��Ӧͨ��Ϊ10-13                
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//PA1,2 ��Ϊģ��ͨ����������         ADC��Ӧͨ��Ϊ1��2              
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

//	NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn; // ADC1��ADC2����ͬһ���ж���
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // ��ռ���ȼ�
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; // �����ȼ�
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

	ADC_DeInit(ADC1);  //��λADC1 
  
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
  
	//ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE); // ����ADC1��ת������ж�
	
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}		


//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
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







