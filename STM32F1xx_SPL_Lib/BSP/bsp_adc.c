
#include "bsp_adc.h"


/*----------------------------------------------------------------------------------*/
/*----------------------------ADC DMA DEMO------------------------------------------*/
/*----------------------------------------------------------------------------------*/

uint16_t ADCConvertedValue;

void BSP_ADC_Init(void)
{
    /* Private variables ---------------------------------------------------------*/
    ADC_InitTypeDef ADC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;

    /* Enable DMA1 clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    /* Enable ADC1 and GPIOC clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    /* Configure PA.00 (ADC Channel123_0) as analog input -------------------------*/
    //配置引脚

    BSP_GPIO_SetCfg(GPIOA, GPIO_Pin_0, GPIO_Speed_50MHz, GPIO_Mode_AIN);

    /* DMA1 channel1 configuration ----------------------------------------------*/
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;             //配置ADC DR寄存器地址（源方向）
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;    //配置转换后值的地址 （目标方向）
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    
    /* Enable DMA1 channel1 */
    DMA_Cmd(DMA1_Channel1, ENABLE);
    
    /* ADC1 configuration ------------------------------------------------------*/
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;     //通道个数
    ADC_Init(ADC1, &ADC_InitStructure);

    /* ADC1 regular channel14 configuration */ 
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5); //配置通道

    /* Enable ADC1 DMA */
    ADC_DMACmd(ADC1, ENABLE);
    
    /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);

    /* Enable ADC1 reset calibration register */   
    ADC_ResetCalibration(ADC1);
    /* Check the end of ADC1 reset calibration register */
    while(ADC_GetResetCalibrationStatus(ADC1));

    /* Start ADC1 calibration */
    ADC_StartCalibration(ADC1);
    /* Check the end of ADC1 calibration */
    while(ADC_GetCalibrationStatus(ADC1));
        
    /* Start ADC1 Software Conversion */ 
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

}

const uint32_t ADC_uRef_C = 3300;	//3300mv

int16_t adc_vltg;
void BSP_ADC_Val2Vltg(void)
{
    int32_t vltg;

    vltg = ((int32_t)ADCConvertedValue * ADC_uRef_C);
	vltg /= 8;
	vltg /= 8;
	vltg /= 8;
	vltg /= 8;

	adc_vltg =  (int16_t)vltg;

}



/*----------------------------------------------------------------------------------*/
/*----------------------------ADC Software Read DEMO------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/**
  * @brief  Initializes the ADC Pin, this is a Aux Function.
  * @param  gp: where x can be (A..G) to select the GPIO peripheral.
  *     @arg GPIOA-GPIOG
  * @param  index: specifies the port bit.
  *     @arg GPIO_Pin_0-GPIO_Pin_15
  * @retval None
  */
static void BSP_ADC_InitPin(GPIO_TypeDef *gp, uint16_t index)
{
    BSP_GPIO_SetCfg(gp, index, GPIO_Speed_50MHz, GPIO_Mode_AIN);
}


/**
  * @brief  Initializes the ADC Channel Pin. User should change this Function for special use.
  *         Max Total Channel Number is 21 . 
  * @retval None
  */
