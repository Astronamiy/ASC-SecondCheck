#include "stm32f10x.h"                  // Device header

#include <stdio.h>

#include "Timer.h"
#include "Motor.h"
#include "Encoder.h"
#include "Delay.h"
#include "Serial.h"
#include "Key.h"
#include "OLED.h"

uint8_t RxData;

//float Target ,Actual ,Out;
//float Kp = 0.001 ,Ki = 0.2 ,Kd = 0;
//float Err0 ,Err1 ,ErrInt;

int main()
{
	Timer_Init();
	Encoder_Init1();
	Encoder_Init2();
	Serial_Init();
	
	Motor_Init();
	Motor_SetPWM(0);
//	Target = 0;
	
	while(1)
	{
		
	}
}

void TIM1_UP_IRQHandler(void)
	{
		if (TIM_GetITStatus(TIM1 ,TIM_IT_Update) == SET)
		{
			Key_Tick();
//			Actual = Encoder_Get2() / 2;
//			
//			Err1 = Err0;
//			Err0 = Target - Actual;
//			
//			ErrInt += Err0;
//			
//			Out = Kp*Err0 + Ki*ErrInt + Kd*(Err0 - Err1);
//			
//			if(Out > 250) Out = 250;
//			if(Out < -250) Out = -250;
//			
//			Motor_SetPWM(Out);
//			
//			Serial_Printf("%f,%f,%f\r\n",Target ,Actual ,Out);
			TIM_ClearITPendingBit(TIM1 ,TIM_IT_Update);
		}
	}
