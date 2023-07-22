#ifndef __BSP_CAN_H
#define __BSP_CAN_H

#include "stm32f10x.h"
#include "bsp_gpio.h"
#include "stm32f10x_gpio.h"
#include "bsp_nvic.h"
#include "stm32f10x_can.h"

// #define USE_CAN2

// #define CAN_REMAP_CAN1_PB8_PB9
#define CAN_REMAP_CAN1_PA11_PA12
// #define CAN_REMAP_CAN1_PD0_PD1

#define CAN_REMAP_CAN2_PB12_PB13
// #define CAN_REMAP_CAN2_PB5_PB6


void BSP_CAN_Init(CAN_TypeDef *CAN);
void BSP_CAN_ClkEn(CAN_TypeDef *CAN);
void BSP_CAN_IoCfg(CAN_TypeDef *CAN);
void BSP_CAN_IrqEn(CAN_TypeDef *CAN);
void BSP_CAN_ModeCfg(CAN_TypeDef *CAN);

extern void USB_LP_CAN_RX0_IRQHandler(void);
extern void CAN2_RX1_IRQHandler(void);

uint8_t CAN1_Send_Msg(uint8_t ID, uint8_t* msg, uint8_t len);
uint8_t CAN1_Receive_Msg(CanRxMsg* RxMessage);

uint8_t CAN2_Send_Msg(uint8_t ID, uint8_t* msg, uint8_t len);
uint8_t CAN2_Receive_Msg(CanRxMsg* RxMessage);

    
#endif//__BSP_CAN_H

