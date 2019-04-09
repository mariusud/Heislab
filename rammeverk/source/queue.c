#include "elev.h"
#include "queue.h"
#include <stdio.h>


static int arr_up[N_FLOORS]; 
static int arr_down[N_FLOORS]; 
static int arr_destination[N_FLOORS];
elev_motor_direction_t g_direction;



void init_arrays(){
    int i;
    for (i =0; i < N_FLOORS;i++){
        arr_destination[i] = 0;
        arr_down[i] = 0;
        arr_up[i] = 0;
    }
}

int check_orders(){
    for(int i = 0; i < N_FLOORS; i++){
        if(arr_destination[i]) return 1;
        if(arr_down[i]) return 1;
        if(arr_up[i]) return 1;
    }
    return 0;
}

int check_queue(){
    int i;
    for (i=0; i < N_FLOORS; i++){
        if (i == 0){
            if(elev_get_button_signal(BUTTON_CALL_UP,i)){
                elev_set_button_lamp(BUTTON_CALL_UP,i,1);
                arr_up[i] = 1;         
                return 1;
            }
            if(elev_get_button_signal(BUTTON_COMMAND,i)){
                elev_set_button_lamp(BUTTON_COMMAND,i,1);
                arr_destination[i] = 1;
                return 1;
                }
            }
        if (i == 3){
            if(elev_get_button_signal(BUTTON_CALL_DOWN,i)){
                elev_set_button_lamp(BUTTON_CALL_DOWN,i,1);
                arr_down[i] = 1;
                return 1;
            }
            if(elev_get_button_signal(BUTTON_COMMAND,i)){
                elev_set_button_lamp(BUTTON_COMMAND,i,1);
                arr_destination[i] = 1;
                return 1;
            }
        } else{
            if(elev_get_button_signal(BUTTON_CALL_UP,i)){
                elev_set_button_lamp(BUTTON_CALL_UP,i,1);
                arr_up[i] = 1;         
                return 1;
                }
            if(elev_get_button_signal(BUTTON_CALL_DOWN,i)){
                elev_set_button_lamp(BUTTON_CALL_DOWN,i,1);
                arr_down[i] = 1;
                return 1;
            }
            if(elev_get_button_signal(BUTTON_COMMAND,i)){
                elev_set_button_lamp(BUTTON_COMMAND,i,1);
                arr_destination[i] = 1;
                return 1;
            }
        }
    }
    return 0;
}


int check_queue_floor(int floor){
    if (floor == -1){return 0;}
    if (arr_up[floor]){
        return 1;
    }
    if (arr_down[floor]){
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
    elev_set_button_lamp(BUTTON_CALL_UP,floor,0);
    elev_set_button_lamp(BUTTON_CALL_DOWN,floor,0);
    elev_set_button_lamp(BUTTON_COMMAND,floor,0);
    arr_up[floor] = 0;
    arr_down[floor] = 0;
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
    for (i=floor+1; i < N_FLOORS; i++){
        if (arr_destination[i]){return 1;} 
        if (arr_down[i]){return 1;} 
        if (arr_up[i]){return 1;}
        }
    return 0;
}


int order_below(int floor){
    for (int i = 0; i < floor; i++){
        if (arr_destination[i]){return 1;} 
        if (arr_down[i]){return 1;} 
        if (arr_up[i]){return 1;}    
    }
    return 0;
}

int order_floor_direction_down(int floor){
    if (arr_destination[floor]){return 1;} 
    if (arr_down[floor]){return 1;} 
    return 0;
}

int order_floor_direction_up(int floor){
    if (arr_destination[floor]){return 1;} 
    if (arr_up[floor]){return 1;} 
    return 0;
}


elev_motor_direction_t get_direction(int floor){
    if ( order_above(floor) && g_direction == DIRN_UP){return DIRN_UP;}
    else if (order_below(floor) && g_direction == DIRN_DOWN){return DIRN_DOWN;}
    else if (order_above(floor)){return DIRN_UP;}
    else if (order_below(floor)){return DIRN_DOWN;}
    else if (floor == -1){
        return g_direction;
        }
    else{
        return g_direction;
    }
}
