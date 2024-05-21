
/*
  ******************************************************************************
	* @file      dispose.c
	* @company   FBO
	* @project   P642
  * @author    zhirui fan
  * @version   V0.0
  * @date      
  * @brief     Computer test coordination control
  ******************************************************************************
*/

#include "dispose.h"
#include "key.h"
#include "main.h"
#include "delay.h"
#include "deploy.h"
#include "display.h"


extern u8 AU1_Change_Flag;
extern u8 AU2_Change_Flag;
extern u8 AU3_Change_Flag;
extern u8 AU4_Change_Flag;
extern u8 AU5_Change_Flag;
extern u8 AU6_Change_Flag;
extern u8 AMP1_Change_Flag;
extern u8 AMP2_Change_Flag;
extern u8 IO_Change_Flag;


u16 ISEN_Flag;

struct _AU AU1,AU2,AU3,AU4,AU5,AU6;
struct _AMP AMP1,AMP2;
u16 IO_STA[8];	

const float Over_vol_val=0.40;//过压保护第二次判断阈值
const float Over_vol_0dB=3.24;//过压保护检测电压
const float Over_vol_20dB=0.29;//过压保护检测电压
const float Open_vol_20dB=5;//20dB电压打开判断
/********************************************
*	函 数 名: AUX_Overvoltage_Dispose
*	功能说明: 过压检测
* 输入电压：过压进行重置3s动作
********************************************/
void AUX_Overvoltage_Dispose(struct _AU *au, u8 adc_channel)
{
	// 输入电压检测,过压进行3s重置

			au->input_voltage = Get_Adc_Average(adc_channel,150);
		if ((au->gain == 0 && au->input_voltage > Over_vol_0dB) || //过压判断条件
				(au->gain == 1 && au->input_voltage >= Over_vol_20dB))             
			au->vol_protecttime = 0;
		
		if(au->vol_flag==1&&au->input_voltage > Over_vol_val)		//过压进入第二次判断
			au->vol_protecttime = 0;

		if(au->vol_protecttime<300)		//3s计数
			{ if(au->overvol_flag!=1)
				{
					au->vol_protect = 1;		//过压保护标志位
					MICX_PRT_ON(au);			 //MIC输入电压检测打开
					Display_Aux_char(au,"OVER");//LCD对应显示OVER
					au->vol_flag=1;
					au->overvol_flag=1;
					
				}
			}
		else
			{ if(au->overvol_flag!=2)
				{
					au->vol_protect = 0;
					MICX_PRT_OFF(au);				//MIC输入电压检测关闭
					Display_Aux_Overvol(au);//LCD回复显示模式
					au->vol_flag=0;
					au->overvol_flag=2;
					
				}
			}			
}

