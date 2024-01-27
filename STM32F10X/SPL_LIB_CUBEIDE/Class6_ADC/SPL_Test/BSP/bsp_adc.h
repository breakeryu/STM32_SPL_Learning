#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "stm32f10x.h"
#include "bsp_rcc.h"
#include "bsp_gpio.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"

/* Private define ------------------------------------------------------------*/
#define ADC1_DR_Address    ((uint32_t)0x4001244C)



void BSP_ADC_Init(void);
void BSP_ADC_Val2Vltg(void);

/* Public variable ------------------------------------------------------------*/
extern  uint16_t ADCConvertedValue;
extern  int16_t adc_vltg;

#endif//__BSP_ADC_H
