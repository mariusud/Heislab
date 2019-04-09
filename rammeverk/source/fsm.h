#include "elev.h"
/**@file
 * @Contains the four states that we use in our Finite State Machine. Contains also the initializing function for the elevator.
*/

/**
  States for main
*/
typedef enum states{
    IDLE,
    DRIVE,
    DOORS_OPEN,
    EMERGENCY_STOP
} State;


/**
 @brief Sends the elevator to a floor
*/
void FSM_init();

