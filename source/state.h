/**
* @file
* @brief A simple state machine for controlling the state of the elevator
* and keeping track of the last floor visited and the last direction used.
*/

/**
* @brief States for checking which state elevator is in.
*/
typedef enum tag_state_state_type {
    INITIALIZE = 0,
    IDLE = 1,
    RUNNING = 2,
    DOOR_OPEN = 3,
    EM_STOP = 4,
    IDLE_BETWEEN_FLOORS = 5
} state_state_type_t;

/**
* @brief Sets the state to INITIALIZE, used upon start of program.
*/
void state_init(void);

/**
* @brief Sets the state to IDLE, used upon arriving at any floor after initializing.
*/
void state_arrived_at_any_floor(void);

/**
* @brief Sets the state to DOOR_OPEN, used upon opening doors in a floor where elevator has an order
* or is stopped with the stop button.
*/
void state_door_opened(void);

/**
* @brief Sets the state to IDLE, used upon closing doors in a floor where elevator had stopped,
* when 3 second timer is finished.
*/
void state_timer_finished(void);

/**
* @brief Sets the state to RUNNING, used upon starting elevator motor, when elevator starts running.
*/
void state_motor_started(void);

/**
* @brief Sets the state to EM_STOP, used when stop button is pressed.
*/
void state_stop_button_pressed(void);

/**
* @brief Sets the state to IDLE_BETWEEN_FLOORS, used when stop button is released
* when elevator is between floors.
*/
void state_stop_button_released(void);

/**
* @brief Get current state of elevator.
*
* @return The current state of the elevator in datatype state_state_type_t.
*/
state_state_type_t state_get_current_state(void);

/**
* @brief Get the last direction the elevator was running.
*
* @return -1 if the last direction was down, 1 if the last direction was up.
*/
int state_get_last_direction(void);

/**
* @brief Set the last direction the elevator was running.
*
* @param [in] direction Which direction the elevator is starting to run.
*/
void state_set_last_direction(int direction);

/**
* @brief Get the last floor the elevator was in or passed.
*
* @return 0-3, 0 is bottom floor 3 is top floor.
*/
int state_get_last_floor(void);

/**
* @brief Set the last floor the elevator was in or passed.
*
* @param [in] current_floor Which floor the elevator is currently in.
*/
void state_set_last_floor(int current_floor);
