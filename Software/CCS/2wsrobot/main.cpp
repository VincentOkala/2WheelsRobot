#include <modules/GY521/GY521.h>
#include <modules/CONSOLE/CONSOLE.h>

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

    CONSOLE console = CONSOLE();

    while(1){
        SysCtlDelay(16000);
        gy521.getAccel(accel);
        gy521.getGyro(gyro);
        gy521.getPitch(&pitch);
        gy521.getRoll(&roll);
        console.printf("pitch: %d, roll: %d \r\n",(int32_t)(pitch), (int32_t)(roll));
    }
}
