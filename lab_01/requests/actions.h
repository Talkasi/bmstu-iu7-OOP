#ifndef ACTIONS_H
#define ACTIONS_H

struct move
{
    double dx;
    double dy;
    double dz;
};

struct rotate
{
    double yaw;
    double pitch;
    double roll;
};

struct scale
{
    double kx;
    double ky;
    double kz;
};


typedef struct move move_t;
typedef struct rotate rotate_t;
typedef struct scale scale_t;

#endif
