#include "point.h"
#include <math.h>

point_3D_t point_default(void)
{
    return point_3D_t{0, 0, 0};
}

err_t fload_point(FILE *f, point_3D_t &point)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    if (fscanf(f, "%lf %lf %lf", &point.x, &point.y, &point.z) != 3)
        rc = WRONG_FILE_ERR;

    return rc;
}

err_t fsave_point(FILE *f, const point_3D_t &point)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    if (fprintf(f, "%lf %lf %lf\n", point.x, point.y, point.z) < 0)
        rc = FSAVE_NPOINTS_ERR;

    return rc;
}

err_t move_point(point_3D_t &point, const move_t &move)
{
    err_t rc = SUCCESS;
    point.x += move.dx;
    point.y += move.dy;
    point.z += move.dz;
    return rc;
}

err_t rotate_point(point_3D_t &point, const point_3D_t &rotate_center, const rotate_t &rotate)
{
    err_t rc = SUCCESS;

    double x = point.x - rotate_center.x;
    double y = point.y - rotate_center.y;
    double z = point.z - rotate_center.z;

    double yaw = rotate.yaw * M_PI / 180;
    double pitch = rotate.pitch * M_PI / 180;
    double roll = rotate.roll * M_PI / 180;

    point.x = x * (cos(yaw) * cos(pitch)) + y * (cos(yaw) * sin(pitch) * sin(roll) - sin(yaw) * cos(roll)) +
              z * (cos(yaw) * sin(pitch) * cos(roll) + sin(yaw) * sin(roll));
    point.y = x * (sin(yaw) * cos(pitch)) + y * (sin(yaw) * sin(pitch) * sin(roll) + cos(yaw) * cos(roll)) +
              z * (sin(yaw) * sin(pitch) * cos(roll) - cos(yaw) * sin(roll));
    point.z = x * (-sin(pitch)) + y * (cos(pitch) * sin(roll)) + z * (cos(pitch) * cos(roll));

    point.x += rotate_center.x;
    point.y += rotate_center.y;
    point.z += rotate_center.z;

    return rc;
}

err_t scale_point(point_3D_t &point, const point_3D_t &scale_center, const scale_t &scale)
{
    err_t rc = SUCCESS;
    point.x = (point.x - scale_center.x) * scale.kx + scale_center.x;
    point.y = (point.y - scale_center.y) * scale.ky + scale_center.y;
    point.z = (point.z - scale_center.z) * scale.kz + scale_center.z;
    return rc;
}
