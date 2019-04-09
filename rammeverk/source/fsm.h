#include "elev.h"


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

