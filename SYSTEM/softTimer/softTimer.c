#include "softTimer.h"
#include "stdio.h"
#include "main.h"

u8 protect3_flag;


u8 Link1_Flag = 5;  //模式状态标志位，0为line ，1为Microphone  ，2为Impedance
u8 Link2_Flag = 5;
u8 Link3_Flag = 5;
u8 Link4_Flag = 5;
u8 Link5_Flag = 5;
u8 Link6_Flag = 5;

extern u8 AMP1_Change_Flag;
extern u8 AMP2_Change_Flag;
extern u8 IO_Change_Flag;

volatile u32 tick_Cnt=0;	//程序时间标记
softTimer_typedef softTimer[Timer_NUM];

void softTimer_config(u8 num,u32 delay,u8 state,handler_typedef* handler)
{
		softTimer[num].state=state;
		if(softTimer[num].state==0)
			softTimer[num].times=0;
		if(delay!=0)
			softTimer[num].timeout=tick_Cnt+delay;
		softTimer[num].handler=handler;	//回调函数
}

void softTimer_updata()
{	
	u8 num;
	for(num=1;num<=Timer_NUM;num++)
	{
		if(softTimer[num].state==0)
			continue;
		else if(softTimer[num].state==1)
		{
			if(softTimer[num].timeout<=tick_Cnt)
			{
				softTimer[num].state=2;
				softTimer[num].times++;
				if(softTimer[num].handler!=0)
					softTimer[num].handler();
			}
		}
			
	}
}

u8 softTimer_cheak_state(u8 num)
{
	return softTimer[num].state;

}

void softTimer_handler0()
{	
	printf("%d\r\n",tick_Cnt);
}

void softTimer_handler1()
{
	if(PORT_AMP1_OUT==0)
	{
		softTimer_config(1,600,1,softTimer_handler1);
	}
	else
	{
		AMP1_OVER_OFF;
		GUI_SetColor(GUI_YELLOW);
		if(AMP1.gain)
		{
			GUI_ClearRect(5, 29, 60, 48);
			GUI_DispStringAt("AMP 1",  12, 31);
		}else{
			GUI_ClearRect(5, 29, 60, 48);
			GUI_DispStringAt("AMP 1",  12, 31);
		}
//		GUI_DispStringAt("          ",  60, 140);
	}
}

void softTimer_handler2()
{
	GUI_SetColor(GUI_RED);
	if(softTimer[1].state==1)
	{
		if(softTimer[2].times%2==0)
			GUI_DispStringAt("OVER",  75, 35);
		else
		{
			GUI_SetColor(GUI_CYAN);
			if(AMP1.gain)
		{
			GUI_ClearRect(61, 29, 120, 48);
			GUI_DispStringAt("20 dB",  72, 31);
		}else{
			GUI_ClearRect(61, 29, 120, 48);
			GUI_DispStringAt("0 dB  ",  79, 31);
		}
		}
//			GUI_DispStringAt("          ",  60, 140);
		
		softTimer_config(2,75,1,softTimer_handler2);
	}
	else
	{
		GUI_SetColor(GUI_CYAN);
		if(AMP1.gain)
		{
			GUI_ClearRect(61, 29, 120, 48);
			GUI_DispStringAt("20 dB",  72, 31);
		}else{
			GUI_ClearRect(61, 29, 120, 48);
			GUI_DispStringAt("0 dB  ",  79, 31);
		}
	}
//		GUI_DispStringAt("          ",  60, 140);
	
}

void softTimer_handler3()
{
	if(PORT_AMP2_OUT==0)
	{
		softTimer_config(3,600,1,softTimer_handler3);
		
	}
	else
	{
		AMP2_OVER_OFF;
		GUI_SetColor(GUI_YELLOW);
		if(AMP2.gain)
		{
			GUI_ClearRect(5, 49, 60, 68);
			GUI_DispStringAt("AMP 2",  12, 51);
		}else{
			GUI_ClearRect(5, 49, 60, 68);
			GUI_DispStringAt("AMP 2",  12, 51);
		}
//		GUI_DispStringAt("          ",  220, 140);
	}
}

