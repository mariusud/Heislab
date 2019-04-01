#include "elev.h"
#include "fsm.h"

#include <assert.h>
#include <stdlib.h>


static State state;

void FSM_init(){
    //checks if elevator is at a floor or inbetween
    if(elev_get_floor_sensor_signal != -1){
        FSM_idle();
    }else{
        while(elev_get_floor_sensor_signal == -1){
            elev_set_motor_direction(DIRN_DOWN);
        }
        FSM_idle();
        return 1;
    }
        

}


void FSM_set_state(State st){
    state = st;
}

State FSM_get_state(){
    return state;
}


void FSM_idle(){
    elev_set_motor_direction(0);
    while(!check_queue()){}
    if (get_direction() ==0){
        FSM_set_state(DOORS_OPEN);
    }else{
        elev_set_motor_direction(get_direction());
        FSM_set_state(DRIVE);
    }
}
