typedef enum tag_button_type {
    QUEUE_CALL_UP = 0,
    QUEUE_CALL_DOWN = 1,
    QUEUE_COMMAND = 2
} queue_button_type_t;

void queue_add_order();
int queue_get_new_direction(int last_floor, int last_direction);
int queue_check_orders_at_current_floor(int current_floor, int last_direction);
int queue_get_new_direction_if_between_floors(int last_floor, int last_direction);
void queue_clear_order(int last_floor);
void queue_clear_all_orders();
