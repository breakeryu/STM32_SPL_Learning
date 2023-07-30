
#include "bsp_rcc.h"


/* Public variables ---------------------------------------------------------*/
uint32_t _mcu_rev_id;
uint32_t _mcu_dev_id;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
RCC_ClocksTypeDef RCC_ClockFreq;




void BSP_RCC_Init(void)
{
  /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
  SystemInit();

  /* Configure the System Peripheral clock prescalers */
  BSP_RCC_Periph_Clock_Init();

  //Update SystemCoreClock variable according to Clock Register Values
  SystemCoreClockUpdate();

  /* This function fills the RCC_ClockFreq structure with the current
  frequencies of different on chip clocks (for debug purpose) */
  RCC_GetClocksFreq(&RCC_ClockFreq);

  /* NVIC configuration ------------------------------------------------------*/
  //BSP_RCC_NVIC_Configuration();

  delay_init(72);

  // _mcu_rev_id = DBGMCU_GetREVID();
  // _mcu_dev_id = DBGMCU_GetDEVID();

}


void BSP_RCC_Periph_Clock_Init(void)
{



  //ADC CLK Prescaler, ADC CLK = 72 / 6 = 12 Mhz
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);
  //USB OTG CLK FS Prescaler, when PLL = 72Mhz, OTGFSPRE = 0
  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
  //MCO 
  RCC_MCOConfig(RCC_MCO_NoClock);


  //Clear Clock interrupt register
  RCC->CIR = 0;

  //Reset APB2 and APB1 Peripheral
  RCC->APB2RSTR = 0;
  RCC->APB1RSTR = 0;

  //AHB Peripheral CLK Enable
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SRAM  | RCC_AHBPeriph_FLITF , ENABLE);
  

  //APB2 Peripheral CLK Enable
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA  |
                          RCC_APB2Periph_GPIOB  | RCC_APB2Periph_GPIOC |
                          RCC_APB2Periph_GPIOD,
                        ENABLE);

  //APB1 Peripheral CLK Enable
  RCC->APB1ENR = 0;
  
  //RTC CLK
  RCC_LSEConfig(RCC_LSE_ON);
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
  RCC_RTCCLKCmd(ENABLE);




}

