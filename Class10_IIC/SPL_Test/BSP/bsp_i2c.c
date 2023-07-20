/**	
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen Majerle, 2014
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */

#include "bsp_i2c.h"

/* Private variables */
static uint32_t TM_I2C_Timeout;
static uint32_t TM_I2C_INT_Clocks[3] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};

/* Private defines */
#define I2C_TRANSMITTER_MODE   0
#define I2C_RECEIVER_MODE      1
#define I2C_ACK_ENABLE         1
#define I2C_ACK_DISABLE        0


void BSP_I2C_Init(I2C_TypeDef *I2Cx)
{

    BSP_I2C_ClkEn(I2Cx);
    BSP_I2C_IOCfg(I2Cx);

    I2C_Cmd(I2Cx,DISABLE);

    BSP_I2C_ModeCfg(I2Cx);

    I2C_Cmd(I2Cx,ENABLE);
}


void BSP_I2C_ClkEn(I2C_TypeDef *I2Cx)
{
    switch ((uint32_t)I2Cx)
    {
    case (uint32_t)I2C1:
        RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
        break;
    case (uint32_t)I2C2:
        RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
        break;
    default:
        break;
    }
}


void BSP_I2C_IOCfg(I2C_TypeDef *I2Cx)
{
    switch ((uint32_t)I2Cx)
    {
    case (uint32_t)I2C1:
    {
        /* Reset I2C IP */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);

        /* Release reset signal of I2C IP */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);

#ifdef  I2C_REMAP_I2C1
        GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);
        BSP_GPIO_SetCfg(GPIOB, GPIO_Pin_8 | GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_AF_OD);
#else
        GPIO_PinRemapConfig(GPIO_Remap_I2C1, DISABLE);
        BSP_GPIO_SetCfg(GPIOB, GPIO_Pin_6 | GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_AF_OD);
#endif
    }
        break;
    case (uint32_t)I2C2:
    {
        /* Reset I2C IP */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);

        /* Release reset signal of I2C IP */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);

        BSP_GPIO_SetCfg(GPIOB, GPIO_Pin_10 | GPIO_Pin_11, GPIO_Speed_50MHz, GPIO_Mode_AF_OD);
    }
        break;
    default:
        break;
    }
}


void BSP_I2C_ModeCfg(I2C_TypeDef *I2Cx)
{
    I2C_InitTypeDef I2C_InitStruct;

    switch ((uint32_t)I2Cx)
    {
    case (uint32_t)I2C1:
        {
            /* Set values */
            I2C_InitStruct.I2C_ClockSpeed = TM_I2C_CLOCK_STANDARD;
            I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
            I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
            I2C_InitStruct.I2C_OwnAddress1 = 0x00;
            I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
            I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
            /* Initialize I2C */
            I2C_Init(I2C1, &I2C_InitStruct);
        }
        break;
    case (uint32_t)I2C2:
        {
            /* Set values */
            I2C_InitStruct.I2C_ClockSpeed = TM_I2C_CLOCK_STANDARD;
            I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
            I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
            I2C_InitStruct.I2C_OwnAddress1 = 0x00;
            I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
            I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
            /* Initialize I2C */
            I2C_Init(I2C2, &I2C_InitStruct);
        }
        break;
    default:
        break;
    }
}


uint8_t BSP_I2C_Read(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg) {
	uint8_t received_data;
	TM_I2C_Start(I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_DISABLE);
	TM_I2C_WriteData(I2Cx, reg);
	TM_I2C_Stop(I2Cx);
	TM_I2C_Start(I2Cx, address, I2C_RECEIVER_MODE, I2C_ACK_DISABLE);
	received_data = TM_I2C_ReadNack(I2Cx);
	return received_data;
}




void BSP_I2C_ReadMulti(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg, uint8_t* data, uint16_t count) {
	TM_I2C_Start(I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_ENABLE);
	TM_I2C_WriteData(I2Cx, reg);
	//TM_I2C_Stop(I2Cx);
	TM_I2C_Start(I2Cx, address, I2C_RECEIVER_MODE, I2C_ACK_ENABLE);
	while (count--) {
		if (!count) {
			/* Last byte */
			*data++ = TM_I2C_ReadNack(I2Cx);
		} else {
			*data++ = TM_I2C_ReadAck(I2Cx);
		}
	}
}


uint8_t BSP_I2C_ReadNoRegister(I2C_TypeDef* I2Cx, uint8_t address) {
	uint8_t data;
	TM_I2C_Start(I2Cx, address, I2C_RECEIVER_MODE, I2C_ACK_ENABLE);
	/* Also stop condition happens */
	data = TM_I2C_ReadNack(I2Cx);
	return data;
}


void BSP_I2C_ReadMultiNoRegister(I2C_TypeDef* I2Cx, uint8_t address, uint8_t* data, uint16_t count) {
	TM_I2C_Start(I2Cx, address, I2C_RECEIVER_MODE, I2C_ACK_ENABLE);
	while (count--) {
		if (!count) {
			/* Last byte */
			*data = TM_I2C_ReadNack(I2Cx);
		} else {
			*data = TM_I2C_ReadAck(I2Cx);
		}
	}
}




