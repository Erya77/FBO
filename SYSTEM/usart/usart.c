
//#include "sys.h"
#include "usart.h"
#include "dispose.h"
//#include "timer.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((UART4->SR&0X40)==0);//ѭ������,ֱ���������   
    UART4->DR = (u8) ch;      
	return ch;
}
#endif 

void uart4_send_str(char* pbuf)
{
//	while(pbuf && *pbuf)
//	{
//		USART_SendData(USART1,*pbuf++);
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
//	}
	
	while(*pbuf!='\0')
	{
		while((UART4->SR&0X40)==0);//ѭ������,ֱ���������
		UART4->DR = (u8) *pbuf++;
		 
	}		
    
}
 
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	


u8 cmd_flag=0;		//�����ַ����ı��
u8 Uart4_buffer_save[20] = {0};	//������λ������������
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u16 USART_RX_STA=0;       //����״̬���	 
u16 USART_RX_CNT=0;			//���յ��ֽ���	

 u16 a[4]  = {0,1,2,3};
 u16 *p = &a[0];

extern u16 uart4_time;

u8 AU1_Change_Flag=0;
u8 AU2_Change_Flag=0;
u8 AU3_Change_Flag=0;
u8 AU4_Change_Flag=0;
u8 AU5_Change_Flag=0;
u8 AU6_Change_Flag=0;
u8 AMP1_Change_Flag=0;
u8 AMP2_Change_Flag=0;
u8 IO_Change_Flag=0;

// 0x55 0x01 0x01 0x01 0x66
//ָ��
u8 Test[]={0x55,0x00,0x00,};

u8 Cmd_AU1_Gain[]={0x55,0x01,0x01,};
u8 Cmd_AU1_Bias[]={0x55,0x01,0x02,};
u8 Cmd_AU1_Microphone[]={0x55,0x01,0x04,};
u8 Cmd_AU1_Line[]={0x55,0x01,0x05,};

u8 Cmd_AU2_Gain[]={0x55,0x02,0x01,};
u8 Cmd_AU2_Bias[]={0x55,0x02,0x02,};
u8 Cmd_AU2_Microphone[]={0x55,0x02,0x04,};
u8 Cmd_AU2_Line[]={0x55,0x02,0x05,};

u8 Cmd_AU3_Gain[]={0x55,0x03,0x01,};
u8 Cmd_AU3_Bias[]={0x55,0x03,0x02,};
u8 Cmd_AU3_Microphone[]={0x55,0x03,0x04,};
u8 Cmd_AU3_Line[]={0x55,0x03,0x05,};

u8 Cmd_AU4_Gain[]={0x55,0x04,0x01,};
u8 Cmd_AU4_Bias[]={0x55,0x04,0x02,};
u8 Cmd_AU4_Microphone[]={0x55,0x04,0x04,};
u8 Cmd_AU4_Line[]={0x55,0x04,0x05,};

u8 Cmd_AU5_Gain[]={0x55,0x05,0x01,};
u8 Cmd_AU5_Bias[]={0x55,0x05,0x02,};
u8 Cmd_AU5_ISEN[]={0x55,0x05,0x03,};
u8 Cmd_AU5_Microphone[]={0x55,0x05,0x04,};
u8 Cmd_AU5_Line[]={0x55,0x05,0x05,};

u8 Cmd_AU6_Gain[]={0x55,0x06,0x01,};
u8 Cmd_AU6_Bias[]={0x55,0x06,0x02,};
u8 Cmd_AU6_ISEN[]={0x55,0x06,0x03,};
u8 Cmd_AU6_Microphone[]={0x55,0x06,0x04,};
u8 Cmd_AU6_Line[]={0x55,0x06,0x05,};

u8 Cmd_AMP1_Gain[]={0x55,0x07,0x01,};
u8 Cmd_AMP2_Gain[]={0x55,0x08,0x01,};

u8 Cmd_IO_Config[]={0x55,0x09,0x01,};
u8 Cmd_IO_Output[]={0x55,0x09,0x02,};
u8 Cmd_IO_Input[]={0x55,0x09,0x03,};

u8 Cmd_Get_State[]={0x55,0x99,0x00,};

