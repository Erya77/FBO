#ifndef __DEPLOY_H
#define __DEPLOY_H
#include "sys.h"
#include "dispose.h"
#include "main.h"

void Deploy_Init(void);


/********************************USB上电识别************************************/
#define usb_state   			PCin(13) 	//usb识别插入
#define xmos_rest					PAout(4)	//拉低->拉高
//#define xmos_usb_state		PAout(3)	//xmos_rest 读取ADC



/********************************前置通道1************************************/

#define AU1_ICP_EN 		PAin(12)      //前置CH1检测MIC插入信号  L

#define AU1_GAIN_ADDR	0X0803F800
#define AU1_BIAS_ADDR	0X0803F802

#define AU1_0DB_GAIN 	  TCA6424_Port(Output_Port0,port_0,2,0)    //前置CH1增益  L:0dB
#define AU1_20DB_GAIN 	TCA6424_Port(Output_Port0,port_0,2,1)    //前置CH1增益  H:20dB  
#define AU1_2V0_ON  		TCA6424_Port(Output_Port1,port_6,1,1)    //前置CH1 bias输出2V    H
#define AU1_2V0_OFF  		TCA6424_Port(Output_Port1,port_6,1,0)    //前置CH1 bias输出2V    L
#define AU1_2V7_ON 			TCA6424_Port(Output_Port1,port_5,1,1)    //前置CH1 bias输出2.7V  H
#define AU1_2V7_OFF 		TCA6424_Port(Output_Port1,port_5,1,0)    //前置CH1 bias输出2.7V  L
#define AU1_ICP_ON 			TCA6424_Port(Output_Port1,port_4,1,1)    //前置CH1 bias输出24V   H
#define AU1_ICP_OFF 		TCA6424_Port(Output_Port1,port_4,1,0)    //前置CH1 bias输出24V   L
#define MIC1_PRT_ON 		TCA6424_Port(Output_Port0,port_6,2,0)    //前置CH1输入电压保护继电器 H
#define MIC1_PRT_OFF 		TCA6424_Port(Output_Port0,port_6,2,1)    //前置CH1输入电压保护继电器 L
#define MIC1_CON_ON 		TCA6424_Port(Output_Port2,port_2,2,1)    //前置CH1麦克风识别保护继电器 H
#define MIC1_CON_OFF 		TCA6424_Port(Output_Port2,port_2,2,0)    //前置CH1麦克风识别保护继电器 L
/********************************前置通道2************************************/

#define AU2_ICP_EN 		PAin(11)      //前置CH2检测MIC插入信号  L

#define AU2_GAIN_ADDR	0X0803F804
#define AU2_BIAS_ADDR	0X0803F806

#define AU2_0DB_GAIN 		TCA6424_Port(Output_Port0,port_1,2,0)    //前置CH2增益  H:20dB  L:0dB
#define AU2_20DB_GAIN 	TCA6424_Port(Output_Port0,port_1,2,1)    //前置CH2增益  H:20dB  L:0dB
#define AU2_2V0_ON  	TCA6424_Port(Output_Port2,port_1,1,1)      //前置CH2 bias输出2V  H
#define AU2_2V0_OFF  	TCA6424_Port(Output_Port2,port_1,1,0)      //前置CH2 bias输出2V  H
#define AU2_2V7_ON 		TCA6424_Port(Output_Port2,port_0,1,1)      //前置CH2 bias输出2.7V  H
#define AU2_2V7_OFF 	TCA6424_Port(Output_Port2,port_0,1,0)      //前置CH2 bias输出2.7V  H
#define AU2_ICP_ON 		TCA6424_Port(Output_Port1,port_7,1,1)      //前置CH2 bias输出24V  H
#define AU2_ICP_OFF 	TCA6424_Port(Output_Port1,port_7,1,0)      //前置CH2 bias输出24V  H
#define MIC2_PRT_ON 		TCA6424_Port(Output_Port0,port_7,2,0)    //前置CH2输入电压保护继电器 H
#define MIC2_PRT_OFF 		TCA6424_Port(Output_Port0,port_7,2,1)    //前置CH2输入电压保护继电器 L
#define MIC2_CON_ON 		TCA6424_Port(Output_Port2,port_3,2,1)    //前置CH2麦克风识别保护继电器 H
#define MIC2_CON_OFF 		TCA6424_Port(Output_Port2,port_3,2,0)    //前置CH2麦克风识别保护继电器 L
/********************************前置通道3************************************/

