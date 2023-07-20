#ifndef __BSP_SPI_H
#define __BSP_SPI_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "bsp_gpio.h"


// #define  SPI_REMAP_SPI1

// #define  SPI_REMAP_SPI3




void BSP_SPI_Init(SPI_TypeDef *spi);
void BSP_SPI_ClkEn(SPI_TypeDef *SPI);
void BSP_SPI_PortCfg(SPI_TypeDef *SPI);
void BSP_SPI_IoCfg(SPI_TypeDef *SPI);
void BSP_SPI_ModeCfg(SPI_TypeDef *SPI);


void BSP_SPI_Tx8Bit(SPI_TypeDef *SPI, uint8_t data);
void BSP_SPI_Tx16Bit(SPI_TypeDef *SPI, uint16_t data);
uint8_t BSP_SPI_TxRx8Bit(SPI_TypeDef *SPI, uint8_t TxData);
uint16_t BSP_SPI_TxRx16Bit(SPI_TypeDef *SPI, uint16_t TxData);



#endif //__BSP_SPI_H
