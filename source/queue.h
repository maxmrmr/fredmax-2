/**
* @file
* @brief An elevator queue and functions deciding which
* order in queue is the next to be excecuted.
*/

/**
* @brief Add an order to queue.
*
* @param [in] order Number from 0-11 deciding which order to add.
*/
void queue_add_order(int order);

/**
* @brief Get new direction for elevator to excecute next order.
*
* @param [in] last_floor Last floor visited or current floor if in a floor.
* @param [in] last_direction Last direction traveled.
*
* @return 0 if elevator is to stay idle, 1 if elevator is to run up, -1 if elevator is to run down.
*/
int queue_get_new_direction(int last_floor, int last_direction);

/**
* @brief Get new direction for elevator to excecute next order, if elevator is between floors.
*
* @param [in] last_floor Last floor visited.
* @param [in] last_direction Last direction traveled.
* @param [in] elevator_above_last_floor Number saying whether elevator is above or below last floor visited.
*
* @return 0 if elevator is to stay idle, 1 if elevator is to run up, -1 if elevator is to run down.
*/
int queue_get_new_direction_if_between_floors(int last_floor, int elevator_above_last_floor);

/**
* @brief Check if elevator should stop when arriving at a floor.
*
* @param [in] current_floor Floor arrived at.
* @param [in] last_direction Last direction traveled.
*
* @return 1 if elevator should stop, 0 if elevator should keep running.
*/
int queue_check_orders_at_current_floor(int current_floor, int last_direction);

/**
* @brief Clear orders in a floor from queue,
* used after picking up all users in a floor.
*
* @param [in] floor Floor to clear orders from.
*
*/
void queue_clear_orders_in_floor(int floor);

/**
* @brief Clear all orders from queue,
* used after stop button is pressed.
*/
void queue_clear_all_orders(void);
