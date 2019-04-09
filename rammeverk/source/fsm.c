#include "elev.h"
#include "fsm.h"

#include <assert.h>
#include <stdlib.h>



void FSM_init(){
    elev_set_motor_direction(DIRN_DOWN);
    while(elev_get_floor_sensor_signal() == -1)
    elev_set_floor_indicator(elev_get_floor_sensor_signal());
    elev_set_motor_direction(DIRN_STOP);
}
