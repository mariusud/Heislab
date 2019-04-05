#include "elev.h"


/**
  States for  FSM_move(states state).
*/
typedef enum states{
    IDLE,
    DRIVE,
    DOORS_OPEN,
    EMERGENCY_STOP
} State;


/**
  Checks if elevator is in a floor and sends it to idle or sends it down to the next floor and puts it in idle
*/
void FSM_init();

