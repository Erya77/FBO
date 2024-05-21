#include "myiic.h"
#include "delay.h"

 
//初始化IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOD, ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_3); 	//PB6,PB7 输出高
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD,GPIO_Pin_2); 
}


void IIC_SDA_IN()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void IIC_SDA_OUT()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//产生IIC起始信号
void IIC_Start(void)
{
	IIC_SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	IIC_SDA_OUT();			//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	IIC_SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(IIC_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL=0;
	IIC_SDA_OUT();		//sda线输出
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	IIC_SDA_OUT();		//sda线输出
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	IIC_SDA_OUT(); 	    //sda线输出
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	IIC_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
		if(IIC_READ_SDA)receive++;
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}






//初始化IIC2
void IIC2_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOD, ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_3); 	//PB6,PB7 输出高
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD,GPIO_Pin_2); 
}


void IIC2_SDA_IN()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void IIC2_SDA_OUT()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

//产生IIC2起始信号
void IIC2_Start(void)
{
	IIC2_SDA_OUT();     //sda线输出
	IIC2_SDA=1;	  	  
	IIC2_SCL=1;
	delay_us(4);
 	IIC2_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC2_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC2停止信号
void IIC2_Stop(void)
{
	IIC2_SDA_OUT();			//sda线输出
	IIC2_SCL=0;
	IIC2_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC2_SCL=1; 
	IIC2_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC2_Wait_Ack(void)
{
	u8 ucErrTime=0;
	IIC2_SDA_IN();      //SDA设置为输入  
	IIC2_SDA=1;delay_us(1);	   
	IIC2_SCL=1;delay_us(1);	 
	while(IIC2_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC2_Stop();
			return 1;
		}
	}
	IIC2_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC2_Ack(void)
{
	IIC2_SCL=0;
	IIC2_SDA_OUT();		//sda线输出
	IIC2_SDA=0;
	delay_us(2);
	IIC2_SCL=1;
	delay_us(2);
	IIC2_SCL=0;
}
//不产生ACK应答		    
void IIC2_NAck(void)
{
	IIC2_SCL=0;
	IIC2_SDA_OUT();		//sda线输出
	IIC2_SDA=1;
	delay_us(2);
	IIC2_SCL=1;
	delay_us(2);
	IIC2_SCL=0;
}					 				     
//IIC2发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC2_Send_Byte(u8 txd)
{                        
    u8 t;   
	IIC2_SDA_OUT(); 	    //sda线输出
    IIC2_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC2_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC2_SDA=1;
		else
			IIC2_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC2_SCL=1;
		delay_us(2); 
		IIC2_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC2_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	IIC2_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
			IIC2_SCL=0; 
			delay_us(2);
		IIC2_SCL=1;
        receive<<=1;
		if(IIC2_READ_SDA)receive++;
		delay_us(1); 
    }					 
    if (!ack)
        IIC2_NAck();//发送nACK
    else
        IIC2_Ack(); //发送ACK   
    return receive;
}







//初始化IIC3
void IIC3_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOD, ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_3); 	//PB6,PB7 输出高
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD,GPIO_Pin_2); 
}


void IIC3_SDA_IN()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOE, ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void IIC3_SDA_OUT()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOE, ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

//产生IIC3起始信号
void IIC3_Start(void)
{
	IIC3_SDA_OUT();     //sda线输出
	IIC3_SDA=1;	  	  
	IIC3_SCL=1;
	delay_us(4);
 	IIC3_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC3_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC3停止信号
void IIC3_Stop(void)
{
	IIC3_SDA_OUT();			//sda线输出
	IIC3_SCL=0;
	IIC3_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC3_SCL=1; 
	IIC3_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC3_Wait_Ack(void)
{
	u8 ucErrTime=0;
	IIC3_SDA_IN();      //SDA设置为输入  
	IIC3_SDA=1;delay_us(1);	   
	IIC3_SCL=1;delay_us(1);	 
	while(IIC3_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC3_Stop();
			return 1;
		}
	}
	IIC3_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC3_Ack(void)
{
	IIC3_SCL=0;
	IIC3_SDA_OUT();		//sda线输出
	IIC3_SDA=0;
	delay_us(2);
	IIC3_SCL=1;
	delay_us(2);
	IIC3_SCL=0;
}
//不产生ACK应答		    
void IIC3_NAck(void)
{
	IIC3_SCL=0;
	IIC3_SDA_OUT();		//sda线输出
	IIC3_SDA=1;
	delay_us(2);
	IIC3_SCL=1;
	delay_us(2);
	IIC3_SCL=0;
}					 				     
//IIC3发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC3_Send_Byte(u8 txd)
{                        
    u8 t;   
	IIC3_SDA_OUT(); 	    //sda线输出
    IIC3_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC3_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC3_SDA=1;
		else
			IIC3_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC3_SCL=1;
		delay_us(2); 
		IIC3_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC3_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	IIC3_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC3_SCL=0; 
        delay_us(2);
		IIC3_SCL=1;
        receive<<=1;
		if(IIC3_READ_SDA)receive++;
		delay_us(1); 
    }					 
    if (!ack)
        IIC3_NAck();//发送nACK
    else
        IIC3_Ack(); //发送ACK   
    return receive;
}







//初始化IIC4
void IIC4_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOD, ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_3); 	//PB6,PB7 输出高
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD,GPIO_Pin_2); 
}


void IIC4_SDA_IN()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void IIC4_SDA_OUT()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//产生IIC4起始信号
void IIC4_Start(void)
{
	IIC4_SDA_OUT();     //sda线输出
	IIC4_SDA=1;	  	  
	IIC4_SCL=1;
	delay_us(4);
 	IIC4_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC4_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC4停止信号
void IIC4_Stop(void)
{
	IIC4_SDA_OUT();			//sda线输出
	IIC4_SCL=0;
	IIC4_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC4_SCL=1; 
	IIC4_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC4_Wait_Ack(void)
{
	u8 ucErrTime=0;
	IIC4_SDA_IN();      //SDA设置为输入  
	IIC4_SDA=1;delay_us(1);	   
	IIC4_SCL=1;delay_us(1);	 
	while(IIC4_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC4_Stop();
			return 1;
		}
	}
	IIC4_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC4_Ack(void)
{
	IIC4_SCL=0;
	IIC4_SDA_OUT();		//sda线输出
	IIC4_SDA=0;
	delay_us(2);
	IIC4_SCL=1;
	delay_us(2);
	IIC4_SCL=0;
}
//不产生ACK应答		    
void IIC4_NAck(void)
{
	IIC4_SCL=0;
	IIC4_SDA_OUT();		//sda线输出
	IIC4_SDA=1;
	delay_us(2);
	IIC4_SCL=1;
	delay_us(2);
	IIC4_SCL=0;
}					 				     
//IIC4发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC4_Send_Byte(u8 txd)
{                        
    u8 t;   
	IIC4_SDA_OUT(); 	    //sda线输出
    IIC4_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC4_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC4_SDA=1;
		else
			IIC4_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC4_SCL=1;
		delay_us(2); 
		IIC4_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC4_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	IIC4_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC4_SCL=0; 
        delay_us(2);
		IIC4_SCL=1;
        receive<<=1;
		if(IIC4_READ_SDA)receive++;
		delay_us(1); 
    }					 
    if (!ack)
        IIC4_NAck();//发送nACK
    else
        IIC4_Ack(); //发送ACK   
    return receive;
}













