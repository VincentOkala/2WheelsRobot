#include <modules/GY521/GY521.h>

/**
 * main.c
 */
float accel[3];
float gyro[3];
float pitch;
float roll;
int main(void)
{
    GY521 gy521 = GY521(I2C0);
    gy521.Init();

    while(1){
        gy521.getAccel(accel);
        gy521.getGyro(gyro);
        gy521.getPitch(&pitch);
        gy521.getRoll(&roll);
    }
}
