#include "bsp_nvic.h"




/**********************************************************************************
  * 中断向量初始化
  * preprio：高优先级
  * subprio：低优先级
  * channel：IRQ通道
  * group：中断组
 **********************************************************************************/
void BSP_NVIC_Init(uint8_t preprio, uint8_t subprio, uint8_t channel, uint32_t group)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(group);
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = preprio;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = subprio;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannel = channel;

    NVIC_Init(&NVIC_InitStructure);

}

