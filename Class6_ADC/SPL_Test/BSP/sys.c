#include "sys.h"  
 




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











