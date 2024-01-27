#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "misc.h"
#include "stm32f10x_usart.h"


/* Private define ------------------------------------------------------------*/

// #define USART1_REMAP         
// #define USART2_REMAP

#define USART3_REMAP_NONE       
// #define USART3_REMAP_PARTIAL    
// #define USART3_REMAP_FULL           




void BSP_USART_Init(USART_TypeDef *usart,  uint32_t baud);
void BSP_USART_SendData(USART_TypeDef *usart, uint16_t data);
void BSP_USART_IOCfg(USART_TypeDef *usart);
void BSP_USART_IORemap(USART_TypeDef *usart);
void BSP_USART_ClockEn(USART_TypeDef *usart);
void BSP_USART_SetIrq(USART_TypeDef *usart);
void BSP_USART_SetMode(USART_TypeDef *usart, uint32_t baud);

extern void USART1_IrqCallBack(uint16_t data);
extern void USART1_IRQHandler(void);
extern void USART2_IrqCallBack(uint16_t data);
extern void USART2_IRQHandler(void);
extern void USART3_IrqCallBack(uint16_t data);
extern void USART3_IRQHandler(void);
extern void UART4_IrqRxCallBack(uint16_t data);
extern void UART4_IRQHandler(void);
extern void UART5_IrqRxCallBack(uint16_t data);
extern void UART5_IRQHandler(void);



/* Public variable ------------------------------------------------------------*/
extern uint16_t	USART1_valRx;
extern uint16_t	USART2_valRx;
extern uint16_t	USART3_valRx;
extern uint16_t	UART4_valRx;
extern uint16_t	UART5_valRx;

#endif//__BSP_USART_H

