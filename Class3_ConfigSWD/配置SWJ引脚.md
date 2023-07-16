# 一、       补充配置RCC寄存器部分

RCC部分由许多寄存器组成，这里参考HIT_HT的代码，来补充我的代码。RCC整体配置如下流图所示：

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230716215222936-1521638734.png)

具体配置如下代码所示：

 

 

 ```c
 
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
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SRAM,ENABLE);
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FLITF,ENABLE);
   //APB2 Peripheral CLK Enable
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
   //APB1 Peripheral CLK Enable
   RCC->APB1ENR = 0;
   //RTC CLK
   RCC_LSEConfig(RCC_LSE_ON);
   RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
   RCC_RTCCLKCmd(ENABLE);
 }
 
 ```



 



# 二、       添加延时函数

添加文件到BSP中，如下图所示：

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230716215223082-1555538298.png)

在“bsp_rcc.h”中包含此头文件，添加 #include "delay.h"。

然后，在RCC初始化函数中初始化。代码如下图所示：

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230716215222850-2087216397.jpg)

延时函数就配置好了，之后可以在函数中使用。

# 三、       添加SWJ配置函数

为了能够适应引脚资源紧张，不得不使用SWJ引脚时，需要重定义SWJ的引脚。在ST的官方手册RM0008中31.4节对此进行了描述。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230716215223049-872206616.jpg)

通过修改SWJ_CFG寄存器，可以对SWJ的引脚进行配置，使之成为通用IO。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230716215223132-811381308.jpg)

参考标准外设库的示例，GPIO中的JTAG_Remap工程。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230716215223037-1888887034.png)

我们来写自己的SWJ配置函数。

在“sys.c”中，我们编写以下函数：

```c

/**
  * @brief  Configures the SWJ Remap.
  * @param  SWJ_REMAP: defines the SWJ Reamp Function.
  *   This parameter can be one of the following values:
  *     @arg SWJ_ENABLE: Full SWJ Enable (JTAG-DP + SW-DP)
  *     @arg SWJ_NONJTRST: Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST
  *     @arg SWJ_NOJTAG: JTAG-DP Disabled and SW-DP Enabled
  *     @arg SWJ_DISABLE: Full SWJ Disabled (JTAG-DP + SW-DP)
  * @retval None
  */
void sys_SWJ_REMAP_Config(uint8_t SWJ_REMAP)
{
    switch (SWJ_REMAP)
    {
    case SWJ_ENABLE:
        /* Full SWJ Enable (JTAG-DP + SW-DP) */
        break;
    case SWJ_NONJTRST:
        /* Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST */
        GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);
        break;
    case SWJ_NOJTAG:
        /* JTAG-DP Disabled and SW-DP Enabled */
        GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    break;
    case SWJ_DISABLE:
        /* Full SWJ Disabled (JTAG-DP + SW-DP) */
        GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    break;
    default:
        break;
    }
}

```



# 四、       SWJ的配置使用

在主函数中，我们使用该配置，给出如下代码示例：

```c

int main(void)
{
  // SYS CLK Init 
  BSP_RCC_Init();
  /** Config SWJ Reamp 
    *   If using the PA15、PA14、PA13、PB4、PB3 for Remapping Pin, these Clock Must be Config before SWJ REMAP config Function!
    */
  sys_SWJ_REMAP_Config(SWJ_DISABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Configure PA.13 (JTMS/SWDAT), PA.14 (JTCK/SWCLK) and PA.15 (JTDI) as 
    output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* Configure PB.03 (JTDO) and PB.04 (JTRST) as output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  while (1)
  {
    /* code */
  }
  
}

```



 

# 参考资料：

1. RM0008文档

2. STM32F10x_StdPeriph_Lib_V3.6.0