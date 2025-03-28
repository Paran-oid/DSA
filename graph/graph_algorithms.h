#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include "graph.h"
typedef struct MstVertex_ {
    void* data;
    double weight;

    VertexColor color;
    double key;

    struct MstVertex_* parent;
} MstVertex;

int mist(Graph* g, const MstVertex* start, List* span, int (*match)(const void*, const void*));

#endif