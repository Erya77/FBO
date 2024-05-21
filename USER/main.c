
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
	delay_init();	 					//delay��ʼ��
	Deploy_Init();					//IO��ʼ��
	Adc_Init();
	uart4_init(115200);
	TIM3_Int_Init();
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);   //open Rcc clk
	
	xmos_rst_time=0;
	
	pca9554_init();					//8bit W/R
	TCA6424_Init();					//3*8  IO
	ILI9341_init();					//��ʼ����ʾ��
	
	MICX_CON_Init();				//
	P646_Init();						//display��ʾ
	
	softTimer_config(5,10,1,softTimer_handler5);
	
	printf("Program Start\r\n");
	
	while(1)
	{
		XMOS_RST();				//USB�ϵ縴λXMOS
		PC_CMD_CTL();			//ָ���ж�
		P646_Action();		//P662����
		softTimer_updata();//�����ʱ��		
		Get_state();			//����״̬����λ����ȡ
	}	
	
}

float xmos_rst_vol;
u8 xmos_rst_flag1=1;
u8 xmos_rst_flag2=0;
/********************************************
*	�� �� ��: XMOS_RST
*	����˵��: USB�ϵ��ʼ��XMOS ������0.5s
********************************************/
void XMOS_RST(void)
{	
	xmos_rst_vol = Get_Adc_Average(3,150);//RST_VOL_ADC
	
	if(usb_state==0 )					//ʶ��USB����
	{ if(xmos_rst_flag1==0)		//�ϵ��һ����λ
		{
			xmos_rst_time = 0;
			xmos_rst_flag1=1;
		}
														//�ڶ����ж��Ƿ����ͣ�û�м�����λ
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
*	�� �� ��: MICX_CON_Init
*	����˵��: MICX_CON�ϵ縴λ50ms
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
*	�� �� ��: P646_Init
*	����˵��: DISPLAY
********************************************/
void P646_Init(void)
{
	GUI_Init();                        //emwin��ʼ��
	P642_Data_Init();

	GUI_DrawBitmapMag(&bmfbo,0,0,2,2); //bmfbo��λͼ�ṹ�壬��0��0����λͼ���Ͻ�Ҫ��ʾ����Ļ�ϵ�λ��
	delay_ms(100);
	GUI_Clear();											 //�����ʾ�˵�
	GUI_SetBkColor(0x00666666);				 //���ñ�����ɫ
	
	DrwaGui();											  	//��ʾ�˵�����
}

