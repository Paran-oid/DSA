#ifndef GRAPH_TRAVERSAL_H
#define GRAPH_TRAVERSAL_H

#include "graph.h"

typedef struct BfsVertex_ {
    VertexColor color;
    int hops;
    void* data;
} BfsVertex;

typedef struct DfsVertex_ {
    void* data;
    VertexColor color;
} DfsVertex;

int bfs(Graph* graph, BfsVertex* start, List* hops);
int dfs(Graph* graph, List* ordered);

#endif