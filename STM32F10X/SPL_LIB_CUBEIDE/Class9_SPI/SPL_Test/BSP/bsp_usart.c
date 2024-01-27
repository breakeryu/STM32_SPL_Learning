
#include "bsp_usart.h"

uint16_t	USART1_valRx;
uint16_t	USART2_valRx;
uint16_t	USART3_valRx;
uint16_t	UART4_valRx;
uint16_t	UART5_valRx;


/**
  * @brief  Initialize the USART or the UART peripheral.
  * @param  usart: Select the USART or the UART peripheral. 
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  baud: specifies the USART baud .
  *   This parameter can be one of the following values:
  *     @arg 4800
  *     @arg 9600
  *     @arg 19200
  *     @arg 38400
  *     @arg 57600
  *     @arg 115200
  *     @arg 921600
  *     @arg etc.
  * @retval None
  */
void BSP_USART_Init(USART_TypeDef *usart, uint32_t baud)
{
    USART_InitTypeDef USART_InitStructure;

    BSP_USART_IOCfg(usart);
    BSP_USART_IORemap(usart);
    BSP_USART_ClockEn(usart);


    /* USARTx configuration ------------------------------------------------------*/
    /* USARTx configured as follow:
        - BaudRate =  baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - None parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* USART configuration */
    USART_Init(usart, &USART_InitStructure);

    /* Enable USART */
    USART_Cmd(usart, ENABLE);

    /* Enable the USART Receive interrupt: this interrupt is generated when the 
    USART receive data register is not empty */
    USART_ITConfig(usart, USART_IT_RXNE, ENABLE);

    BSP_USART_SetIrq(usart);

}

/**********************************************************************************
  * USART发送函数
 **********************************************************************************/
void BSP_USART_SendData(USART_TypeDef *usart, uint16_t data)
{
	uint32_t cnt;

	if(usart->CR1 & USART_WordLength_9b)
	{
		usart->DR = data & 0x1FF;
	}
	else
	{
		usart->DR = data & 0xFF;
	}

	cnt = 0;
	while(0 == (usart->SR & USART_FLAG_TC))
	{
		if(cnt++ > 2000000)
		{
			break;
		}
	}
}


/**
  * @brief  Config the USART or the UART peripheral IO.
  * @param  usart: Select the USART or the UART peripheral. 
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @retval None
  */
void BSP_USART_IOCfg(USART_TypeDef *usart)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    switch((uint32_t)usart)
	{
	case USART1_BASE:
		{
            #ifdef  USART1_REMAP

            /* Configure USART Tx as alternate function push-pull */
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOB, &GPIO_InitStructure);

            /* Configure USART Rx as input floating */
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            
            #else

			/* Configure USART Tx as alternate function push-pull */
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOA, &GPIO_InitStructure);

            /* Configure USART Rx as input floating */
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
			
			#endif

		}
		break;
	case USART2_BASE:
		{

			#ifdef  USART2_REMAP

            /* Configure USART Tx as alternate function push-pull */
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOD, &GPIO_InitStructure);

            /* Configure USART Rx as input floating */
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIO_Init(GPIOD, &GPIO_InitStructure);

			#else

            /* Configure USART Tx as alternate function push-pull */
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOA, &GPIO_InitStructure);

            /* Configure USART Rx as input floating */
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_Init(GPIOA, &GPIO_InitStructure);

			#endif

		}
		break;
	case USART3_BASE:
		{

			#if defined USART3_REMAP_PARTIAL
				/* Configure USART Tx as alternate function push-pull */
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOC, &GPIO_InitStructure);

				/* Configure USART Rx as input floating */
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
				GPIO_Init(GPIOC, &GPIO_InitStructure);

			#elif defined USART3_REMAP_FULL
				/* Configure USART Tx as alternate function push-pull */
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOD, &GPIO_InitStructure);

				/* Configure USART Rx as input floating */
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
				GPIO_Init(GPIOD, &GPIO_InitStructure);

			#elif defined USART3_REMAP_NONE

				/* Configure USART Tx as alternate function push-pull */
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOB, &GPIO_InitStructure);

				/* Configure USART Rx as input floating */
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
				GPIO_Init(GPIOB, &GPIO_InitStructure);

			#endif
			
		
		}
		break;

	case UART4_BASE:
		{
            /* Configure USART Tx as alternate function push-pull */
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOC, &GPIO_InitStructure);

            /* Configure USART Rx as input floating */
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
            GPIO_Init(GPIOC, &GPIO_InitStructure);

		}
		break;

	case UART5_BASE:
		{
            /* Configure USART Tx as alternate function push-pull */
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOC, &GPIO_InitStructure);

            /* Configure USART Rx as input floating */
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_Init(GPIOD, &GPIO_InitStructure);

		}
		break;

	default:
		{

		}
	}
}



/**
  * @brief  Remap the USART or the UART peripheral IO.
  * @param  usart: Select the USART or the UART peripheral. 
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @retval None
  */
void BSP_USART_IORemap(USART_TypeDef *usart)
{
	switch((uint32_t)usart)
	{
	case USART1_BASE:
		{
			#ifdef  USART1_REMAP
				GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);//PB6 PB7
			#else
				GPIO_PinRemapConfig(GPIO_Remap_USART1, DISABLE);//PA9 PA10
			#endif
		}
		break;
	case USART2_BASE:
		{
			#ifdef  USART2_REMAP

			GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);//PD5 PD6

			#else

			GPIO_PinRemapConfig(GPIO_Remap_USART2, DISABLE);//PA2 PA3

			#endif

		}
		break;
	case USART3_BASE:
		{
			#if defined USART3_REMAP_PARTIAL
				GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);//PC10 PC11
			#elif defined USART3_REMAP_FULL
				GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);//PD8 PD9
			#elif defined USART3_REMAP_NONE
				GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, DISABLE);
				//RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, DISABLE);//PB10 PB11
			#endif
		}
		break;

