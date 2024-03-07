#include <stdio.h>
#include "figure.h"
#include "tools.h"

err_t free_figure(figure_t &figure)
{
    err_t rc = SUCCESS;
    free_points(figure.points);
    free_edges(figure.edges);
    return rc;
}


err_t get_max_figure_point(point_3D_t &max_point, const point_3D_t *points, const size_t npoints)
{
    if (points == NULL)
        return WRONG_POINTS_PTR_ERR;

    if (npoints == 0)
        return WRONG_NPOINTS_ERR;

    err_t rc = SUCCESS;

    max_point = points[0];
    for (size_t i = 1; i < npoints; ++i) {
        if (points[i].x > max_point.x)
            max_point.x = points[i].x;

        if (points[i].y > max_point.y)
            max_point.y = points[i].y;

        if (points[i].z > max_point.z)
            max_point.z = points[i].z;
    }

    return rc;
}

err_t get_min_figure_point(point_3D_t &min_point, const point_3D_t *points, const size_t npoints)
{
    if (points == NULL)
        return WRONG_POINTS_PTR_ERR;

    if (npoints == 0)
        return WRONG_NPOINTS_ERR;

    err_t rc = SUCCESS;

    min_point = points[0];
    for (size_t i = 1; i < npoints; ++i) {
        if (points[i].x < min_point.x)
            min_point.x = points[i].x;

        if (points[i].y < min_point.y)
            min_point.y = points[i].y;

        if (points[i].z < min_point.z)
            min_point.z = points[i].z;
    }

    return rc;
}

err_t compute_center(point_3D_t center, point_3D_t min_point, point_3D_t max_point)
{
    err_t rc = SUCCESS;
    center.x = min_point.x + (max_point.x - min_point.x) / 2;
    center.y = min_point.y + (max_point.y - min_point.y) / 2;
    center.z = min_point.z + (max_point.z - min_point.z) / 2;
    return rc;
}

err_t compute_figure_center(point_3D_t &figure_center, points_3D_t &points)
{
    if (points.data == NULL)
        return WRONG_POINTS_PTR_ERR;

    if (points.n == 0)
        return WRONG_NPOINTS_ERR;

    err_t rc = SUCCESS;

    point_3D_t max_point = point_default();
    point_3D_t min_point = point_default();

    rc = get_max_figure_point(max_point, points.data, points.n);

    if (rc == SUCCESS) {
        rc = get_min_figure_point(min_point, points.data, points.n);

        if (rc == SUCCESS) {
            rc = compute_center(figure_center, min_point, max_point);
        }
    }

    return rc;
}


figure_t &init_figure()
{
    static figure_t figure;
    figure.center = point_default();
    figure.points = points_default();
    figure.edges = edges_default();
    return figure;
}

err_t copy_figure(figure_t &dst_figure, const figure_t &src_figure)
{
    err_t rc = SUCCESS;
    dst_figure = src_figure;
    return rc;
}

err_t load_figure_from_file(figure_t &figure, FILE *f)
{
    err_t rc = SUCCESS;
    rc = fload_points_segment(f, figure.points);

    if (rc == SUCCESS) {
        rc = fload_edges_segment(f, figure.edges);

        if (rc != SUCCESS)
            rc = free_points(figure.points);
    }

    return rc;
}

err_t fload_figure(figure_t &figure, const char *file_name)
{
    if (file_name == NULL)
        return EMPTY_FILE_NAME;

    FILE *f = fopen(file_name, "r");
    if (f == NULL)
        return OPEN_FILE_ERR;

    err_t rc = SUCCESS;
    figure_t tmp_figure = init_figure();
    rc = load_figure_from_file(tmp_figure, f);

    if (rc == SUCCESS) {
        free_figure(figure);
        rc = copy_figure(tmp_figure, figure);
    }

    fclose(f);
    return rc;
}

err_t save_figure_to_file(FILE *f, figure_t &figure)
{
    err_t rc = SUCCESS;

    rc = fsave_points_segment(f, figure.points);

    if (rc == SUCCESS) {
        rc = fsave_edges_segment(f, figure.edges);

        if (rc != SUCCESS)
            rc = clear_file(f);
    }

    return rc;
}

err_t fsave_figure(figure_t &figure, const char *file_name)
{
    if (file_name == NULL)
        return EMPTY_FILE_NAME;

    err_t rc = SUCCESS;
    FILE *f = fopen(file_name, "w");
    if (f == NULL)
        return OPEN_FILE_ERR;

    rc = save_figure_to_file(f, figure);

    fclose(f);
    return rc;
}


err_t move_figure(figure_t &figure, const move_t &move)
{
    err_t rc = SUCCESS;
    rc = move_points(figure.points, move);
    return rc;
}


err_t scale_figure(figure_t &figure, const scale_t &scale)
{
    err_t rc = SUCCESS;
    rc = compute_figure_center(figure.center, figure.points);
    if (rc == SUCCESS)
        rc = scale_points(figure.points, figure.center, scale);
    return rc;
}


err_t rotate_figure(figure_t &figure, const rotate_t &rotate)
{
    err_t rc = SUCCESS;
    rc = compute_figure_center(figure.center, figure.points);
    if (rc == SUCCESS)
        rc = rotate_points(figure.points, figure.center, rotate);
    return rc;
}

