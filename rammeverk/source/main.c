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
    /*
    State state = IDLE;
  
    while (1) {
        switch (state){
            case IDLE:

            case DRIVE:
                //finds out which direction to drive in
                elev_set_motor_direction(get_direction(elev_get_floor_sensor_signal()));
                //checks if the elevator is in a floor and has orders in that floor
                if ((elev_get_floor_sensor_signal() != -1) && check_queue_floor(elev_get_floor_sensor_signal())){
                    elev_set_motor_direction(DIRN_STOP);
                    state = DOORS_OPEN;
                }
                break;
            case DOORS_OPEN:


            case EMERGENCY_STOP:

        }
    //if stop ()

    }
    */
    return 0;
}
