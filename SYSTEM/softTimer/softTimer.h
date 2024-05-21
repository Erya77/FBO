#ifndef __SOFTTIMER_H
#define __SOFTTIMER_H
#include "stm32f10x.h"

#define Timer_NUM	50
typedef void (handler_typedef)(void);

typedef struct struct_softTimer{
	u8 state;			//��ʱ��״̬ 0��ֹͣ��δ������  1��������  2����ʱ������������
	u32 timer_cnt;		//��ʱ����ǰ����ֵ
	u32 timeout;		//��ʱ����ʱʱ��
	u32 times;			//������ɴ���
//	void (*handler)();
	handler_typedef* handler;
}softTimer_typedef;


extern softTimer_typedef softTimer[Timer_NUM];
extern volatile u32 tick_Cnt;

void softTimer_handler0(void);
void softTimer_handler1(void);
void softTimer_handler2(void);
void softTimer_handler3(void);
void softTimer_handler4(void);
void softTimer_handler5(void);
void softTimer_handler6(void);
void softTimer_handler7(void);
void softTimer_handler8(void);
void softTimer_handler9(void);
void softTimer_handler10(void);
void softTimer_handler11(void);

void softTimer_config(u8 num,u32 delay,u8 state,handler_typedef* handler);
void softTimer_updata(void);
u8 softTimer_cheak_state(u8 num);

#endif
