#include "queue.h"
#include "elev.h"
#include <stdio.h>


int arr_opp[N_FLOORS]; // mulig det må brukes static int
int arr_ned[N_FLOORS]; // ned og opp er for eksterne heistilkallinger
int arr_destination[N_FLOORS];

// opp = 1 betyr opp, ned = 1 betyr ned



int check_queue(){
    int i;
    for (i=0; i < N_FLOORS; i++){
        if (arr_opp[i] == 1) //set lamp
            return 1;
        
        if (arr_ned[i] == 1)
            //set lamp
            return 1;
        
        if (arr_destination[i] == 1)
            //set lamp
            return 1;
        
        else
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
}


void delete_floor_order(int floor){
    
}


void Add_order(int button){

}
