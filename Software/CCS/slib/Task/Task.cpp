/*
 * Task.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: 16138
 */

#include <slib/Task/Task.h>

GPTM Task::task_timer;

Task::Task(){}

Task::~Task(){}

void Task::init(){
    task_timer = GPTM(GPTM_0, TIMER_FREQ);

    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER0_BASE, TIMER_BOTH, Task::timerISR);
}

/**
 * @brief Register event
 * @param callback function name
 * @param ms event timeout
 * @return timer ID
 */
Task_ID Task::registerEvent(TIMER_CALLBACK_FUNC callback, unsigned long ms)
{
    int i;
    for(i=0; i< MAX_TIMEOUT_EVT; i++)
    {
      if((timer_event_list[i].period_cnt == 0) && (timer_event_list[i].callback == nullptr)) break;
    }
    if(i == MAX_TIMEOUT_EVT)
        return INVALID_TIMER_ID;

    timer_event_list[i].period = (unsigned long)(ms/TIMER_PERIOD_MS);
    timer_event_list[i].period_cnt = timer_event_list[i].period;
    timer_event_list[i].callback = callback;

    return (Task_ID)i;
}

bool Task::unregisterEvent(Task_ID timer_id)
{
    bool ret = false;
    if(timer_id < MAX_TIMEOUT_EVT)
    {
        timer_event_list[timer_id].period_cnt = 0;
        timer_event_list[timer_id].callback = nullptr;
        ret = true;
    }
    return ret;
}

void Task::timerISR()
{
    uint32_t flag = TimerIntStatus(TIMER0_BASE, true);
    TimerIntClear(TIMER0_BASE, flag);

    int i;
    for(i = 0; i < MAX_TIMEOUT_EVT; i++)
    {
        if(timer_event_list[i].period_cnt > 0)
        {
            timer_event_list[i].period_cnt--;
            if(timer_event_list[i].period_cnt == 0 && timer_event_list[i].callback != nullptr)
            {
                (timer_event_list[i].callback)();
                 timer_event_list[i].period_cnt = timer_event_list[i].period;
            }
        }
    }
}

