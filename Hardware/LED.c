#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

uint16_t Count;
uint32_t LED_Num = GPIO_Pin_12;

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructureB;
	GPIO_InitStructureB.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructureB.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructureB.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructureB);
	
	GPIO_SetBits(GPIOB ,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
}

void LED_Flow(int16_t speed)
{
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	Delay_ms (speed);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	Delay_ms (speed);
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	Delay_ms (speed);
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	Delay_ms (speed);
	GPIO_SetBits(GPIOB,GPIO_Pin_15);
	
}

void LED_ON(uint16_t LED_Num)
{
	GPIO_ResetBits(GPIOB ,LED_Num);
}

void LED_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
	GPIO_SetBits(GPIOB,GPIO_Pin_15);
}

void LED_1Flash(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	Delay_ms(1000);
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
	Delay_ms(1000);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
}

void LED_1Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_12) == 0)
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
	else
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}

void LED_Flash(uint16_t a)
{
	GPIO_ResetBits(GPIOA,a);
	Delay_ms(1000);
	GPIO_SetBits(GPIOA,a);
	Delay_ms(1000);
	GPIO_ResetBits(GPIOA,a);
}

void LED_Tick(uint8_t LED_speed ,uint8_t LED_dir)
{
	LED_Init();
	Count ++;
	LED_ON(LED_Num);
	if(LED_dir == 1)
	{
		switch(LED_speed)
		{
			case 1:
				if(Count > 500)
				{
					LED_OFF();
					Count = 0;
					LED_Num *= 2;
					if(LED_Num > GPIO_Pin_15)
					{
						LED_Num = GPIO_Pin_12;
					}
				}
				break;
			case 2:
				if(Count > 1000)
				{
					LED_OFF();
					Count = 0;
					LED_Num *= 2;
					if(LED_Num > GPIO_Pin_15)
					{
						LED_Num = GPIO_Pin_12;
					}
				}
				break;
			case 3:
				if(Count > 200)
				{
					LED_OFF();
					Count = 0;
					LED_Num *= 2;
					if(LED_Num > GPIO_Pin_15)
					{
						LED_Num = GPIO_Pin_12;
					}
				}
				break;
		}
	}
	else if(LED_dir == 2)
	{
		switch(LED_speed)
		{
			case 1:
				if(Count > 500)
				{
					LED_OFF();
					Count = 0;
					LED_Num /= 2;
					if(LED_Num < GPIO_Pin_12)
					{
						LED_Num = GPIO_Pin_15;
					}
				}
				break;
			case 2:
				if(Count > 1000)
				{
					LED_OFF();
					Count = 0;
					LED_Num /= 2;
					if(LED_Num < GPIO_Pin_12)
					{
						LED_Num = GPIO_Pin_15;
					}
				}
				break;
			case 3:
				if(Count > 200)
				{
					LED_OFF();
					Count = 0;
					LED_Num /= 2;
					if(LED_Num < GPIO_Pin_12)
					{
						LED_Num = GPIO_Pin_15;
					}
				}
				break;
		}
	}
}
