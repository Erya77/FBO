#ifndef __TCA6424A_H
#define __TCA6424A_H

#include "sys.h"



void TCA6424_Init(void);

//IIC2  TCA6424A-1   IIC  -----------------
void tca6424a_1_init(void);
int tca6424a_1_Read(u8 *buf);
int tca6424a_1_Cmd_Cmd(u8 cmd);

int tca6424a_1_Write_Process(u8 cmd, u8 data);
int tca6424a_1_Read_Process(u8 cmd);

uint8_t tca6424a_1_read(uint8_t reg);

//IIC3  TCA6424A-2   IIC  -----------------
void tca6424a_2_init(void);
int tca6424a_2_Read(u8 *buf);
int tca6424a_2_Cmd_Cmd(u8 cmd);

int tca6424a_2_Write_Process(u8 cmd, u8 data);
int tca6424a_2_Read_Process(u8 cmd);

uint8_t tca6424a_2_read(uint8_t reg);

#endif
