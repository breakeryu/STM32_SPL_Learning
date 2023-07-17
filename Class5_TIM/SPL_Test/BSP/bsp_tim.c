
#include "bsp_tim.h"

/*----------------------------------------------------------------------------------*/
/*----------------------------PWM OUTPUT DEMO---------------------------------------*/
/*----------------------------------------------------------------------------------*/

/* Public variables ---------------------------------------------------------*/
uint16_t CCR3_Val = 249;
uint16_t CCR1_Val = 23999;
uint16_t PrescalerValue = 0;
uint16_t TIM4_cntOverFolw = 0;

/* Private variables ---------------------------------------------------------*/
uint16_t capture = 0;

void BSP_PWM_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  /* Remap TIM4_CH3 on PB7 pin */
  GPIO_PinRemapConfig(GPIO_Remap_TIM4, DISABLE);

  /* GPIOB clock enable In BSP_RCC*/

  //Configure the TIM4 Ouput Channel 3 as alternate function push-pull 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);


  /* -----------------------------------------------------------------------
    TIM4 Configuration: generate 1 PWM signals with 1 different duty cycles:
    The TIM4CLK frequency is set to SystemCoreClock (Hz), to get TIM4 counter
    clock at 24 MHz the Prescaler is computed as following:
     - Prescaler = (TIM4CLK / TIM4 counter clock) - 1
    SystemCoreClock is set to 72 MHz for Low-density, Medium-density, High-density
    and Connectivity line devices and to 24 MHz for Low-Density Value line and
    Medium-Density Value line devices

    The TIM4 is running at 36 KHz: TIM4 Frequency = TIM4 counter clock/(ARR + 1)
                                                  = 24 MHz / 666 = 36 KHz
    TIM4 Channel3 duty cycle = (TIM4_CCR3/ TIM4_ARR)* 100 = 50%
    TIM4 Channel3 duty cycle = (TIM4_CCR3/ TIM4_ARR)* 100 = 37.5%
    TIM4 Channel3 duty cycle = (TIM4_CCR3/ TIM4_ARR)* 100 = 25%
    TIM4 Channel3 duty cycle = (TIM4_CCR3/ TIM4_ARR)* 100 = 12.5%
  ----------------------------------------------------------------------- */

  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) (SystemCoreClock / 24000000) - 1;
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 665;
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* PWM Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC3Init(TIM4, &TIM_OCInitStructure);

  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);



  TIM_ARRPreloadConfig(TIM4, ENABLE);

  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);


}


void BSP_PWM_TestDemo(void)
{
  TIM_SetCompare3(TIM4,CCR3_Val);
}


/*----------------------------------------------------------------------------------*/
/*----------------------------BASE TIMER DEMO---------------------------------------*/
/*----------------------------------------------------------------------------------*/

void BSP_Timer_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
   /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);


  /* Remap TIM4_CH1 on PB6 pin */
  GPIO_PinRemapConfig(GPIO_Remap_TIM4, DISABLE);

  /* GPIOB clock enable In BSP_RCC*/

  //Configure the TIM4 Ouput Channel 1 as alternate function push-pull 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

/* -----------------------------------------------------------------------
    TIM4 Configuration: generate 1 PWM signals with 1 different duty cycles:
    The TIM4CLK frequency is set to SystemCoreClock (Hz), to get TIM4 counter
    clock at 24 MHz the Prescaler is computed as following:
     - Prescaler = (TIM4CLK / TIM4 counter clock) - 1
    SystemCoreClock is set to 72 MHz for Low-density, Medium-density, High-density
    and Connectivity line devices and to 24 MHz for Low-Density Value line and
    Medium-Density Value line devices

    The TIM4 is running at 24MHz
  ----------------------------------------------------------------------- */

  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) (SystemCoreClock / 24000000) - 1;
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 65535;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* Prescaler configuration */
  TIM_PrescalerConfig(TIM4, PrescalerValue, TIM_PSCReloadMode_Immediate);


  /* Output Compare Timing Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM4, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Disable);

  TIM_ITConfig(TIM4, TIM_IT_CC1 ,ENABLE);


  /* Enable the TIM4 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);


  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);

}



/**
  * @brief  This function handles TIM4 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM4_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);

    /* Pin PC.06 toggling with frequency = 500 Hz */
    GPIO_WriteBit(GPIOB, GPIO_Pin_6, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_6)));
    capture = TIM_GetCapture1(TIM4);
    TIM_SetCompare1(TIM4, capture + CCR1_Val);
  }

 
}
