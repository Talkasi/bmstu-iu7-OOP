#ifndef REQUESTS_H
#define REQUESTS_H
#include "actions.h"
#include "errors.h"
#include "draw.h"

typedef enum
{
    LOAD,
    SAVE,
    MOVE,
    ROTATE,
    SCALE,
    DRAW,
    QUIT
} action_t;

typedef struct
{
    action_t action;
    union
    {
        const char *filename;
        move_t move;
        rotate_t rotate;
        scale_t scale;
        scene_t scene;
    };
} request_t;


err_t requests_handler(request_t &request);

#endif
