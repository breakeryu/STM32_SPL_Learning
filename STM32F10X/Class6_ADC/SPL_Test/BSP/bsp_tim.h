#ifndef __BSP_TIM_H
#define __BSP_TIM_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"


void BSP_PWM_Init(void);
void BSP_PWM_TestDemo(void);
void BSP_Timer_Init(void);
void BSP_TIM_OCAcitve(void);
void BSP_PWM_INPUT_Init(void);


extern uint16_t CCR3_Val;
extern uint16_t PrescalerValue;
extern uint16_t IC1Value;
extern uint16_t DutyCycle;
extern uint32_t Frequency;
#endif //__BSP_TIM_H

