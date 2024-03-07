#ifndef POINT_H
#define POINT_H
#include <stdio.h>
#include "actions.h"
#include "errors.h"

typedef struct point_3D point_3D_t;

struct point_3D
{
    double x;
    double y;
    double z;
};

point_3D_t point_default(void);

err_t fload_point(FILE *f, point_3D_t &point);
err_t fsave_point(FILE *f, const point_3D_t &point);

err_t move_point(point_3D_t &point, const move_t &move);
err_t scale_point(point_3D_t &point, const point_3D_t &scale_center, const scale_t &scale);
err_t rotate_point(point_3D_t &point, const point_3D_t &rotate_center, const rotate_t &rotate);

#endif // POINT_H