/*******************************************
*	函 数 名: AUX_Mic_Mode2  
* 通    道：输入1-4 不含MODE:IMP
* 标 志 位：0-line  1-mic
*	功能说明: 麦克风检测处理，打开base_control
********************************************/
void AUX_Mic_Mode2(struct _AU *au)
{
	u8 tmp;
	tmp=(u8)au->Microphone;
		
		if(tmp&0x01)
		{ if(au->mode_flag!=1)
			{
				MICX_CON_ON(au);
				if(au->vol_protect ==0)		
				Display_Aux_Mode(au);	
				au->mode_flag = 1;
			}
		}
		else
		{ if(au->mode_flag!=0)
			{
				MICX_CON_OFF(au);	
				if(au->vol_protect ==0)		
				Display_Aux_Mode(au);
				au->mode_flag = 0;
			}
		}
	
}
/*******************************************
*	函 数 名: AUX_Mic_Mode3  
* 通    道：输入5-6 含MODE:IMP
* 标 志 位：0-line  1-mic  2-imp
*	功能说明: 麦克风检测处理，打开base_control
********************************************/
void AUX_Mic_Mode3(struct _AU *au)
{
	u8 tmp;
	

	tmp=(u8)au->Microphone;
		
		if(tmp&0x01)
		{ if(au->mode_flag!=1)
			{
				MICX_CON_ON(au);
				if(au->vol_protect ==0)		
				Display_Aux_Mode(au);	
				au->mode_flag = 1;
			}
			if (au->i_sen==1)
			ISENX_IN_ON(au);
			else
			ISENX_IN_OFF(au);
		}
		else 
			if (au->i_sen==1)
		{	if(au->mode_flag!=2)
			{
				MICX_CON_OFF(au);
				if(au->vol_protect ==0)
				Display_Aux_Mode(au);	
				ISENX_IN_ON(au);
				au->mode_flag = 2;
			}
		}		
		else
		{	if(au->mode_flag!=0)
			{
				MICX_CON_OFF(au);
				if(au->vol_protect ==0)		
				Display_Aux_Mode(au);
				ISENX_IN_OFF(au);
				au->mode_flag = 0;
			}
		}	
}
/********************************************
*	函 数 名: AUX_Mic_Dispose
*	功能说明: Mic检测插入显示
********************************************/
void AUX_Mic_Dispose(struct _AU *au,u8 AUX_ICP_EN)
{	
	if(AUX_ICP_EN!=au->mic_in)//MIC检测处理
	{
		au->mic_in_flag = au->mic_in_flag+1;
		printf("mir change");
		if (au == &AU1)
		au->mic_in=AU1_ICP_EN;
		else if (au == &AU2)
		au->mic_in=AU2_ICP_EN;
		else if (au == &AU3)
		au->mic_in=AU3_ICP_EN;
		else if (au == &AU4)
		au->mic_in=AU4_ICP_EN;
		else if (au == &AU5)
		au->mic_in=AU5_ICP_EN;
		else if (au == &AU6)
		au->mic_in=AU6_ICP_EN;
	}
	
		if(au->mic_in_flag>=1)   //表示麦克风状态有变化
	{ if(au->mic_in_counts>=6)   //防止波动，等待循环8次后在执行改变
		{	if(au->mic_in_flag ==2 )  //表示短时间内连续进入
				au->mic_in_flag = au->mic_in_flag +1;
			else
			{ if(!au->mic_in)//MIC输入处理
					Display_Aux_char(au,"ICP-BACK");
				else
				{	if(au->bias==1)
						Display_Aux_char(au,"2.0V");
					else if(au->bias==2)
						Display_Aux_char(au,"2.7V");
					else if(au->bias==3)
						Display_Aux_char(au,"ICP");
					else 
						Display_Aux_char(au,"NONE");
				}
				au->mic_in_flag = 0;
				au->mic_in_counts = 0;
			}
		}
			au->mic_in_counts = au->mic_in_counts + 1;
	}	
}
/********************************************
*	函 数 名: AUX_Gain_Mode
*	功能说明: 通道增益模式处理--自动/手动
*	自		动：满足输入电压自动打开20dB
*	手		动：手动打开0/20dB
********************************************/
u8 _mode = 0;		//上电默认手动模式    0手动/1自动  
void AUX_Gain_Mode(struct _AU *au,u32 Aux_Gain_Addr,u16 *pBuffer)
{
	u16 val_a[4]  = {0,1,0x10,0x11};
	u16 *_val = &val_a[0];
	//u8 _mode = 0;		//上电默认手动模式    0手动/1自动  							
	GUI_SetColor(GUI_CYAN);
	_mode = (au->gain >> 4);//判断自动手动模式

	if(_mode ==0)//手动
	{ if(au->gain==1 && au->input_voltage < Open_vol_20dB && au->gain_flag!=1)
		{
			AUX_20DB_GAIN(au);		//打开20dB
			Display_Aux_char(au,"20dB");//LCD显示20dB
			au->gain_flag=1;
		}
		else if( au->gain==1 && au->input_voltage >= Open_vol_20dB&& au->gain_flag!=2)//恢复0dB
		{
			STMFLASH_Write(Aux_Gain_Addr,_val,1);STMFLASH_Read(Aux_Gain_Addr,pBuffer,1);
			au->gain_flag=2;
		}
		else if( au->gain==0 && au->gain_flag!=3)			//恢复0dB
		{
			AUX_0DB_GAIN(au);
			Display_Aux_char(au,"0dB");//LCD显示0dB
			au->gain_flag=3;
		}			
	}
	else if(_mode ==1)//自动
	{ if( au->input_voltage < Open_vol_20dB&& au->gain_flag!=4)
		{
			STMFLASH_Write(Aux_Gain_Addr,_val+3,1);STMFLASH_Read(Aux_Gain_Addr,pBuffer,1);
			AUX_20DB_GAIN(au);
			Display_Aux_char(au,"20dB");//LCD显示20dB
			au->gain_flag=4;
		}
		else if( au->input_voltage >= Open_vol_20dB&& au->gain_flag!=5)
		{
			STMFLASH_Write(Aux_Gain_Addr,_val+2,1);STMFLASH_Read(Aux_Gain_Addr,pBuffer,1);
			AUX_0DB_GAIN(au);
			Display_Aux_char(au,"0dB");//LCD显示0dB
			au->gain_flag=5;
		}
	}		
}

