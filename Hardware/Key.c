#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Timer.h"
#include "Key.h"

uint8_t Key_Flag[KEY_COUNT];

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructureC;
	GPIO_InitStructureC.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructureC.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructureC.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructureC);
	
	GPIO_InitTypeDef GPIO_InitStructureA;
	GPIO_InitStructureA.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructureA.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_4;
	GPIO_InitStructureA.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructureA);
}

uint8_t Key_Check(uint8_t n ,uint8_t Flag)
{
	if(Key_Flag[n] & Flag)
	{
		if(Flag != KEY_HOLD)
		{
			Key_Flag[n] &= ~Flag;
		}
		return 1;
	}
	return 0;
}

uint8_t Key_GetState(uint8_t n)
{
	if(n == 0)
	{
		if(GPIO_ReadInputDataBit(GPIOA ,GPIO_Pin_0) == 0)
		{
			return KEY_PRESSED;
		}
		return KEY_UNPRESSED;
	}
	else if(n == 1)
	{
		if(GPIO_ReadInputDataBit(GPIOA ,GPIO_Pin_2) == 0)
		{
			return KEY_PRESSED;
		}
		return KEY_UNPRESSED;
	}
	else if(n == 2)
	{
		if(GPIO_ReadInputDataBit(GPIOA ,GPIO_Pin_4) == 0)
		{
			return KEY_PRESSED;
		}
		return KEY_UNPRESSED;
	}
	else if(n == 3)
	{
		if(GPIO_ReadInputDataBit(GPIOC ,GPIO_Pin_14) == 0)
		{
			return KEY_PRESSED;
		}
		return KEY_UNPRESSED;
	}
	return 0;
}

void Key_Tick(void)
{
	static uint8_t Count ,i;
	static uint8_t CurrState[KEY_COUNT] ,PrevState[KEY_COUNT];
	static uint8_t S[KEY_COUNT];
	static uint16_t Time[KEY_COUNT];
	
	for(i = 0; i < KEY_COUNT; i ++)
	{
		if(Time[i] > 0)
		{
			Time[i] --;
		}

	}
	
	Count++;
	if(Count >= 20)
	{
		Count = 0;
		for(i = 0; i < KEY_COUNT; i ++)
		{
			PrevState[i] = CurrState[i];
			CurrState[i] = Key_GetState(i);
		}
	}
	
	for(i = 0; i < KEY_COUNT; i ++)
	{
		if(CurrState[i] == KEY_PRESSED)
		{
			Key_Flag[i] |= KEY_HOLD;//HOLD == 1
		}
		else
		{
			Key_Flag[i] &= ~KEY_HOLD;//HOLD == 0
		}
	
		if(CurrState[i] == KEY_PRESSED && PrevState[i] == KEY_UNPRESSED)
		{
			Key_Flag[i] |= KEY_DOWN;//DOWN == 1
		}
		
		if(CurrState[i] == KEY_UNPRESSED && PrevState[i] == KEY_PRESSED)
		{
			Key_Flag[i] |= KEY_UP;//UP == 1
		}
		
		switch(S[i])
		{
			case 0://空闲
				if(CurrState[i] == KEY_PRESSED)
				{
					Time[i] = 1000;
					S[i] = 1;
				}
				break;
			case 1://单击
				if(CurrState[i] == KEY_UNPRESSED)
				{
					Key_Flag[i] |= KEY_SINGLE;
					S[i] = 0;
				}
				else if(Time[i] == 0)
				{
					Time[i] = 100;
					Key_Flag[i] |= KEY_LONG;
					S[i] = 2;
				}
				break;
			case 2://长按
				if(CurrState[i] == KEY_UNPRESSED)
				{
					S[i] = 0;
				}
				else if(Time[i] == 1)
				{
					Key_Flag[i] |= KEY_REPEAT;
					Time[i] = 100;
					S[i] = 2;
				}
				break;
				
				
		}

	}
	
}