void BSP_I2C_Write(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg, uint8_t data) {
	TM_I2C_Start(I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_DISABLE);
	TM_I2C_WriteData(I2Cx, reg);
	TM_I2C_WriteData(I2Cx, data);
	TM_I2C_Stop(I2Cx);
}

void BSP_I2C_WriteMulti(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg, uint8_t* data, uint16_t count) {
	TM_I2C_Start(I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_DISABLE);
	TM_I2C_WriteData(I2Cx, reg);
	while (count--) {
		TM_I2C_WriteData(I2Cx, *data++);
	}
	TM_I2C_Stop(I2Cx);
}

void BSP_I2C_WriteNoRegister(I2C_TypeDef* I2Cx, uint8_t address, uint8_t data) {
	TM_I2C_Start(I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_DISABLE);
	TM_I2C_WriteData(I2Cx, data);
	TM_I2C_Stop(I2Cx);
}

void BSP_I2C_WriteMultiNoRegister(I2C_TypeDef* I2Cx, uint8_t address, uint8_t* data, uint16_t count) {
	TM_I2C_Start(I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_DISABLE);
	while (count--) {
		TM_I2C_WriteData(I2Cx, *data++);
	}
	TM_I2C_Stop(I2Cx);
}


uint8_t BSP_I2C_IsDeviceConnected(I2C_TypeDef* I2Cx, uint8_t address) {
	uint8_t connected = 0;
	/* Try to start, function will return 0 in case device will send ACK */
	if (!TM_I2C_Start(I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_ENABLE)) {
		connected = 1;
	}
	
	/* STOP I2C */
	TM_I2C_Stop(I2Cx);
	
	/* Return status */
	return connected;
}




/* Private functions */
int16_t TM_I2C_Start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction, uint8_t ack) {
	/* Generate I2C start pulse */
	I2Cx->CR1 |= I2C_CR1_START;
	
	/* Wait till I2C is busy */
	TM_I2C_Timeout = TM_I2C_TIMEOUT;
	while (!(I2Cx->SR1 & I2C_SR1_SB)) {
		if (--TM_I2C_Timeout == 0x00) {
			return 1;
		}
	}

	/* Enable ack if we select it */
	if (ack) {
		I2Cx->CR1 |= I2C_CR1_ACK;
	}

	/* Send write/read bit */
	if (direction == I2C_TRANSMITTER_MODE) {
		/* Send address with zero last bit */
		I2Cx->DR = address & ~I2C_OAR1_ADD0;
		
		/* Wait till finished */
		TM_I2C_Timeout = TM_I2C_TIMEOUT;
		while (!(I2Cx->SR1 & I2C_SR1_ADDR)) {
			if (--TM_I2C_Timeout == 0x00) {
				return 1;
			}
		}
	}
	if (direction == I2C_RECEIVER_MODE) {
		/* Send address with 1 last bit */
		I2Cx->DR = address | I2C_OAR1_ADD0;
		
		/* Wait till finished */
		TM_I2C_Timeout = TM_I2C_TIMEOUT;
		while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) {
			if (--TM_I2C_Timeout == 0x00) {
				return 1;
			}
		}
	}
	
	/* Read status register to clear ADDR flag */
	I2Cx->SR2;
	
	/* Return 0, everything ok */
	return 0;
}

void TM_I2C_WriteData(I2C_TypeDef* I2Cx, uint8_t data) {
	/* Wait till I2C is not busy anymore */
	TM_I2C_Timeout = TM_I2C_TIMEOUT;
	while (!(I2Cx->SR1 & I2C_SR1_TXE) && TM_I2C_Timeout) {
		TM_I2C_Timeout--;
	}
	
	/* Send I2C data */
	I2Cx->DR = data;
}

uint8_t TM_I2C_ReadAck(I2C_TypeDef* I2Cx) {
	uint8_t data;
	
	/* Enable ACK */
	I2Cx->CR1 |= I2C_CR1_ACK;
	
	/* Wait till not received */
	TM_I2C_Timeout = TM_I2C_TIMEOUT;
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)) {
		if (--TM_I2C_Timeout == 0x00) {
			return 1;
		}
	}
	
	/* Read data */
	data = I2Cx->DR;
	
	/* Return data */
	return data;
}

uint8_t TM_I2C_ReadNack(I2C_TypeDef* I2Cx) {
	uint8_t data;
	
	/* Disable ACK */
	I2Cx->CR1 &= ~I2C_CR1_ACK;
	
	/* Generate stop */
	I2Cx->CR1 |= I2C_CR1_STOP;
	
	/* Wait till received */
	TM_I2C_Timeout = TM_I2C_TIMEOUT;
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)) {
		if (--TM_I2C_Timeout == 0x00) {
			return 1;
		}
	}

	/* Read data */
	data = I2Cx->DR;
	
	/* Return data */
	return data;
}

uint8_t TM_I2C_Stop(I2C_TypeDef* I2Cx) {
	/* Wait till transmitter not empty */
	TM_I2C_Timeout = TM_I2C_TIMEOUT;
	while (((!(I2Cx->SR1 & I2C_SR1_TXE)) || (!(I2Cx->SR1 & I2C_SR1_BTF)))) {
		if (--TM_I2C_Timeout == 0x00) {
			return 1;
		}
	}
	
	/* Generate stop */
	I2Cx->CR1 |= I2C_CR1_STOP;
	
	/* Return 0, everything ok */
	return 0;
}