/********************************************
*	函 数 名: AUX_Bias_Mode
*	功能说明: Bias切换处理
*	可    选：NONE-2.0V-2.7V-24V
*	标 志 位：0-NONE 1-2.0V 2-2.7V 3-ICP
********************************************/
void AUX_Bias_Mode(struct _AU *au)
{
		if(au->bias==1)
		{  if(au->bias_flag !=1)
			{			
				AUX_2V0_ON(au);
				Display_Aux_char(au,"2.0V");
				au->bias_flag = 1;
			}	
		}
		else if(au->bias==2)
		{ if(au->bias_flag !=2)
			{		
				AUX_2V7_ON(au);
				Display_Aux_char(au,"2.7V");
				au->bias_flag = 2;
			}			
		}
		else if(au->bias==3)
		{ if(au->bias_flag !=3)
			{	if(!au->mic_in)
				{
					AUX_ICP_ON(au);
					Display_Aux_char(au,"ICP-BACK");
					au->bias_flag = 3;
				}
				else
				{
					AUX_ICP_ON(au);
					Display_Aux_char(au,"ICP");
					au->bias_flag = 3;
				}
		  }		
		}
		else 
		{	if(au->bias_flag != 0)
			{
				AUX_NONE_ON(au);
				Display_Aux_char(au,"NONE");
				au->bias_flag = 0;
			}
		}
}


/********************************************
*	函 数 名: AMPX_Out_Dispose
*	功能说明: 输出过载动作
********************************************/
void AMPX_Out_Dispose(struct _AMP *amp)//, u8 PORT_AMPX_OUT)
{
		if(amp == &AMP1)
	{
		if(PORT_AMP1_OUT==0)
		amp->out_protecttime = 0;
  }
	else if(amp == &AMP2)
	{
		if(PORT_AMP2_OUT==0)
		amp->out_protecttime = 0;
	}
		
	
	if(amp->out_protecttime<300)
		{ if(amp->overload_flag!=1)
				{
					AMPX_OVER_ON(amp);
					Display_Ampx_char(amp,"OVER");
					amp->overload=1;
					amp->overload_flag=1;
				}
		}
	else
		{ if(amp->overload_flag!=2)
			{
				AMPX_OVER_OFF(amp);
				Display_Ampx_Out(amp);
				amp->overload=0;
				amp->overload_flag=2;
			}	
		}
}
/********************************************
*	函 数 名: AUX_Gain_Mode
*	功能说明: AMPX增益切换
********************************************/
void AMPX_Gain_Mode(struct _AMP *amp)
{
	//Gain处理
	if(amp->gain==1)
	{ if(amp->gain_flag!=1)
		{
			AMPX_20DB_GAIN(amp);
			Display_Ampx_char(amp,"20dB");
			amp->gain_flag=1;
		}
	}
	else
	{ if(amp->gain_flag!=2)
		{
			AMPX_0DB_GAIN(amp);
			Display_Ampx_char(amp,"0dB");
			amp->gain_flag=2;
		}
	}			
}
//AU1动作处理
void AU1_Dispose()
{
	
	AUX_Mic_Mode2(&AU1);//麦克风模式切换，base_control
	
	AUX_Overvoltage_Dispose(&AU1,10);//AU1过压检测处理
	
	AUX_Mic_Dispose(&AU1,AU1_ICP_EN);//麦克风检测插入
	
	AUX_Bias_Mode(&AU1);//bias切换处理
	
	AUX_Gain_Mode(&AU1,AU1_GAIN_ADDR,&AU1.gain);//增益动作处理

}

