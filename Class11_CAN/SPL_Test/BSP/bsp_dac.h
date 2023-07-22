#ifndef __BSP_DAC_H
#define __BSP_DAC_H

#include "stm32f10x.h"


void BSP_DAC_init(void);
void BSP_DAC_SetChVal(void);


extern uint16_t dac_Data;

#endif//__BSP_DAC_H

