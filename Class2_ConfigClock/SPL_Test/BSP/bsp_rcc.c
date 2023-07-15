
#include "bsp_rcc.h"


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
RCC_ClocksTypeDef RCC_ClockFreq;
ErrorStatus HSEStartUpStatus;

/**
  * @brief  Configures Vector Table base location.
  * @param  None
  * @retval None
  */
void BSP_RCC_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable and configure RCC global IRQ channel */
  NVIC_InitStructure.NVIC_IRQChannel = RCC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}





void BSP_RCC_Init(void)
{
  /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
  SystemInit();
   
  /* This function fills the RCC_ClockFreq structure with the current
  frequencies of different on chip clocks (for debug purpose) */
  RCC_GetClocksFreq(&RCC_ClockFreq);

  /* NVIC configuration ------------------------------------------------------*/
  BSP_RCC_NVIC_Configuration();


}



