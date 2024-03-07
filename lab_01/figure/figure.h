#ifndef FIGURE_H
#define FIGURE_H

#include <stdio.h>
#include "actions.h"
#include "errors.h"
#include "points.h"
#include "edges.h"

struct figure
{
    point_3D_t center;
    points_3D_t points;
    edges_t edges;
};

typedef struct figure figure_t;

figure_t &init_figure();

err_t free_figure(figure_t &figure);
err_t move_figure(figure_t &figure, const move_t &move);
err_t scale_figure(figure_t &figure, const scale_t &scale);
err_t rotate_figure(figure_t &figure, const rotate_t &rotate);

err_t fload_figure(figure_t &figure, const char *file_name);
err_t fsave_figure(figure_t &figure, const char *file_name);

#endif // FIGURE_H
