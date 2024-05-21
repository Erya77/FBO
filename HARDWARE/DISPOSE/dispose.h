#ifndef __DISPOSE_H
#define __DISPOSE_H
#include "sys.h"


struct _AU{
	u16 gain;
	u16 bias;
	u8 mic_in;//���MIC�Ƿ����
	u16 i_sen;//�迹�����л�
	float input_voltage;//�����ѹ
	u8 vol_protect;//�����ѹ������־
	u16 Microphone; //�Ƿ���ʾ��˷�ģʽ
	
	u8 vol_flag;		//�ڶ����жϱ�־
	u16 vol_protecttime;//��ѹ����ʱ��
	u8 overvol_flag;
	u8 gain_flag;
	u8 mode_flag;//		0/1/2ģʽ
	u8 bias_flag;
	u8 mic_in_flag;
	u8 mic_in_counts; //��������
};

extern struct _AU AU1,AU2,AU3,AU4,AU5,AU6;


struct _AMP{
	u16 gain;
	u8 overload;//������ر�����־
	u16 out_protecttime;//���ر���ʱ��
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
void AUX_Gain_Mode(struct _AU *au,u32 WriteAddr,u16 *pBuffer);//ָ��AU�ṹ��ָ��
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
