
#ifndef __BSP_RCC_H
#define __BSP_RCC_H

#include "stm32f10x.h"
#include "misc.h"
#include "stm32f10x_rcc.h"
#include "system_stm32f10x.h"


void BSP_RCC_NVIC_Configuration(void);

void BSP_RCC_Init(void);

#endif// __BSP_RCC_H
