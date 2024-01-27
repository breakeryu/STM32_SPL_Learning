#include "bsp_dac.h"


void BSP_DAC_init(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef            DAC_InitStructure;

    /* DAC Periph clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

 

    /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically 
        connected to the DAC converter. In order to avoid parasitic consumption, 
        the GPIO pin should be configured in analog */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    /* DAC channel1 Configuration */
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_Software;
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
    DAC_Init(DAC_Channel_1, &DAC_InitStructure);

    /* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is 
    automatically connected to the DAC converter. */
    DAC_Cmd(DAC_Channel_1, ENABLE);

    

}


uint16_t dac_Data = 100;

void BSP_DAC_SetChVal(void)
{
    /* Set DAC Channel1 DHR12L register */
    DAC_SetChannel1Data(DAC_Align_12b_R, dac_Data);

    /* Start DAC Channel1 conversion by software */
    DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);
}
