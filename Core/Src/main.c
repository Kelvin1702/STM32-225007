/*
 * main.c
 *
 *  Created on: Mar 23, 2025
 *      Author: Dell
 */
#include "main.h"
#define GPIOD_BASE_ADDR  0x40020C00
#define EXTI_BASE_ADDR  0x40013C00
void LedInit()
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	uint32_t* GPIOD_MODER = (uint32_t*)(GPIOD_BASE_ADDR + 0x00);
	*GPIOD_MODER &= ~(0b1111 << 24);
	*GPIOD_MODER |= (0b01 << 24);
}
#define GPIOA_BASE_ADDR  0x40020000

void ButtonInit()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	uint32_t* GPIOA_MODER = (uint32_t*)(GPIOA_BASE_ADDR + 0x00);
	*GPIOA_MODER &= ~(0b11 << 0);
}

typedef enum (
		LED_GREEN = 12;
        LED_ORANGE ;
        LED_RED ;
        LED_BLUE;

) LED_t;

void LedCtrl(LED_t led, int on_off)
{
#if 0
	uint32_t* GPIOD_MODER = (uint32_t*)(GPIOD_BASE_ADDR + 0x14);
	if(on_off == 1)
	{
		*GPIOD_MODER |= (1 << led);
	}
	else
	{
		*GPIOD_MODER &= ~(1<<led);
	}
#else
	uint32_t* GPIOD_BSRR = (uint32_t*)(GPIOD_BASE_ADDR + 0x18);
	if(on_off == 1)
	{
		*GPIOD_BSRR |= (1<<led);
	}
	else
	{
		*GPIOD_BSRR |= (1<<led+16);
	}
#endif
}

char ButtonState()
{
  uint32_t* GPIOA_IDR = (uint32_t*)(GPIOA_BASE_ADDR + 0x10);
  return (*GPIOA_IDR >> 0) & 1;
}


void EXTI0Init()
{
 uint32_t* EXTI_RSTR = (uint32_t*)(EXTI_BASE_ADDR + 0x08);
 *EXTI_RSTR |= (1 <<0);
 uint32_t* EXTI_FSTR = (uint32_t*)(EXTI_BASE_ADDR + 0x0C);
 uint32_t* EXTI_IMR = (uint32_t*)(EXTI_BASE_ADDR + 0x00);
 *EXTI_IMR |=
}

int main()
{
	HAL_Init();
	LedInit();
	ButtonInit();
	while(1)
	{
		LedCtrl(1);
		HAL_Delay(1000);
		LedCtrl(0);
		HAL_Delay(1000);
	}
	return 0;
}
