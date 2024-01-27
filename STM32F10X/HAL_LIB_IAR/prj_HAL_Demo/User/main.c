/*
*********************************************************************************************************
*
*	模块名称 : 主程序模块
*	文件名称 : main.c
*	版    本 : V1.0
*	说    明 : 学习Armfly的底层驱动
*
*	修改记录 :
*		版本号   日期         作者        说明
*		V1.0    2019-07-27   yuXiaoee     1. CMSIS软包版本 V5.5.0
*                                         2. HAL库版本 V2.4.0
*
*	Copyright (C), 2018-2030, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/	
#include "bsp.h"			/* 底层硬件驱动 */





/*
*********************************************************************************************************
*	函 数 名: main
*	功能说明: c程序入口
*	形    参: 无
*	返 回 值: 错误代码(无需处理)
*********************************************************************************************************
*/
int main(void)
{
  uint8_t ucKeyCode;		/* 按键代码 */
  bsp_Init();		/* 硬件初始化 */


  bsp_StartAutoTimer(0, 500);	/* 启动1个500ms的自动重装的定时器 */
  
  /* 进入主程序循环体 */
  while (1)
  {
     
      bsp_Idle();		/* 这个函数在bsp.c文件。用户可以修改这个函数实现CPU休眠和喂狗 */

      /* 判断定时器超时时间 */
      if (bsp_CheckTimer(0))	
      {
          /* 每隔500ms 进来一次 */  
          bsp_LedToggle(0);			
      }
		
    
      /* 按键滤波和检测由后台systick中断服务程序实现，我们只需要调用bsp_GetKey读取键值即可。 */
		ucKeyCode = bsp_GetKey();	/* 读取键值, 无键按下时返回 KEY_NONE = 0 */
		if (ucKeyCode != KEY_NONE)
		{
			switch (ucKeyCode)
			{
				case KEY_DOWN_K1:			/* K1键按下 */
					BEEP_KeyTone();//提示音
					break;

				case KEY_UP_K1:				/* K1键弹起 */
					//no use
					break;

				case KEY_DOWN_K2:			/* K2键按下 */
					BEEP_Start(5, 5, 10); /* 鸣叫50ms，停止50ms，10次*/
					break;

				case KEY_UP_K2:				/* K2键弹起 */
					//no use
					break;

				case KEY_DOWN_K0:			/* K3键按下 */
					BEEP_Start(50, 50, 3); /* 鸣叫500ms，停止500ms，3次*/
					break;

				case KEY_UP_K0:				/* K3键弹起 */
					//no use
					break;
                
                case KEY_DOWN_WKUP:			/* K3键按下 */
					//no use
					break;

				case KEY_UP_WKUP:				/* K3键弹起 */
					//no use
					break;
				
                case SYS_DOWN_K1K2:			/* 摇杆OK键弹起 */
					//no use
					break;

				default:
					/* 其它的键值不处理 */
					break;
			}
		
		}
      
      
  }
}


