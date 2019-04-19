#include "state.h"

state_state_type_t current_state;
int last_direction;
int last_floor;
int elevator_above_last_floor;

void state_init(void){
    current_state = INITIALIZE;
}

void state_arrived_at_any_floor(void){
    current_state = IDLE;
}

void state_door_opened(void){
    current_state = DOOR_OPEN;
}

void state_timer_finished(void){
    current_state = IDLE;
}

void state_motor_started(void){
    current_state = RUNNING;
}

void state_stop_button_pressed(void){
    current_state = EM_STOP;
}

void state_stop_button_released(void){
    current_state = IDLE_BETWEEN_FLOORS;
}


state_state_type_t state_get_current_state(void){
    return current_state;
}


int state_get_last_direction(void){
    return last_direction;
}

void state_set_last_direction(int direction){
    last_direction = direction;
}

int state_get_last_floor(void){
    return last_floor;
}

void state_set_last_floor(int current_floor){
    last_floor = current_floor;
}

void state_set_elevator_above_last_floor(void){
    elevator_above_last_floor = 1;
}

void state_clear_elevator_above_last_floor(void){
    elevator_above_last_floor = 0;
}


int state_get_elevator_above_last_floor(void){
    return elevator_above_last_floor;
}
