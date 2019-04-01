#include "queue.h"
#include "elev.h"
#include <stdio.h>


static int arr_opp[N_FLOORS-1]; 
static int arr_ned[N_FLOORS-1]; // ned og opp er for eksterne heistilkallinger
static int arr_destination[N_FLOORS-1];
// int floor;


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

int should_stop(int floor){

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

int get_direction(int floor){
    int i;
    for (i = 0; i < N_FLOORS;i++){
        if (check_queue_floor(i)){
            // if a direction is already set, follow until  no more orders in that direction
            // if no set direction do the below
            if (i < floor){
                return -1;
            }
            if (i == floor){
                return 0;
            }
            if (i > floor){
                return 1;
            }
        }
    }
}



//problem: if direction set down, and new order pops up above. how to make it finish order to go all the way down, not just stop at one floor.
// arr_direction needs to have priority med andre ord