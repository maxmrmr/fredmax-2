#include "queue.h"
#include "elev.h"

int queue[12];

void queue_add_order(int order){
	queue[order] = 1;
}

int queue_get_new_direction_if_between_floors(int last_floor, int last_direction){
	int i;
	for (i=0; i<=11; i++){
		if (last_direction < 0){
			if (queue[i]){
				if (i < (last_floor)*3){ //calculate number for order under last floor
					return -1;
				}
				else if (i > ((last_floor-1)*3+2)){ //calculate number for order over last floor
					return 1;
				}
			}
		}
		else if (last_direction > 0){
			if (queue[i]){
				if (i > ((last_floor)*3+2)){ //calculate number for order over last floor
					return 1;
				}
				else if (i < (last_floor+1)*3){ //calculate number for order under last floor
					return -1;
				}
			}
		}
	}
	return 0;
}

int queue_get_new_direction(int last_floor, int last_direction){
	int i;
	for (i=0; i<=11; i++){
		if (last_direction < 0){
			if (queue[i]){
				if (i < (last_floor)*3){ //calculate number for order under last floor
					if (last_floor != 0){  //Not allowed to run down if at first floor
						return -1;
					}
				}
				else if (i > ((last_floor)*3+2)){ //calculate number for order over last floor
					if (last_floor != 3){  //Not allowed to run up if at top floor
						return 1;
					}
				}
			}
		}
		else if (last_direction > 0){
			if (queue[i]){
				if (i > ((last_floor)*3+2)){ //calculate number for order over last floor
					if (last_floor != 3){  //Not allowed to run up if at top floor
						return 1;
					}
				}
				else if (i < (last_floor)*3){ //calculate number for order under last floor
					if (last_floor != 0){  //Not allowed to run down if at first floor
						return -1;
					}
				}
			}
		}
	}
	return 0;
}


int queue_check_orders_at_current_floor(int current_floor, int last_direction){
//Check if order in same direction or command in current floor
	if (current_floor == 0){
		if ((queue[((current_floor*3)+QUEUE_CALL_UP)]==1 || queue[(((current_floor)*3)+QUEUE_COMMAND)]==1)){
			return 1;
		}
	}
	else if (current_floor == 1){
		if (queue[((current_floor*3)+QUEUE_COMMAND)] == 1){
			return 1;
		}
		if (last_direction < 0){
			if (queue[((current_floor*3)+QUEUE_CALL_DOWN)] == 1){
				return 1;
			}
		}

		else if (last_direction > 0){
			if (queue[(((current_floor)*3)+QUEUE_CALL_UP)] == 1){
				return 1;
			}
		}
	}
	else if (current_floor == 2){
			if (queue[(((current_floor)*3)+QUEUE_COMMAND)] == 1){
				return 1;
			}
		if (last_direction < 0){
			if (queue[(((current_floor)*3)+QUEUE_CALL_DOWN)] == 1){
				return 1;
			}
		}

		else if (last_direction > 0){
			if (queue[(((current_floor)*3)+QUEUE_CALL_UP)] == 1){
				return 1;
			}
		}
	}
	else if (current_floor == 3){
		if ((queue[(((current_floor)*3)+QUEUE_CALL_DOWN)]==1 || queue[(((current_floor)*3)+QUEUE_COMMAND)]==1)){
			return 1;
		}
	}
//-------------------------------------------------------------------------------

//No orders in same direction or command in current floor, check if stop anyway

	if (last_direction < 0){
		if (current_floor == 1){
			if ((queue[(((current_floor)*3)+QUEUE_CALL_UP)]!=1 && queue[(((current_floor)*3)+QUEUE_COMMAND)]!=1)){
				if (queue[(((current_floor)*3)+QUEUE_CALL_UP)]==1){
					return 1;
				}
			}
		}


		else if (current_floor == 2){
			if ((queue[(((current_floor)*3)+QUEUE_CALL_UP)]!=1 && queue[(((current_floor)*3)+QUEUE_COMMAND)]!=1)){
				if (queue[(((current_floor)*3)+QUEUE_CALL_UP)]!=1 && queue[(((current_floor)*3)+QUEUE_CALL_DOWN)]!=1 && queue[(((current_floor)*3)+QUEUE_COMMAND)]!=1){
					if (queue[(((current_floor)*3)+QUEUE_CALL_UP)]==1){
						return 1;
					}
				}
			}
		}
	}
	if (last_direction > 0){
		if (current_floor == 2){
			if ((queue[(((current_floor)*3)+QUEUE_CALL_DOWN)]!=1 && queue[(((current_floor)*3)+QUEUE_COMMAND)]!=1)){
				if (queue[(((current_floor)*3)+QUEUE_CALL_DOWN)]==1){
					return 1;
				}
			}
		}
		else if (current_floor == 1){
			if ((queue[(((current_floor)*3)+QUEUE_CALL_DOWN)]!=1 && queue[(((current_floor)*3)+QUEUE_COMMAND)]!=1)){
				if (queue[(((current_floor)*3)+QUEUE_CALL_UP)]!=1 && queue[(((current_floor)*3)+QUEUE_CALL_DOWN)]!=1 && queue[(((current_floor)*3)+QUEUE_COMMAND)]!=1){
					if (queue[(((current_floor)*3)+QUEUE_CALL_DOWN)]==1){
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

void queue_clear_order(int last_floor){
	if (last_floor == 0){
		queue[0] = 0;
		queue[1] = 0;	//dummy
		queue[2] = 0;
	}
	else if (last_floor == 1){
		queue[3] = 0;
		queue[4] = 0;
		queue[5] = 0;
	}
	else if (last_floor == 2){
		queue[6] = 0;
		queue[7] = 0;
		queue[8] = 0;
	}
	else if (last_floor == 3){
		queue[9] = 0;	//dummy
		queue[10] = 0;
		queue[11] = 0;
	}
}

void queue_clear_all_orders(void){
	int i;
	for (i=0; i<=11; i++){
		queue[i] = 0;
	}
}

void queue_clear_all_lamps(void){
	int i;
	for (i=0; i<=3; i++){
		elev_set_button_lamp(BUTTON_CALL_UP, i, 0);
		elev_set_button_lamp(BUTTON_CALL_DOWN, i, 0);
		elev_set_button_lamp(BUTTON_COMMAND, i, 0);
	}
}

//void queue_clear_all_lamps(void){}
