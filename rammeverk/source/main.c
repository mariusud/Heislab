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
    int last_direction;
    int last_state;    //0-3 // emg is 3
    while (1) {

        printf("state %d\n\n\n", state);
        //updates current_floor continousley
        current_floor = elev_get_floor_sensor_signal();
        //updates queue continuosely
        check_queue();

        if (elev_get_stop_signal()){
            elev_set_motor_direction(DIRN_STOP);
            printf("kom inn i den første løkka aka moren til håkon");
            direction = DIRN_STOP;
            last_state = 3;
            state = EMERGENCY_STOP;
        }

        switch (state){
            case IDLE:
                //checks if there are any orders
                printf("idle \n");
                printf("current floor: %d",current_floor);
                printf("direction: %d", direction);
                if ((current_floor == -1) && (direction == DIRN_STOP)){
                    printf("FUCKED IN THE ASS");
                    elev_set_motor_direction(DIRN_STOP);
                    if (order_above(last_floor-(last_direction==DIRN_DOWN))){
                        direction = DIRN_UP;
                        elev_set_motor_direction(direction);  
                        state = DRIVE;
                    } 
                    else if(check_queue()){
                        direction = DIRN_DOWN;
                        elev_set_motor_direction(direction); 
                        state = DRIVE;
                    }

                    break;
                    }
                if (check_orders()){
                    //checks if order is in current floor
                    if(check_queue_floor(current_floor)){
                        state = DOORS_OPEN;
                    }else{
                        //finds out which direction to drive in
                        if(current_floor == -1){
                            direction = get_direction(last_floor);
                            elev_set_motor_direction(direction);
                            state = DRIVE; 
                            
                            
                            
                        }else{
                            direction = get_direction(current_floor);
                            elev_set_motor_direction(direction);
                            last_floor = current_floor;
                            state = DRIVE;
                        }
                    } last_floor = current_floor;
                }
                break;

            case DRIVE:
                //printf("DRIVE \n");
                //printf("DIRECTION: %d \n", direction);
                //printf("floor: %d \n ", current_floor);
                last_state = 1;
                if(elev_get_floor_sensor_signal() !=-1){
                    elev_set_floor_indicator(current_floor);
                }
                if (check_queue_floor(current_floor)){
                    if((direction == DIRN_DOWN) && (order_floor_direction_down(current_floor) || (current_floor == 0) || (!order_below(current_floor)))){
                        elev_set_motor_direction(DIRN_STOP);
                        state = DOORS_OPEN;
                    }
                    else if((direction == DIRN_UP) && (order_floor_direction_up(current_floor) || (current_floor == N_FLOORS-1) || (!order_above(current_floor)))){
                        elev_set_motor_direction(DIRN_STOP);
                        state = DOORS_OPEN;
                    } 
                }
                break;

            case DOORS_OPEN:
                last_floor = current_floor;
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
                last_state = 2;
                break;

            case EMERGENCY_STOP:
                last_direction = direction;
                elev_set_motor_direction(DIRN_STOP);
                direction = DIRN_STOP;
                delete_all_orders();
                while(elev_get_stop_signal()){
                    printf("EMERGENDCY button pressed \n");
                    elev_set_stop_lamp(1);
                    if (current_floor != -1){
                        elev_set_door_open_lamp(1);
                    }
                }
                elev_set_stop_lamp(0);
                //this part turns on the doorlamp if the elevator is in a floor
                if(current_floor != -1){
                    if(!is_timer_on()){
                    timer_start();
                    }
                    delete_floor_order(current_floor);
                    elev_set_door_open_lamp(1);
                    if(timer_three_seconds()){
                        elev_set_door_open_lamp(0);
                        turn_off_timer();
                        state = IDLE;
                }
                //this part is if the elevator is not in a floor
                }else{
                    if(elev_get_stop_signal()){
                        state = EMERGENCY_STOP;
                    }else{

                        state = IDLE;
                    }
                }
                last_state = 3;
                break;
        }

    }
    return 0;
}