//AU2动作处理·
void AU2_Dispose()
{		
	
	AUX_Mic_Mode2(&AU2);//麦克风模式切换，base_control

	AUX_Overvoltage_Dispose(&AU2,11);//AU2过压检测处理

	AUX_Mic_Dispose(&AU2,AU2_ICP_EN);//麦克风检测插入

	AUX_Bias_Mode(&AU2);//bias切换处理

	AUX_Gain_Mode(&AU2,AU2_GAIN_ADDR,&AU2.gain);//增益动作处理
	
}

//AU3动作处理
void AU3_Dispose()
{
	
	AUX_Mic_Mode2(&AU3);//麦克风模式切换，base_control

	AUX_Overvoltage_Dispose(&AU3,12);//AU3过压检测处理

	AUX_Mic_Dispose(&AU3,AU3_ICP_EN);//麦克风检测插入

	AUX_Bias_Mode(&AU3);//bias切换处理

	AUX_Gain_Mode(&AU3,AU3_GAIN_ADDR,&AU3.gain);//增益动作处理
	
}


//AU4动作处理
void AU4_Dispose()
{
	
	AUX_Mic_Mode2(&AU4);//麦克风模式切换，base_control

	AUX_Overvoltage_Dispose(&AU4,13);//AU4过压检测处理

	AUX_Mic_Dispose(&AU4,AU4_ICP_EN);//麦克风检测插入

	AUX_Bias_Mode(&AU4);//bias切换处理

	AUX_Gain_Mode(&AU4,AU4_GAIN_ADDR,&AU4.gain);//增益动作处理
		
}

//AU5动作处理
void AU5_Dispose()
{
	
	AUX_Mic_Mode3(&AU5);//麦克风模式切换，base_control

	AUX_Overvoltage_Dispose(&AU5,1);//AU5过压检测处理

	AUX_Mic_Dispose(&AU5,AU5_ICP_EN);//麦克风检测插入
	
	AUX_Bias_Mode(&AU5);//bias切换处理

	AUX_Gain_Mode(&AU5,AU5_GAIN_ADDR,&AU5.gain);//增益动作处理
	
}

//AU6动作处理
void AU6_Dispose()
{
		
	AUX_Mic_Mode3(&AU6);//麦克风模式切换，base_control

	AUX_Overvoltage_Dispose(&AU6,2);//AU6过压检测处理
	
	AUX_Mic_Dispose(&AU6,AU6_ICP_EN);//麦克风检测插入

	AUX_Bias_Mode(&AU6);//bias切换处理

	AUX_Gain_Mode(&AU6,AU6_GAIN_ADDR,&AU6.gain);//增益动作处理	
		
}

//AMP1动作处理
void AMP1_Dispose()
{
	AMPX_Out_Dispose(&AMP1);//, PORT_AMP1_OUT);
	
	AMPX_Gain_Mode(&AMP1);
}

//AMP2动作处理
void AMP2_Dispose()
{
	AMPX_Out_Dispose(&AMP2);//, PORT_AMP2_OUT);
	
	AMPX_Gain_Mode(&AMP2);
}

