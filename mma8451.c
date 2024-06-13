#include "MKL46Z4.h"
#include "i2c.h"
#include "mma8451.h"
#include "delay.h"

void MMA8451_Init(void) {
	I2C_Write(MMA8451_ADD, CTRL_REG1, 0x1);
}

Accel MMA8451_Read(void) {
	uint8_t X_MSB = I2C_Read(MMA8451_ADD, OUT_X_MSB);	delay(1);
	uint8_t X_LSB = I2C_Read(MMA8451_ADD, OUT_X_LSB);	delay(1);
	uint8_t Y_MSB = I2C_Read(MMA8451_ADD, OUT_Y_MSB);	delay(1);
	uint8_t Y_LSB = I2C_Read(MMA8451_ADD, OUT_Y_LSB);	delay(1);
	uint8_t Z_MSB = I2C_Read(MMA8451_ADD, OUT_Z_MSB);	delay(1);
	uint8_t Z_LSB = I2C_Read(MMA8451_ADD, OUT_Z_LSB);	delay(1);

	int16_t X = ((int16_t)(X_MSB << 8 | X_LSB)) >> 2;
	int16_t Y = ((int16_t)(Y_MSB << 8 | Y_LSB)) >> 2;
	int16_t Z = ((int16_t)(Z_MSB << 8 | Z_LSB)) >> 2;

	//2^14 = 16384 -> 2g: -8192 to 8191
	Accel data;
	data.x = (float)X / 8192 * 2;
	data.y = (float)Y / 8192 * 2;
	data.z = (float)Z / 8192 * 2;
	
	return data;
}