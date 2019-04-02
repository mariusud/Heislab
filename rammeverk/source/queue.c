#include "queue.h"
#include "elev.h"
#include <stdio.h>


static int arr_opp[N_FLOORS-1]; 
static int arr_ned[N_FLOORS-1]; // ned og opp er for eksterne heistilkallinger
static int arr_destination[N_FLOORS-1];

elev_button_type_t direction;
// int floor;
int order;


int check_queue(){
    int i;
    for (i=0; i < N_FLOORS; i++){
        if(elev_get_button_signal(BUTTON_CALL_UP,i)){
            arr_opp[i] = 1;         
            return 1;
        }
        if(elev_get_button_signal(BUTTON_CALL_DOWN,i)){
            arr_ned[i] = 1;
            return 1;
        }
        if(elev_get_button_signal(BUTTON_COMMAND,i)){
            arr_destination[i] = 1;
            return 1;
        }
        else{return 0;}  
    }
}


int check_queue_floor(int floor){
    if (arr_opp[floor]){
        return 1;
    }
    if (arr_ned[floor]){
        return 1;
    }
    if (arr_destination[floor]){
        return 1;
    }
    else{
        return 0;
    }
}


void delete_floor_order(int floor){
    // delete lamps aswell
    arr_opp[floor] = 0;
    arr_ned[floor] = 0;
    arr_destination[floor] = 0;

}

void delete_all_orders(){
    int i;
    for (i = 0; i < N_FLOORS;i++){
        delete_floor_order(i);
    }
}


int order_above(int floor){
    int i;
    for (i =floor; i < N_FLOORS; i++){
        if (arr_destination[i] || arr_ned[i] || arr_opp[i]){
            return 1;
        } else{
            return 0;
        }
    }
}

int order_below(int floor){
    int i;
    for (i = 0; i < floor; i++){
        if (arr_destination[i] || arr_ned[i] || arr_opp[i]){
            return 1;
        } else{
            return 0;
        }
    }
}




elev_motor_direction_t get_direction(int floor){
    if ( order_above(floor) && direction == DIRN_UP){return DIRN_UP;}
    else if (order_below(floor) && direction == DIRN_DOWN){return DIRN_DOWN;}
    else if (order_above(floor)){return DIRN_UP;}
    else if (order_below(floor)){return DIRN_DOWN;}
    else if ((floor == -1) || !(floor)){
        printf("Someting wong");
        return DIRN_STOP;
        }
}
