
/*
  ******************************************************************************
	* @file      time.c
	* @company   FBO
	* @project   P632
  * @author    zhirui fan
  * @version   V0.0
  * @date      2019-9-15
  * @brief     Computer test coordination control
  ******************************************************************************
*/

#include "main.h"

u16 timer_xmos_iic=0;
u8 xmos_flag=0;

u16 uart4_time=0;

u16 timer_cmd=0;

u16 xmos_rst_time=100;

void TIM3_Int_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = 1000-1;
	TIM_TimeBaseStructure.TIM_Prescaler =720-1 ;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(  TIM3,TIM_IT_Update,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  

	TIM_Cmd(TIM3, ENABLE);  
							 
}

void TIM3_IRQHandler(void)   //10ms  timekeeping     
{
	//static uint16_t main_menu_state=0;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update );  //清除TIMx的中断待处理位:TIM 中断源
			
		//开机计时5s初始化xmos_adc_iic
		if(xmos_flag==0)
		{
			timer_xmos_iic++;
			if(timer_xmos_iic>=500)
			{
					xmos_adc_init();
					MCU_Write_ADC1_Process(XMOS_ADC1_ADDRESS,REG_ADC1_ADDRESS, XMOS_ADC_DATA[1]);
					MCU_Write_ADC1_Process(XMOS_ADC2_ADDRESS,REG_ADC2_ADDRESS, XMOS_ADC_DATA[2]);
					xmos_flag=1;
			}
		}
		
		//软件定时器计时
		tick_Cnt++;
		
		//通道过压计时保护3s	
		if(AU1.vol_protecttime<300)
		AU1.vol_protecttime++;
		if(AU2.vol_protecttime<300)
		AU2.vol_protecttime++;
		if(AU3.vol_protecttime<300)
		AU3.vol_protecttime++;
		if(AU4.vol_protecttime<300)
		AU4.vol_protecttime++;
		if(AU5.vol_protecttime<300)
		AU5.vol_protecttime++;
		if(AU6.vol_protecttime<300)
		AU6.vol_protecttime++;
		if(AMP1.out_protecttime<300)
		AMP1.out_protecttime++;
		if(AMP2.out_protecttime<300)
		AMP2.out_protecttime++;
		
		if(xmos_rst_time<=50)
		{xmos_rst_time++;xmos_rest=0;}
		else if((xmos_rst_time>50) && (xmos_rst_time<100))
		{xmos_rst_time++;xmos_rest=1;}

		
		//监视串口接收是否完成	
		if(USART_RX_STA>0)
		{
			uart4_time++;
		}
		else
		{
			uart4_time=0;
		}
	}
}