u8 Cmd_Xmos_adc1[]={0x55,XMOS_ADC1_ADDRESS,};
u8 Cmd_Xmos_adc2[]={0x55,XMOS_ADC2_ADDRESS,};

//ָ�����
u8 *ALL_CMD_CODE[] = 
{
	Test, Cmd_AU1_Gain, Cmd_AU1_Bias, Cmd_AU2_Gain, Cmd_AU2_Bias,	Cmd_AU3_Gain, Cmd_AU3_Bias, Cmd_AU4_Gain, Cmd_AU4_Bias, 
	Cmd_AU5_Gain, Cmd_AU5_Bias,Cmd_AU6_Gain, Cmd_AU6_Bias, 	Cmd_AMP1_Gain, Cmd_AMP2_Gain, Cmd_IO_Config, Cmd_IO_Output,
	 Cmd_IO_Input, Cmd_AU5_ISEN, Cmd_AU6_ISEN,Cmd_Get_State,	Cmd_AU1_Microphone,Cmd_AU2_Microphone,Cmd_AU3_Microphone,
	Cmd_AU4_Microphone,Cmd_AU5_Microphone,Cmd_AU6_Microphone,
	Cmd_AU1_Line,Cmd_AU2_Line,Cmd_AU3_Line,Cmd_AU4_Line,Cmd_AU5_Line,Cmd_AU6_Line,
	Cmd_Xmos_adc1,Cmd_Xmos_adc2,
	"cmd_end"	//ָ�������־������ָ�����
};
  
void uart4_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//ʹ��USART4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//ʹ��GPIOCʱ��
  
	//UART4_TX   GPIOC.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PC.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.10
   
  //UART4_RX	  GPIOC.11��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PC11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.11  

  //Uart4 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(UART4, &USART_InitStructure); //��ʼ������4
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(UART4, ENABLE);                    //ʹ�ܴ���4 

}
void UART4_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(UART4);	//��ȡ���յ�������
#if USART_Need_Line			
		if((USART_RX_STA&0x8000)==0)//����δ���
			{
			if(USART_RX_STA&0x4000)//���յ���0x0d
				{
				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
				else USART_RX_STA|=0x8000;	//��������� 
				}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}
#else
		//Change_Case(&Res);	//��д��ĸת��Сд��ĸ
		USART_RX_BUF[USART_RX_STA]=Res;
		uart4_time=0;
		USART_RX_STA++;
		if(USART_RX_STA>USART_REC_LEN)USART_RX_STA=USART_REC_LEN;	
#endif   		 
    } 
} 

