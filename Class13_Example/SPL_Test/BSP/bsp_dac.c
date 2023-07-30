#include "bsp_dac.h"


void BSP_DAC_init(DAC_Channel_t DACx)
{

    GPIO_InitTypeDef    GPIO_InitStructure;
    DAC_InitTypeDef     DAC_InitStructure;
    uint16_t GPIO_Pin;
    /* DAC Periph clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

    /* Select proper GPIO pin */
	if (DACx == BSP_DAC1) {
		GPIO_Pin = GPIO_Pin_4;
	} else {
		GPIO_Pin = GPIO_Pin_5;
	}

    /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically 
        connected to the DAC converter. In order to avoid parasitic consumption, 
        the GPIO pin should be configured in analog */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    /* DAC channel1 Configuration */
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
   

    /* Init and enable proper DAC */
	if (DACx == BSP_DAC1) {
        DAC_Init(DAC_Channel_1, &DAC_InitStructure);

        /* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is 
        automatically connected to the DAC converter. */
        DAC_Cmd(DAC_Channel_1, ENABLE);
	} else {
        DAC_Init(DAC_Channel_2, &DAC_InitStructure);

        /* Enable DAC Channel2: Once the DAC channel2 is enabled, PA.04 is 
        automatically connected to the DAC converter. */
        DAC_Cmd(DAC_Channel_2, ENABLE);
	}

}


void BSP_DAC_SetChVal(DAC_Channel_t DACx, uint16_t value)
{
    /* Check value */
	if (value > 4095) {
		value = 4095;
	}

    /* Set 12-bit value, right aligned */
	if (DACx == BSP_DAC1) {
        /* Set DAC Channel1 DHR12L register */
        DAC_SetChannel1Data(DAC_Align_12b_R, value);
	} else {
		/* Set DAC Channel2 DHR12L register */
        DAC_SetChannel2Data(DAC_Align_12b_R, value);
	}

}



