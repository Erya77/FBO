#ifndef __DISPOSE_H
#define __DISPOSE_H
#include "sys.h"


struct _AU{
	u16 gain;
	u16 bias;
	u8 mic_in;//检测MIC是否插入
	u16 i_sen;//阻抗测试切换
	float input_voltage;//输入电压
	u8 vol_protect;//输入过压保护标志
	u16 Microphone; //是否显示麦克风模式
	
	u8 vol_flag;		//第二次判断标志
	u16 vol_protecttime;//过压保护时间
	u8 overvol_flag;
	u8 gain_flag;
	u8 mode_flag;//		0/1/2模式
	u8 bias_flag;
	u8 mic_in_flag;
	u8 mic_in_counts; //防抖计数
};

extern struct _AU AU1,AU2,AU3,AU4,AU5,AU6;


struct _AMP{
	u16 gain;
	u8 overload;//输出过载保护标志
	u16 out_protecttime;//过载保护时间
	u8 overload_flag;
	u8 gain_flag;
};

extern struct _AMP AMP1,AMP2;

extern u16 IO_STA[8];
extern u16 ISEN_Flag;
extern u8 Link1_Flag;
extern u8 Link2_Flag;
extern u8 Link3_Flag;
extern u8 Link4_Flag;
extern u8 Link5_Flag;
extern u8 Link6_Flag;

extern u8 AU1_Change_Flag;
extern u8 AU2_Change_Flag;
extern u8 AU3_Change_Flag;
extern u8 AU4_Change_Flag;
extern u8 AU5_Change_Flag;
extern u8 AU6_Change_Flag;


void AUX_Overvoltage_Dispose(struct _AU *au, u8 adc_channel);
void AUX_Gain_Mode(struct _AU *au,u32 WriteAddr,u16 *pBuffer);//指向AU结构体指针
void AUX_Mic_Mode2(struct _AU *au);
void AUX_Mic_Mode3(struct _AU *au);
void AUX_Bias_Mode(struct _AU *au);
void AUX_Mic_Dispose(struct _AU *au,u8 AUX_ICP_EN);

void AMPX_Out_Dispose(struct _AMP *amp);//, u8 PORT_AMPX_OUT);
void AMPX_Gain_Mode(struct _AMP *amp);
	

void P646_Action(void);
void LCD_Display(void);
void P642_Data_Init(void);

#endif
