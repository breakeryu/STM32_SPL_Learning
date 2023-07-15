# 一、     SPL库中芯片选择的宏定义

官方文档中的芯片定义如下：

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105905347-1934182609.jpg)

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105905509-1355193975.jpg)

## 宏定义修改方法一：在代码中修改

在STM32F10x.h中有如下代码：

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105905384-1631544372.jpg)

该代码的是让用户根据自己所使用的芯片的存储器（flash）大小，选择相应的flash编程算法，如果用户使用的是大容量存储芯片（如STM32F103VCT6），则只需要将对应大容量存储器前面的屏蔽符去掉即可，去掉后为：

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105906016-782257519.jpg)其它部分代码不变。

如果使用的是中等容量的存储器芯片(如stm32f103c8t6)，同样是将对应代码前面的屏蔽符去掉即可，如:

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105905360-1053191316.jpg)

## 宏定义修改方法二：在预编译中添加

在第一课，创建工程中，我们演示了如何添加。这里再复习一遍。

选中工程，然后点击Project，选中Properties。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105905554-436876303.png)

选择Symbols，添加对应的宏定义：

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105905405-2122848382.jpg)

 

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105905388-515070683.jpg)

# 二、     时钟频率配置

## 配置时钟频率

函数：system_stm32f10x.c

一般默认72Mhz即可。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105905410-1148046549.jpg)

## 选择并配置外部晶振

配置函数stm32f10x.h

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105906366-401459276.jpg)

这里默认是8Mhz外部晶振。

# 三、     标准外设库的宏定义

## 在预编译中添加“USE_STDPERIPH_DRIVER”

选中工程，然后点击Project，选中Properties。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105905554-436876303.png)

选择Symbols，添加对应的宏定义：

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105905735-411988874.jpg)

 

点击确定，并应用设置。

编译后，没有错误。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105905321-655442268.jpg)

# 四、     编写时钟初始化函数

## 添加文件

我们创建一个文件夹，命名为BSP。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105905378-1889975389.jpg)

接着新建四个文件：

l bsp_board.c    放置板级驱动初始化函数

l bsp_board.h       包含板级驱动的所有头文件

l bsp_rcc.c      时钟驱动函数

l bsp_rcc.h      包含相关的头文件

 

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105905513-2138730175.jpg)

## 查看库函数

我们找到下面的文件“system_stm32f10x.c”，可以查看库函数的时钟配置函数。![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105905494-402637386.png)

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105905430-1303352672.png)

查看系统初始化函数：

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105905410-316307271.jpg)

同样在本文件中，可以修改时钟的频率：

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230715105905733-356055338.jpg)

## 编写时钟初始化函数

```c
#include "bsp_rcc.h"
2.	
3.	
4.	/* Private macro -------------------------------------------------------------*/
5.	/* Private variables ---------------------------------------------------------*/
6.	RCC_ClocksTypeDef RCC_ClockFreq;
7.	ErrorStatus HSEStartUpStatus;
8.	
9.	/**
10.	  * @brief  Configures Vector Table base location.
11.	  * @param  None
12.	  * @retval None
13.	  */
14.	void BSP_RCC_NVIC_Configuration(void)
15.	{
16.	  NVIC_InitTypeDef NVIC_InitStructure;
17.	
18.	  /* Enable and configure RCC global IRQ channel */
19.	  NVIC_InitStructure.NVIC_IRQChannel = RCC_IRQn;
20.	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
21.	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
22.	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
23.	  NVIC_Init(&NVIC_InitStructure);
24.	}
25.	
26.	
27.	
28.	
29.	
30.	void BSP_RCC_Init(void)
31.	{
32.	  /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
33.	  SystemInit();
34.	   
35.	  /* This function fills the RCC_ClockFreq structure with the current
36.	  frequencies of different on chip clocks (for debug purpose) */
37.	  RCC_GetClocksFreq(&RCC_ClockFreq);
38.	
39.	  /* NVIC configuration ------------------------------------------------------*/
40.	  BSP_RCC_NVIC_Configuration();
41.	
42.	
43.	}
44.	
45.	
46.	

```



在bsp_board.h中包含bsp_rcc.h的头文件。

然后在主函数中包含头文件，使用函数。运行。调试。

# 参考资料：

1. [《STM32 库开发实战指南 基于野火 MINI 开发板》12.3.2 断言](https://doc.embedfire.com/mcu/stm32/f103mini/std/pdf/[野火EmbedFire]《STM32库开发实战指南——基于野火MINI开发板》.pdf)

2. [《（已解决）STM32报错Error: L6218E: Undefined symbol assert_param (referred from misc.o).》](https://blog.csdn.net/weixin_52167116/article/details/123219610)