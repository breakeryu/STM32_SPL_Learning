#ifndef __SYS_H
#define __SYS_H	 
#include "stm32f10x.h"
#include <stdio.h>
#include "misc.h"
#include "stm32f10x_gpio.h"

																	    
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).M4同M3类似,只是寄存器地址变了.
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 






#define SWJ_ENABLE     (uint8_t)0    //Full SWJ (JTAG-DP + SW-DP): Reset State
#define SWJ_NONJTRST   (uint8_t)1    //Full SWJ (JTAG-DP + SW-DP) but without NJTRST
#define SWJ_NOJTAG     (uint8_t)2    //JTAG-DP Disabled and SW-DP Enabled
#define SWJ_DISABLE    (uint8_t)3    //JTAG-DP Disabled and SW-DP Disabled

void sys_SWJ_REMAP_Config(uint8_t SWJ_REMAP);


#endif











