#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"


extern u16 AD_Value[6];

void Adc_Init(void);
u16  Get_Adc(u8 ch);
 void AD_GetValue(void);
//float Get_Adc_Average(u8 ch,u8 times);
float Get_Adc_Average(u8 ch,u8 times);
void Adc_Process_Conversion(void);
 
#endif 