void IO_Dispose()
{
	if(IO_Change_Flag)
	{
//		//配置IO输入模式或者输出模式
//		pca9554_Write_Process(0x03,IO_STA[0]);
//		
//		//设置输出模式IO的输出状态
//		pca9554_Write_Process(0x01,IO_STA[1]);
		
		u8 tmp,i;
		
		for(i=0;i<=7;i++)
		{
			tmp=(u8)IO_STA[0]>>i;

			
			tmp&=0x01;
			if(tmp)
			{

				GUI_SetColor(GUI_CYAN);
				
					GUI_ClearRect(293-28*i, 214, 308-28*i, 234);
					GUI_DispStringAt("R",  293-28*i, 216);	//GUI_DispStringAt("1",  295-40*i, 220);
					tmp=(u8)IO_STA[2]>>i;
					tmp&=0x01;
				if(tmp)
				{
					GUI_ClearRect(295-28*i, 193, 305-28*i, 213);
					GUI_DispStringAt("1",  295-28*i, 196);	//LCD_ShowString6_8(143-20*i,112,(u8 *)"1",BRRED);
				}else{
					GUI_ClearRect(295-28*i, 193, 305-28*i, 213);
					GUI_DispStringAt("0",  295-28*i, 196);	//LCD_ShowString6_8(143-20*i,112,(u8 *)"0",BRRED);
				}

			}
			else
			{
						GUI_ClearRect(293-28*i, 214, 308-28*i, 234);
					GUI_DispStringAt("W",  293-28*i, 216);	//GUI_DispStringAt("0",  295-40*i, 220);
				tmp=(u8)IO_STA[1]>>i;
				tmp&=0x01;
						if(tmp)
				{
					GUI_ClearRect(295-28*i, 193, 305-28*i, 213);
					GUI_DispStringAt("1",  295-28*i, 196);	//LCD_ShowString6_8(143-20*i,112,(u8 *)"1",BRRED);
				}else{
					GUI_ClearRect(295-28*i, 193, 305-28*i, 213);
					GUI_DispStringAt("0",  295-28*i, 196);	//LCD_ShowString6_8(143-20*i,112,(u8 *)"0",BRRED);
				}
				
		}
	}
					
		IO_Change_Flag=0;
	}
		
	IO_STA[2]=IIC_BUF[0];
	
}


void P646_Action()
{
	AU1_Dispose();
	AU2_Dispose();
	AU3_Dispose();
	AU4_Dispose();
	AU5_Dispose();
	AU6_Dispose();
	AMP1_Dispose();
	AMP2_Dispose();
	IO_Dispose();
}

