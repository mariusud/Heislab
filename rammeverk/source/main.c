#include "elev.h"
#include "fsm.h"
#include "timer.h"
#include "queue.h"
#include <stdio.h>


int main() {
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    FSM_init();
    queue_init_arrays();
    State state = IDLE;

    int current_floor;
    int last_floor;     
    int last_direction;

    while (1) {

        //updates current_floor, queue and last_floor continuously
        current_floor = elev_get_floor_sensor_signal();
        queue_update_orders();
        if (elev_get_floor_sensor_signal() != -1){ last_floor = elev_get_floor_sensor_signal();}

        if (elev_get_stop_signal()){
            elev_set_motor_direction(DIRN_STOP);
            state = EMERGENCY_STOP;
        }

        switch (state){
            case IDLE:
                //checks if the elevator has stopped inbetween floors
                if ((current_floor == -1) && (g_direction == DIRN_STOP)){
                    elev_set_motor_direction(DIRN_STOP);
                    //checks if there are any orders and if the orders are above the previous floor
                    if (queue_check_orders() && queue_order_above(last_floor-(last_direction==DIRN_DOWN))) {
                        g_direction = DIRN_UP;
                        elev_set_motor_direction(g_direction);  
                        state = DRIVE;
                    } 
                    else if(queue_check_orders()){
                        g_direction = DIRN_DOWN;
                        elev_set_motor_direction(g_direction); 
                        state = DRIVE;
                    }
                    break;
                }
                //goes here if the elevator is in a floor
                if (queue_check_orders()){
                    if(queue_check_order_in_floor(current_floor)){
                        state = DOORS_OPEN;
                    }else{
                        if(current_floor == -1){
                            g_direction = queue_get_direction(last_floor);
                            elev_set_motor_direction(g_direction);
                            state = DRIVE; 
                        }else{
                            g_direction = queue_get_direction(current_floor);
                            elev_set_motor_direction(g_direction);
                            state = DRIVE;
                        }
                    }
                }
                break;

            case DRIVE:
                if(elev_get_floor_sensor_signal() !=-1){
                    elev_set_floor_indicator(current_floor);
                }
                if(elev_safety(g_direction)){
                    state = IDLE;
                }
                if (queue_check_order_in_floor(current_floor)){
                    //checks if the elevator is going to stop if a floor has an order
                    if((g_direction == DIRN_DOWN) && (queue_order_floor_direction_down(current_floor) || (current_floor == 0) || (!queue_order_below(current_floor)))){
                        elev_set_motor_direction(DIRN_STOP);
                        state = DOORS_OPEN;
                    }
                    else if((g_direction == DIRN_UP) && (queue_order_floor_direction_up(current_floor) || (current_floor == N_FLOORS-1) || (!queue_order_above(current_floor)))){
                        elev_set_motor_direction(DIRN_STOP);
                        state = DOORS_OPEN;
                    } 
                }
                break;

            case DOORS_OPEN:
                last_floor = current_floor;
                if(!timer_on()){
                    timer_start();
                }
                queue_delete_floor_order(current_floor);
                elev_set_door_open_lamp(1);
                if(timer_three_seconds()){
                    elev_set_door_open_lamp(0);
                    timer_turn_off();
                    if(queue_check_orders()){
                        g_direction = queue_get_direction(current_floor);
                        elev_set_motor_direction(g_direction);
                        state = DRIVE;
                    }else{
                        state = IDLE;
                    }
                }
                break;

            case EMERGENCY_STOP:
                last_direction = g_direction;
                elev_set_motor_direction(DIRN_STOP);
                g_direction = DIRN_STOP;
                queue_delete_all_orders();
                while(elev_get_stop_signal()){
                    elev_set_stop_lamp(1);
                    if (current_floor != -1){
                        elev_set_door_open_lamp(1);
                    }
                }
                elev_set_stop_lamp(0);
                //checks if the stop button was pushed when the elevator was in a floor
                if(current_floor != -1){
                    if(!timer_on()){
                        timer_start();
                    }
                    if(elev_get_stop_signal()){
                        timer_turn_off();
                        state = EMERGENCY_STOP;
                    }
                    elev_set_door_open_lamp(1);
                    if(timer_three_seconds()){
                        elev_set_door_open_lamp(0);
                        timer_turn_off();
                        state = IDLE;
                    }
                }else{
                    if(elev_get_stop_signal()){
                        state = EMERGENCY_STOP;
                    }else{

                        state = IDLE;
                    }
                }
                break;
        }

    }
    return 0;
}
