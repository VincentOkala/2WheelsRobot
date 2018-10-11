/*
 * Task.h
 *
 *  Created on: Jul 23, 2018
 *      Author: 16138
 */

#ifndef SLIB_TASK_TASK_H_
#define SLIB_TASK_TASK_H_

#include <stdint.h>
#include <stdbool.h>

#include "../../peripheral/GPTM/GPTM.h"

#define MAX_TIMEOUT_EVT     10
#define INVALID_TIMER_ID    0xff
#define TIMER_PERIOD_MS     1
#define TIMER_FREQ          1000

typedef void (*TIMER_CALLBACK_FUNC)();
typedef unsigned char Task_ID;

typedef struct
{
  TIMER_CALLBACK_FUNC callback;
  unsigned long period;
  unsigned long period_cnt;
}TIMEOUT_EVT;

static TIMEOUT_EVT timer_event_list[MAX_TIMEOUT_EVT];

class Task
{
public:
    Task();
    virtual ~Task();
    static void init();
    static Task_ID registerEvent(TIMER_CALLBACK_FUNC callback, unsigned int ms);
    static bool unregisterEvent(Task_ID timer_id);
    static void timerISR();
private:
    static GPTM task_timer;
};

#endif /* SLIB_TASK_TASK_H_ */
