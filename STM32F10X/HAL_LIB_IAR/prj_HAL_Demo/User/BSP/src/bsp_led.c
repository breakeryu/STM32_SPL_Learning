/*
*********************************************************************************************************
*
*	ģ������ : LEDָʾ������ģ��
*	�ļ����� : bsp_led.c
*	��    �� : V1.0
*	˵    �� : ����LEDָʾ��
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2018-09-05 armfly  ��ʽ����
*
*	Copyright (C), 2015-2030, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp.h"


#define HARD_LED_NUM	    2
#define LED0 0
#define LED1 1


/* ʹ��GPIOʱ�� */
#define ALL_LED_GPIO_CLK_ENABLE() {	\
		__HAL_RCC_GPIOB_CLK_ENABLE();	\
		__HAL_RCC_GPIOE_CLK_ENABLE();	\
	};


/* ���ζ���GPIO */
typedef struct
{
	GPIO_TypeDef* gpio;
	uint16_t pin;
}LED_GPIO_T;


/* GPIO��PIN���� */
static const LED_GPIO_T led_gpio_list[HARD_LED_NUM] = {
	{GPIOB, GPIO_PIN_5},	/* LED0 */
	{GPIOE, GPIO_PIN_5}	    /* LED1 */
};	


static void LED_configGPIO(void);
static void LED_SetPin(uint8_t i, uint8_t _value);
static uint8_t LED_ReadPin(uint8_t i);

/*
*********************************************************************************************************
*	�� �� ��: bsp_InitLed
*	����˵��: ����LEDָʾ����ص�GPIO,  �ú����� bsp_Init() ���á�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitLed(void)
{
    LED_configGPIO();
    LED_SetPin(LED0,1);
    LED_SetPin(LED1,1);
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_LedOn
*	����˵��: ����ָ����LEDָʾ�ơ�
*	��    ��:  _no : ָʾ����ţ���Χ 1 - 2
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_LedOn(uint8_t _no)
{
	if (_no == 0)
	{
		LED_SetPin(LED0, 0);
	}
	else if (_no == 1)
	{
		LED_SetPin(LED1, 0);
	}
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_LedOff
*	����˵��: Ϩ��ָ����LEDָʾ�ơ�
*	��    ��:  _no : ָʾ����ţ���Χ 1 - 4
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_LedOff(uint8_t _no)
{
	if (_no == 0)
	{
		LED_SetPin(LED0, 1);
	}
	else if (_no == 1)
	{
		LED_SetPin(LED1, 1);
	}
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_LedToggle
*	����˵��: ��תָ����LEDָʾ�ơ�
*	��    ��:  _no : ָʾ����ţ���Χ 1 - 4
*	�� �� ֵ: ��������
*********************************************************************************************************
*/
void bsp_LedToggle(uint8_t _no)
{
	uint32_t pin;
	
	if (_no == 0)
	{
		pin = LED0;
	}
	else if (_no == 1)
	{
		pin = LED1;
	}
	else
	{
		return;
	}

	if (LED_ReadPin(pin))
	{
		LED_SetPin(pin, 0);
	}
	else
	{
		LED_SetPin(pin, 1);
	}	
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_IsLedOn
*	����˵��: �ж�LEDָʾ���Ƿ��Ѿ�������
*	��    ��:  _no : ָʾ����ţ���Χ 1 - 4
*	�� �� ֵ: 1��ʾ�Ѿ�������0��ʾδ����
*********************************************************************************************************
*/
uint8_t bsp_IsLedOn(uint8_t _no)
{
	uint32_t pin;
	
	if (_no == 0)
	{
		pin = LED0;
	}
	else if (_no == 1)
	{
		pin = LED1;
	}
	else
	{
		return 0;
	}
	
	if (LED_ReadPin(pin))
	{
		return 0;	/* �� */
	}
	else
	{
		return 1;	/* �� */
	}
}



/*
*********************************************************************************************************
*	�� �� ��: LED_configGPIO
*	����˵��: ����LED��GPIO
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void LED_configGPIO(void)
{
  
  /*
  ʹ�����пƼ�����103������

  PB5 -- LED0
  PE5 -- LED1

  */
  
  
  
  GPIO_InitTypeDef gpio_init_structure;
  uint8_t i;
  
  /* ʹ�� GPIOʱ�� */
  ALL_LED_GPIO_CLK_ENABLE();  
  
  /* ���� GPIOD ��ص�IOΪ����������� */
  gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init_structure.Pull = GPIO_PULLUP;
  gpio_init_structure.Speed = GPIO_SPEED_FREQ_HIGH;

  for (i = 0; i < HARD_LED_NUM; i++)
  {
      gpio_init_structure.Pin = led_gpio_list[i].pin;
      HAL_GPIO_Init(led_gpio_list[i].gpio, &gpio_init_structure);	
  }
  
  
}



/*
*********************************************************************************************************
*	�� �� ��: LED_SetPin
*	����˵��: ����LED���������״̬
*	��    ��:  i :LED��id�� ��0��ʼ����
*              _value : 1��ʾ����ߵ�ƽ��0��ʾ����͵�ƽ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void LED_SetPin(uint8_t i, uint8_t _value)
{
  
  	if (_value == 0)
	{
		HAL_GPIO_WritePin(led_gpio_list[i].gpio,led_gpio_list[i].pin,GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(led_gpio_list[i].gpio,led_gpio_list[i].pin,GPIO_PIN_SET);
	}
  
}


/*
*********************************************************************************************************
*	�� �� ��: LED_ReadPin
*	����˵��: ����LED���������״̬
*	��    ��:  i :LED��id�� ��0��ʼ����
*	�� �� ֵ: 0��ʾ�Ѿ�������1��ʾδ����
*********************************************************************************************************
*/
static uint8_t LED_ReadPin(uint8_t i)
{
  
  	if (HAL_GPIO_ReadPin(led_gpio_list[i].gpio,led_gpio_list[i].pin) == GPIO_PIN_RESET)
	{
		return 0;
	}
	else
	{
		return 1;
	}
  
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
