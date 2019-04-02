
extern elev_button_type_t direction;


/**
 Needs to be running all the time. 
 if a button is pushed, adds the order to the floor 
returns 1 if there IS an order, 0 else
*/
int check_queue();


/**
  Check for order on input floor 
  returns 1 if there exists an order in the floor, 0 else
*/
int check_queue_floor(int floor);



/**
  tells the system whether it should stop at the current floor
*/
int should_stop(int floor);


/**
  delete all orders on input floor
*/
void delete_floor_order(int floor);


/**
  deletes arr_opp, arr_ned, arr_destination on all floors using delete_floor_order
*/
void delete_all_orders();


/**
  Check for order on all floors and in elevator
  iterate through whole lists to see if orders above, below or in current floor
  returns 1 if direction up, 0 if order in current floor or -1 if direction down
  floor is the last locally known floor the elevator is in
*/
int get_direction(int floor);



/**
  checks the destination array
  if array empty returns -1, else returns floor 
*/
int check_arr_destination();


int order_above(int floor);
int order_below(int floor);