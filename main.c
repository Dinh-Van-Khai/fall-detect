#include "MKL46Z4.h"
#include "i2c.h"
#include "mma8451.h"
#include "delay.h"
#include "led.h"
#include "state.h"
#include "slcd.h"
#include <math.h>

int main(void) {
	Systick_Init();
	I2C_Init();
	MMA8451_Init();
	delay(1);
	LED_Init();
	EXTI_Init();
	SLCD_Init();
	SLCD_EnablePins();
	
	while (1) {
		switch (state) {
			case 0:
				PTD->PSOR |= 1<<5;
				PTE->PSOR |= 1<<29;
				Systick_Stop();
				break;
			
			case 1:
				SLCD_WriteChar('0');
				Systick_Init();
				PTE->PSOR |= 1<<29;
			
				Accel data = MMA8451_Read();
				float realData = sqrt(data.x * data.x + data.y * data.y + data.z * data.z);
				if (realData > 2) {
					state = 2;
				} else {
					delay(100);
				}
				break;
				
			case 2:
				SLCD_WriteChar('1');
				break;
			
			default:
				break;
		}
	}
}
