# 一、     NVIC基础

在PM0056这个数据手册中，4.3节对NVIC进行了详细的说明，可以参考其进行NVIC的配置。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230722192239510-1760299529.jpg)

其中，介绍了中断配置的各个寄存器，也说明了使用SPL的配置方法。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230722192239365-1207585887.jpg)

参考涛哥的代码，我们对NVIC进行了一次封装。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230722192239347-1618002732.jpg)

这样，我们就可以方便的调用配置。

# 二、       NVIC中断向量表

在SPL库文件的路径下，我们可以找到“stm32f10x.h”文件。该文件中对芯片的终端向量表进行了详细的定义。在写代码的时候可以参考其名称，进行调用。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230722192239365-1105208409.jpg)

# 三、       NVIC中断回调函数表

在芯片的启动文件中，可以找到所有相关的外设的中断回调函数在STM32的启动文件中定义。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230722192239487-1456262908.jpg)

# 参考资料：

1. [STM32F4 Discovery](https://stm32f4-discovery.net/)

[Libraries and tutorials for STM32F4 series MCUs by Tilen Majerle](https://stm32f4-discovery.net/)

 