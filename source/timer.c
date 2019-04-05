#include <time.h>
#include "timer.h"


#define STOP_TIME (CLOCKS_PER_SEC*3)


clock_t START_TIME;
clock_t CURRENT_TIME;

void timer_start(void){
	START_TIME = clock();
}


int timer_is_time_out(){
	CURRENT_TIME = clock();
	if ((CURRENT_TIME - START_TIME) > STOP_TIME) 
		return 1;
	else
		return 0;
}