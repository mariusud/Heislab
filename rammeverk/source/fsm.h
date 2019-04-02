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
  @return Non-zero on success, 0 on failure.
*/
void FSM_init();

/**
 sets state
*/
void FSM_set_state(State st);


void FSM_move(State st);

State FSM_check_state();

void FSM_idle();

