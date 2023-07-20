#include "bsp_gpio.h"


void BSP_GPIO_Init(void)
{
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
    //GPIOA、GPIOB、GPIOC peripheral clock are Enabled in bsp_rcc.c

    BSP_GPIO_SetCfg(GPIOB, GPIO_Pin_5 | GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
    BSP_GPIO_SetCfg(GPIOE, GPIO_Pin_5, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);

}


void BSP_GPIO_Write_Demo(void)
{
    uint8_t actionBit = 0;//变量的类型转换演示

    actionBit = 1;
    GPIO_WriteBit(GPIOB, GPIO_Pin_5, Bit_SET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)actionBit);
    GPIO_WriteBit(GPIOE, GPIO_Pin_5, Bit_SET);
    delay_ms(500);

    actionBit = 0;
    GPIO_WriteBit(GPIOB, GPIO_Pin_5, Bit_RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)actionBit);
    GPIO_WriteBit(GPIOE, GPIO_Pin_5, Bit_RESET);
    delay_ms(500);

}


/**
  * @brief  Initializes the GPIOx peripheral according to the specified
  *         parameters.
  * @param  gp: where x can be (A..G) to select the GPIO peripheral.
  *     @arg GPIOA-GPIOG
  * @param  index: specifies the port bit.
  *     @arg GPIO_Pin_0-GPIO_Pin_15
  * @param  mode: specifies the GPIO peripheral mode.
  *     @arg GPIO_Mode_AIN
  *     @arg GPIO_Mode_IN_FLOATING
  *     @arg GPIO_Mode_IPD
  *     @arg GPIO_Mode_IPU
  *     @arg GPIO_Mode_Out_OD
  *     @arg GPIO_Mode_Out_PP
  *     @arg GPIO_Mode_AF_OD
  *     @arg GPIO_Mode_AF_PP
  * @param  speed: specifies the GPIO peripheral speed.
  *     @arg GPIO_Speed_10MHz
  *     @arg GPIO_Speed_2MHz
  *     @arg GPIO_Speed_50MHz
  * @retval None
  */
void BSP_GPIO_SetCfg(GPIO_TypeDef *gp, uint16_t index,GPIOSpeed_TypeDef speed, GPIOMode_TypeDef mode)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = index;
    GPIO_InitStructure.GPIO_Speed = speed;
    GPIO_InitStructure.GPIO_Mode = mode;
    GPIO_Init(gp, &GPIO_InitStructure);

}


/**********************************************************************************
  * 获得GPIO的16个输入端口状态
  * gp：指向端口的指针
  * return：index端口的状态
 **********************************************************************************/
uint16_t BSP_GPIO_GetGPIO_InSt(GPIO_TypeDef *gp)
{
	return (uint16_t)(gp->IDR & 0x0000FFFF);
}

/**********************************************************************************
  * 获得GPIO某一个输入端口的状态
  * gp：指向端口的指针
  * index：端口号
  * return：index端口的状态
 **********************************************************************************/
uint8_t BSP_GPIO_GetGPIO_InPortSt(GPIO_TypeDef *gp, uint8_t index)
{
	return (uint8_t)((gp->IDR >> index) & 0b1);
}

/**********************************************************************************
  * 获得GPIO的16个输出端口状态
  * gp：指向端口的指针
  * return：GPIO的16个输出端口状态
 **********************************************************************************/
uint16_t BSP_GPIO_GetGPIO_OutSt(GPIO_TypeDef *gp)
{
	return (uint16_t)(gp->ODR & 0x0000FFFF);
}

/**********************************************************************************
  * 获得GPIO某一个输出端口的状态
  * gp：指向端口的指针
  * index：端口号
  * return：index端口的状态
 **********************************************************************************/
uint8_t BSP_GPIO_GetGPIO_OutPortSt(GPIO_TypeDef *gp, uint8_t index)
{
	return (uint8_t)((gp->ODR >> index) & 0b1);
}

/**********************************************************************************
  * 设置GPIO的16个输出端口状态
  * gp：指向端口的指针
  * val：GPIO的16个输出端口状态
 **********************************************************************************/
void BSP_GPIO_SetGPIO_OutSt(GPIO_TypeDef *gp, uint16_t val)
{
	gp->ODR = val;
}

/**********************************************************************************
  * 设置GPIO某一个输出端口的状态
  * gp：指向端口的指针
  * index：端口号
  * val：index端口的状态
 **********************************************************************************/
void BSP_GPIO_SetGPIO_OutPortSt(GPIO_TypeDef *gp, uint8_t index, uint8_t val)
{
	if(val & 0b1)
	{
		gp->BSRR |= ((uint16_t)1 << index);
	}
	else
	{
		gp->BRR |= ((uint16_t)1 << index);
	}
}

/**********************************************************************************
  * 设置GPIO锁定
  * gp：指向端口的指针
  * val：GPIO的16个输出端口状态
 **********************************************************************************/
uint8_t BSP_GPIO_SetGPIO_Lock(GPIO_TypeDef *gp, uint16_t val)
{
	uint32_t temp;

	if((gp->LCKR & 0x00010000) == 0)
	{
		gp->LCKR = val;
		gp->LCKR |= 0x00010000;
		gp->LCKR &= ~0x00010000;
		gp->LCKR |= 0x00010000;
		temp = gp->LCKR;
		temp = gp->LCKR;

		if(temp & 0x00010000)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 2;
	}
}


