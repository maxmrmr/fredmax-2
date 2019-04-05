#include "elev.h"
#include "queue.h"
#include "timer.h"
#include "state.h"

#include <stdio.h>


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    //printf("Press STOP button to stop elevator and exit program.\n");

    //Initialize elevator, if between floors drive down until any floor is reached

    state_init();
    queue_clear_all_orders();
    
    elev_set_motor_direction(DIRN_DOWN);
    state_set_last_direction(DIRN_DOWN);

    while(elev_get_floor_sensor_signal() < 0){}
    elev_set_motor_direction(DIRN_STOP);
    state_arrived_at_any_floor();
    if (elev_get_floor_sensor_signal() >= 0){
        state_set_last_floor(elev_get_floor_sensor_signal());
    }

    while (1) {
        /**Stop when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_STOP);
        }
        else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_STOP);
        }*/

        //Check if stop button is pressed, if pressed stop motor, clear queue and turn on stop light
        if (elev_get_stop_signal()){
            elev_set_motor_direction(DIRN_STOP);
            state_stop_button_pressed();
            queue_clear_all_orders();
            elev_set_stop_lamp(1);
            if (elev_get_floor_sensor_signal() >= 0)
                elev_set_door_open_lamp(1);
        }

        if (!(elev_get_stop_signal())){
            if (state_get_current_state() == EM_STOP){
                elev_set_stop_lamp(0);
                if (elev_get_floor_sensor_signal() >= 0){
                    state_arrived_at_correct_floor();
                    elev_set_door_open_lamp(1);
                    timer_start();
                }
                else{
                    state_stop_button_released();
                }
            }
        }

        //Only allowed to do stuff when not in emergency stop
        if (state_get_current_state() != EM_STOP){

            //Check timer, if time is out close door
            if (timer_is_time_out()){
                elev_set_door_open_lamp(0);
                if (state_get_current_state() == DOOR_OPEN)
                    state_timer_finished();
                    //Check queue, if another order is in queue run in needed direction
                    if(queue_get_new_direction( state_get_last_floor(), state_get_last_direction() )){
                        state_set_last_direction(queue_get_new_direction( state_get_last_floor(), state_get_last_direction()));
                        elev_set_motor_direction( state_get_last_direction() );
                        state_motor_started();
                    }
            }

            //For loop checking all button signals except stop
            int i;
            for (i = 0; i < N_FLOORS; ++i) {
                if (i != 0){
                    if (elev_get_button_signal(BUTTON_CALL_DOWN, i)){
                        queue_add_order((3*i+1));                      //3*i for floor number, +1 for BUTTON_CALL_DOWN
                        elev_set_button_lamp(BUTTON_CALL_DOWN, i, 1);
                    }
                }


                if (i != N_FLOORS - 1)
                    if (elev_get_button_signal(BUTTON_CALL_UP, i)){
                        queue_add_order((3*i));                       //3*i for floor number, +0 for BUTTON_CALL_UP
                        elev_set_button_lamp(BUTTON_CALL_UP, i, 1);
                    }

                if (elev_get_button_signal(BUTTON_COMMAND, i)){
                    queue_add_order((3*i)+2);                          //3*i for floor number, +2 for BUTTON_COMMAND
                    elev_set_button_lamp(BUTTON_COMMAND, i, 1);
                }
            }

            if (elev_get_floor_sensor_signal() >= 0){
                state_set_last_floor( elev_get_floor_sensor_signal());
                elev_set_floor_indicator( state_get_last_floor() );
                if (queue_check_orders_at_current_floor( state_get_last_floor(), state_get_last_direction() )){
                    elev_set_motor_direction(DIRN_STOP);
                    queue_clear_order( state_get_last_floor() );
                    int i;
                    for (i = 0; i < 3; ++i){
                        if (state_get_last_floor() == 0){
                            if (i != 1){
                            elev_set_button_lamp(i, state_get_last_floor(), 0);
                            }
                        }
                        else if (state_get_last_floor() == 3){
                            if (i != 0){
                            elev_set_button_lamp(i, state_get_last_floor(), 0);
                            }
                        }
                        else{
                            elev_set_button_lamp(i, state_get_last_floor(), 0);
                        }
                    }
                    state_arrived_at_correct_floor();
                    elev_set_door_open_lamp(1);
                    timer_start();
                }
            }

            if (state_get_current_state() == IDLE_BETWEEN_FLOORS){
                if (queue_get_new_direction_if_between_floors((state_get_last_floor() ), state_get_last_direction())){
                    state_set_last_direction(queue_get_new_direction_if_between_floors((state_get_last_floor() ), state_get_last_direction()));
                    elev_set_motor_direction(state_get_last_direction());
                    state_motor_started();
                }
            }
        }




    }

            //queue_check_orders_at_current_floor()


            //queue_get_new_direction(int last_floor, int direction)

    return 0;
}