void BSP_ADC_Channel_Init(void)
{
    
    BSP_ADC_InitPin( GPIOC, GPIO_Pin_0 );   /*      ADC1/2/3 CH10    */
    // BSP_ADC_InitPin( GPIOC, GPIO_Pin_1 );   /*      ADC1/2/3 CH11    */
    // BSP_ADC_InitPin( GPIOC, GPIO_Pin_2 );   /*      ADC1/2/3 CH12    */
    // BSP_ADC_InitPin( GPIOC, GPIO_Pin_3 );   /*      ADC1/2/3 CH13    */

    // BSP_ADC_InitPin( GPIOA, GPIO_Pin_0 );   /*      ADC1/2/3 CH0    */
    // BSP_ADC_InitPin( GPIOA, GPIO_Pin_1 );   /*      ADC1/2/3 CH1    */
    // BSP_ADC_InitPin( GPIOA, GPIO_Pin_2 );   /*      ADC1/2/3 CH2    */
    // BSP_ADC_InitPin( GPIOA, GPIO_Pin_3 );   /*      ADC1/2/3 CH3    */

    // BSP_ADC_InitPin( GPIOA, GPIO_Pin_4 );   /*      ADC1/2   CH4    */
    // BSP_ADC_InitPin( GPIOA, GPIO_Pin_5 );   /*      ADC1/2   CH5    */
    // BSP_ADC_InitPin( GPIOA, GPIO_Pin_6 );   /*      ADC1/2   CH6    */
    // BSP_ADC_InitPin( GPIOA, GPIO_Pin_7 );   /*      ADC1/2   CH7    */

    // BSP_ADC_InitPin( GPIOC, GPIO_Pin_4 );   /*      ADC1/2   CH14    */
    // BSP_ADC_InitPin( GPIOC, GPIO_Pin_5 );   /*      ADC1/2   CH15    */

    // BSP_ADC_InitPin( GPIOB, GPIO_Pin_0 );   /*      ADC1/2   CH8    */
    // BSP_ADC_InitPin( GPIOB, GPIO_Pin_1 );   /*      ADC1/2   CH9    */

    // BSP_ADC_InitPin( GPIOF, GPIO_Pin_6 );   /*      ADC3     CH4    */
    // BSP_ADC_InitPin( GPIOF, GPIO_Pin_7 );   /*      ADC3     CH5    */
    // BSP_ADC_InitPin( GPIOF, GPIO_Pin_8 );   /*      ADC3     CH6    */
    // BSP_ADC_InitPin( GPIOF, GPIO_Pin_9 );   /*      ADC3     CH7    */
    // BSP_ADC_InitPin( GPIOF, GPIO_Pin_10 );  /*      ADC3     CH8    */


}

/**
  * @brief  Enable the specified ADC Clock . This is a Aux Function.
  *      
  * @retval None
  */
static void BSP_ADC_CfgCLK(ADC_TypeDef *ADC)
{
    switch ((uint32_t)ADC)
    {
    case (uint32_t)ADC1:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
        }
        break;

    case (uint32_t)ADC2:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
        }
        break;

    case (uint32_t)ADC3:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
        }
        break;
    default:
        break;
    }
}


/**
  * @brief  Initializes the ADC Mode.
  * @param  ADC:  Select the ADC peripheral.
  *     @arg ADC1, ADC2, ADC3
  * @retval None
  */
void BSP_ADC_Init_ADCxMode(ADC_TypeDef * ADC)
{
    ADC_InitTypeDef ADC_InitStructure;

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;     //通道个数
    ADC_Init(ADC, &ADC_InitStructure);

    /* DISABLE ADC DMA */
    ADC_DMACmd(ADC, DISABLE);
    
    /* Enable ADC */
    ADC_Cmd(ADC, ENABLE);

    /* Enable ADC reset calibration register */   
    ADC_ResetCalibration(ADC);
    /* Check the end of ADC reset calibration register */
    while(ADC_GetResetCalibrationStatus(ADC));

    /* Start ADC calibration */
    ADC_StartCalibration(ADC);
    /* Check the end of ADC calibration */
    while(ADC_GetCalibrationStatus(ADC));

}


/**
  * @brief  Initializes all ADC Channels, and config their mode.
  * @retval None
  */
void BSP_ADC_Init_All(void)
{
    BSP_ADC_Channel_Init();

    BSP_ADC_CfgCLK(ADC1);
    BSP_ADC_Init_ADCxMode(ADC1);

    // BSP_ADC_CfgCLK(ADC2);
    // BSP_ADC_Init_ADCxMode(ADC2);

    // BSP_ADC_CfgCLK(ADC3);
    // BSP_ADC_Init_ADCxMode(ADC3);

}

/**
  * @brief  Read the selected ADC Channel.
  * @param  ADC:  Select the ADC peripheral.
  *     @arg ADC1, ADC2, ADC3
  * @param  channel:  read channel.
  *     @arg 1-21
  * @retval None
  */
void BSP_ADC_Read(ADC_TypeDef * ADC, uint8_t channel)
{
    uint32_t timeout = 0xFFF;
	
    ADC_RegularChannelConfig(ADC, channel, 1, ADC_SampleTime_15Cycles); //配置通道

	/* Start software conversion */
	ADC->CR2 |= (uint32_t)ADC_CR2_SWSTART;
	
	/* Wait till done */
	while (!(ADC->SR & ADC_SR_EOC)) {
		if (timeout-- == 0x00) {
			return 0;
		}
	}
	
	/* Return result */
	return ADC->DR;

}