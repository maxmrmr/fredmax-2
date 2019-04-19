#include <time.h>
#include "timer.h"

//Number of clock ticks in 3 seconds
#define STOP_TIME (CLOCKS_PER_SEC*3)


clock_t START_TIME;
clock_t CURRENT_TIME;

//Set a start time when starting the timer
void timer_start(void){
    START_TIME = clock();
}

//Check if 3 seconds has passed since start time was set
//If 3 seconds has passed return 1, else return 0
int timer_is_time_out(void){
    CURRENT_TIME = clock();
    if ((CURRENT_TIME - START_TIME) > STOP_TIME)
        return 1;
    else
        return 0;
}
