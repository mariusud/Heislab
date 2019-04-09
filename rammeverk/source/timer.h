#include <time.h>
/**@file
 * @Contains functions that takes care of the three second timer.
*/


/**
Starts timer
*/
void timer_start();

/**
@brief Tells if timer has exceeded three seconds
@returns 1 if timer has exceeded three seconds, 0 else
*/
int timer_three_seconds();

/**
@brief Tells if timer is on
@returns 1 if timer is on, 0 else
*/
int timer_on();


/**
@brief Turns of timer. Sets the value of the timer variable to -1
*/
void timer_turn_off();