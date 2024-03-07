#include "points.h"
#include "point.h"
#include "tools.h"
#include <stdlib.h>


points_3D_t points_default(void)
{
    return points_3D_t{0, 0};
}


err_t alloc_points(point_3D_t *&points, const size_t npoints)
{
    if (points != NULL)
        return WRONG_POINTS_PTR_ERR;

    if (npoints == 0)
        return WRONG_NPOINTS_ERR;

    err_t rc = SUCCESS;
    points = (point_3D_t *)calloc(npoints, sizeof(point_3D_t));
    if (points == NULL)
        rc = POINTS_ALLOC_ERR;

    return rc;
}

err_t free_points(points_3D_t &points)
{
    free(points.data);
    points.data = NULL;
    points.n = 0;
    return SUCCESS;
}


err_t free_points_data(point_3D_t *&points, size_t &npoints)
{
    free(points);
    points = NULL;
    npoints = 0;
    return SUCCESS;
}


err_t fload_points(FILE *f, point_3D_t *points, const size_t npoints)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    if (points == NULL)
        return WRONG_POINTS_PTR_ERR;

    if (npoints == 0)
        return WRONG_NPOINTS_ERR;

    err_t rc = SUCCESS;
    for (size_t i = 0; (i < npoints) && (rc == SUCCESS); ++i)
        rc = fload_point(f, points[i]);

    return rc;
}


err_t fload_npoints(FILE *f, size_t &n)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    if (fscanf(f, "%zu", &n) != 1)
        rc = WRONG_FILE_ERR;

    return rc;
}


err_t fload_points_segment(FILE *f, points_3D_t &points)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    if (points.data != NULL)
        return WRONG_POINTS_PTR_ERR;

    if (points.n != 0)
        return WRONG_NPOINTS_ERR;

    err_t rc = SUCCESS;
    rc = fload_npoints(f, points.n);

    if (rc == SUCCESS) {
        rc = alloc_points(points.data, points.n);

        if (rc == SUCCESS) {
            rc = fload_points(f, points.data, points.n);

            if (rc != SUCCESS)
                rc = free_points_data(points.data, points.n);
        }
    }

    return rc;
}


err_t fsave_npoints(FILE *f, const size_t npoints)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    if (fprintf(f, "%zu\n", npoints) < 0)
        rc = FSAVE_NPOINTS_ERR;

    return rc;
}


err_t fsave_points(FILE *f, const point_3D_t *points, const size_t npoints)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    if (points == NULL)
        return WRONG_POINTS_PTR_ERR;

    if (npoints == 0)
        return WRONG_NPOINTS_ERR;

    err_t rc = SUCCESS;
    for (size_t i = 0; (i < npoints) && (rc == SUCCESS); ++i)
        rc = fsave_point(f, points[i]);

    return rc;
}


err_t fsave_points_segment(FILE *f, const points_3D_t &points)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;

    rc = fsave_npoints(f, points.n);
    if (rc == SUCCESS) {
        rc = fsave_points(f, points.data, points.n);

        if (rc != SUCCESS)
            rc = clear_file(f);
    }

    return rc;
}


err_t move_points(points_3D_t &points, const move_t move)
{
    err_t rc = SUCCESS;
    for (size_t i = 0; (i < points.n) && (rc == SUCCESS); ++i)
        rc = move_point(points.data[i], move);
    return rc;
}


err_t scale_points(points_3D_t &points, point_3D_t scale_center, const scale_t &scale)
{
    err_t rc = SUCCESS;
    for (size_t i = 0; (i < points.n) && (rc == SUCCESS); ++i)
        rc = scale_point(points.data[i], scale_center, scale);
    return rc;
}


err_t rotate_points(points_3D_t &points, point_3D_t rotate_center, const rotate_t &rotate)
{
    err_t rc = SUCCESS;
    for (size_t i = 0; (i < points.n) && (rc == SUCCESS); ++i)
        rc = rotate_point(points.data[i], rotate_center, rotate);
    return rc;
}
