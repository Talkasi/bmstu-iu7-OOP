#include "edges.h"
#include "tools.h"
#include <stdlib.h>


edges_t edges_default(void)
{
    return edges_t{0, 0};
}


err_t fload_edges(FILE *f, edge_t *edges, const size_t nedges)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    if (edges == NULL)
        return WRONG_EDGES_PTR_ERR;

    if (nedges == 0)
        return WRONG_NEDGES_ERR;

    err_t rc = SUCCESS;
    for (size_t i = 0; (i < nedges) && (rc == SUCCESS); ++i)
        rc = fload_edge(f, edges[i]);

    return rc;
}



err_t fload_nedges(FILE *f, size_t &n)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    if (fscanf(f, "%zu", &n) != 1)
        rc = WRONG_FILE_ERR;

    return rc;
}
err_t alloc_edges(edge_t *&edges, const size_t n)
{
    if (edges != NULL)
        return WRONG_EDGES_PTR_ERR;

    if (n == 0)
        return WRONG_NEDGES_ERR;

    err_t rc = SUCCESS;
    edges = (edge_t *)calloc(n, sizeof(edge_t));
    if (edges == NULL)
        rc = EDGES_ALLOC_ERR;

    return rc;
}

err_t free_edges(edges_t &edges)
{
    free(edges.data);
    edges.data = NULL;
    edges.n = 0;
    return SUCCESS;
}

err_t free_edges_data(edge_t *&edges, size_t &nedges)
{
    free(edges);
    edges = NULL;
    nedges = 0;
    return SUCCESS;
}

err_t fload_edges_segment(FILE *f, edges_t &edges)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    if (edges.data != NULL)
        return WRONG_EDGES_PTR_ERR;

    if (edges.n != 0)
        return WRONG_NEDGES_ERR;

    err_t rc = SUCCESS;
    rc = fload_nedges(f, edges.n);

    if (rc == SUCCESS) {
        rc = alloc_edges(edges.data, edges.n);

        if (rc == SUCCESS) {
            rc = fload_edges(f, edges.data, edges.n);

            if (rc != SUCCESS)
                rc = free_edges_data(edges.data, edges.n);
        }
    }

    return rc;
}


err_t fsave_nedges(FILE *f, size_t nedges)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    if (fprintf(f, "%zu\n", nedges) < 0)
        rc = FSAVE_NEDGES_ERR;

    return rc;
}



err_t fsave_edges(FILE *f, const edge_t *edges, size_t nedges)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    if (edges != NULL)
        return WRONG_EDGES_PTR_ERR;

    if (nedges != 0)
        return WRONG_NEDGES_ERR;

    err_t rc = SUCCESS;
    for (size_t i = 0; (i < nedges) && (rc == SUCCESS); ++i)
        rc = fsave_edge(f, edges[i]);

    return rc;
}

err_t fsave_edges_segment(FILE *f, const edges_t &edges)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;

    rc = fsave_nedges(f, edges.n);
    if (rc == SUCCESS) {
        rc = fsave_edges(f, edges.data, edges.n);

        if (rc != SUCCESS)
            rc = clear_file(f);
    }

    return rc;
}
