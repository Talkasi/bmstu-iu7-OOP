#include "edge.h"

err_t fload_edge(FILE *f, edge_t &edge)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    if (fscanf(f, "%zu %zu", &edge.first, &edge.second) != 2)
        rc = WRONG_FILE_ERR;

    if (rc == SUCCESS) {
        if (edge.first == 0 || edge.second == 0)
            rc = WRONG_EDGE_ERR;

        if (rc == SUCCESS) {
            --edge.first;
            --edge.second;

            if (edge.first == edge.second)
                rc = WRONG_EDGE_ERR;
        }
    }

    return rc;
}

err_t fsave_edge(FILE *f, const edge_t &edge)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    if (fprintf(f, "%zu %zu\n", edge.first + 1, edge.second + 1) < 0)
        rc = FSAVE_NEDGES_ERR;

    return rc;
}
