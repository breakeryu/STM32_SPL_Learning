/*
*********************************************************************************************************
*
*	ģ������ : ������ģ��
*	�ļ����� : main.c
*	��    �� : V1.0
*	˵    �� : ѧϰArmfly�ĵײ�����
*
*	�޸ļ�¼ :
*		�汾��   ����         ����        ˵��
*		V1.0    2019-07-27   yuXiaoee     1. CMSIS����汾 V5.5.0
*                                         2. HAL��汾 V2.4.0
*
*	Copyright (C), 2018-2030, ���������� www.armfly.com
*
*********************************************************************************************************
*/	
#include "bsp.h"			/* �ײ�Ӳ������ */





/*
*********************************************************************************************************
*	�� �� ��: main
*	����˵��: c�������
*	��    ��: ��
*	�� �� ֵ: �������(���账��)
*********************************************************************************************************
*/
int main(void)
{
  uint8_t ucKeyCode;		/* �������� */
  uint8_t read;
  const char buf1[] = "���յ���������1\r\n";
  const char buf2[] = "���յ���������2\r\n";
  const char buf3[] = "���յ���������3\r\n";
  const char buf4[] = "���յ���������4\r\n";
  
  bsp_Init();		/* Ӳ����ʼ�� */
  bsp_StartAutoTimer(0, 500);	/* ����1��500ms���Զ���װ�Ķ�ʱ�� */
  comSendBuf(COM1, (uint8_t *)buf1, strlen(buf1));
  /* ����������ѭ���� */
  while (1)
  {
     
      bsp_Idle();		/* ���������bsp.c�ļ����û������޸��������ʵ��CPU���ߺ�ι�� */

      /* �ж϶�ʱ����ʱʱ�� */
      if (bsp_CheckTimer(0))	
      {
          /* ÿ��500ms ����һ�� */  
          bsp_LedToggle(0);			
      }
      
      /* ���յ��Ĵ�������� */
      if (comGetChar(COM1, &read))
      {
          switch (read)
          {
              case '1':
                  comSendBuf(COM1, (uint8_t *)buf1, strlen(buf1));
                  break;

              case '2':
                  comSendBuf(COM1, (uint8_t *)buf2, strlen(buf2));
                  break;

              case '3':
                  comSendBuf(COM1, (uint8_t *)buf3, strlen(buf3));
                  break;

              case '4':
                  comSendBuf(COM1, (uint8_t *)buf4, strlen(buf4));
                  break;	
              
              default:
                  break;
          }
      }
    
      /* �����˲��ͼ���ɺ�̨systick�жϷ������ʵ�֣�����ֻ��Ҫ����bsp_GetKey��ȡ��ֵ���ɡ� */
		ucKeyCode = bsp_GetKey();	/* ��ȡ��ֵ, �޼�����ʱ���� KEY_NONE = 0 */
		if (ucKeyCode != KEY_NONE)
		{
			switch (ucKeyCode)
			{
				case KEY_DOWN_K1:			/* K1������ */
					BEEP_KeyTone();//��ʾ��
					break;

				case KEY_UP_K1:				/* K1������ */
					//no use
					break;

				case KEY_DOWN_K2:			/* K2������ */
					BEEP_Start(5, 5, 10); /* ����50ms��ֹͣ50ms��10��*/
					break;

				case KEY_UP_K2:				/* K2������ */
					//no use
					break;

				case KEY_DOWN_K0:			/* K3������ */
					BEEP_Start(50, 50, 3); /* ����500ms��ֹͣ500ms��3��*/
					break;

				case KEY_UP_K0:				/* K3������ */
					//no use
					break;
                
                case KEY_DOWN_WKUP:			/* K3������ */
					//no use
					break;

				case KEY_UP_WKUP:				/* K3������ */
					//no use
					break;
				
                case SYS_DOWN_K1K2:			/* ҡ��OK������ */
					//no use
					break;

				default:
					/* �����ļ�ֵ������ */
					break;
			}
		
		}
      
      
  }
}


