#include "stm32f10x.h"                  // Device header
#include "Encoder.h"

int16_t Encoder_Count = 0;
uint8_t CurrState ,PrevState;

uint8_t Encoder_Flag;

void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

uint8_t Encoder_Check(uint8_t Flag)
{
	if(Encoder_Flag & Flag)
	{
		Encoder_Flag &= ~Flag;
		return 1;
	}
	return 0;
}

uint8_t Encoder_GetState(void)
{
	if(GPIO_ReadInputDataBit(GPIOB ,GPIO_Pin_0) == 0 && GPIO_ReadInputDataBit(GPIOB ,GPIO_Pin_1) == 1)
	{
		return ENCODER_PRESSED1;
	}
	else if(GPIO_ReadInputDataBit(GPIOB ,GPIO_Pin_0) == 1 && GPIO_ReadInputDataBit(GPIOB ,GPIO_Pin_1) == 0)
	{
		return ENCODER_PRESSED2;
	}
	return ENCODER_UNPRESSED;
}

void Encoder_Tick(void)
{
	static uint8_t Count;
	static uint8_t CurrState ,PrevState;
	
	Count++;
	if(Count >= 25)
	{
		Count = 0;
		PrevState = CurrState;
		CurrState = Encoder_GetState();
	}
	
	if(CurrState == ENCODER_PRESSED1 && PrevState == ENCODER_UNPRESSED)
	{
		Encoder_Flag |= Encoder_Turn1;//DOWN == 1
	}
	else if(CurrState == ENCODER_PRESSED2 && PrevState == ENCODER_UNPRESSED)
	{
		Encoder_Flag |= Encoder_Turn2;//UP == 1
	}
}
	

