stm32cubeide创建一个SPL项目

# 1.   新建一个STM32项目，选择芯片型号

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230714083253601-1939387911.jpg)

# 2.   选择空白项目类型

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230714083253626-2067269378.jpg)

# 3.   创建好的空白工程

 

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230714083253654-327978818.png)

 

# 4.   下载SPL库，并添加SPL库到工程文件夹

下载地址：https://www.st.com/en/embedded-software/stm32-standard-peripheral-libraries.html

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230714083253609-171397629.jpg)

这里我下载是F1的，解压后，

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230714083253541-1066196171.jpg)

进入解压后的文件夹，复制Libraries文件夹到我们创建的工程文件夹：

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230714083253597-738740377.jpg)

# 5.   配置工程

在Libraries上右键选择Resource Configurations->Exclude from Build…将Debug和Release的勾去掉，OK使这个文件夹编译进工程。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230714083253685-324956458.jpg)

之后右键标准库中的startup删除这个文件夹，我们使用IDE自动生成的启动文件。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230714083253568-604372094.jpg)

下一步将库文件中的stm32f10x_conf.h和stm32f10x_it.h复制到工程目录的Inc文件夹中，将stm32f10x_it.c放到Src文件夹中，Refresh工程。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230714083253652-487160686.jpg)

------

之后右键工程名，点击Properties，添加头文件路径和全局宏。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230714083253599-1597522329.png)

 

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230714083253683-572585701.jpg)

选择有头文件的文件夹，添加头文件路径：

Libraries\STM32F10x_StdPeriph_Driver\inc

Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x

Libraries\CMSIS\CM3\CoreSupport



------

添加宏STM32F10X_HD和USE_STDPERIPH_DRIVE。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230714083253568-1509471985.jpg)

------

下一步打开工程中的core_cm3.c,修改__STREXB和__STREXH函数，在r前加&符号。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230714083253659-223838658.jpg)

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230714083253691-1816207170.png)

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230714083253696-1163990470.jpg)

 

# 6.   点击编译工程，没有错误。至此，完成了SPL的工程的创建。

![img](https://img2023.cnblogs.com/blog/1423856/202307/1423856-20230714083253623-1434760329.jpg)

 