#define AU3_ICP_EN 		PAin(10)      //前置CH3检测MIC插入信号  L

#define AU3_GAIN_ADDR	0X0803F808
#define AU3_BIAS_ADDR	0X0803F80A

#define AU3_0DB_GAIN 	  TCA6424_Port(Output_Port0,port_2,2,0)    //前置CH3增益  L:0dB
#define AU3_20DB_GAIN 	TCA6424_Port(Output_Port0,port_2,2,1)    //前置CH3增益  H:20dB  
#define AU3_2V0_ON  		TCA6424_Port(Output_Port1,port_0,1,1)      //前置CH3 bias输出2V  H
#define AU3_2V0_OFF  		TCA6424_Port(Output_Port1,port_0,1,0)      //前置CH3 bias输出2V  L
#define AU3_2V7_ON 			TCA6424_Port(Output_Port0,port_7,1,1)      //前置CH3 bias输出2.7V  H
#define AU3_2V7_OFF 		TCA6424_Port(Output_Port0,port_7,1,0)    //前置CH3 bias输出2.7V  L
#define AU3_ICP_ON 			TCA6424_Port(Output_Port0,port_6,1,1)      //前置CH3 bias输出24V  H
#define AU3_ICP_OFF 		TCA6424_Port(Output_Port0,port_6,1,0)    //前置CH3 bias输出24V  L
#define MIC3_PRT_ON 		TCA6424_Port(Output_Port1,port_0,2,0)      //前置CH3输入电压保护继电器 H
#define MIC3_PRT_OFF 		TCA6424_Port(Output_Port1,port_0,2,1)      //前置CH3输入电压保护继电器 L
#define MIC3_CON_ON 		TCA6424_Port(Output_Port2,port_4,2,1)      //前置CH3麦克风识别保护继电器 H
#define MIC3_CON_OFF 		TCA6424_Port(Output_Port2,port_4,2,0)      //前置CH3麦克风识别保护继电器 L

/********************************前置通道4************************************/

#define AU4_ICP_EN 		PAin(9)      //前置CH4检测MIC插入信号  L

#define AU4_GAIN_ADDR	0X0803F80C
#define AU4_BIAS_ADDR	0X0803F80E

#define AU4_0DB_GAIN 	  TCA6424_Port(Output_Port0,port_3,2,0)    //前置CH4增益  L:0dB
#define AU4_20DB_GAIN 	TCA6424_Port(Output_Port0,port_3,2,1)    //前置CH4增益  H:20dB  
#define AU4_2V0_ON  		TCA6424_Port(Output_Port1,port_3,1,1)      //前置CH4 bias输出2V  H
#define AU4_2V0_OFF  		TCA6424_Port(Output_Port1,port_3,1,0)      //前置CH4 bias输出2V  L
#define AU4_2V7_ON 			TCA6424_Port(Output_Port1,port_2,1,1)      //前置CH4 bias输出2.7V  H
#define AU4_2V7_OFF 		TCA6424_Port(Output_Port1,port_2,1,0)    //前置CH4 bias输出2.7V  L
#define AU4_ICP_ON 			TCA6424_Port(Output_Port1,port_1,1,1)      //前置CH4 bias输出24V  H
#define AU4_ICP_OFF 		TCA6424_Port(Output_Port1,port_1,1,0)    //前置CH4 bias输出24V  L
#define MIC4_PRT_ON 		TCA6424_Port(Output_Port1,port_1,2,0)      //前置CH4输入电压保护继电器 H
#define MIC4_PRT_OFF 		TCA6424_Port(Output_Port1,port_1,2,1)      //前置CH4输入电压保护继电器 L
#define MIC4_CON_ON 		TCA6424_Port(Output_Port2,port_5,2,1)      //前置CH4麦克风识别保护继电器 H
#define MIC4_CON_OFF 		TCA6424_Port(Output_Port2,port_5,2,0)      //前置CH4麦克风识别保护继电器 L

/********************************前置通道5************************************/

