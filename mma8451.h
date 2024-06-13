#include "MKL46Z4.h"

#define MMA8451_ADD 0x1D
#define CTRL_REG1 0x2A
#define OUT_X_MSB 0x01
#define OUT_X_LSB 0x02
#define OUT_Y_MSB 0x03
#define OUT_Y_LSB 0x04
#define OUT_Z_MSB 0x05
#define OUT_Z_LSB 0x06

typedef struct {
    float x;
    float y;
    float z;
} Accel;

void MMA8451_Init(void);
Accel MMA8451_Read(void);
