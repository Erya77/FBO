#ifndef __XMOS_ADC_H
#define __XMOS_ADC_H


#include "sys.h"

#define XMOS_ADC1_ADDRESS 0x40
#define XMOS_ADC2_ADDRESS 0x46

#define REG_ADC1_ADDRESS 0x20
#define REG_ADC2_ADDRESS 0x22

void xmos_adc_init(void);//PB7 SDA  PB6  SCL 
int MCU_Write_ADC1_Process(u8 address,u8 cmd, u8 data);
#endif
