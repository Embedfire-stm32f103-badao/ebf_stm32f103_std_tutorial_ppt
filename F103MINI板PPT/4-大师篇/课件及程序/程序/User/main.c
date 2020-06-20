/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����led
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
	
#include "stm32f10x.h"
#include "bsp_led.h"
#include "./key/bsp_key.h"  
#include "./usart/bsp_usart.h"


#define SOFT_DELAY Delay(0x0FFFFF);

void Delay(__IO u32 nCount); 

/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	
	uint32_t status=0;
	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	
	Key_GPIO_Config();	
	USART_Config();
	
	printf("\r\n����FLASH�Ķ�д����ʵ��\r\n");
	
	status = FLASH_GetWriteProtectionOptionByte();
	
	printf("\r\n��ǰд����״̬ = 0x%x\r\n",status);		
	
	
	if (FLASH_GetReadOutProtectionStatus() == SET)
	{
		printf("��ǰΪ������״̬");
	}	
	else
	{
			printf("��ǰΪ�޶�����״̬");
	}


	printf("\r\n����KEY1���Խ���������� д����\r\n");	
	
	printf("\r\n����KEY2���Խ���������� ������\r\n");	

	

	while (1)
	{
		if(Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON)	
		{
			
			if(FLASH_GetWriteProtectionOptionByte() == 0xFFFFFFFF)
			{
				printf("\r\n��ǰΪ ��д ����״̬");
				
				//1.��FLASH_CR�Ĵ��������������
				FLASH_Unlock();
				
				printf("\r\n��������д����\r\n");
				
				//2.������ҳ����д����
				FLASH_EnableWriteProtection(FLASH_WRProt_AllPages);
				
				status = FLASH_GetWriteProtectionOptionByte();
				
				printf("\r\n��ǰд����״̬ = 0x%x\r\n",status);					
				
				printf("\r\n��������ϵͳ��λ������������\r\n");	

				NVIC_SystemReset();		
				
			}
			else
			{
				printf("\r\n��ǰΪ д ����״̬");
				
				printf("\r\n�������д����");

				FLASH_Unlock();

				FLASH_EraseOptionBytes();
				
				//���д������ʱ�򣬲���Ҫ�������
//				FLASH_EnableWriteProtection(0x0);		
				
				printf("\r\n���д����������ɣ�ϵͳ���Զ���λ����������\r\n");	

				NVIC_SystemReset();					

			}
		}
		
		if(Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON)	
		{
			
			if(FLASH_GetReadOutProtectionStatus() == SET)
			{
				printf("\r\n��ǰΪ������״̬\r\n");
				
				FLASH_Unlock();

				printf("\r\n�������������\r\n");
				
				printf("\r\n���������ʱ����Ҫ�ȴ�20�룬Ȼ��������������µĳ���");

				FLASH_ReadOutProtection(DISABLE);					
			
				printf("\r\n��Ϊ���������״̬ʱ������ᱻ�����������ῴ������������RAM����ģʽ���⣩\r\n");	
			}
			else
			{
				
				printf("\r\n��ǰΪ �޶� ����״̬\r\n");

			
				FLASH_Unlock();

				printf("\r\n��������Ϊ������\r\n");

				FLASH_ReadOutProtection(ENABLE);						
			
				printf("\r\n���ö�������ɣ���������������ϵ�\r\n");	
				
			}


		}
		
		
		
//		LED1_ON;			  // ��

	
	}
}

void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/
