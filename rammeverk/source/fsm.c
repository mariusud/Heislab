#include "elev.h"
#include "fsm.h"

#include <assert.h>
#include <stdlib.h>
int last_floor;

static State state;

void FSM_init(){
    //checks if elevator is at a floor or inbetween
    if(elev_get_floor_sensor_signal != -1){
        FSM_idle();
    }else{
        elev_set_motor_direction(DIRN_DOWN);
        while(elev_get_floor_sensor_signal == -1){}
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
    //sjekker om det kommer en ordre i samme etasje eller en annen
    if (check_queue_floor(elev_get_floor_sensor_signal())){
        FSM_set_state(DOORS_OPEN);
    }else{
        FSM_set_state(DRIVE);
    }
}

void FSM_drive(){
    last_floor = elev_get_floor_sensor_signal();
    elev_set_motor_direction(get_direction());
    while(elev_get_floor_sensor_signal == -1){}
    if(check_queue_floor(elev_get_floor_sensor_signal())){
        elev_set_motor_direction(0);
        FSM_set_state(DOORS_OPEN);
    }
}

void FSM_doors_open(){
    if(elev_get_floor_sensor_signal == -1){
        printf("heisen er ikke i en etasje");
    }
    elev_set_floor_indicator(elev_get_floor_sensor_signal());
}

//gjør ferdig doorsopen
//legg til lys
//legg til doxygen