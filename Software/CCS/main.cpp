#include <slib/CONSOLE/CONSOLE.h>

/**
 * main.c
 */

float roll;

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

    CONSOLE console = CONSOLE();
    while(1){
        SysCtlDelay(8000);
        console.printf("-90 %d %d %d 90 \r\n",(int32_t)(roll));
    }
}
