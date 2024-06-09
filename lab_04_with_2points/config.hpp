#ifndef LAB_04_CONFIG_HPP
#define LAB_04_CONFIG_HPP

#define NO_TEXT_COLOR "\033[0m"
#define RED_TEXT_COLOR "\033[0;31m"
#define GREEN_TEXT_COLOR "\033[0;32m"
#define BLUE_TEXT_COLOR "\033[0;34m"
#define PURPLE_TEXT_COLOR "\033[0;35m"
#define CYAN_TEXT_COLOR "\033[0;36m"
#define WHITE_TEXT_COLOR "\033[0;37m"

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

enum cabin_id_t
{
    FIRST_CABIN_ID,
    SECOND_CABIN_ID
};

enum direction_t
{
    DOWN = -1,
    STAND = 0,
    UP = 1,
};

enum to_visit_t
{
    TO_VISIT_WHILE_UP,
    TO_VISIT_WHILE_DOWN,
    TO_VISIT_ON_ANY,
    N_CASES_TO_VISIT
};

enum direction_id_t
{
    UP_ID,
    DOWN_ID
};

#endif // LAB_04_CONFIG_HPP
