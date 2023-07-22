#ifndef __BSP_NVIC_H
#define __BSP_NVIC_H

#include "stm32f10x.h"
#include "misc.h"


void BSP_NVIC_Init(uint8_t preprio, uint8_t subprio, uint8_t channel, uint32_t group);

#endif//__BSP_NVIC_H
