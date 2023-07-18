/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "stm32f10x.h"
#include "bsp_board.h"
#include "stm32f10x_gpio.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{

  // SYS CLK Init 
  BSP_RCC_Init();

  /** Config SWJ Reamp 
    *   If using the PA15、PA14、PA13、PB4、PB3 for Remapping Pin, these Clock Must be Config before SWJ REMAP config Function!
    */
  sys_SWJ_REMAP_Config(SWJ_ENABLE);

  BSP_PWM_INPUT_Init();


  while (1)
  {
  
  }
  
}
