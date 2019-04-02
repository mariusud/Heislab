#include "elev.h"
#include "fsm.h"
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

        switch (state){
            case IDLE:
                elev_set_motor_direction(DIRN_STOP);
                //light on in correct floor
                elev_set_button_lamp(BUTTON_COMMAND, current_floor, 1);
                //sjekker om det kommer en ordre i samme etasje eller en annen
                if (check_queue_floor(current_floor)){
                    FSM_set_state(DOORS_OPEN);
                }else{

                    FSM_set_state(DRIVE);
                }
                break;

            case DRIVE:
                //finds out which direction to drive in
                elev_set_motor_direction(get_direction(current_floor));
                //turns off lights
                elev_set_button_lamp(BUTTON_COMMAND, last_floor, 0);
                //checks if the elevator is in a floor and has orders in that floor
                if ((current_floor != -1) && check_queue_floor(current_floor)){
                    elev_set_motor_direction(DIRN_STOP);
                    state = DOORS_OPEN;
                }
                break;

            case DOORS_OPEN:
            //stops elevator
                elev_set_button_lamp(BUTTON_COMMAND, current_floor, 1);

            case EMERGENCY_STOP:

        }
        if (elev_get_stop_signal()){
            state = EMERGENCY_STOP;
        }

    }
    return 0;
}
