#include <stdbool.h>
#include <stdint.h>

#include <slib/system/System.h>
#include <slib/console/Console.h>
#include <slib/DRIVER/DRIVER.h>
#include <slib/StateSystem/StateSystem.h>
#include <modules/ESP8266/ESP8266.h>

/**
 * main.c
 */

int main(void)
{
    System::init();

    ESP8266 esp8266 = ESP8266();

    while(1){
    }
}
