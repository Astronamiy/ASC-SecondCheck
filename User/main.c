#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "Encoder.h"
#include "OLED.h"
#include "Timer.h"
#include "Delay.h"
#include "Serial.h"

uint8_t RxData;

int main()
{
	while(1)
	{
		if(Serial_GetRxFlag() == 1)
		{
		}
	}
}

