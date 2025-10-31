#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Key.h"

void OLED_Menu_Father(uint8_t a)
{
	OLED_ShowChar(a ,1 ,'>');
	OLED_ShowString(1 ,2 ,"LED Control");
	OLED_ShowString(2 ,2 ,"PID");
	OLED_ShowString(3 ,2 ,"Image");
	OLED_ShowString(4 ,2 ,"Angle");
}

void OLED_Menu_LED_Control(uint8_t a)
{
	OLED_ShowChar(a ,1 ,'>');
	OLED_ShowString(1 ,1 ,"LED Control");
	OLED_ShowString(2 ,2 ,"LED_speed");
	OLED_ShowString(3 ,2 ,"LED_dir");
}

void OLED_Menu_PID(uint8_t a)
{
	OLED_ShowChar(a ,1 ,'>');
	OLED_ShowString(1 ,1 ,"PID");
	OLED_ShowString(2 ,2 ,"kp");
	OLED_ShowString(3 ,2 ,"ki");
	OLED_ShowString(4 ,2 ,"kd");
}

void OLED_Menu_Image(void)
{
	OLED_ShowChar(2 ,1 ,'>');
	OLED_ShowString(1 ,1 ,"Image");
	OLED_ShowString(2 ,2 ,"Image");
}

void OLED_Menu_Angle(void)
{
	OLED_ShowChar(2 ,1 ,'>');
	OLED_ShowString(1 ,1 ,"Angle");
	OLED_ShowString(2 ,2 ,"Angle");
}


