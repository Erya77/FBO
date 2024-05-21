#ifndef _MAN_H_
#define _MAN_H_

#include "delay.h"
#include "sys.h"
//#include "ST7789V.h"
#include "stmflash.h"
#include "malloc.h"
#include "GUI.h"
#include "timer.h"
#include "myexti.h"
#include "adc.h"
#include "key.h"
#include "deploy.h"
#include "dispose.h"
#include "cstring"
#include "myiic.h"
#include "usart.h"
#include "DIALOG.h"
#include "softTimer.h"
#include "pca9554.h"
#include "ILI9341.h"
#include "myiic.h"
#include "tca6424a.h"
#include "xmos_adc.h"
#include "fbo.h" 				//ŒªÕºœ‘ æ
#include "weiruan24.h"	//◊÷ÃÂŒ¢»Ì24
#include "display.h"



void XMOS_RST(void);
void P646_Init(void);
void MICX_CON_Init(void);
void XMOS_ADC_INIT(void);


extern u16 FLASH_R[30];
extern u16 FLASH_W[30];



extern u16 current_tca1_reg0;
extern u16 current_tca1_reg1;
extern u16 current_tca1_reg2;
extern u16 current_tca2_reg0;
extern u16 current_tca2_reg1;
extern u16 current_tca2_reg2;

extern u16 XMOS_ADC_DATA[8];

#endif
