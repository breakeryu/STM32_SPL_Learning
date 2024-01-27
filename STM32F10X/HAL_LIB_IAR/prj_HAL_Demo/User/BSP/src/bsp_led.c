/*
*********************************************************************************************************
*
*	模块名称 : LED指示灯驱动模块
*	文件名称 : bsp_led.c
*	版    本 : V1.0
*	说    明 : 驱动LED指示灯
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2018-09-05 armfly  正式发布
*
*	Copyright (C), 2015-2030, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp.h"


#define HARD_LED_NUM	    2
#define LED0 0
#define LED1 1


/* 使能GPIO时钟 */
#define ALL_LED_GPIO_CLK_ENABLE() {	\
		__HAL_RCC_GPIOB_CLK_ENABLE();	\
		__HAL_RCC_GPIOE_CLK_ENABLE();	\
	};


/* 依次定义GPIO */
typedef struct
{
	GPIO_TypeDef* gpio;
	uint16_t pin;
}LED_GPIO_T;


/* GPIO和PIN定义 */
static const LED_GPIO_T led_gpio_list[HARD_LED_NUM] = {
	{GPIOB, GPIO_PIN_5},	/* LED0 */
	{GPIOE, GPIO_PIN_5}	    /* LED1 */
};	


static void LED_configGPIO(void);
static void LED_SetPin(uint8_t i, uint8_t _value);
static uint8_t LED_ReadPin(uint8_t i);

/*
*********************************************************************************************************
*	函 数 名: bsp_InitLed
*	功能说明: 配置LED指示灯相关的GPIO,  该函数被 bsp_Init() 调用。
*	形    参:  无
*	返 回 值: 无
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
*	函 数 名: bsp_LedOn
*	功能说明: 点亮指定的LED指示灯。
*	形    参:  _no : 指示灯序号，范围 1 - 2
*	返 回 值: 无
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
*	函 数 名: bsp_LedOff
*	功能说明: 熄灭指定的LED指示灯。
*	形    参:  _no : 指示灯序号，范围 1 - 4
*	返 回 值: 无
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
*	函 数 名: bsp_LedToggle
*	功能说明: 翻转指定的LED指示灯。
*	形    参:  _no : 指示灯序号，范围 1 - 4
*	返 回 值: 按键代码
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
*	函 数 名: bsp_IsLedOn
*	功能说明: 判断LED指示灯是否已经点亮。
*	形    参:  _no : 指示灯序号，范围 1 - 4
*	返 回 值: 1表示已经点亮，0表示未点亮
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
		return 0;	/* 灭 */
	}
	else
	{
		return 1;	/* 亮 */
	}
}



/*
*********************************************************************************************************
*	函 数 名: LED_configGPIO
*	功能说明: 配置LED的GPIO
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void LED_configGPIO(void)
{
  
  /*
  使用普中科技玄武103开发板

  PB5 -- LED0
  PE5 -- LED1

  */
  
  
  
  GPIO_InitTypeDef gpio_init_structure;
  uint8_t i;
  
  /* 使能 GPIO时钟 */
  ALL_LED_GPIO_CLK_ENABLE();  
  
  /* 设置 GPIOD 相关的IO为复用推挽输出 */
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
*	函 数 名: LED_SetPin
*	功能说明: 设置LED的引脚输出状态
*	形    参:  i :LED的id， 从0开始编码
*              _value : 1表示输出高电平，0表示输出低电平
*	返 回 值: 无
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
*	函 数 名: LED_ReadPin
*	功能说明: 设置LED的引脚输出状态
*	形    参:  i :LED的id， 从0开始编码
*	返 回 值: 0表示已经点亮，1表示未点亮
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

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
