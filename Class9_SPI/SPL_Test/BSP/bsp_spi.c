#include "bsp_spi.h"



void BSP_SPI_Init(SPI_TypeDef *spi)
{
    BSP_SPI_ClkEn(spi);
    BSP_SPI_PortCfg(spi);
    BSP_SPI_ModeCfg(spi);

}

/**********************************************************************************
  * SPI时钟使能
  * SPI:指向SPI1、SPI2、SPI3的指针
 **********************************************************************************/
void BSP_SPI_ClkEn(SPI_TypeDef *SPI)
{
    switch((uint32_t)SPI)
	{
		case (uint32_t)SPI1:
		{
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
			
		}
		break;

		case (uint32_t)SPI2:
		{
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
			
		}
		break;

		case (uint32_t)SPI3:
		{
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
			
		}
		break;

		default:
		{

		}
	}
}

/**********************************************************************************
  * SPI端口配置
  * SPI:指向SPI1、SPI2、SPI3的指针
 **********************************************************************************/
void BSP_SPI_PortCfg(SPI_TypeDef *SPI)
{
    

    switch((uint32_t)SPI)
	{
		case (uint32_t)SPI1:
		{
            BSP_SPI_IoCfg(SPI1);
        }
		break;

		case (uint32_t)SPI2:
		{
            BSP_SPI_IoCfg(SPI2);
		}
		break;

		case (uint32_t)SPI3:
		{

		}
		break;

		default:
		{

		}
	}
}


void BSP_SPI_IoCfg(SPI_TypeDef *SPI)
{

    switch((uint32_t)SPI)
	{
		case (uint32_t)SPI1:
		{
#ifdef	SPI_REMAP_SPI1
            BSP_GPIO_SetCfg(GPIOA, GPIO_Pin_15, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);	    //NSS
			BSP_GPIO_SetCfg(GPIOB, GPIO_Pin_3,  GPIO_Speed_50MHz, GPIO_Mode_AF_PP);	        //SCLK
			BSP_GPIO_SetCfg(GPIOB, GPIO_Pin_4,  GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING);   //MISO
			BSP_GPIO_SetCfg(GPIOB, GPIO_Pin_5,  GPIO_Speed_50MHz, GPIO_Mode_AF_PP);	        //MOSI
#else

			BSP_GPIO_SetCfg(GPIOA, GPIO_Pin_4, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);	//NSS
			BSP_GPIO_SetCfg(GPIOA, GPIO_Pin_5, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);	//SCLK
//			BSP_GPIO_SetCfg(GPIOA, GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING);		//MISO
			BSP_GPIO_SetCfg(GPIOA, GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);          
			BSP_GPIO_SetCfg(GPIOA, GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);	//MOSI
#endif
		}
		break;

		case (uint32_t)SPI2:
		{

            BSP_GPIO_SetCfg(GPIOB, GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);	    //NSS
			BSP_GPIO_SetCfg(GPIOB, GPIO_Pin_13, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);	        //SCLK
//			BSP_GPIO_SetCfg(GPIOB, GPIO_Pin_14, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING);	            //MISO
			BSP_GPIO_SetCfg(GPIOB, GPIO_Pin_14, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
			BSP_GPIO_SetCfg(GPIOB, GPIO_Pin_15, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);	        //MOSI
			
		}
		break;

		case (uint32_t)SPI3:
		{
           
			
		}
		break;

		default:
		{

		}
	}

   
}



void BSP_SPI_ModeCfg(SPI_TypeDef *SPI)
{
    SPI_InitTypeDef   SPI_InitStructure;

    switch((uint32_t)SPI)
	{
		case (uint32_t)SPI1:
		{
#ifdef	SPI_REMAP_SPI1

            /* SPIy Config -------------------------------------------------------------*/
            SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
            SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
            SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
            SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
            SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
            SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
            SPI_InitStructure.SPI_CRCPolynomial = 7;
            SPI_Init(SPI1, &SPI_InitStructure);

            /* Enable SPI1 */
            SPI_Cmd(SPI1, ENABLE);

#else

            /* SPIy Config -------------------------------------------------------------*/
            SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
            SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
            SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
            SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
            SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
            SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
            SPI_InitStructure.SPI_CRCPolynomial = 7;
            SPI_Init(SPI1, &SPI_InitStructure);

            /* Enable SPI1 */
            SPI_Cmd(SPI1, ENABLE);

#endif
		}
		break;

		case (uint32_t)SPI2:
		{
            /* SPIy Config -------------------------------------------------------------*/
            SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
            SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
            SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
            SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
            SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
            SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
            SPI_InitStructure.SPI_CRCPolynomial = 7;
            SPI_Init(SPI2, &SPI_InitStructure);

            /* Enable SPI2 */
            SPI_Cmd(SPI2, ENABLE);
			
		}
		break;

		case (uint32_t)SPI3:
		{
           
			
		}
		break;

		default:
		{

		}
	}

}


/**********************************************************************************
  * SPI发送8位数据
  * SPI:指向SPI1、SPI2、SPI3的指针
  * data:要发送的数据
 **********************************************************************************/
void BSP_SPI_Tx8Bit(SPI_TypeDef *SPI, uint8_t data)
{
	SPI->DR = data;
}

/**********************************************************************************
  * SPI发送16位数据
  * SPI:指向SPI1、SPI2、SPI3的指针
  * data:要发送的数据
 **********************************************************************************/
void BSP_SPI_Tx16Bit(SPI_TypeDef *SPI, uint16_t data)
{
	SPI->DR = data;
}

/**********************************************************************************
  * SPI读写8位数
  * SPI:指向SPI1、SPI2、SPI3的指针
  * TxData：要发送的数据
 **********************************************************************************/
uint8_t BSP_SPI_TxRx8Bit(SPI_TypeDef *SPI, uint8_t TxData)
{
	uint16_t retry=0;

	while((SPI->SR & SPI_I2S_FLAG_TXE)==0) //等待发送区空
	{
	retry++;
	if(retry >= 0XFFFE) return 0; //超时退出
	}
	SPI->DR = TxData; //发送一个 byte

	retry=0;
	while((SPI->SR & SPI_I2S_FLAG_RXNE)==0) //等待接收完一个 byte
	{
	retry++;
	if(retry >= 0XFFFE) return 0; //超时退出
	}
	return (uint8_t)SPI->DR; //返回收到的数据
}

/**********************************************************************************
  * SPI读写16位数据
  * SPI:指向SPI1、SPI2、SPI3的指针
  * TxData：要发送的数据
 **********************************************************************************/
uint16_t BSP_SPI_TxRx16Bit(SPI_TypeDef *SPI, uint16_t TxData)
{
	uint16_t retry=0;

	while((SPI->SR & SPI_I2S_FLAG_TXE)==0) //等待发送区空
	{
	retry++;
	if(retry>=0XFFFE)return 0; //超时退出
	}
	SPI->DR = TxData; //发送一个 byte

	retry=0;
	while((SPI->SR & SPI_I2S_FLAG_RXNE)==0) //等待接收完一个 byte
	{
	retry++;
	if(retry>=0XFFFE)return 0; //超时退出
	}
	return SPI->DR; //返回收到的数据
}

