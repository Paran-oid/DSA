#include "graph.h"
#include "graph_algorithms.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int match(const void* k1, const void* k2)
{
    return *(char*)k1 == *(char*)k2 ? 0 : -1;
}
void vertex_create(MstVertex* vertex, void* data, double weight)
{
    vertex->data = data;
    vertex->weight = weight;
}

int main(void)
{
    char val1 = 'A';
    char val2 = 'B';
    char val3 = 'C';
    char val4 = 'D';
    char val5 = 'E';
    char val6 = 'F';

    MstVertex* v1 = malloc(sizeof(MstVertex)); // A
    MstVertex* v2 = malloc(sizeof(MstVertex)); // B
    MstVertex* v3 = malloc(sizeof(MstVertex)); // C
    MstVertex* v4 = malloc(sizeof(MstVertex)); // D
    MstVertex* v5 = malloc(sizeof(MstVertex)); // E
    MstVertex* v6 = malloc(sizeof(MstVertex)); // F

    Graph g;
    graph_create(&g, match, free);

    vertex_create(v1, &val1, 0); // A
    vertex_create(v2, &val2, 4.0); // B
    vertex_create(v3, &val3, 3.0); // C
    vertex_create(v4, &val4, 6.0); // D
    vertex_create(v5, &val5, 5.0); // E
    vertex_create(v6, &val6, 5.0); // F

    graph_ins_vertex(&g, v1);
    graph_ins_vertex(&g, v2);
    graph_ins_vertex(&g, v3);
    graph_ins_vertex(&g, v4);
    graph_ins_vertex(&g, v5);
    graph_ins_vertex(&g, v6);

    graph_ins_edge(&g, v1, v2); // A-B
    graph_ins_edge(&g, v1, v3); // A-C
    graph_ins_edge(&g, v2, v4); // B-D
    graph_ins_edge(&g, v3, v5); // C-E
    graph_ins_edge(&g, v4, v5); // D-E
    graph_ins_edge(&g, v5, v6); // E-F

    List my_list;
    if (mist(&g, v1, &my_list, match) != 0) {
        return -1;
    }

    ListNode* node;
    for (node = list_head(&my_list); node != NULL; node = list_next(node)) {
        MstVertex* vertex = list_data(node);
        printf("Vertex: %c, Parent: %c, Key: %.2f\n",
            *(char*)vertex->data,
            vertex->parent ? *(char*)vertex->parent->data : 'N',
            vertex->key);
    }

    printf("\n");
    graph_destroy(&g);
    list_destroy(&my_list);

    return 0;
}