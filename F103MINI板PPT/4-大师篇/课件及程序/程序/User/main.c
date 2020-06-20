/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   测试led
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
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
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{	
	uint32_t status=0;
	
	/* LED 端口初始化 */
	LED_GPIO_Config();	
	Key_GPIO_Config();	
	USART_Config();
	
	printf("\r\n设置FLASH的读写保护实验\r\n");
	
	status = FLASH_GetWriteProtectionOptionByte();
	
	printf("\r\n当前写保护状态 = 0x%x\r\n",status);		
	
	
	if (FLASH_GetReadOutProtectionStatus() == SET)
	{
		printf("当前为读保护状态");
	}	
	else
	{
			printf("当前为无读保护状态");
	}


	printf("\r\n按下KEY1可以解除或者设置 写保护\r\n");	
	
	printf("\r\n按下KEY2可以解除或者设置 读保护\r\n");	

	

	while (1)
	{
		if(Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON)	
		{
			
			if(FLASH_GetWriteProtectionOptionByte() == 0xFFFFFFFF)
			{
				printf("\r\n当前为 无写 保护状态");
				
				//1.对FLASH_CR寄存器解除访问限制
				FLASH_Unlock();
				
				printf("\r\n即将进行写保护\r\n");
				
				//2.对所有页进行写保护
				FLASH_EnableWriteProtection(FLASH_WRProt_AllPages);
				
				status = FLASH_GetWriteProtectionOptionByte();
				
				printf("\r\n当前写保护状态 = 0x%x\r\n",status);					
				
				printf("\r\n即将进行系统复位，加载新配置\r\n");	

				NVIC_SystemReset();		
				
			}
			else
			{
				printf("\r\n当前为 写 保护状态");
				
				printf("\r\n即将解除写保护");

				FLASH_Unlock();

				FLASH_EraseOptionBytes();
				
				//解除写保护的时候，不需要如下语句
//				FLASH_EnableWriteProtection(0x0);		
				
				printf("\r\n解除写保护配置完成，系统将自动复位加载新配置\r\n");	

				NVIC_SystemReset();					

			}
		}
		
		if(Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON)	
		{
			
			if(FLASH_GetReadOutProtectionStatus() == SET)
			{
				printf("\r\n当前为读保护状态\r\n");
				
				FLASH_Unlock();

				printf("\r\n即将解除读保护\r\n");
				
				printf("\r\n解除读保护时，需要等待20秒，然后可以重新下载新的程序");

				FLASH_ReadOutProtection(DISABLE);					
			
				printf("\r\n因为解除读保护状态时，程序会被擦除掉，不会看到本语句输出（RAM调试模式除外）\r\n");	
			}
			else
			{
				
				printf("\r\n当前为 无读 保护状态\r\n");

			
				FLASH_Unlock();

				printf("\r\n即将配置为读保护\r\n");

				FLASH_ReadOutProtection(ENABLE);						
			
				printf("\r\n设置读保护完成，请给开发板重新上电\r\n");	
				
			}


		}
		
		
		
//		LED1_ON;			  // 亮

	
	}
}

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/
