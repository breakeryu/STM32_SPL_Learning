/*
*********************************************************************************************************
*
*	ģ������ : BSPģ��(For STM32F103)
*	�ļ����� : bsp.c
*	��    �� : V1.0
*	˵    �� : ����Ӳ���ײ�������������ļ���ÿ��c�ļ����� #include "bsp.h" ���������е���������ģ�顣
*			   bsp = Borad surport packet �弶֧�ְ�
*	�޸ļ�¼ :
*		�汾��  ����         ����       ˵��
*		V1.0    2018-07-29  Eric2013   ��ʽ����
*
*	Copyright (C), 2018-2030, ���������� www.armfly.com
*
*********************************************************************************************************
*/
#include "bsp.h"



/*
*********************************************************************************************************
*	                                   ��������
*********************************************************************************************************
*/
static void SystemClock_Config(void);


/*
*********************************************************************************************************
*	�� �� ��: bsp_Init
*	����˵��: ��ʼ�����е�Ӳ���豸���ú�������CPU�Ĵ���������ļĴ�������ʼ��һЩȫ�ֱ�����ֻ��Ҫ����һ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_Init(void)
{
	/* 
       STM32F103 HAL ���ʼ������ʱϵͳ�õĻ���F103�Դ���16MHz��HSIʱ��:
	   - ���ú���HAL_InitTick����ʼ���δ�ʱ���ж�1ms��
	   - ����NVIV���ȼ�����Ϊ4��
	 */
	HAL_Init();

	/* 
       ����ϵͳʱ�ӵ�72MHz
       - �л�ʹ��HSE��
       - �˺��������ȫ�ֱ���SystemCoreClock������������HAL_InitTick��
    */
	SystemClock_Config();

	bsp_InitKey();    	/* ������ʼ����Ҫ���ڵδ�ʱ��֮ǰ����Ϊ��ť�����ͨ���δ�ʱ��ɨ�� */
	bsp_InitTimer();  	/* ��ʼ���δ�ʱ�� */
	bsp_InitUart();		/* ��ʼ������ */
	bsp_InitLed();    	/* ��ʼ��LED */	
    BEEP_InitHard();    /* ��ʼ�������� */
}

/*
*********************************************************************************************************
*	�� �� ��: SystemClock_Config
*	����˵��: ��ʼ��ϵͳʱ��
*            System Clock source            = PLL (HSE)
*            SYSCLK(Hz)                     = 72000000
*            HCLK(Hz)                       = 72000000
*            PCLK2 = HCLK / 1               = 72000000  (APB2Periph)
*            PCLK1 = HCLK / 2               = 36000000  (APB1Periph)
*            AHB Prescaler                  = 1
*            APB1 Prescaler                 = 2
*            APB2 Prescaler                 = 1
*            HSE Frequency(Hz)              = 8000000
*            HSE PREDIV1                    = 1
*            PLLMUL                         = 9
*            Flash Latency(WS)              = 2
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	
	/* оƬ�ڲ���LDO��ѹ������ĵ�ѹ��Χ��ѡ�õ�PWR_REGULATOR_VOLTAGE_SCALE1 */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* ʹ��HSE����ѡ��HSE��ΪPLLʱ��Դ */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
        Error_Handler(__FILE__, __LINE__);
	}

	/* 
       ѡ��PLL�������Ϊϵͳʱ��
		HCLK = SYSCLK / 1  (AHB1Periph)
		PCLK2 = HCLK / 1   (APB2Periph)
		PCLK1 = HCLK / 2   (APB1Periph)
    */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
								  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	/* �˺��������SystemCoreClock������������HAL_InitTick */
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
        Error_Handler(__FILE__, __LINE__);
	}

    /* ʹ��SYSʱ��*/
	__HAL_RCC_SYSCFG_CLK_ENABLE() ;

}

/*
*********************************************************************************************************
*	�� �� ��: Error_Handler
*	��    ��: file : Դ�����ļ����ơ��ؼ��� __FILE__ ��ʾԴ�����ļ�����
*			  line �������кš��ؼ��� __LINE__ ��ʾԴ�����к�
*	�� �� ֵ: ��
*		Error_Handler(__FILE__, __LINE__);
*********************************************************************************************************
*/
void Error_Handler(char *file, uint32_t line)
{
	/* 
		�û���������Լ��Ĵ��뱨��Դ�����ļ����ʹ����кţ����罫�����ļ����кŴ�ӡ������
		printf("Wrong parameters value: file %s on line %d\r\n", file, line) 
	*/
	
	/* ����һ����ѭ��������ʧ��ʱ������ڴ˴��������Ա����û���� */
	if (line == 0)
	{
		return;
	}
	
	while(1)
	{
	}
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_RunPer10ms
*	����˵��: �ú���ÿ��10ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ����ʱ��Ҫ���ϸ��
*			������Է��ڴ˺��������磺����ɨ�衢���������п��Ƶȡ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_RunPer10ms(void)
{
	bsp_KeyScan10ms();
    BEEP_Pro();
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_RunPer1ms
*	����˵��: �ú���ÿ��1ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ��Ҫ�����Դ��������
*			 ���Է��ڴ˺��������磺��������ɨ�衣
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_RunPer1ms(void)
{
	
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_Idle
*	����˵��: ����ʱִ�еĺ�����һ����������for��whileѭ������������Ҫ���� CPU_IDLE() �������ñ�������
*			 ������ȱʡΪ�ղ������û��������ι��������CPU��������ģʽ�Ĺ��ܡ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_Idle(void)
{
	/* --- ι�� */

	/* --- ��CPU�������ߣ���Systick��ʱ�жϻ��ѻ��������жϻ��� */

	/* ���� emWin ͼ�ο⣬���Բ���ͼ�ο���Ҫ����ѯ���� */
	//GUI_Exec();

	/* ���� uIP Э�飬���Բ���uip��ѯ���� */
	//TOUCH_CapScan();
}

/*
*********************************************************************************************************
*	�� �� ��: HAL_Delay
*	����˵��: �ض�������ӳٺ������滻HAL�еĺ�������ΪHAL�е�ȱʡ����������Systick�жϣ������USB��SD��
*             �ж������ӳٺ��������������Ҳ����ͨ������HAL_NVIC_SetPriority����Systick�ж�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
/* ��ǰ����ʹ��stm32f4xx_hal.cĬ�Ϸ�ʽʵ�֣�δʹ�������ض���ĺ��� */
#if 0
void HAL_Delay(uint32_t Delay)
{
	bsp_DelayUS(Delay * 1000);
}
#endif

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
