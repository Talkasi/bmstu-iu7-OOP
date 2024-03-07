#ifndef DRAW_H
#define DRAW_H
#include <QGraphicsScene>
#include "errors.h"
#include "figure.h"

typedef struct {
    double x;
    double y;
} point_2D_t;

typedef struct {
  point_2D_t first;
  point_2D_t second;
} line_2D_t;

typedef struct {
  point_3D_t first;
  point_3D_t second;
} line_3D_t;

struct scene {
    QGraphicsScene *scene;
    double width;
    double height;
};

typedef struct scene scene_t;

err_t draw_figure(const figure_t &figure, const scene_t &scene);

#endif // DRAW_H
