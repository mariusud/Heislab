#include "elev.h"
#include "fsm.h"
#include "timer.h"
#include "queue.h"
#include <time.h>
#include <stdio.h>


int main() {
    // Initialize hardware

    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    //initializes the elevator
    FSM_init();
    init_arrays();
    State state = IDLE;
    //variables declared before while-loop
    int current_floor;
    int last_floor;
  

    while (1) {
        //updates current_floor continousley
        current_floor = elev_get_floor_sensor_signal();
        //updates queue continuosely
        check_queue();
        switch (state){

            case IDLE:
                //checks if there are any orders
                if (check_orders()){
                    //checks if order is in current floor
                    if(check_queue_floor(current_floor)){
                        state = DOORS_OPEN;
                    }else{
                        //finds out which direction to drive in
                        direction = get_direction(current_floor);
                        elev_set_motor_direction(direction);
                        last_floor = current_floor;
                        state = DRIVE;
                    }
                }
                break;

            case DRIVE:
                if(elev_get_floor_sensor_signal() !=-1){
                    elev_set_floor_indicator(current_floor);
                }
            
                
                if (check_queue_floor(current_floor)){
                    
                    if((direction == DIRN_DOWN && order_floor_direction_down(current_floor ) )|| ( direction == DIRN_DOWN && current_floor == 0)){
                        elev_set_motor_direction(DIRN_STOP);
                        state = DOORS_OPEN;
                    }
                    else if((direction == DIRN_UP && order_floor_direction_up(current_floor) )|| ( direction == DIRN_UP && current_floor == 3)){
                        elev_set_motor_direction(DIRN_STOP);
                        state = DOORS_OPEN;
                    } 
                    
                    /*
                    elev_set_motor_direction(DIRN_STOP);
                    state = DOORS_OPEN;*/
                }
                break;

            case DOORS_OPEN:
                if(current_floor == -1){
                    FSM_init();
                }
                if(!is_timer_on()){
                    //turns on timer if it is not already on
                    timer_start();
                }
                delete_floor_order(current_floor); //FIKS HER  FIKS HER    FIKS HER            FIKS HER        FIKS HER
                //turns on doorlamp
                elev_set_door_open_lamp(1);
                //checks if timer has exceeded three seconds
                if(timer_three_seconds()){
                    //turns off doorlamp and timer
                    elev_set_door_open_lamp(0);
                    turn_off_timer();
                    //checks if there are any more orders
                    if(check_orders()){
                        last_floor = current_floor;
                        //finds out which direction to drive in
                        direction = get_direction(current_floor);
                        elev_set_motor_direction(direction);
                        state = DRIVE;
                    }else{
                        //Idle
                        state = IDLE;
                }}
                break;

            case EMERGENCY_STOP:
                elev_set_motor_direction(DIRN_STOP);
                delete_all_orders();
                while(elev_get_stop_signal()){
                    elev_set_stop_lamp(1);
                    if (current_floor != -1){
                        elev_set_door_open_lamp(1);
                    }
                }
                elev_set_stop_lamp(0);
                if(current_floor != -1){
                    if(!is_timer_on()){
                    timer_start();
                    }
                    delete_floor_order(current_floor);
                    //turns on doorlamp
                    elev_set_door_open_lamp(1);
                    //checks if timer has exceeded three seconds
                    if(timer_three_seconds()){
                        //turns off doorlamp and timer
                        elev_set_door_open_lamp(0);
                        turn_off_timer();
                        state = IDLE;
                }
                }else{
                    elev_set_motor_direction(direction);
                    while(elev_get_floor_sensor_signal()==-1 && !elev_get_stop_signal()){
                    };
                    if(elev_get_stop_signal()){
                        state = EMERGENCY_STOP;
                    }else{
                        elev_set_floor_indicator(elev_get_floor_sensor_signal());
                        elev_set_motor_direction(DIRN_STOP);
                        state = IDLE;
                    }
                }
                break;

        }
        if (elev_get_stop_signal()){
            state = EMERGENCY_STOP;
        }
    }
    return 0;
}
