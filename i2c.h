#include "MKL46Z4.h"

void I2C_Init(void);
void I2C_Write(uint8_t device_address, uint8_t register_address, uint8_t data);
uint8_t I2C_Read(uint8_t device_address, uint8_t register_address);
