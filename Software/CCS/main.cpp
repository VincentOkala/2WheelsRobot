#include <stdbool.h>
#include <stdint.h>

#include <modules/ESP8266/ESP8266.h>
#include <slib/Console/Console.h>

#include <slib/Driver/Driver.h>
#include <slib/StateSystem/StateSystem.h>
#include <slib/Params/Params.h>
#include <slib/System/System.h>
#include <slib/Task/Task.h>

/**
 * main.c
 */

int main(void)
{
    System::init();

    Params params;
    // ESP8266 esp8266 = ESP8266(&params);
    StateSystem ss = StateSystem(&params);

    while(1){
    }
}
