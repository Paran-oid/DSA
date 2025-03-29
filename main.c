#include "graph.h"
#include "graph_traversal.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int match(const void* k1, const void* k2)
{
    return *(int*)((BfsVertex*)k1)->data - *(int*)((BfsVertex*)k2)->data;
}

void vertex_create(BfsVertex* vertex, void* data)
{
    vertex->color = VERTEX_WHITE;
    vertex->data = data;
}

int main(void)
{
    int val1 = 1;
    int val2 = 2;
    int val3 = 3;
    int val4 = 4;
    int val5 = 5;
    int val6 = 6;

    BfsVertex* v1 = malloc(sizeof(BfsVertex));
    BfsVertex* v2 = malloc(sizeof(BfsVertex));
    BfsVertex* v3 = malloc(sizeof(BfsVertex));
    BfsVertex* v4 = malloc(sizeof(BfsVertex));
    BfsVertex* v5 = malloc(sizeof(BfsVertex));
    BfsVertex* v6 = malloc(sizeof(BfsVertex));

    Graph g;
    graph_create(&g, match, free);

    vertex_create(v1, &val1);
    vertex_create(v2, &val2);
    vertex_create(v3, &val3);
    vertex_create(v4, &val4);
    vertex_create(v5, &val5);
    vertex_create(v6, &val6);

    graph_ins_vertex(&g, v1);
    graph_ins_vertex(&g, v2);
    graph_ins_vertex(&g, v3);
    graph_ins_vertex(&g, v4);
    graph_ins_vertex(&g, v5);
    graph_ins_vertex(&g, v6);

    graph_ins_edge(&g, v1, v6   );
    graph_ins_edge(&g, v1, v2);
    graph_ins_edge(&g, v1, v3);
    graph_ins_edge(&g, v3, v4);
    graph_ins_edge(&g, v3, v5);

    ListNode* curr;

    List my_list;
    bfs(&g, v1, &my_list);

    for (curr = list_head(&my_list); curr != NULL; curr = list_next(curr)) {
        BfsVertex* vertex = ((BfsVertex*)list_data(curr));
        printf("%d ", *(int*)vertex->data);
    }
    printf("\n");
    graph_destroy(&g);
    list_destroy(&my_list);

    return 0;
}