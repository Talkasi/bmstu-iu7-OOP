#ifndef EDGE_H
#define EDGE_H
#include "errors.h"
#include <stdio.h>

typedef struct edge edge_t;

struct edge
{
    size_t first;
    size_t second;
};

err_t fload_edge(FILE *f, edge_t &edge);
err_t fsave_edge(FILE *f, const edge_t &edge);

#endif // EDGE_H
