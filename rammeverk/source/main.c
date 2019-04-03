#include "elev.h"
#include "fsm.h"
#include "queue.h"
#include <time.h>
#include <stdio.h>


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");
    //initializes the elevator
    FSM_init();

    elev_set_button_lamp(BUTTON_COMMAND, elev_get_floor_sensor_signal(), 1);

    init_arrays();
    State state = IDLE;
    int current_floor;
    int last_floor;
  

    while (1) {
        current_floor = elev_get_floor_sensor_signal();
        //updates queue continuosely
        check_queue();
        switch (state){
            case IDLE:
                //printf("idle");
                //checks if there are any orders
                if (check_queue()){
                    printf("queue");
                    //checks if order is in current floor
                    if(check_queue_floor(current_floor)){
                        state = DOORS_OPEN;
                        printf("Kommer inn hit");
                    }else{
                        //finds out which direction to drive in
                         printf("current floor: %d\n", (current_floor));
                        direction = get_direction(current_floor);
                         printf("current dir: %d\n", get_direction(current_floor));
                        elev_set_motor_direction(direction);
                        int sleeper = 1000000;
                        while(--sleeper);
                        last_floor = current_floor;
                        state = DRIVE;
                    }
                }
                break;

            case DRIVE:
                //printf("drive");
                //checks if the elevator is in a floor and has orders in that floorprin
               /* printf("current floor: %d\n", current_floor);
                 printf("dir: %d\n", direction);
               printf("check floor: %d\n", check_queue_floor(current_floor));
*/
                if ((current_floor != -1) && check_queue_floor(current_floor)){
                    //stop elevator
                    elev_set_motor_direction(DIRN_STOP);
                    //turns off lights at last floor
                    elev_set_button_lamp(BUTTON_COMMAND, last_floor, 0);
                    //Turns on light on current floor
                    elev_set_button_lamp(BUTTON_COMMAND, current_floor, 1);
                    state = DOORS_OPEN;
                }
                break;

            case DOORS_OPEN:
                //printf("doors");
                if(current_floor == -1){
                    printf("heisen er ikke i en etasje");
                }
                //timer
                //elev_set_door_open_lamp(int value);
                //timer
                delete_floor_order(current_floor);

                if(check_queue()){
                    //finds out which direction to drive in
                    elev_set_motor_direction(get_direction(current_floor));
                    //current_direction = get_direction(current_floor);
                    //Drive
                    state = DRIVE;
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
