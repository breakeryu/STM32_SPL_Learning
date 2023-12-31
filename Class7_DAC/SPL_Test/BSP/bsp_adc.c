
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
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable DMA1 clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    /* Enable ADC1 and GPIOC clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    /* Configure PA.00 (ADC Channel123_0) as analog input -------------------------*/
    //配置引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


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