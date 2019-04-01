#include "queue.h"
#include "elev.h"
#include <stdio.h>


static int arr_opp[N_FLOORS-1]; // mulig det må brukes static int
static int arr_ned[N_FLOORS-1]; // ned og opp er for eksterne heistilkallinger
static int arr_destination[N_FLOORS-1];
int floor;

// opp = 1 betyr opp, ned = 1 betyr ned



int check_queue(){
    int i;
    for (i=0; i < N_FLOORS; i++){
        if(elev_get_button_signal(BUTTON_CALL_UP,i))
            arr_opp[i] = 1;
            return 1;
        if(elev_get_button_signal(BUTTON_CALL_DOWN,i))
            arr_ned[i] = 1;
            return 1;
        if(elev_get_button_signal(BUTTON_COMMAND,i))
            arr_destination[i] = 1;
            return 1;
        else
        {
            return 0;
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


void Add_order(int button){

}




void set_direction(){
    if (check_queue){
        if (elev_get_floor_sensor_signal == floor)
            return 0; //do something
    }else{
        elev_get_button_signal(BUTTON_CALL_UP,floor);
        //set direction 
    }

}