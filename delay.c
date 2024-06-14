#include "MKL46Z4.h"
#include "delay.h"
#include "state.h"

volatile uint32_t msTick;
volatile uint32_t LED_Blue_Tick;
volatile uint32_t LED_Red_Tick;

void Systick_Init(void) {
	SysTick->CTRL |= (1 << 0);
	SysTick->CTRL |= (1 << 1);
	SysTick->CTRL |= (1 << 2);
	SysTick->LOAD = SystemCoreClock/1000;
	
	NVIC_SetPriority(SysTick_IRQn, 15);
}

void SysTick_Handler(void) {
	msTick++;
	
	if (state == 1 || state == 2) {
		if (LED_Blue_Tick < 500) LED_Blue_Tick++;
		else {
			PTD->PTOR |= 1 << 5;		//Toggle LED xanh
			LED_Blue_Tick = 0;
		}
	}
	
	if (state == 2) {
		if (LED_Red_Tick < 250) LED_Red_Tick++;
		else {
			PTE->PTOR |= 1 << 29;		//Toggle LED do
			LED_Red_Tick = 0;
		}
	}
}

void delay(uint32_t tick) {
	msTick = 0;
	while (msTick < tick);
}
