#include "bsp_gpio.h"


void BSP_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
    //GPIOA、GPIOB、GPIOC peripheral clock are Enabled in bsp_rcc.c

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

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