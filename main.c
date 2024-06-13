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
	ITR_Init();
	SLCD_Init();
	SLCD_EnablePins();
	
    while (1) {
		if (state ==0) {
			LED_Active_Reset();
			Systick_Shutdown();
			
		} else {
			Systick_Init();
			PTE->PSOR |= 1<<29;
			SLCD_WriteChar('0');
			Value data = MMA8451_Read();
			float realData = sqrt(data.x * data.x + data.y * data.y + data.z * data.z);
			if (realData > 2) {
				state = 2;
				while (state == 2) {
					LED_Fall_Detected();
					SLCD_WriteChar('1');
				}
			}
			delay(100);
		}
    }
}
