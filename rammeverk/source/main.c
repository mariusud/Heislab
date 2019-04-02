#include "elev.h"
#include "fsm.h"
#include "queue.c"
#include <stdio.h>


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");
    FSM_init();
    elev_set_button_lamp(BUTTON_COMMAND, elev_get_floor_sensor_signal(), 1);
    
    State state = IDLE;
    int current_floor;
    int last_floor;
    int current_direction;
  
    while (1) {
        current_floor = elev_get_floor_sensor_signal();
        //updates queue continuosely
        check_queue();
        switch (state){
            case IDLE:
                //checks if there are any orders
                if (check_queue()){
                    //checks if order is in current floor
                    if(check_queue_floor(current_floor)){
                        FSM_set_state(DOORS_OPEN);
                    }else{
                        //finds out which direction to drive in
                        elev_set_motor_direction(get_direction(current_floor));
                        current_direction = get_direction(current_floor);
                        //turns off lights
                        elev_set_button_lamp(BUTTON_COMMAND, current_floor, 0);
                        FSM_set_state(DRIVE);
                    }
                }
                break;

            case DRIVE:
                //checks if the elevator is in a floor and has orders in that floor
                if ((current_floor != -1) && check_queue_floor(current_floor)){
                    //stop elevator
                    elev_set_motor_direction(DIRN_STOP);
                    //Turns on light on current floor
                    elev_set_button_lamp(BUTTON_COMMAND, current_floor, 1);
                    state = DOORS_OPEN;
                }
                break;

            case DOORS_OPEN:
                if(current_floor == -1){
                    printf("heisen er ikke i en etasje");
                }
                //timer
                //elev_set_door_open_lamp(int value);
                //timer
                if(check_queue()){
                    //finds out which direction to drive in
                    elev_set_motor_direction(get_direction(current_floor));
                    //current_direction = get_direction(current_floor);
                    //turns off lights
                    elev_set_button_lamp(BUTTON_COMMAND, current_floor, 0);
                    //Drive
                    FSM_set_state(DRIVE);
                }else{
                    //Idle
                    state = IDLE;
                }

            case EMERGENCY_STOP:
                for(int i = 0; i < 4; i++)
                {
                    elev_set_button_lamp(BUTTON_COMMAND, i, 1);
                }
                
                break;

        }
        if (elev_get_stop_signal()){
            state = EMERGENCY_STOP;
        }

    }
    return 0;
}