void P642_Data_Init()
{

	u8 i=0;
	u16 data[2]={0x0000,0x00ff};
	
	STMFLASH_Read(AU1_GAIN_ADDR,FLASH_R,26);
	for(i=0;i<=16;i++)
	{
		if(FLASH_R[i]==0xffff)
		{
			//FLASH_R[i]=0;
			if(i<=15)
				STMFLASH_Write(AU1_GAIN_ADDR+i*2,data,1);
			else
				STMFLASH_Write(AU1_GAIN_ADDR+i*2,data+1,1);
		}
	}
	STMFLASH_Read(AU1_GAIN_ADDR,FLASH_R,26);
	
	AU1.gain=FLASH_R[0];
	AU1.bias=FLASH_R[1];
	
	AU2.gain=FLASH_R[2];
	AU2.bias=FLASH_R[3];
	
	AU3.gain=FLASH_R[4];
	AU3.bias=FLASH_R[5];
	
	AU4.gain=FLASH_R[6];
	AU4.bias=FLASH_R[7];
	
	AU5.gain=FLASH_R[8];
	AU5.bias=FLASH_R[9];
	AU5.i_sen=FLASH_R[10];
	
	AU6.gain=FLASH_R[11];
	AU6.bias=FLASH_R[12];
	AU6.i_sen=FLASH_R[13];
	
	AMP1.gain=FLASH_R[14];
	AMP2.gain=FLASH_R[15];
	
	IO_STA[0]=FLASH_R[16];
	IO_STA[1]=FLASH_R[17];
	
	AU1.Microphone=FLASH_R[18];
	AU2.Microphone=FLASH_R[19];
	AU3.Microphone=FLASH_R[20];
	AU4.Microphone=FLASH_R[21];
	AU5.Microphone=FLASH_R[22];
	AU6.Microphone=FLASH_R[23];
	
	XMOS_ADC_DATA[1]=FLASH_R[24];
	XMOS_ADC_DATA[2]=FLASH_R[25];
	

	
	AU1.mic_in=AU1_ICP_EN;
	AU2.mic_in=AU2_ICP_EN;
	AU3.mic_in=AU3_ICP_EN;
	AU4.mic_in=AU4_ICP_EN;
	AU5.mic_in=AU5_ICP_EN;
	AU6.mic_in=AU6_ICP_EN;
	
	
	AU1_Change_Flag=1;
	AU2_Change_Flag=1;
	AU3_Change_Flag=1;
	AU4_Change_Flag=1;
	AU5_Change_Flag=1;
	AU6_Change_Flag=1;
	AMP1_Change_Flag=1;
	AMP2_Change_Flag=1;
	IO_Change_Flag=1;
	
	AU1.vol_protecttime=300;//过压保护时间初始化
	AU2.vol_protecttime=300;//过压保护时间初始化
	AU3.vol_protecttime=300;//过压保护时间初始化
	AU4.vol_protecttime=300;//过压保护时间初始化
	AU5.vol_protecttime=300;//过压保护时间初始化
	AU6.vol_protecttime=300;//过压保护时间初始化
	
	AU1.overvol_flag =3;			//过压保护标志位
	AU2.overvol_flag =3;			//过压保护标志位
	AU3.overvol_flag =3;			//过压保护标志位
	AU4.overvol_flag =3;			//过压保护标志位
	AU5.overvol_flag =3;			//过压保护标志位
	AU6.overvol_flag =3;			//过压保护标志位
	
	AU1.vol_flag=0;	//第二次跳变判断
	AU2.vol_flag=0;
	AU3.vol_flag=0;	
	AU4.vol_flag=0;
	AU5.vol_flag=0;
	AU6.vol_flag=0;
	
	AU1.mode_flag=5;
	AU2.mode_flag=5;
	AU3.mode_flag=5;
	AU4.mode_flag=5;
	AU5.mode_flag=5;
	AU6.mode_flag=5;
	
	AU1.gain_flag=0;			//增益切换标志位
	AU2.gain_flag=0;			//增益切换标志位
	AU3.gain_flag=0;			//增益切换标志位
	AU4.gain_flag=0;			//增益切换标志位
	AU5.gain_flag=0;			//增益切换标志位
	AU6.gain_flag=0;			//增益切换标志位
	
	AU1.bias_flag=5;
	AU2.bias_flag=5;
	AU3.bias_flag=5;
	AU4.bias_flag=5;
	AU5.bias_flag=5;
	AU6.bias_flag=5;
	
	AU1.mic_in_flag = 0; 
	AU2.mic_in_flag = 0; 
	AU3.mic_in_flag = 0; 
	AU4.mic_in_flag = 0; 
	AU5.mic_in_flag = 0; 
	AU6.mic_in_flag = 0; 
	
	AU1.mic_in_counts = 0;//计数延迟防止麦克风模式反复横跳
	AU2.mic_in_counts = 0;
	AU3.mic_in_counts = 0;
	AU4.mic_in_counts = 0;
	AU5.mic_in_counts = 0;
	AU6.mic_in_counts = 0;
	
	AMP1.out_protecttime = 300;
	AMP2.out_protecttime = 300;
	
	AMP1.overload_flag=0;
	AMP2.overload_flag=0;
	
	AMP1.gain_flag=0;
	AMP2.gain_flag=0;
	
	pca9554_Write_Process(0x03,IO_STA[0]);
	delay_ms(10);
	pca9554_Write_Process(0x01,IO_STA[1]);
	

}