#define AU5_ICP_EN 		PAin(8)      //前置CH3检测MIC插入信号  L
#define ISEN1_IN_EN	 	PEout(6)      //前置CH3阻抗测试切换

#define AU5_GAIN_ADDR	0X0803F810
#define AU5_BIAS_ADDR	0X0803F812
#define AU5_ISEN_ADDR	0X0803F814

#define AU5_0DB_GAIN 	  TCA6424_Port(Output_Port0,port_4,2,0)    //前置CH5增益  L:0dB
#define AU5_20DB_GAIN 	TCA6424_Port(Output_Port0,port_4,2,1)    //前置CH5增益  H:20dB  
#define AU5_2V0_ON  		TCA6424_Port(Output_Port0,port_2,1,1)      //前置CH5 bias输出2V  H
#define AU5_2V0_OFF  		TCA6424_Port(Output_Port0,port_2,1,0)      //前置CH5 bias输出2V  L
#define AU5_2V7_ON 			TCA6424_Port(Output_Port0,port_1,1,1)      //前置CH5 bias输出2.7V  H
#define AU5_2V7_OFF 		TCA6424_Port(Output_Port0,port_1,1,0)    //前置CH5 bias输出2.7V  L
#define AU5_ICP_ON 			TCA6424_Port(Output_Port0,port_0,1,1)      //前置CH5 bias输出24V  H
#define AU5_ICP_OFF 		TCA6424_Port(Output_Port0,port_0,1,0)    //前置CH5 bias输出24V  L
#define MIC5_PRT_ON 		TCA6424_Port(Output_Port1,port_2,2,0)      //前置CH5输入电压保护继电器 H
#define MIC5_PRT_OFF 		TCA6424_Port(Output_Port1,port_2,2,1)      //前置CH5输入电压保护继电器 L
#define MIC5_CON_ON 		TCA6424_Port(Output_Port2,port_6,2,1)      //前置CH5麦克风识别保护继电器 H
#define MIC5_CON_OFF 		TCA6424_Port(Output_Port2,port_6,2,0)      //前置CH5麦克风识别保护继电器 L

/********************************前置通道6************************************/

#define AU6_ICP_EN 		PBin(11)      //前置CH4检测MIC插入信号  L
#define ISEN2_IN_EN	 	PBout(0)      //前置CH4阻抗测试切换

#define AU6_GAIN_ADDR	0X0803F816
#define AU6_BIAS_ADDR	0X0803F818
#define AU6_ISEN_ADDR	0X0803F81A

#define AU6_0DB_GAIN 	  TCA6424_Port(Output_Port0,port_5,2,0)    //前置CH6增益  L:0dB
#define AU6_20DB_GAIN 	TCA6424_Port(Output_Port0,port_5,2,1)    //前置CH6增益  H:20dB  
#define AU6_2V0_ON  		TCA6424_Port(Output_Port0,port_5,1,1)      //前置CH6 bias输出2V  H
#define AU6_2V0_OFF  		TCA6424_Port(Output_Port0,port_5,1,0)      //前置CH6 bias输出2V  L
#define AU6_2V7_ON 			TCA6424_Port(Output_Port0,port_4,1,1)      //前置CH6 bias输出2.7V  H
#define AU6_2V7_OFF 		TCA6424_Port(Output_Port0,port_4,1,0)    //前置CH6 bias输出2.7V  L
#define AU6_ICP_ON 			TCA6424_Port(Output_Port0,port_3,1,1)      //前置CH6 bias输出24V  H
#define AU6_ICP_OFF 		TCA6424_Port(Output_Port0,port_3,1,0)    //前置CH6 bias输出24V  L
#define MIC6_PRT_ON 		TCA6424_Port(Output_Port1,port_3,2,0)      //前置CH6输入电压保护继电器 H
#define MIC6_PRT_OFF 		TCA6424_Port(Output_Port1,port_3,2,1)      //前置CH6输入电压保护继电器 L
#define MIC6_CON_ON 		TCA6424_Port(Output_Port2,port_7,2,1)      //前置CH6麦克风识别保护继电器 H
#define MIC6_CON_OFF 		TCA6424_Port(Output_Port2,port_7,2,0)      //前置CH6麦克风识别保护继电器 L

/********************************功放通道1************************************/

#define PORT_AMP1_OUT  	PDin(12)      //功放CH1输出过载保护信号  L

