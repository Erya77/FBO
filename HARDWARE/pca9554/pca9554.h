#ifndef __PCA9554_H
#define __PCA9554_H

#include "sys.h"


void pca9554_init(void);
int pca9554_Read(u8 *buf);
int pca9554_Cmd_Cmd(u8 cmd);

int pca9554_Write_Process(u8 cmd, u8 data);
int pca9554_Read_Process(u8 cmd);
extern u8 IIC_BUF[4];

#endif

