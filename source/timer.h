/**
* @file
* @brief A simple timer setting a starttime which
* can be checked if three seconds has passed. Used for
* holding an elevator door open for three seconds.
*/


#include <time.h>

/**
* @brief Set a starttime based on the program clock
*/
void timer_start(void);

/**
* @brief Check if three seconds has passed since setting the starttime
*
* @return 1 if three seconds or more has passed since starttime,
* 0 if less than three seconds has passed.
*/
int timer_is_time_out(void);