#define AMP1_0DB_GAIN 	TCA6424_Port(Output_Port2,port_1,2,1)       //功放CH1增益  H:0dB  L:20dB
#define AMP1_20DB_GAIN 	TCA6424_Port(Output_Port2,port_1,2,0)       //功放CH1增益  H:0dB  L:20dB
#define AMP1_OVER_OFF 	TCA6424_Port(Output_Port1,port_7,2,0)       //功放CH1保护继电器使能信号  H-L
#define AMP1_OVER_ON 		TCA6424_Port(Output_Port1,port_7,2,1)      //功放CH1保护继电器使能信号  H-L

#define AMP1_GAIN_ADDR	0X0803F81C


/********************************功放通道2************************************/

#define PORT_AMP2_OUT  	PDin(15)      //功放CH2输出过载保护信号  L

#define AMP2_GAIN_ADDR	0X0803F81E

#define AMP2_0DB_GAIN 	TCA6424_Port(Output_Port2,port_0,2,1)       //功放CH2增益  H:0dB  L:20dB
#define AMP2_20DB_GAIN 	TCA6424_Port(Output_Port2,port_0,2,0)       //功放CH2增益  H:0dB  L:20dB
#define AMP2_OVER_OFF 	TCA6424_Port(Output_Port1,port_6,2,0)       //功放CH2保护继电器使能信号  H-L
#define AMP2_OVER_ON 		TCA6424_Port(Output_Port1,port_6,2,1)       //功放CH2保护继电器使能信号  H-L


#define IO_Config_ADDR		0X0803F820
#define IO_Output_ADDR		0X0803F822

/********************************设置是否显示麦克风模式************************************/
#define AU1_Microphone_ADDR		0X0803F824
#define AU2_Microphone_ADDR		0X0803F826
#define AU3_Microphone_ADDR		0X0803F828
#define AU4_Microphone_ADDR		0X0803F82A
#define AU5_Microphone_ADDR		0X0803F82C
#define AU6_Microphone_ADDR		0X0803F82E

/********************************TCA************************************/

#define TCA1_REG0_ADDR        0X0803F830
#define TCA1_REG1_ADDR        0X0803F832
#define TCA1_REG2_ADDR        0X0803F834
#define TCA2_REG0_ADDR        0X0803F836
#define TCA2_REG1_ADDR        0X0803F838
#define TCA2_REG2_ADDR        0X0803F83A

//#define IO2_ADDR		0X0803F818
//#define IO3_ADDR		0X0803F81A
//#define IO4_ADDR		0X0803F81C
//#define IO5_ADDR		0X0803F81E
//#define IO6_ADDR		0X0803F820
//#define IO7_ADDR		0X0803F822


#define XMOS_ADC1_ADDR		0X0803F830
#define XMOS_ADC2_ADDR		0X0803F832


//置位设置  --------------------------- -----------------
#define  Output_Port0  0x04
#define  Output_Port1  0x05
#define  Output_Port2  0x06

#define  port_0  0x00
#define  port_1  0x01
#define  port_2  0x02
#define  port_3  0x03
#define  port_4  0x04
#define  port_5  0x05
#define  port_6  0x06
#define  port_7  0x07


void TCA6424_Port_val(u8 port,u8 pin);

void TCA6424_Port(u8 reg,u8 port,u8 tca,u8 state);

void MICX_PRT_ON(struct _AU *au);
void MICX_PRT_OFF(struct _AU *au);
void AUX_0DB_GAIN(struct _AU *au);
void AUX_20DB_GAIN(struct _AU *au);
void MICX_CON_ON(struct _AU *au);
void MICX_CON_OFF(struct _AU *au);
void ISENX_IN_ON(struct _AU *au);
void ISENX_IN_OFF(struct _AU *au);
void AUX_2V0_ON(struct _AU *au);
void AUX_2V7_ON(struct _AU *au);
void AUX_ICP_ON(struct _AU *au);
void AUX_NONE_ON(struct _AU *au);
void AMPX_OVER_ON(struct _AMP *amp);
void AMPX_OVER_OFF(struct _AMP *amp);
void AMPX_0DB_GAIN(struct _AMP *amp);
void AMPX_20DB_GAIN(struct _AMP *amp);

#endif

