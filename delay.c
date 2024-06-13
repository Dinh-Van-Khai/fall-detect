#include "MKL46Z4.h"
#include "delay.h"
#include "state.h"

volatile uint32_t msTick;
volatile uint32_t LED_Tick;

void Systick_Init(void) {
	SysTick->CTRL |= (1 << 0);
	SysTick->CTRL |= (1 << 1);
	SysTick->CTRL |= (1 << 2);
	SysTick->LOAD = SystemCoreClock/1000;
	
	NVIC_SetPriority(SysTick_IRQn, 15);
}

void Systick_Stop(void) {
	SysTick->CTRL &= ~((uint32_t)(1 << 0));
}

void SysTick_Handler(void) {
	msTick++;
	LED_Tick++;
	if (state == 1) {
		if (LED_Tick == 500) {	//500ms
			PTD->PTOR |= 1 <<5;		//Toggle LED xanh
			LED_Tick = 0;
		}
	} else if (state == 2) {
		if (LED_Tick == 250) {	//250ms
			PTE->PTOR |= 1 <<29;	//Toggle LED do
		}
		if (LED_Tick == 500) { 	//500ms
			PTE->PTOR |= 1 <<29;	//Toggle LED do
			PTD->PTOR |= 1 <<5;		//Toggle LED xanh
			LED_Tick = 0;
		}
	}
}

void delay(uint32_t tick) {
	while (msTick < tick);
	msTick = 0;
}
