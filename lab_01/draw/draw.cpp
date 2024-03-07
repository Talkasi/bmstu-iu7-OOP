#include "draw.h"
#include <QLine>


line_2D_t line_2D_default(void)
{
    return line_2D_t{0, 0};
}

line_3D_t line_3D_default(void)
{
    return line_3D_t{0, 0};
}

err_t draw_line2D(const point_2D_t &first_point, 
                  const point_2D_t &second_point, const scene_t &scene)
{
    err_t rc = SUCCESS;
    QPen Pen = QPen(Qt::black, 2);
    scene.scene->addLine(QLineF(first_point.x, first_point.y,
                                second_point.x, second_point.y), Pen);
    return rc;
}

err_t convert_point(point_2D_t &dst, const point_3D_t &src, const scene_t &scene)
{
    err_t rc = SUCCESS;
    dst.x = src.x + scene.width / 2;
    dst.y = src.y + scene.height / 2;
    return rc;
}

err_t clear_point2D(point_2D_t &point)
{
    err_t rc = SUCCESS;
    point.x = 0;
    point.y = 0;
    return rc;
}

err_t convert_line(line_2D_t &dst, const line_3D_t &src, const scene_t &scene)
{
    err_t rc = SUCCESS;

    rc = convert_point(dst.first, src.first, scene);
    if (rc == SUCCESS) {
        rc = convert_point(dst.second, src.second, scene);

        if (rc != SUCCESS)
            rc = clear_point2D(dst.first);
    }

    return rc;
}

err_t get_point(point_3D_t &dst, const points_3D_t &points, const size_t &point_index)
{
    if (points.n <= point_index)
        return WRONG_POINT_INDEX_ERR;

    err_t rc = SUCCESS;
    dst = points.data[point_index];
    return rc;
}

err_t clear_point3D(point_3D_t &p)
{
    err_t rc = SUCCESS;
    p.x = 0;
    p.y = 0;
    p.z = 0;
    return rc;
}

err_t get_line3D_points(line_3D_t &line, const edge_t &edge_desc, const points_3D_t &points)
{
    if (edge_desc.first == edge_desc.second)
        return WRONG_EDGE_ERR;

    err_t rc = SUCCESS;
    rc = get_point(line.first, points, edge_desc.first);

    if (rc == SUCCESS) {
        rc = get_point(line.second, points, edge_desc.second);

        if (rc != SUCCESS)
            rc = clear_point3D(line.first);
    }

    return rc;
}

err_t draw_edges(const edges_t &edges, const points_3D_t &points, const scene_t &scene)
{
    err_t rc = SUCCESS;

    for (size_t i = 0; (i < edges.n) && (rc == SUCCESS); ++i) {
        line_3D_t line3D = line_3D_default();
        rc = get_line3D_points(line3D, edges.data[i], points);

        if (rc == SUCCESS) {
            line_2D_t line2D = line_2D_default();
            rc = convert_line(line2D, line3D, scene);

            if (rc == SUCCESS)
                rc = draw_line2D(line2D.first, line2D.second, scene);
        }
    }

    return rc;
}

err_t draw_figure(const figure_t &figure, const scene_t &scene)
{
    scene.scene->clear();
    err_t rc = draw_edges(figure.edges, figure.points, scene);
    return rc;
}
