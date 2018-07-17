#include <stdbool.h>
#include <stdint.h>

#include <slib/system/System.h>
#include <slib/console/Console.h>
#include <slib/DRIVER/DRIVER.h>
#include <slib/StateSystem/StateSystem.h>

/**
 * main.c
 */

int main(void)
{
    System::init();

    StateSystem ss = StateSystem();
    float roll;

    while(1){
        roll = ss.getRoll();
        Console::printf("-180 %d 180 \r\n", (int)roll);
        System::delayMs(10);
    }
}