/*
*********************************************************************************************************
*	�� �� ��: PC_CMD_PRO
*	����˵��: ��λ�����ݽ����ж�	
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void PC_CMD_PRO(void)
{
	 u8 j;
	 u8 k;  
	 u16 len;	
	 //u16 times=0;
#if USART_Need_Line	
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			cmh_memcpyn(Uart4_buffer_save, USART_RX_BUF,len);
			for(k=0;k<COM_NUM;k++)
			{
				if(cmh_strcmp(ALL_CMD_CODE[k],Uart4_buffer_save,(uint8_t)len))
				{
					cmd_flag = ++k;//����k+1 ����com_flag=k
					break;
				}
			}
			//�����������/
			for(j=0;j<USART_REC_LEN;j++)
			{
				USART_RX_BUF[j]=0;
			}
			// �������״̬
			USART_RX_STA=0;			
		}
#else
		if(uart4_time>2)        //10ms���ղ���c���ݾ���Ϊ���ս���
		{		
			uart4_time=0;			
			len=USART_RX_STA;//�õ��˴ν��յ������ݳ���
			cmh_memcpyn(Uart4_buffer_save, USART_RX_BUF,len);
			USART_RX_STA=0;
			for(k=0;k<COM_NUM;k++)
			{
				if(k<=32)
				{
						if(cmh_strcmp(ALL_CMD_CODE[k],Uart4_buffer_save,3))		//ֻ�Ƚ�ǰ3���ֽ�����
					{
						if(Uart4_buffer_save[4]==0x66)	//�ж�ָ�������־
							cmd_flag = ++k;//����k+1 ����com_flag=k
						break;
					}
				}
			  else
				{
					if(cmh_strcmp(ALL_CMD_CODE[k],Uart4_buffer_save,2))		//ֻ�Ƚ�ǰ3���ֽ�����
					{
						if(Uart4_buffer_save[3]==0x66)	//�ж�ָ�������־
							cmd_flag = ++k;//����k+1 ����com_flag=k
						break;
					}
				}

				if(cmh_strcmp(ALL_CMD_CODE[k],"cmd_end",(uint8_t)strlen((char *)ALL_CMD_CODE[k])))
					break;
				
				
//				if(cmh_strcmp(ALL_CMD_CODE[k],Uart4_buffer_save,(uint8_t)strlen((char *)ALL_CMD_CODE[k])))
//				{
//					cmd_flag = ++k;//����k+1 ����com_flag=k
//					break;
//				}				

//				if(cmh_strcmp(ALL_CMD_CODE[k],"cmd_end",(uint8_t)strlen((char *)ALL_CMD_CODE[k])))
//					break;

			}
			//�����������/
			for(j=0;j<USART_REC_LEN;j++)
			{
				USART_RX_BUF[j]=0;
			}
			
			
			
			
			// �������״̬
			USART_RX_STA=0;			
		}
#endif		
}

u16 data;
u16 data1;
void Data_Process()
{
	data=Uart4_buffer_save[3];
	data1=Uart4_buffer_save[2];

}

void Get_state()
{

	
	printf("Version model : PAI662-1.0_20230908 \r\n");	
	printf("AU1_gain %x\r\n",AU1.gain);
	printf("AU1_bias %x\r\n",AU1.bias);
	printf("AU1_mic %x\r\n",AU1.mic_in);
	printf("AU1_vol_protect %x\r\n",AU1.vol_protect);
		
	printf("AU2_gain %x\r\n",AU2.gain);
	printf("AU2_bias %x\r\n",AU2.bias);
	printf("AU2_mic %x\r\n",AU2.mic_in);
	printf("AU2_vol_protect %x\r\n",AU2.vol_protect);
		
	printf("AU3_gain %x\r\n",AU3.gain);
	printf("AU3_bias %x\r\n",AU3.bias);
	printf("AU3_mic %x\r\n",AU3.mic_in);
	printf("AU3_vol_protect %x\r\n",AU3.vol_protect);
		
	printf("AU4_gain %x\r\n",AU4.gain);
	printf("AU4_bias %x\r\n",AU4.bias);
	printf("AU4_mic %x\r\n",AU4.mic_in);
	printf("AU4_vol_protect %x\r\n",AU4.vol_protect);
	
	printf("AU5_gain %x\r\n",AU5.gain);
	printf("AU5_bias %x\r\n",AU5.bias);
	printf("AU5_mic %x\r\n",AU5.mic_in);
	printf("AU5_isen %x\r\n",AU5.i_sen);
	printf("AU5_vol_protect %x\r\n",AU5.vol_protect);
	
	printf("AU6_gain %x\r\n",AU6.gain);
	printf("AU6_bias %x\r\n",AU6.bias);
	printf("AU6_mic %x\r\n",AU6.mic_in);	
	printf("AU6_isen %x\r\n",AU6.i_sen);
	printf("AU6_vol_protect %x\r\n",AU6.vol_protect);
	
	printf("AMP1_gain %x\r\n",AMP1.gain);
	printf("AMP1_overload %x\r\n",AMP1.overload);
	
	printf("AMP2_gain %x\r\n",AMP2.gain);
	printf("AMP2_overload %x\r\n",AMP2.overload);
	
	printf("IO_config %x\r\n",IO_STA[0]);
	printf("IO_output %x\r\n",IO_STA[1]);
	printf("IO_input %x\r\n",IO_STA[2]);
	
	printf("Link1_Flag %x\r\n",AU1.mode_flag);
	printf("Link2_Flag %x\r\n",AU2.mode_flag);
	printf("Link3_Flag %x\r\n",AU3.mode_flag);
	printf("Link4_Flag %x\r\n",AU4.mode_flag);
	printf("Link5_Flag %x\r\n",AU5.mode_flag);
	printf("Link6_Flag %x\r\n",AU6.mode_flag);

}

/*
*********************************************************************************************************
*	�� �� ��: PC_CMD_CTL
*	����˵��: ���ڽ��յ�ָ���жϺ��ڲ����׶���	
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void PC_CMD_CTL(void)
{
//	Test, Cmd_AU1_Gain, Cmd_AU1_Bias, Cmd_AU2_Gain, Cmd_AU2_Bias,	Cmd_AU3_Gain, Cmd_AU3_Bias, Cmd_AU4_Gain, Cmd_AU4_Bias, 
//	Cmd_AU5_Gain, Cmd_AU5_Bias,Cmd_AU6_Gain, Cmd_AU6_Bias, 	Cmd_AMP1_Gain, Cmd_AMP2_Gain, Cmd_IO_Config, Cmd_IO_Output,
//	 Cmd_IO_Input, Cmd_AU5_ISEN, Cmd_AU6_ISEN,Cmd_Get_State,	Cmd_AU1_Microphone,Cmd_AU2_Microphone,Cmd_AU3_Microphone,
//	Cmd_AU4_Microphone,Cmd_AU5_Microphone,Cmd_AU6_Microphone,
//	Cmd_AU1_Line,Cmd_AU2_Line,Cmd_AU3_Line,Cmd_AU4_Line,Cmd_AU5_Line,Cmd_AU6_Line,
//	"cmd_end"	//ָ�������־������ָ�����
	
	PC_CMD_PRO();
	if(cmd_flag)
		Data_Process();
	switch(cmd_flag)
	{
		//case 0:uart4_send_str((char *)Uart4_buffer_save);cmd_flag=0;break;
//		case 1:	AU1.input_voltage = Get_Adc_Average(10);printf("CH1: %f\r\n",AU1.input_voltage);
//						AU2.input_voltage = Get_Adc_Average(11);printf("CH2: %f\r\n",AU2.input_voltage);
//						AU3.input_voltage = Get_Adc_Average(12);printf("CH3: %f\r\n",AU3.input_voltage);
//						AU4.input_voltage = Get_Adc_Average(13);printf("CH4: %f\r\n",AU4.input_voltage);
//						AU5.input_voltage = Get_Adc_Average(1);printf("CH5: %f\r\n",AU5.input_voltage);
//						AU6.input_voltage = Get_Adc_Average(2);printf("CH6: %f\r\n",AU6.input_voltage);
//						cmd_flag=0;break;
		
		//Cmd_AU1_Gain
		case 2:AU1_Change_Flag=1;STMFLASH_Write(AU1_GAIN_ADDR,&data,1);STMFLASH_Read(AU1_GAIN_ADDR,&AU1.gain,1);cmd_flag=0;break;
		//Cmd_AU1_Bias
		case 3:AU1_Change_Flag=1;STMFLASH_Write(AU1_BIAS_ADDR,&data,1);STMFLASH_Read(AU1_BIAS_ADDR,&AU1.bias,1);cmd_flag=0;break;
		//Cmd_AU2_Gain
		case 4:AU2_Change_Flag=1;STMFLASH_Write(AU2_GAIN_ADDR,&data,1);STMFLASH_Read(AU2_GAIN_ADDR,&AU2.gain,1);cmd_flag=0;break;
		//Cmd_AU2_Bias
		case 5:AU2_Change_Flag=1;STMFLASH_Write(AU2_BIAS_ADDR,&data,1);STMFLASH_Read(AU2_BIAS_ADDR,&AU2.bias,1);cmd_flag=0;break;
		//Cmd_AU3_Gain
		case 6:AU3_Change_Flag=1;STMFLASH_Write(AU3_GAIN_ADDR,&data,1);STMFLASH_Read(AU3_GAIN_ADDR,&AU3.gain,1);cmd_flag=0;break;
		//Cmd_AU3_Bias
		case 7:AU3_Change_Flag=1;STMFLASH_Write(AU3_BIAS_ADDR,&data,1);STMFLASH_Read(AU3_BIAS_ADDR,&AU3.bias,1);cmd_flag=0;break;
		//Cmd_AU4_Gain
		case 8:AU4_Change_Flag=1;STMFLASH_Write(AU4_GAIN_ADDR,&data,1);STMFLASH_Read(AU4_GAIN_ADDR,&AU4.gain,1);cmd_flag=0;break;
		//Cmd_AU4_Bias
		case 9:AU4_Change_Flag=1;STMFLASH_Write(AU4_BIAS_ADDR,&data,1);STMFLASH_Read(AU4_BIAS_ADDR,&AU4.bias,1);cmd_flag=0;break;
		//Cmd_AU5_Gain
		case 10:AU5_Change_Flag=1;STMFLASH_Write(AU5_GAIN_ADDR,&data,1);STMFLASH_Read(AU5_GAIN_ADDR,&AU5.gain,1);cmd_flag=0;break;
		//Cmd_AU5_Bias
		case 11:AU5_Change_Flag=1;STMFLASH_Write(AU5_BIAS_ADDR,&data,1);STMFLASH_Read(AU5_BIAS_ADDR,&AU5.bias,1);cmd_flag=0;break;
		//Cmd_AU6_Gain
		case 12:AU6_Change_Flag=1;STMFLASH_Write(AU6_GAIN_ADDR,&data,1);STMFLASH_Read(AU6_GAIN_ADDR,&AU6.gain,1);cmd_flag=0;break;
		//Cmd_AU6_Bias
		case 13:AU6_Change_Flag=1;STMFLASH_Write(AU6_BIAS_ADDR,&data,1);STMFLASH_Read(AU6_BIAS_ADDR,&AU6.bias,1);cmd_flag=0;break;
		//Cmd_AMP1_Gain
		case 14:AMP1_Change_Flag=1;STMFLASH_Write(AMP1_GAIN_ADDR,&data,1);STMFLASH_Read(AMP1_GAIN_ADDR,&AMP1.gain,1);cmd_flag=0;break;
		//Cmd_AMP2_Gain
		case 15:AMP2_Change_Flag=1;STMFLASH_Write(AMP2_GAIN_ADDR,&data,1);STMFLASH_Read(AMP2_GAIN_ADDR,&AMP2.gain,1);cmd_flag=0;break;
		//Cmd_IO_Config
		case 16:IO_Change_Flag=1;
						STMFLASH_Write(IO_Config_ADDR,&data,1);
						STMFLASH_Read(IO_Config_ADDR,&IO_STA[0],1);
						pca9554_Write_Process(0x03,IO_STA[0]);cmd_flag=0;break;
		//Cmd_IO_Output
		case 17:IO_Change_Flag=1;STMFLASH_Write(IO_Output_ADDR,&data,1);STMFLASH_Read(IO_Output_ADDR,&IO_STA[1],1);
						pca9554_Write_Process(0x01,IO_STA[1]);cmd_flag=0;break;
		//Cmd_IO_Input
		case 18:pca9554_Read_Process(0x00);IO_STA[2]=IIC_BUF[0];printf("BUF=%x\r\n",IO_STA[2]);cmd_flag=0;break;

		
		//Cmd_AU5_ISEN
		case 19:AU5_Change_Flag=1;STMFLASH_Write(AU5_Microphone_ADDR,p,1);STMFLASH_Read(AU5_Microphone_ADDR,&AU5.Microphone,1);
															STMFLASH_Write(AU5_ISEN_ADDR,&data,1);STMFLASH_Read(AU5_ISEN_ADDR,&AU5.i_sen,1);
															STMFLASH_Write(AU5_BIAS_ADDR,p,1);STMFLASH_Read(AU5_BIAS_ADDR,&AU5.bias,1);
															STMFLASH_Write(AU5_GAIN_ADDR,p,1);STMFLASH_Read(AU5_GAIN_ADDR,&AU5.gain,1);cmd_flag=0;break;
		//Cmd_AU6_ISEN
		case 20:AU6_Change_Flag=1;STMFLASH_Write(AU6_Microphone_ADDR,p,1);STMFLASH_Read(AU6_Microphone_ADDR,&AU6.Microphone,1);
															STMFLASH_Write(AU6_ISEN_ADDR,&data,1);STMFLASH_Read(AU6_ISEN_ADDR,&AU6.i_sen,1);
															STMFLASH_Write(AU6_BIAS_ADDR,p,1);STMFLASH_Read(AU6_BIAS_ADDR,&AU6.bias,1);
															STMFLASH_Write(AU6_GAIN_ADDR,p,1);STMFLASH_Read(AU6_GAIN_ADDR,&AU6.gain,1);cmd_flag=0;break;
															
		//Cmd_Get_State			
		case 21:Get_state();cmd_flag=0;break;
		
		//Cmd_AU1_Microphone	
		case 22:AU1_Change_Flag=1;STMFLASH_Write(AU1_Microphone_ADDR,&data,1);STMFLASH_Read(AU1_Microphone_ADDR,&AU1.Microphone,1);
															STMFLASH_Write(AU1_BIAS_ADDR,p+3,1);STMFLASH_Read(AU1_BIAS_ADDR,&AU1.bias,1);cmd_flag=0;break;
		//Cmd_AU2_Microphone
		case 23:AU2_Change_Flag=1;STMFLASH_Write(AU2_Microphone_ADDR,&data,1);STMFLASH_Read(AU2_Microphone_ADDR,&AU2.Microphone,1);
															STMFLASH_Write(AU2_BIAS_ADDR,p+3,1);STMFLASH_Read(AU2_BIAS_ADDR,&AU2.bias,1);cmd_flag=0;break;
		//Cmd_AU3_Microphone
		case 24:AU3_Change_Flag=1;STMFLASH_Write(AU3_Microphone_ADDR,&data,1);STMFLASH_Read(AU3_Microphone_ADDR,&AU3.Microphone,1);
															STMFLASH_Write(AU3_BIAS_ADDR,p+3,1);STMFLASH_Read(AU3_BIAS_ADDR,&AU3.bias,1);cmd_flag=0;break;
		//Cmd_AU4_Microphone
		case 25:AU4_Change_Flag=1;STMFLASH_Write(AU4_Microphone_ADDR,&data,1);STMFLASH_Read(AU4_Microphone_ADDR,&AU4.Microphone,1);
															STMFLASH_Write(AU4_BIAS_ADDR,p+3,1);STMFLASH_Read(AU4_BIAS_ADDR,&AU4.bias,1);cmd_flag=0;break;
		//Cmd_AU5_Microphone
		case 26:AU5_Change_Flag=1;STMFLASH_Write(AU5_Microphone_ADDR,&data,1);STMFLASH_Read(AU5_Microphone_ADDR,&AU5.Microphone,1);
															STMFLASH_Write(AU5_ISEN_ADDR,p,1);STMFLASH_Read(AU5_ISEN_ADDR,&AU5.i_sen,1);
															STMFLASH_Write(AU5_BIAS_ADDR,p+3,1);STMFLASH_Read(AU5_BIAS_ADDR,&AU5.bias,1);cmd_flag=0;break;
		//Cmd_AU6_Microphone
		case 27:AU6_Change_Flag=1;STMFLASH_Write(AU6_Microphone_ADDR,&data,1);STMFLASH_Read(AU6_Microphone_ADDR,&AU6.Microphone,1);
															STMFLASH_Write(AU6_ISEN_ADDR,p,1);STMFLASH_Read(AU6_ISEN_ADDR,&AU6.i_sen,1);
															STMFLASH_Write(AU6_BIAS_ADDR,p+3,1);STMFLASH_Read(AU6_BIAS_ADDR,&AU6.bias,1);cmd_flag=0;break;
		
		//Cmd_AU1_Line
		case 28:AU1_Change_Flag=1;STMFLASH_Write(AU1_Microphone_ADDR,p,1);STMFLASH_Read(AU1_Microphone_ADDR,&AU1.Microphone,1);
															STMFLASH_Write(AU1_BIAS_ADDR,p,1);STMFLASH_Read(AU1_BIAS_ADDR,&AU1.bias,1);cmd_flag=0;break;
		//Cmd_AU2_Line
		case 29:AU2_Change_Flag=1;STMFLASH_Write(AU2_Microphone_ADDR,p,1);STMFLASH_Read(AU2_Microphone_ADDR,&AU2.Microphone,1);
															STMFLASH_Write(AU2_BIAS_ADDR,p,1);STMFLASH_Read(AU2_BIAS_ADDR,&AU2.bias,1);cmd_flag=0;break;
		//Cmd_AU3_Line
		case 30:AU3_Change_Flag=1;STMFLASH_Write(AU3_Microphone_ADDR,p,1);STMFLASH_Read(AU3_Microphone_ADDR,&AU3.Microphone,1);
															STMFLASH_Write(AU3_BIAS_ADDR,p,1);STMFLASH_Read(AU3_BIAS_ADDR,&AU3.bias,1);cmd_flag=0;break;
		//Cmd_AU4_Line
		case 31:AU4_Change_Flag=1;STMFLASH_Write(AU4_Microphone_ADDR,p,1);STMFLASH_Read(AU4_Microphone_ADDR,&AU4.Microphone,1);
															STMFLASH_Write(AU4_BIAS_ADDR,p,1);STMFLASH_Read(AU4_BIAS_ADDR,&AU4.bias,1);cmd_flag=0;break;
		//Cmd_AU5_Line
		case 32:AU5_Change_Flag=1;STMFLASH_Write(AU5_Microphone_ADDR,p,1);STMFLASH_Read(AU5_Microphone_ADDR,&AU5.Microphone,1);
															STMFLASH_Write(AU5_ISEN_ADDR,p,1);STMFLASH_Read(AU5_ISEN_ADDR,&AU5.i_sen,1);
															STMFLASH_Write(AU5_BIAS_ADDR,p,1);STMFLASH_Read(AU5_BIAS_ADDR,&AU5.bias,1);cmd_flag=0;break;
		//Cmd_AU6_Line
		case 33:AU6_Change_Flag=1;STMFLASH_Write(AU6_Microphone_ADDR,p,1);STMFLASH_Read(AU6_Microphone_ADDR,&AU6.Microphone,1);
															STMFLASH_Write(AU6_ISEN_ADDR,p,1);STMFLASH_Read(AU6_ISEN_ADDR,&AU6.i_sen,1);
															STMFLASH_Write(AU6_BIAS_ADDR,p,1);STMFLASH_Read(AU6_BIAS_ADDR,&AU6.bias,1);cmd_flag=0;break;
		
		//Cmd_Xmos_adc1
		case 34:STMFLASH_Write(XMOS_ADC1_ADDR,&data1,1);STMFLASH_Read(XMOS_ADC1_ADDR,&XMOS_ADC_DATA[1],1);
						MCU_Write_ADC1_Process(XMOS_ADC1_ADDRESS,REG_ADC1_ADDRESS, XMOS_ADC_DATA[1]);
						//tca6424a_1_Write_Process(0x04, XMOS_ADC_DATA[1]);
						cmd_flag=0;break;
		//Cmd_Xmos_adc2
		case 35:STMFLASH_Write(XMOS_ADC2_ADDR,&data1,1);STMFLASH_Read(XMOS_ADC2_ADDR,&XMOS_ADC_DATA[2],1);
						MCU_Write_ADC1_Process(XMOS_ADC2_ADDRESS,REG_ADC2_ADDRESS, XMOS_ADC_DATA[2]);
						//tca6424a_1_Write_Process(0x05, XMOS_ADC_DATA[2]);
						cmd_flag=0;break;
						
		default : if(cmd_flag){cmd_flag=0;}break;
	}
	
	memset(Uart4_buffer_save,'\0',sizeof Uart4_buffer_save);
}



void cmh_memcpyn(uint8_t *buffer1, uint8_t *buffer2,uint8_t number)
{
    char i;
    for(i=0; i<number; i++)
    {
        *buffer1++=*buffer2++;
    }
}

uint8_t cmh_strcmp(uint8_t *str1,uint8_t *str2,uint8_t number)
{
    int i;
    for(i=0; i<number; i++)
    {
        if(str1[i]!=str2[i])
        {
            return 0;
        }
    }

    return 1;
}


