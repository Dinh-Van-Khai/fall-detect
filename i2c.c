#include "MKL46Z4.h"
#include "i2c.h"

void I2C_Init(void) {
	SIM->CLKDIV1 |= (1u<<17) | (1u<<16);	//bus clock is 24/3 = 8MHz

	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK; 	//clock to PTE24 and PTE25 for I2C0
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK; 		//clock to I2C0

	PORTE->PCR[24] |= 0x5 << 8;		//alternative 5 - 101 for MUX field
	PORTE->PCR[25] |= 0x5 << 8;

	I2C0->F = 0x80;		//mult=2h ICR=00h

	I2C0->C1 = 0xB0;	//10110000 - module enable, interrupt disable, master, transmit,

	//acknowledge bit sent,repeated start off, wake up off, DMA off
	I2C0->C2 = 0x00;
}

void I2C_Write(uint8_t device_address, uint8_t register_address, uint8_t data) {
	// Start I2C transmission
	// Set to transmit mode
	I2C0->C1 |= I2C_C1_TX_MASK;

	// Send start signal
	I2C0->C1 |= I2C_C1_MST_MASK;

	// Send device address with write bit
	I2C0->D = device_address << 1;
	while (!(I2C0->S & I2C_S_IICIF_MASK));
	I2C0->S |= I2C_S_IICIF_MASK;

	// Send register address
	I2C0->D = register_address;
	while (!(I2C0->S & I2C_S_IICIF_MASK));
	I2C0->S |= I2C_S_IICIF_MASK;

	// Send data
	I2C0->D = data;
	while (!(I2C0->S & I2C_S_IICIF_MASK));
	I2C0->S |= I2C_S_IICIF_MASK;

	// Send stop signal    
	I2C0->C1 &= ~I2C_C1_MST_MASK;
	// Set to receive mode
	I2C0->C1 &= ~I2C_C1_TX_MASK;
}

uint8_t I2C_Read(uint8_t device_address, uint8_t register_address) {
	uint8_t result;
	//Start I2C transmission
	I2C0->C1 |= I2C_C1_TX_MASK;
	I2C0->C1 |= I2C_C1_MST_MASK;

	//Send device address with write bit
	I2C0->D = device_address << 1;
	while (!(I2C0->S & I2C_S_IICIF_MASK));
	I2C0->S |= I2C_S_IICIF_MASK;

	//Send register address
	I2C0->D = register_address;
	while (!(I2C0->S & I2C_S_IICIF_MASK));
	I2C0->S |= I2C_S_IICIF_MASK;

	//Repeated start to change to read mode
	I2C0->C1 |= I2C_C1_RSTA_MASK;

	//Send device address
	I2C0->D = (device_address << 1) | 0x01;
	while (!(I2C0->S & I2C_S_IICIF_MASK));
	I2C0->S |= I2C_S_IICIF_MASK;

	//Recieve mode
	I2C0->C1 &= ~I2C_C1_TX_MASK;

	//Send NACK
	I2C0->C1 |= I2C_C1_TXAK_MASK; 

	//Fake read
	result = I2C0->D;
	while (!(I2C0->S & I2C_S_IICIF_MASK));
	I2C0->S |= I2C_S_IICIF_MASK;

	//Read data
	result = I2C0->D;
	while (!(I2C0->S & I2C_S_IICIF_MASK)){}
	I2C0->S |= I2C_S_IICIF_MASK;

	//Send stop signal
	I2C0->C1 &= ~I2C_C1_MST_MASK;

	return result;
}

