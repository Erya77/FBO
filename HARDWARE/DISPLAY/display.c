#include "display.h"


/*	�˵������ʾ
			���˵�Ч��ͼ�������

			Output , Input , TTL Control�ֳ��������������ʾ

			��Ţ١���Ϊ������Ӧλ��
										 ____________________________________
										|  Outout    |         Input         |
										|������������������������������������������������������������������������|
										|	AMP1:  ��   | mode��	  bias��  gian��|
										|	AMP2:  ��   | mode��  	bias��  gian��|
										|	LINE3: ��   | mode�� 	 	bias��  gian��|	
										| LINE4: ��   | mode��  	bias��  gian��|
										|					   | mode��  	bias��  gian��|									 
										|						 | mode��  	bias��  gian��|										 
										|������������������������������������������������������������������������|
										|__TTL_Control_______________________|
										|	Bits: 9	 8	 7  6  5  4	 3 	 2   1 |
										|	W/R:+5V GND										     |
										|_1/0:_______________________________|

*/		
void DrwaGui(void)
{
	int i,v;
	
	//OUTPUT,INPUT  ���⽥��׿�	
	GUI_DrawGradientH(5,7,310,27, GUI_BLUE, GUI_GRAY);
	
	// ���Ʒ����ʽ���з��� �� ARGB��ʽ��ɫ���壺0x00666666
	for(i=0;i<6;i++)
	{
		GUI_DrawGradientH(  5,29+20*i,  60,48+20*i,  0x00666666, 0x00666666);
		GUI_DrawGradientH( 61,29+20*i, 120,48+20*i,  0x00666666, 0x00666666);
		GUI_DrawGradientH(123,29+20*i, 180,48+20*i,  0x00666666, 0x00666666);
		GUI_DrawGradientH(181,29+20*i, 258,48+20*i,  0x00666666, 0x00666666);
		GUI_DrawGradientH(259,29+20*i, 310,48+20*i,  0x00666666, 0x00666666);
	}

	//TTL Control  ���⽥��׿�
	GUI_DrawGradientH(5,150,310,170, GUI_BLUE, GUI_GRAY);
	
	// ���Ʒ����ʽ���з��� �� ARGB��ʽ��ɫ���壺0x00666666
		for(i=0;i<11;i++)
	{
			for(v=0;v<3;v++)
		{	
				GUI_DrawGradientH(4+28*i,172+21*v,31+28*i,192+21*v, 0x00666666, 0x00666666);
																		// 4��31      160,184   172��192
																		// 4��31      185,209   193��213
																		// 4��31      210,234   214��234 
		}
	}
	
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);		//����ģʽ
	GUI_SetColor(GUI_YELLOW);								//���ñ�����ɫ
	GUI_SetFont(&GUI_Fontweiruan24);				//���ñ������壺΢��24  
	
	//OUTPUT
	GUI_DispStringAt("OUTPUT",  15, 6);
	//INPUT
	GUI_DispStringAt("INPUT",  190, 6);
	//TTL CONTROL
	GUI_DispStringAt("TTL Control",  15, 149);
	
 
	// OUTPUT
	GUI_SetFont(GUI_FONT_16_ASCII); 				//��������
	// AMP1
	GUI_DispStringAt("Amp 1",  12, 31);

	// AMP2
	GUI_DispStringAt("Amp 2",  12, 51);
	
	// LINE3
	GUI_DispStringAt("Line 3",  14, 71);
	GUI_DispStringAt("0 dB",    79, 71);
	
	// LINE4
	GUI_DispStringAt("Line 4",  14, 91);
	GUI_DispStringAt("0 dB",    79, 91);

	// IO
	GUI_DispStringAt("Bit",  8,   173);
	GUI_DispStringAt("9",  33+10, 173);
	GUI_DispStringAt("8",  61+10, 173);
	GUI_DispStringAt("7",  89+10, 173);
	GUI_DispStringAt("6",  117+10, 173);
	GUI_DispStringAt("5",  145+10, 173);
	GUI_DispStringAt("4",  173+10, 173);
	GUI_DispStringAt("3",  201+10, 173);
	GUI_DispStringAt("2",  229+10, 173);
	GUI_DispStringAt("1",  257+10, 173);
	GUI_DispStringAt("0",  285+10, 173);
	
	// W/R
	GUI_DispStringAt("W/R",  5, 216);
	GUI_DispStringAt("1/0",  5, 196);
	GUI_SetColor(GUI_RED);
	GUI_DispStringAt("+5V",  32, 196);
	GUI_DispStringAt("GND",  60, 196);
	
}

