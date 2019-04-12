/**
* @file
* @brief Main control of elevator system for use at the real time lab NTNU
*/

#include "elev.h"
#include "queue.h"
#include "timer.h"
#include "state.h"

#include <stdio.h>

/**
* @brief Clear all lamps, used when initializing and when stop button is pressed
*/
void clear_all_lamps(void){
	int i;
	for (i=0; i<=3; i++){
		if (i != 3) {
			elev_set_button_lamp(BUTTON_CALL_UP, i, 0);
		}
		if (i != 0) {
			elev_set_button_lamp(BUTTON_CALL_DOWN, i, 0);
		}
		elev_set_button_lamp(BUTTON_COMMAND, i, 0);
	}
}

/**
* @brief Clear lamps in current floor, used when reaching a floor and picking up users
*/
void clear_lamps_in_current_floor(void){
	int i;
	for (i = 0; i < 3; ++i) {
		if (state_get_last_floor() == 0) {
			if (i != 1) {
				elev_set_button_lamp(i, state_get_last_floor(), 0);
			}
		}
		else if (state_get_last_floor() == 3) {
			if (i != 0) {
				elev_set_button_lamp(i, state_get_last_floor(), 0);
			}
		}
		else {
			elev_set_button_lamp(i, state_get_last_floor(), 0);
		}
	}
}

/**
* @brief Main control system controlling elevator.
*
* @return 1 if unable to initialize elevator hardware, 0 if finished running
*/
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
		clear_all_lamps();
		int current_floor = -1; //Variable used to temporarly hold current floor in if statement with elev_get_floor_sensor_signal()
		int new_direction = 0;  //Variable used to temporarly hold new direction in if statement with queue_get_new_direction()
		int elevator_above_last_floor = 0; //Variable used to check if elevator is above or below last known floor. 1 for above, 0 for below.

    elev_set_motor_direction(DIRN_DOWN);
    state_set_last_direction(DIRN_DOWN);

    while(elev_get_floor_sensor_signal() < 0){}
    elev_set_motor_direction(DIRN_STOP);
    state_arrived_at_any_floor();
    if ((current_floor = elev_get_floor_sensor_signal()) != -1){
        state_set_last_floor(current_floor);
    }

	while (1) {

		//Check if stop button is pressed, if pressed stop motor, clear queue, turn on stop light and clear all lamps
		if (elev_get_stop_signal()) {
			elev_set_motor_direction(DIRN_STOP);
			state_stop_button_pressed();
			queue_clear_all_orders();
			elev_set_stop_lamp(1);
			clear_all_lamps();

			//if elevator is in a floor when stop button is pressed, open door
			if (elev_get_floor_sensor_signal() >= 0){
				elev_set_door_open_lamp(1);
			}
		}

		//Check if stop button is released, if released and previous state was EM_STOP, handle starting after EM_STOP
		if (!(elev_get_stop_signal())) {
			if (state_get_current_state() == EM_STOP) {
				elev_set_stop_lamp(0);
				state_stop_button_released();
				if ((current_floor = elev_get_floor_sensor_signal()) != -1) {
					elev_set_door_open_lamp(1);
					state_door_opened();
					timer_start();
				}
			}
		}

		//Only allowed to do stuff when not in emergency stop
		if (state_get_current_state() != EM_STOP) {

			//Check timer, if the time is out and the door is open close the door
			if (timer_is_time_out()) {
				if (state_get_current_state() == DOOR_OPEN){
					elev_set_door_open_lamp(0);
					state_timer_finished();
				}
			}

			//If elevator is idle, check queue, if another order is in queue run in needed direction
			if (state_get_current_state() == IDLE ){
				if ((new_direction = queue_get_new_direction(state_get_last_floor(), state_get_last_direction()))) {
					state_set_last_direction(new_direction);
					elev_set_motor_direction(state_get_last_direction());
					state_motor_started();
				}
			}

			//For loop checking all button signals except stop, adding orders to queue and turning on lights if any button is pressed
			int i;
			for (i = 0; i < N_FLOORS; ++i) {
				if (i != 0) {
					if (elev_get_button_signal(BUTTON_CALL_DOWN, i)) {
						queue_add_order((3 * i + 1));                      //3*i for floor number, +1 for BUTTON_CALL_DOWN
						elev_set_button_lamp(BUTTON_CALL_DOWN, i, 1);
					}
				}


				if (i != N_FLOORS - 1){
					if (elev_get_button_signal(BUTTON_CALL_UP, i)) {
						queue_add_order((3 * i));                       //3*i for floor number, +0 for BUTTON_CALL_UP
						elev_set_button_lamp(BUTTON_CALL_UP, i, 1);
					}
				}

				if (elev_get_button_signal(BUTTON_COMMAND, i)) {
					queue_add_order((3 * i) + 2);                          //3*i for floor number, +2 for BUTTON_COMMAND
					elev_set_button_lamp(BUTTON_COMMAND, i, 1);
				}
			}

			//When arriving or passing a floor set last floor and set floor indicator light
			if ((current_floor = elev_get_floor_sensor_signal()) != -1) {
				state_set_last_floor(current_floor);
				if (state_get_last_direction() > 0){
					elevator_above_last_floor = 1;
				}
				else{
					elevator_above_last_floor = 0;
				}
				elev_set_floor_indicator(state_get_last_floor());


				//Check if elevator should stop when arriving at any floor, if stop clear orders and turn off lamps in floor and open door
				if (queue_check_orders_at_current_floor(state_get_last_floor(), state_get_last_direction())) {
					elev_set_motor_direction(DIRN_STOP);
					queue_clear_orders_in_floor(state_get_last_floor());
					clear_lamps_in_current_floor();
					elev_set_door_open_lamp(1);
					state_door_opened();
					timer_start();
				}
			}

			//Check if state is IDLE_BETWEEN_FLOORS if it is, check orders and get correct new direction when between floors
			if (state_get_current_state() == IDLE_BETWEEN_FLOORS) {
				if ((new_direction = queue_get_new_direction_if_between_floors((state_get_last_floor()), state_get_last_direction()))) {
					state_set_last_direction(new_direction);
					elev_set_motor_direction(state_get_last_direction());
					state_motor_started();
				}
			}
		}
	}

    return 0;
}
