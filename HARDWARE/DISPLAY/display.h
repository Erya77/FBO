#ifndef _Display_H
#define _Display_H


#include "main.h"

void DrwaGui(void);

void Display_Aux_Overvol(struct _AU *au);
void Display_Aux_char(struct _AU *au,const char *gain);
void Display_Aux_Mode(struct _AU *au);
void Display_Ampx_char(struct _AMP *amp,const char *gain);
void Display_Ampx_Out(struct _AMP *amp);
#endif