//	case UART4_BASE:
//		{
//			STM32F1xx_AFIOReMap(AFIO_REMAP_USART3_PB10_PB11_PB12_PB13_PB14, AFIO_REMAP_USART3_MASK);
//		}
//		break;
//
//	case UART5_BASE:
//		{
//			STM32F1xx_AFIOReMap(AFIO_REMAP_USART3_PB10_PB11_PB12_PB13_PB14, AFIO_REMAP_USART3_MASK);
//		}
//		break;

	default:
		{

		}
	}
}

/**
  * @brief  Enable the USART or the UART peripheral Clock.
  * @param  usart: Select the USART or the UART peripheral. 
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @retval None
  */
void BSP_USART_ClockEn(USART_TypeDef *usart)
{
    switch((uint32_t)usart)
	{
	case USART1_BASE:
		{
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		}
		break;
	case USART2_BASE:
		{
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
		}
		break;
	case USART3_BASE:
		{
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
		}
		break;

	case UART4_BASE:
		{
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
		}
		break;

	case UART5_BASE:
		{
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
		}
		break;

	default:
		{

		}
	}
}

/**
  * @brief  Config the USART or the UART peripheral Irq.
  * @param  usart: Select the USART or the UART peripheral. 
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @retval None
  */
void BSP_USART_SetIrq(USART_TypeDef *usart)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    switch((uint32_t)usart)
	{
	case USART1_BASE:
		{
            NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
            NVIC_Init(&NVIC_InitStructure);
		}
		break;
	case USART2_BASE:
		{
            NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
            NVIC_Init(&NVIC_InitStructure);
		}
		break;
	case USART3_BASE:
		{
            NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
            NVIC_Init(&NVIC_InitStructure);
		}
		break;

	case UART4_BASE:
		{
            NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
            NVIC_Init(&NVIC_InitStructure);
		}
		break;

	case UART5_BASE:
		{
            NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
            NVIC_Init(&NVIC_InitStructure);
		}
		break;

	default:
		{

		}
	}


}

/**********************************************************************************
  * USART1接收中断函数
 **********************************************************************************/
void __attribute((weak)) USART1_IrqRxCallBack(uint16_t data)
{

}

void USART1_IRQHandler(void)
{
	uint32_t st,cr;

	st = USART1->SR;
	cr = USART1->CR1;

	if(st & USART_FLAG_RXNE)
	{
		if(cr & USART_WordLength_9b)
		{
			USART1_valRx = (uint16_t)(USART1->DR & 0X1FF);
		}
		else
		{
			USART1_valRx = (uint16_t)(USART1->DR & 0XFF);
		}

		USART1_IrqRxCallBack(USART1_valRx);
	}
}


/**********************************************************************************
  * USART2接收中断函数
 **********************************************************************************/
void __attribute((weak)) USART2_IrqCallBack(uint16_t data)
{

}

void USART2_IRQHandler(void)
{
	if(USART2->CR1 & USART_WordLength_9b)
	{
		USART2_valRx = (uint16_t)(USART2->DR & 0X1FF);
	}
	else
	{
		USART2_valRx = (uint16_t)(USART2->DR & 0XFF);
	}

	USART2_IrqCallBack(USART2_valRx);
}

/**********************************************************************************
  * USART3接收中断函数
 **********************************************************************************/
void __attribute((weak)) USART3_IrqCallBack(uint16_t data)
{

}

void USART3_IRQHandler(void)
{
	if(USART3->CR1 & USART_WordLength_9b)
	{
		USART3_valRx = (uint16_t)(USART3->DR & 0X1FF);
	}
	else
	{
		USART3_valRx = (uint16_t)(USART3->DR & 0XFF);
	}

	USART3_IrqCallBack(USART3_valRx);
}


/**********************************************************************************
  * UART4接收中断函数
 **********************************************************************************/
void __attribute((weak)) UART4_IrqRxCallBack(uint16_t data)
{

}

void UART4_IRQHandler(void)
{
	uint32_t st,cr;

	st = UART4->SR;
	cr = UART4->CR1;

	if(st & USART_FLAG_RXNE)
	{
		if(cr & USART_WordLength_9b)
		{
			UART4_valRx = (uint16_t)(UART4->DR & 0X1FF);
		}
		else
		{
			UART4_valRx = (uint16_t)(UART4->DR & 0XFF);
		}

		UART4_IrqRxCallBack(UART4_valRx);
	}

}

/**********************************************************************************
  * UART5接收中断函数
 **********************************************************************************/
void __attribute((weak)) UART5_IrqRxCallBack(uint16_t data)
{

}

void UART5_IRQHandler(void)
{
	uint32_t st,cr;

	st = UART5->SR;
	cr = UART5->CR1;

	if(st & USART_FLAG_RXNE)
	{
		if(cr & USART_WordLength_9b)
		{
			UART5_valRx = (uint16_t)(UART5->DR & 0X1FF);
		}
		else
		{
			UART5_valRx = (uint16_t)(UART5->DR & 0XFF);
		}

		UART5_IrqRxCallBack(UART5_valRx);
	}

}

