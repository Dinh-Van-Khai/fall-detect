#include "MKL46Z4.h"
#include "delay.h"

void LED_Init(void) {
	//Clock
	SIM->SCGC5 |= (1<<12);
	SIM->SCGC5 |= (1<<13);
	
	//GPIO alternative function
	PORTD->PCR[5] |= (1<<8);
	PORTE->PCR[29] |= (1<<8);
	
	//Output mode
	PTD->PDDR |= 1<<5;
	PTE->PDDR |= 1<<29;
	
	PTE->PSOR |= 1<<29;
}

void LED_Active_Reset(void) {
	PTD->PSOR |= 1 << 5;
}

void LED_Fall_Detected(void) {
	PTE->PSOR |= 1<<29;
	delay(250);
	PTE->PCOR |= 1<<29;
	delay(250);
}