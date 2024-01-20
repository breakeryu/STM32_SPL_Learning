#ifndef __BSP_DAC_H
#define __BSP_DAC_H

#include "stm32f10x.h"


/**
 * @brief  Select which DAC channel
 */
typedef enum {
	BSP_DAC1, /*!< DAC channel 1 */
	BSP_DAC2  /*!< DAC channel 2 */
} DAC_Channel_t;


void BSP_DAC_init(DAC_Channel_t DACx);
void BSP_DAC_SetChVal(DAC_Channel_t DACx, uint16_t value);


extern uint16_t dac_Data;

#endif//__BSP_DAC_H

