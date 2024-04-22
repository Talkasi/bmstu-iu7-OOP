#include "requests.h"

#include "figure.h"

err_t requests_handler(request_t &request)
{
    static figure_t figure = init_figure();
    err_t rc;

    switch (request.action) {
    case LOAD:
        rc = fload_figure(figure, request.filename);
        break;
    case SAVE:
        rc = fsave_figure(figure, request.filename);
        break;
    case MOVE:
        rc = move_figure(figure, request.move);
        break;
    case SCALE:
        rc = scale_figure(figure, request.scale);
        break;
    case ROTATE:
        rc = rotate_figure(figure, request.rotate);
        break;
    case DRAW:
        rc = draw_figure(figure, request.scene);
        break;
    case QUIT:
        rc = free_figure(figure);
        break;
    default:
        rc = UNDEFINED_COMMAND;
        break;
    }

    return rc;
}
