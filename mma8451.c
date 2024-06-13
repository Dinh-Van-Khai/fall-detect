#include "MKL46Z4.h"
#include "i2c.h"
#include "mma8451.h"
#include "delay.h"

//MMA8451Q address: 0x1D

void MMA8451_Init(void) {
    I2C_WriteRegister(0x1D, 0x2A, 0x1);
}

Value MMA8451_Read(void) {
    Value data;
	
    uint8_t X_MSB = I2C_ReadRegister(0x1D, OUT_X_MSB);
	delay(1);
    uint8_t X_LSB = I2C_ReadRegister(0x1D, OUT_X_LSB);
	delay(1);
    uint8_t Y_MSB = I2C_ReadRegister(0x1D, OUT_Y_MSB);
	delay(1);
    uint8_t Y_LSB = I2C_ReadRegister(0x1D, OUT_Y_LSB);
	delay(1);
    uint8_t Z_MSB = I2C_ReadRegister(0x1D, OUT_Z_MSB);
	delay(1);
    uint8_t Z_LSB = I2C_ReadRegister(0x1D, OUT_Z_LSB);
    delay(1);
	
	
    int16_t X = ((int16_t)(X_MSB << 8 | X_LSB)) >> 2;
    int16_t Y = ((int16_t)(Y_MSB << 8 | Y_LSB)) >> 2;
    int16_t Z = ((int16_t)(Z_MSB << 8 | Z_LSB)) >> 2;
	
    //Output buffer data format full scale. Default value: 00 (2g)
    //Sensitivity: 4096 counts/g
    //2^14 = 16384 -> 2g: -8192 to 8191

	data.x = (float)X / 8192 * 2;
    data.y = (float)Y / 8192 * 2;
	data.z = (float)Z / 8192 * 2;
	
    return data;
}