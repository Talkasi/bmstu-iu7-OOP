#ifndef LAB_04_CONFIG_HPP
#define LAB_04_CONFIG_HPP

enum cabin_id_t
{
    FIRST_CABIN_ID,
    SECOND_CABIN_ID
};

enum direction_t
{
    DOWN = -1,
    STAND = 0,
    UP = 1
};

enum direction_id_t
{
    UP_ID,
    DOWN_ID
};


#define FLOOR_NOT_FOUND -50
#define N_DIRECTIONS 2

#define COLOR_BUTTON_ACTIVE "green"
#define COLOR_BUTTON_INACTIVE "grey"

#define N_FLOORS 10
#define START_FLOOR 1
#define N_CABINS 2

#define WAIT_TIME 1000
#define DOOR_TIME 1000
#define MOVE_TIME 1000

#endif // LAB_04_CONFIG_HPP
