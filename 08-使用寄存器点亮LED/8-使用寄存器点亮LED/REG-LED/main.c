
#if 0

#include <rge52.h>

sbit LED  = P0^0

void main(void)
{
	P0 = 0XFE;     // 总线操作  sfr P0   0X80
	
	LED = 0;       // 位操作
}

#endif



#include "stm32f10x.h"

int main (void)
{
#if 0	
	// 打开 GPIOB 端口的时钟
	*( unsigned int * )0x40021018 |=  ( (1) << 3 );
	
	// 配置IO口为输出
	*( unsigned int * )0x40010C00 &=  ~( (0x0f) << (4*0) );
	*( unsigned int * )0x40010C00 |=  ( (1) << (4*0) );
	
	// 控制 ODR 寄存器
	*( unsigned int * )0x40010C0C &= ~(1<<0);
#else
	
	// 打开 GPIOB 端口的时钟
	RCC_APB2ENR  |=  ( (1) << 3 );
	
	// 配置IO口为输出
	GPIOB_CRL &=  ~( (0x0f) << (4*0) );
	GPIOB_CRL |=  ( (1) << (4*0) );
	
	// 控制 ODR 寄存器
	GPIOB_ODR &= ~(1<<0);
	//GPIOB_ODR |= (1<<0);
	
	
#endif
}


void SystemInit(void)
{
	// 函数体为空，目的是为了骗过编译器不报错
}

// 作业

// 1、 实现 GPIO 的其他寄存器的映射

// 2、采用操作BSRR、BRR 来编程，点亮LED






