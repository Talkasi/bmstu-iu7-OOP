#ifndef POINTS_H
#define POINTS_H
#include "actions.h"
#include "errors.h"
#include "point.h"
#include <stdio.h>

typedef struct points_3D points_3D_t;

struct points_3D
{
    point_3D_t *data;
    size_t n;
};

points_3D_t points_default(void);

err_t alloc_points(point_3D_t *&points, const size_t npoints);
err_t free_points_data(point_3D_t *&points, size_t &npoints);
err_t free_points(points_3D_t &points);

err_t fload_points(FILE *f, point_3D_t *points, const size_t npoints);
err_t fload_npoints(FILE *f, size_t &n);
err_t fload_points_segment(FILE *f, points_3D_t &points);

err_t fsave_npoints(FILE *f, const size_t npoints);
err_t fsave_points(FILE *f, const point_3D_t *points, const size_t npoints);
err_t fsave_points_segment(FILE *f, const points_3D_t &points);

err_t move_points(points_3D_t &points, const move_t move);
err_t scale_points(points_3D_t &points, point_3D_t scale_center, const scale_t &scale);
err_t rotate_points(points_3D_t &points, point_3D_t rotate_center, const rotate_t &rotate);

#endif // POINTS_H