//��ѹ�ָ���ʾ
void Display_Aux_Overvol(struct _AU *au)
{
		GUI_SetColor(GUI_CYAN);
		if(au == &AU1)
		{
			if(au->mode_flag==1)
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
		else if(au == &AU2)
		{	
			if(au->mode_flag==1)
			{
			GUI_ClearRect(123, 49, 180, 68);
			GUI_DispStringAt("Mic 2",  135, 51);
			}
			else
			{				
			GUI_ClearRect(123, 49, 180, 68);
			GUI_DispStringAt("Line 2",  132, 51);
			}
		}
		else if(au == &AU3)
		{	
			if(au->mode_flag==1)
			{
			GUI_ClearRect(123, 69, 180, 88);
			GUI_DispStringAt("Mic 3",  135, 71);
			}
			else
			{				
			GUI_ClearRect(123, 69, 180, 88);
			GUI_DispStringAt("Line 3",  132, 71);
			}
		}
		else if(au == &AU4)
		{	
			if(au->mode_flag==1)
			{
			GUI_ClearRect(123, 89, 180, 108);
			GUI_DispStringAt("Mic 4",  135, 91);
			}
			else
			{				
			GUI_ClearRect(123, 89, 180, 108);
			GUI_DispStringAt("Line 4",  132, 91);
			}
		}
		else if(au == &AU5)
		{	
			if(au->mode_flag==1){
			GUI_ClearRect(123, 109, 180, 128);
			GUI_DispStringAt("Mic 5",  135, 111);
			}
			else if(au->mode_flag==2){				
			GUI_ClearRect(123, 109, 180, 128);
			GUI_DispStringAt("Imp 5 ",  135, 111);
			}
			else{
				GUI_ClearRect(123, 109, 180, 128);
				GUI_DispStringAt("Line 5",  132, 111);
			}
	
	
		}
		else if(au == &AU6)
		{	
			if(au->mode_flag==1)
			{
			GUI_ClearRect(123, 129, 180, 148);
			GUI_DispStringAt("Mic 6",  135, 131);
			}
			else if(au->mode_flag==2)
			{				
			GUI_ClearRect(123, 129, 180, 148);
			GUI_DispStringAt("Imp 6 ",  135, 131);
			}
			else{
				GUI_ClearRect(123, 129, 180, 148);
				GUI_DispStringAt("Line 6",  132, 131);
			}
		}
}

//MODE��ʾ
void Display_Aux_Mode(struct _AU *au)
{
		GUI_SetColor(GUI_CYAN);
		if(au == &AU1)
		{
			if(au->mode_flag==0)
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
		else if(au == &AU2)
		{	
			if(au->mode_flag==0)
			{
			GUI_ClearRect(123, 49, 180, 68);
			GUI_DispStringAt("Mic 2",  135, 51);
			}
			else
			{				
			GUI_ClearRect(123, 49, 180, 68);
			GUI_DispStringAt("Line 2",  132, 51);
			}
		}
		else if(au == &AU3)
		{	
			if(au->mode_flag==0)
			{
			GUI_ClearRect(123, 69, 180, 88);
			GUI_DispStringAt("Mic 3",  135, 71);
			}
			else
			{				
			GUI_ClearRect(123, 69, 180, 88);
			GUI_DispStringAt("Line 3",  132, 71);
			}
		}
		else if(au == &AU4)
		{	
			if(au->mode_flag==0)
			{
			GUI_ClearRect(123, 89, 180, 108);
			GUI_DispStringAt("Mic 4",  135, 91);
			}
			else
			{				
			GUI_ClearRect(123, 89, 180, 108);
			GUI_DispStringAt("Line 4",  132, 91);
			}
		}
		else if(au == &AU5)
		{	
			if((u8)au->Microphone&0x01){
			GUI_ClearRect(123, 109, 180, 128);
			GUI_DispStringAt("Mic 5",  135, 111);
			}
			else if(au->i_sen==1){				
			GUI_ClearRect(123, 109, 180, 128);
			GUI_DispStringAt("Imp 5 ",  135, 111);
			}
			else{
				GUI_ClearRect(123, 109, 180, 128);
				GUI_DispStringAt("Line 5",  132, 111);
			}
	
	
		}
		else if(au == &AU6)
		{	
			if((u8)au->Microphone&0x01)
			{
			GUI_ClearRect(123, 129, 180, 148);
			GUI_DispStringAt("Mic 6",  135, 131);
			}
			else if(au->i_sen==1)
			{				
			GUI_ClearRect(123, 129, 180, 148);
			GUI_DispStringAt("Imp 6 ",  135, 131);
			}
			else{
				GUI_ClearRect(123, 129, 180, 148);
				GUI_DispStringAt("Line 6",  132, 131);
			}
		}
}

void Display_Aux_char(struct _AU *au,const char *gain)
{
		u8 i;
	
		if(au == &AU1)
		i = 0;
		else if(au == &AU2)
		i = 20;
		else if(au == &AU3)
		i = 40;
		else if(au == &AU4)
		i = 60;
		else if(au == &AU5)
		i = 80;
		else if(au == &AU6)
		i = 100;
		
		 // ��ʾ����ֵ��ʹ�ô���������ַ���
    if (strcmp(gain, "0dB") == 0) {
				GUI_SetColor(GUI_CYAN);
				GUI_ClearRect(259, 29+i, 310, 48+i);	
        GUI_DispStringAt(" 0 dB  ", 270, 31+i);
    } else if (strcmp(gain, "20dB") == 0) {
				GUI_SetColor(GUI_CYAN);
				GUI_ClearRect(259, 29+i, 310, 48+i);	
        GUI_DispStringAt("20 dB", 267, 31+i);
    } else if (strcmp(gain, "OVER") == 0) {//��ѹ��ʾ
				GUI_SetColor(GUI_RED);
				GUI_ClearRect(123, 29+i, 180, 48+i);
				GUI_DispStringAt("OVER",  130, 31+i);
		} else if (strcmp(gain, "2.0V") == 0) {//
				GUI_SetColor(GUI_CYAN);
				GUI_DrawGradientH(181, 29+i, 258, 48+i,0x00666666,0x00666666);		
				GUI_DispStringAt("Volt 2.0V",  190, 31+i);
		} else if (strcmp(gain, "2.7V") == 0) {//
				GUI_SetColor(GUI_CYAN);
				GUI_DrawGradientH(181, 29+i, 258, 48+i,0x00666666,0x00666666);		
				GUI_DispStringAt("Volt 2.7V",  190, 31+i);
		} else if (strcmp(gain, "ICP") == 0) {//
				GUI_SetColor(GUI_CYAN);
				GUI_DrawGradientH(181, 29+i, 258, 48+i,0x00666666,0x00666666);
				//GUI_ClearRect(181, 29+i, 258, 48+i);			
				GUI_DispStringAt("CCP(24V)",  190, 31+i);
		} else if (strcmp(gain, "ICP-BACK") == 0) {//
				GUI_SetColor(GUI_CYAN);
				GUI_DrawGradientH(181, 29+i, 258, 48+i,0x00800000,0x00800000);			
				GUI_DispStringAt("CCP(24V)",  190, 31+i);
 		} else if (strcmp(gain, "NONE") == 0) {//
				GUI_SetColor(GUI_CYAN);
				GUI_DrawGradientH(181, 29+i, 258, 48+i,0x00666666,0x00666666);			
				GUI_DispStringAt("None",  205, 31+i);
		}

}
void Display_Ampx_char(struct _AMP *amp,const char *gain)
{
		u8 i;
	
		if(amp == &AMP1)
		i = 0;
		else if(amp == &AMP2)
		i = 20;
		
		 // ��ʾ����ֵ��ʹ�ô���������ַ���
    if (strcmp(gain, "OVER") == 0) {
			GUI_SetColor(GUI_RED);
			GUI_ClearRect(5, 29+i, 60, 48+i);
			GUI_DispStringAt("OVER", 15, 31+i);
    } else if (strcmp(gain, "20dB") == 0) {
			GUI_SetColor(GUI_CYAN);
			GUI_ClearRect(61, 29+i, 120, 48+i);
			GUI_DispStringAt("20 dB",  72, 31+i);
    } else if (strcmp(gain, "0dB") == 0) {
			GUI_SetColor(GUI_CYAN);
			GUI_ClearRect(61, 29+i, 120, 48+i);
			GUI_DispStringAt("0 dB  ",  79, 31+i);
    }
	
}
void Display_Ampx_Out(struct _AMP *amp)
{
		GUI_SetColor(GUI_YELLOW);
		if(amp == &AMP1)
		{
			GUI_ClearRect(5, 29, 60, 48);
			GUI_DispStringAt("AMP 1",  12, 31);
		}
		else if(amp == &AMP2)
		{
			GUI_ClearRect(5, 49, 60, 68);
			GUI_DispStringAt("AMP 2",  12, 51);
		}
		
}
