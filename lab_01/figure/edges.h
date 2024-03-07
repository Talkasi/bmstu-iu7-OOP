#ifndef EDGES_H
#define EDGES_H
#include <stdio.h>
#include "edge.h"


typedef struct edges edges_t;


struct edges
{
    edge_t *data;
    size_t n;
};


edges_t edges_default(void);

err_t alloc_edges(edge_t *&edges, const size_t n);
err_t free_edges(edges_t &edges);

err_t fload_nedges(FILE *f, size_t &n);
err_t fload_edges(FILE *f, edge_t *edges, const size_t nedges);
err_t fload_edges_segment(FILE *f, edges_t &edges);

err_t fsave_nedges(FILE *f, const size_t nedges);
err_t fsave_edges(FILE *f, const edge_t *edges, const size_t nedges);
err_t fsave_edges_segment(FILE *f, const edges_t &edges);


#endif // EDGES_H
