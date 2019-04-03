#include "elev.h"
#include "fsm.h"

#include <assert.h>
#include <stdlib.h>



void FSM_init(){
    //checks if elevator is at a floor or inbetween
    if(elev_get_floor_sensor_signal() != -1){
        //FSM_idle();
        elev_set_motor_direction(DIRN_STOP);
    }else{
        elev_set_motor_direction(DIRN_DOWN);
        while(elev_get_floor_sensor_signal() == -1){}//legg til stop button?
        //FSM_idle();
        elev_set_motor_direction(DIRN_STOP);
    }
}


//gjør ferdig doorsopen
//legg til lys
//legg til doxygen

