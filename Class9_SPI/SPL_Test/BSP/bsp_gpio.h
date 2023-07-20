#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"



void BSP_GPIO_Init(void);
void BSP_GPIO_Write_Demo(void);

void BSP_GPIO_SetCfg(GPIO_TypeDef *gp, uint16_t index,GPIOSpeed_TypeDef speed, GPIOMode_TypeDef mode);
uint16_t BSP_GPIO_GetGPIO_InSt(GPIO_TypeDef *gp);
uint8_t BSP_GPIO_GetGPIO_InPortSt(GPIO_TypeDef *gp, uint8_t index);
uint16_t BSP_GPIO_GetGPIO_OutSt(GPIO_TypeDef *gp);
uint8_t BSP_GPIO_GetGPIO_OutPortSt(GPIO_TypeDef *gp, uint8_t index);
void BSP_GPIO_SetGPIO_OutSt(GPIO_TypeDef *gp, uint16_t val);
void BSP_GPIO_SetGPIO_OutPortSt(GPIO_TypeDef *gp, uint8_t index, uint8_t val);
uint8_t BSP_GPIO_SetGPIO_Lock(GPIO_TypeDef *gp, uint16_t val);


#endif//__BSP_GPIO_H

