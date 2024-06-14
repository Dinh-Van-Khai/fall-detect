#include "MKL46Z4.h"

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
	
	PTD->PSOR |= 1<<5;
	PTE->PSOR |= 1<<29;
}
