#include <stdbool.h>
#include <stdint.h>
#include "driverlib/sysctl.h"

#include <slib/system/System.h>

/**
 * main.c
 */

float roll;

int main(void)
{

    System::init();
    while(1){
        Log::logInfo("hi %d", 123);
        System::delayMs(1000);
    }
}
