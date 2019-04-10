#include "queue.h"

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
		if (queue[(current_floor*3 + QUEUE_CALL_UP)] || queue[(((current_floor)*3)+QUEUE_COMMAND)]){
			return 1;
		}
	}
	else if (current_floor == 1){
		if (queue[(current_floor*3 + QUEUE_COMMAND)]){
			return 1;
		}
		if (last_direction < 0){
			if (queue[(current_floor*3 + QUEUE_CALL_DOWN)]){
				return 1;
			}
		}

		else if (last_direction > 0){
			if (queue[(current_floor*3 + QUEUE_CALL_UP)]){
				return 1;
			}
		}
	}
	else if (current_floor == 2){
			if (queue[(current_floor*3 + QUEUE_COMMAND)]){
				return 1;
			}
		if (last_direction < 0){
			if (queue[(current_floor*3 + QUEUE_CALL_DOWN)]){
				return 1;
			}
		}

		else if (last_direction > 0){
			if (queue[(current_floor*3 + QUEUE_CALL_UP)]){
				return 1;
			}
		}
	}
	else if (current_floor == 3){
		if (queue[(current_floor*3 + QUEUE_CALL_DOWN)] || queue[(current_floor*3 + QUEUE_COMMAND)]){
			return 1;
		}
	}

//-------------------------------------------------------------------------------

//No orders in same direction or command in current floor, check if stop anyway

	if (last_direction < 0){
		if (current_floor == 2){
			if ( (!queue[0]) && (!queue[1]) && (!queue[2]) ){  		//Check if no orders in 1st floor
				if ( (!queue[3]) && (!queue[4]) && (!queue[5]) ){ 	//Check if no orders in 2nd floor
					if (queue[6]){									//Check if order in 3rd floor, not in same direction or command
						return 1;
					}
				}
			}
		}

		if (current_floor == 1){
			if ( (!queue[0]) && (!queue[1]) && (!queue[2]) ){ 	//Check if no orders in 1st floor
				if (queue[3]){									//Check if order in 2nd floor, not in same direction or command
					return 1;
				}
			}
		}
	}
	if (last_direction > 0){
		if (current_floor == 1){
			if ( (!queue[6]) && (!queue[7]) && (queue[8]!=1) ){ 	//Check if no orders in 3rd floor
				if ( (!queue[9]) && (!queue[10]) && (!queue[11]) ){ //Check if no orders in 4th floor
					if (queue[4]){									//Check if order in 2nd floor, not in same direction or command
						return 1;
					}
				}
			}
		}

		if (current_floor == 2){
			if ( (!queue[9]) &&	(!queue[10]) && (!queue[11]) ){ 	//Check if no orders in 4th floor
				if (queue[7]){									//Check if order in 3rd floor, not in same direction or command
					return 1;
				}
			}
		}
	}
	return 0;
}

void queue_clear_order(int last_floor){
	if (last_floor == 0){
		queue[0] = 0;	//1st floor CALL_UP
		queue[1] = 0;	//Dummy
		queue[2] = 0;	//1st floor COMMAND
	}
	else if (last_floor == 1){
		queue[3] = 0;	//2nd floor CALL_UP
		queue[4] = 0;	//2nd floor CALL_DOWN
		queue[5] = 0;	//2nd floor COMMAND
	}
	else if (last_floor == 2){
		queue[6] = 0;	//3rd floor CALL_UP
		queue[7] = 0;	//3rd floor CALL_DOWN
		queue[8] = 0;	//3rd floor COMMAND
	}
	else if (last_floor == 3){
		queue[9] = 0;	//Dummy
		queue[10] = 0;	//4th floor CALL_DOWN
		queue[11] = 0;	//4th floor COMMAND
	}
}

void queue_clear_all_orders(void){
	int i;
	for (i=0; i<=11; i++){
		queue[i] = 0;
	}
}
