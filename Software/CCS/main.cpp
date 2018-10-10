#include <stdint.h>
#include <stdbool.h>

#include <slib/Params/Params.h>
#include <slib/State/State.h>
#include <slib/System/System.h>

/**
 * main.c
 */

int main(void)
{
    System::init();

    Params params;
    State state = State(&params);

    while(1){
    }
}
