#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include "graph.h"
#include "math.h"

typedef struct MstVertex_ {
    void* data;
    double weight;

    VertexColor color;
    double key;

    struct MstVertex_* parent;
} MstVertex;

typedef struct PathVertex_ {
    void* data;
    double weight;

    VertexColor color;
    double d;
    struct PathVertex_* parent;
} PathVertex;

typedef struct TspVertex_ {
    void* data;

    double x;
    double y;

    VertexColor color;
} TspVertex;

int mist(Graph* g, const MstVertex* start, List* span, int (*match)(const void*, const void*));
int shortest(Graph* g, const PathVertex* start, List* paths, int (*match)(const void*, const void*));
int tsp(List* vertices, const TspVertex* start, List* tour, int (*match)(const void*, const void*));

#endif