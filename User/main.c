#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "Encoder.h"
#include "OLED.h"
#include "Timer.h"

int Speed;

int main()
{
	Motor_Init();
	Encoder_Init();
	OLED_Init();
	Timer_Init();
	Motor_SetSpeed1(-0);
	Motor_SetSpeed2(-20);
	while(1)
	{
		OLED_ShowSignedNum(1 ,1 ,Speed ,5);
	}
}

void TIM2_IRQHandler(void)
	{
		if (TIM_GetITStatus(TIM2 ,TIM_IT_Update) == SET)
		{
			Speed = Encoder_Get();
			TIM_ClearITPendingBit(TIM2 ,TIM_IT_Update);
		}
	}