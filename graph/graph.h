#ifndef GRAPH_H
#define GRAPH_H

#include "set.h"

typedef struct AdjList_ {
    void* vertex;
    Set adjacent;
} AdjList;

typedef struct Graph_ {
    List adjlists;

    void (*destroy)(void*);
    int (*match)(const void*, const void*);

    size_t ecount;
    size_t vcount;
} Graph;

typedef enum VertexColor_ {
    VERTEX_GRAY,
    VERTEX_WHITE,
    VERTEX_BLACK,
    VERTEX_COLOR_COUNT
} VertexColor;

void graph_create(Graph* g, int (*match)(const void*, const void*), void (*destroy)(void*));
void graph_destroy(Graph* g);

int graph_ins_vertex(Graph* g, const void* data);
int graph_ins_edge(Graph* g, const void* data1, const void* data2);
int graph_rem_vertex(Graph* g, void** data);
int graph_rem_edge(Graph* g, const void* data1, void** data2);
int graph_adjlist(const Graph* g, const void* data, AdjList** adjlist);
int graph_is_adjacent(const Graph* g, const void* data1, const void* data2);

#define graph_vcount(g) ((g)->vcount)
#define graph_ecount(g) ((g)->ecount)
#define graph_adjlists(g) ((g)->adjlists)

#endif