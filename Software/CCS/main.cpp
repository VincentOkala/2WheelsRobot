#include <stdint.h>
#include <stdbool.h>

#include <slib/PAV/PAV.h>
#include <slib/State/State.h>
#include <slib/Controller/Controller.h>

#include <slib/System/System.h>

/**
 * main.c
 */

PAV pav;
State state;
Controller controller;

int main(void)
{
    System::init();

    pav.init();
    state.init(&pav);
    controller.init(&pav);

    while(1){}
}
