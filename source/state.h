
typedef enum tag_state_state_type {
    INITIALIZE = 0,
    IDLE = 1,
    RUNNING = 2,
    DOOR_OPEN = 3,
    EM_STOP = 4,
    IDLE_BETWEEN_FLOORS = 5
} state_state_type_t;

void state_init(void);

void state_arrived_at_any_floor(void);

void state_arrived_at_correct_floor(void);

void state_timer_finished(void);

void state_motor_started(void);

void state_stop_button_pressed(void);

void state_stop_button_released(void);


state_state_type_t state_get_current_state(void);


int state_get_last_direction(void);

void state_set_last_direction(int direction);



int state_get_last_floor(void);

void state_set_last_floor(int current_floor);