void softTimer_handler4()
{
	GUI_SetColor(GUI_RED);
	if(softTimer[3].state==1)
	{
		if(softTimer[4].times%2==0)
			GUI_DispStringAt("OVER",  75, 51);
		else
		{
			GUI_SetColor(GUI_CYAN);
					if(AMP2.gain)
		{
			GUI_ClearRect(61, 49, 120, 68);
			GUI_DispStringAt("20 dB",  72, 51);
		}else{
			GUI_ClearRect(61, 49, 120, 68);
			GUI_DispStringAt("0 dB  ",  79, 51);
		}
	}
//			GUI_DispStringAt("          ",  220, 140);
		
		softTimer_config(4,75,1,softTimer_handler4);
	}
	else
	{
		GUI_SetColor(GUI_CYAN);
				if(AMP2.gain)
		{
			GUI_ClearRect(61, 49, 120, 68);
			GUI_DispStringAt("20 dB",  72, 51);
		}else{
			GUI_ClearRect(61, 49, 120, 68);
			GUI_DispStringAt("0 dB  ",  79, 51);
		}
	}
}

void softTimer_handler5()
{
	pca9554_Read_Process(0x00);
	if(IO_STA[2]!=IIC_BUF[0])
	{
		IO_STA[2]=IIC_BUF[0];
		IO_Change_Flag=1;
		//printf("BUF=%x\r\n",IO_STA[2]);		
	}
	softTimer[5].state=1;
	softTimer[5].timeout=tick_Cnt+10;
}

void softTimer_handler6()
{
		MIC1_PRT_OFF;
	GUI_SetColor(GUI_CYAN);
	if(Link1_Flag==1)
		{
		GUI_ClearRect(123, 29, 180, 48);
		GUI_DispStringAt("Mic 1",  135, 31);
		}
		else
		{				
					GUI_ClearRect(123, 29, 180, 48);
		GUI_DispStringAt("Line 1",  132, 31);
		}
}

void softTimer_handler7()
{
	MIC2_PRT_OFF;
	GUI_SetColor(GUI_CYAN);

	if(Link2_Flag==1)
	{
	GUI_ClearRect(123, 49, 180, 68);
	GUI_DispStringAt("Mic 2",  135, 51);
	}
	else{				
		GUI_ClearRect(123, 49, 180, 68);
	GUI_DispStringAt("Line 2",  132, 51);
	}
		
//	GUI_DispStringAt("         ",  50, 50);
}

void softTimer_handler8()
{
	if(protect3_flag==1)
	{MIC3_PRT_OFF;
	protect3_flag=0;}
	GUI_SetColor(GUI_CYAN);

	if(Link3_Flag==1)
			{
			GUI_ClearRect(123, 69, 180, 88);
			GUI_DispStringAt("Mic 3",  135, 71);
			}
			else{				
				GUI_ClearRect(123, 69, 180, 88);
			GUI_DispStringAt("Line 3",  132, 71);
			}
		
//	GUI_DispStringAt("         ",  50, 50);
}

void softTimer_handler9()
{
	MIC4_PRT_OFF;
	GUI_SetColor(GUI_CYAN);

	if(Link4_Flag==1)
			{
			GUI_ClearRect(123, 89, 180, 108);
			GUI_DispStringAt("Mic 4",  135, 91);
			}
			else{				
				GUI_ClearRect(123, 89, 180, 108);
			GUI_DispStringAt("Line 4",  132, 91);
			}
		
//	GUI_DispStringAt("         ",  50, 50);
}

void softTimer_handler10()
{
	MIC5_PRT_OFF;
		GUI_SetColor(GUI_CYAN);

		if(Link5_Flag ==1){
		GUI_ClearRect(123, 109, 180, 128);
		GUI_DispStringAt("Mic 5",  135, 111);
		}else if(Link5_Flag==2)
		{
			GUI_ClearRect(123, 109, 180, 128);
			GUI_DispStringAt("Imp 5 ",  135, 111);
		}else{
				GUI_ClearRect(123, 109, 180, 128);
				GUI_DispStringAt("Line 5",  132, 111);
	
	}
//	GUI_DispStringAt("         ",  50, 75);
}

void softTimer_handler11()
{
	MIC6_PRT_OFF;
			GUI_SetColor(GUI_CYAN);
		if(Link6_Flag ==1){
		GUI_ClearRect(123, 129, 180, 148);
		GUI_DispStringAt("Mic 6",  135, 131);
		}else if(Link6_Flag==2)
		{
			GUI_ClearRect(123, 129, 180, 148);
			GUI_DispStringAt("Imp 6 ",  135, 131);
		}else{
				GUI_ClearRect(123, 129, 180, 148);
				GUI_DispStringAt("Line 6",  132, 131);
		}

//	GUI_DispStringAt("         ",  50, 100);
}
