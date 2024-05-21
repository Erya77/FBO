
/*
  ******************************************************************************
	* @file      main.c
	* @company   FBO
	* @project   P632
  * @author    bin
  * @version   V0.1
  * @update    2024-05-17
  * @brief     Computer test coordination control
  ******************************************************************************
*/

#include "main.h"


u16 FLASH_R[30];
u16 FLASH_W[30];

u16 XMOS_ADC_DATA[8];

extern u16 xmos_rst_time;


int main(void)
{	
	delay_init();	 					//delay初始化
	Deploy_Init();					//IO初始化
	Adc_Init();
	uart4_init(115200);
	TIM3_Int_Init();
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);   //open Rcc clk
	
	xmos_rst_time=0;
	
	pca9554_init();					//8bit W/R
	TCA6424_Init();					//3*8  IO
	ILI9341_init();					//初始化显示屏
	
	MICX_CON_Init();				//
	P646_Init();						//display显示
	
	softTimer_config(5,10,1,softTimer_handler5);
	
	printf("Program Start\r\n");
	
	while(1)
	{
		XMOS_RST();				//USB上电复位XMOS
		PC_CMD_CTL();			//指令判断
		P646_Action();		//P662动作
		softTimer_updata();//软件定时器		
		Get_state();			//返回状态，上位机读取
	}	
	
}

float xmos_rst_vol;
u8 xmos_rst_flag1=1;
u8 xmos_rst_flag2=0;
/********************************************
*	函 数 名: XMOS_RST
*	功能说明: USB上电初始化XMOS ，下拉0.5s
********************************************/
void XMOS_RST(void)
{	
	xmos_rst_vol = Get_Adc_Average(3,150);//RST_VOL_ADC
	
	if(usb_state==0 )					//识别USB插入
	{ if(xmos_rst_flag1==0)		//上电第一次置位
		{
			xmos_rst_time = 0;
			xmos_rst_flag1=1;
		}
														//第二次判断是否拉低，没有继续置位
		if(xmos_rst_vol>0.5 && xmos_rst_time>=100 && xmos_rst_flag2==0)
		{
			xmos_rst_time = 0;
			xmos_rst_flag2= 1;
		}
	}
	else 
	{
		xmos_rst_flag1=0;
		xmos_rst_flag2=0;
	}
}

/********************************************
*	函 数 名: MICX_CON_Init
*	功能说明: MICX_CON上电复位50ms
********************************************/
void MICX_CON_Init(void)
{
	MIC1_CON_ON;
	delay_ms(50);
	MIC1_CON_OFF;
	
	MIC2_CON_ON;
	delay_ms(50);
	MIC2_CON_OFF;
	
	MIC3_CON_ON;
	delay_ms(50);
	MIC3_CON_OFF;
	
	MIC4_CON_ON;
	delay_ms(50);
	MIC4_CON_OFF;
	
	MIC5_CON_ON;
	delay_ms(50);
	MIC5_CON_OFF;
	
	MIC6_CON_ON;
	delay_ms(50);
	MIC6_CON_OFF;
}

/********************************************
*	函 数 名: P646_Init
*	功能说明: DISPLAY
********************************************/
void P646_Init(void)
{
	GUI_Init();                        //emwin初始化
	P642_Data_Init();

	GUI_DrawBitmapMag(&bmfbo,0,0,2,2); //bmfbo是位图结构体，（0，0）是位图左上角要显示在屏幕上的位置
	delay_ms(100);
	GUI_Clear();											 //清空显示菜单
	GUI_SetBkColor(0x00666666);				 //设置背景底色
	
	DrwaGui();											  	//显示菜单界面
}

