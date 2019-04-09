/**@file
 * @Contains the variables and functions we use for our queue system. 
*/
extern elev_motor_direction_t direction;


/**
  @brief initilializes queue arrays.
*/
void init_arrays();

/**
 @brief Checks if there are any orders at all
@returns 1 if there IS an order, 0 else
*/

int check_orders();
/**
 @brief If a button is pushed, adds the order to the floor. Needs to be running all the time. 
@returns 1 if someone is pushing a button, 0 else
*/
int check_queue();

/**
  @brief Check for order on input floor.
  @param floor Which floor to check the queue in.
  @returns 1 if there exists an order in the floor, 0 else
*/
int check_queue_floor(int floor);

/**
  @brief delete all orders on input floor
  @param floor Which floor to delete orders in.
*/
void delete_floor_order(int floor);

/**
  @brief sets arr_opp, arr_ned, arr_destination to zero in all floors.
*/
void delete_all_orders();

/**
  @brief checks if there are any orders above the input floor.
  @param floor Which floor to check if there are orders above.
  @returns 1 if true, 0 else
*/
int order_above(int floor);

/**
  @brief checks if there are any orders below the input floor.
  @param floor Which floor to check if there are orders below.
  @returns 1 if true, 0 else
*/
int order_below(int floor);

/**
@brief checks if there any orders that's going down or from inside in the input floor.
@param floor Which floor to check if there are any orders to take.
@returns 1 if true, 0 else
*/
int order_floor_direction_down(int floor);

/**
@brief checks if there any orders that's going up or from inside in the input floor.
@param floor Which floor to check if there are any orders to take.
@returns 1 if true, 0 else
*/
int order_floor_direction_up(int floor);


/**
  @brief tells the elevator which way to go.
  Check for order on all floors and in elevator.
  Iterate through whole lists to see if orders above, below or in current floor.
  @param floor Which floor the elevator was in last.
  @returns DIRN_UP if direction up, DIRN_STOP if order in current floor or DIRN_DOWN if direction down
  
*/
elev_motor_direction_t get_direction(int floor);

