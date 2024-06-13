#include "MKL46Z4.h"

extern volatile uint32_t msTick;
extern volatile uint32_t LED_Tick;

void Systick_Init(void);
void Systick_Stop(void);
void delay(uint32_t tick);
