#ifndef __BSP_ID_H
#define __BSP_ID_H

#include "stm32f10x.h"


/**
 * @defgroup TM_ID_Macros
 * @brief    Library defines
 *
 * Defines for register locations inside STM32F4xx devices
 * @{
 */

/**
 * @brief Unique ID register address location
 */
#define ID_UNIQUE_ADDRESS		0x1FFFF7E8

/**
 * @brief Flash size register address
 */
#define ID_FLASH_ADDRESS		0x1FFFF7E0

/**
 * @brief Device ID register address
 */
#define ID_DBGMCU_IDCODE		0xE0042000

 /**
 * @}
 */

/**
 * @defgroup TM_ID_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Get STM32F1xx device signature
 * @note   Defined as macro to get maximal response time
 * @param  None
 * @retval Device signature, bits 11:0 are valid, 15:12 are always 0.
 *           - 0x412: low-density devices
 *           - 0x410: medium-density devices
 *           - 0x414: high-density devices
 *           - 0x430: XL-density devices
 *           - 0x418: connectivity devices
 */
#define TM_ID_GetSignature()	((*(uint16_t *) (ID_DBGMCU_IDCODE)) & 0x0FFF)

/**
 * @brief  Get STM32F1xx device revision
 * @note   Defined as macro to get maximal response time
 * @param  None
 * @retval Device revision value
 * low-density devices:
 *           - 0x1000: Revision A
 * medium-density devices:
 *           - 0x0000: Revision A
 *           - 0x2000: Revision B
 *           - 0x2001: Revision Y
 *           - 0x2003: Revision 1, 2, 3, X or Y
 * high-density devices:
 *           – 0x1000 = Revision A or 1
 *           – 0x1001 = Revision Z
 *           – 0x1003 = Revision 1, 2, 3, X or Y
 * In XL-density devices:
 *           – 0x1000 = Revision A or 1
 * In connectivity line devices:
 *           – 0x1000 = Revision A
 *           – 0x1001 = Revision Z
 * 
 */
#define TM_ID_GetRevision()		(*(uint16_t *) (DBGMCU->IDCODE + 2))

/**
 * @brief  Get STM32F1xx device's flash size in kilo bytes
 * @note   Defined as macro to get maximal response time
 * @param  None
 * @retval Flash size in kilo bytes
 */
#define TM_ID_GetFlashSize()	(*(uint16_t *) (ID_FLASH_ADDRESS))

/**
 * @brief  Get unique ID number in 8-bit format
 * @note   STM32F1xx has 96bits long unique ID, so 12 bytes are available for read in 8-bit format
 * @note   Defined as macro to get maximal response time
 * @param  x: Byte number: specify which part of 8 bits you want to read
 *               - Values between 0 and 11 are allowed
 * @retval Unique ID address
 */
#define TM_ID_GetUnique8(x)		((x >= 0 && x < 12) ? (*(uint8_t *) (ID_UNIQUE_ADDRESS + (x))) : 0)
	
/**
 * @brief  Get unique ID number in 16-bit format
 * @note   STM32F1xx has 96bits long unique ID, so 6 2-bytes values are available for read in 16-bit format
 * @note   Defined as macro to get maximal response time
 * @param  x: Byte number: specify which part of 16 bits you want to read
 *               - Values between 0 and 5 are allowed
 * @retval Unique ID address
 */
#define TM_ID_GetUnique16(x)	((x >= 0 && x < 6) ? (*(uint16_t *) (ID_UNIQUE_ADDRESS + 2 * (x))) : 0)

/**
 * @brief  Get unique ID number in 32-bit format
 * @note   STM32F1xx has 96bits long unique ID, so 3 4-bytes values are available for read in 32-bit format
 * @note   Defined as macro to get maximal response time
 * @param  x: Byte number: specify which part of 16 bits you want to read
 *               - Values between 0 and 2 are allowed
 * @retval Unique ID address
 */
#define TM_ID_GetUnique32(x)	((x >= 0 && x < 3) ? (*(uint32_t *) (ID_UNIQUE_ADDRESS + 4 * (x))) : 0)

/**
 * @}
 */
 
/**
 * @}
 */

/**
 * @}
 */




#endif//__BSP_ID_H


