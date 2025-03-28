#include "graph.h"
#include "graph_algorithms.h"
#include "list.h"
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Match function for vertices
int match_vertex(const void* a, const void* b)
{
    // Assuming data is an integer pointer
    return *(int*)((MstVertex*)a)->data - *(int*)((MstVertex*)b)->data;
}

// Function to print MST results
void print_mst(List* span)
{
    ListNode* node;
    MstVertex* v;
    double total_weight = 0.0;

    printf("Minimum Spanning Tree:\n");
    for (node = list_head(span); node != NULL; node = list_next(node)) {
        v = list_data(node);

        if (v->parent != NULL) {
            printf("Edge: %d -> %d (Weight: %.2f)\n",
                *(int*)((MstVertex*)v->parent)->data,
                *(int*)v->data,
                v->key);
            total_weight += v->key;
        } else {
            printf("Root: %d\n", *(int*)v->data);
        }
    }

    printf("Total MST Weight: %.2f\n", total_weight);
}

// Free function for vertices
void free_vertex(void* vertex)
{
    MstVertex* v = (MstVertex*)vertex;
    free(v->data);
    free(v);
}

// Helper function to create a vertex
MstVertex* create_vertex(int id)
{
    MstVertex* v = (MstVertex*)malloc(sizeof(MstVertex));
    if (!v)
        return NULL;

    v->data = malloc(sizeof(int));
    if (!v->data) {
        free(v);
        return NULL;
    }

    *(int*)v->data = id;
    v->key = 0.0;
    v->weight = 0.0;
    v->color = VERTEX_WHITE;
    v->parent = NULL;

    return v;
}

int main()
{
    Graph graph;
    List span;
    MstVertex *v1, *v2, *v3, *v4, *v5;
    int result;

    // Create graph
    graph_create(&graph, match_vertex, free_vertex);

    // Create vertices
    v1 = create_vertex(1);
    v2 = create_vertex(2);
    v3 = create_vertex(3);
    v4 = create_vertex(4);
    v5 = create_vertex(5);

    // Insert vertices
    graph_ins_vertex(&graph, v1);
    graph_ins_vertex(&graph, v2);
    graph_ins_vertex(&graph, v3);
    graph_ins_vertex(&graph, v4);
    graph_ins_vertex(&graph, v5);

    // Create edges with weights (undirected graph)
    // Insert edges (both directions for undirected graph)
    graph_ins_edge(&graph, v1, v2);
    graph_ins_edge(&graph, v2, v1);

    graph_ins_edge(&graph, v1, v3);
    graph_ins_edge(&graph, v3, v1);

    graph_ins_edge(&graph, v2, v3);
    graph_ins_edge(&graph, v3, v2);

    graph_ins_edge(&graph, v2, v4);
    graph_ins_edge(&graph, v4, v2);

    graph_ins_edge(&graph, v2, v5);
    graph_ins_edge(&graph, v5, v2);

    graph_ins_edge(&graph, v3, v4);
    graph_ins_edge(&graph, v4, v3);

    graph_ins_edge(&graph, v3, v5);
    graph_ins_edge(&graph, v5, v3);

    graph_ins_edge(&graph, v4, v5);
    graph_ins_edge(&graph, v5, v4);

    // list weights for all edges
    // To list weights, we need to access the vertices in the adjacency lists
    AdjList* adjlist;
    ListNode* node;
    MstVertex* adj_vertex;

    // Edge 1-2: weight 4
    graph_adjlist(&graph, v1, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 2)
            adj_vertex->weight = 4.0;
    }

    graph_adjlist(&graph, v2, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 1)
            adj_vertex->weight = 4.0;
    }

    // Edge 1-3: weight 2
    graph_adjlist(&graph, v1, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 3)
            adj_vertex->weight = 2.0;
    }

    graph_adjlist(&graph, v3, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 1)
            adj_vertex->weight = 2.0;
    }

    // Edge 2-3: weight 3
    graph_adjlist(&graph, v2, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 3)
            adj_vertex->weight = 3.0;
    }

    graph_adjlist(&graph, v3, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 2)
            adj_vertex->weight = 3.0;
    }

    // Edge 2-4: weight 5
    graph_adjlist(&graph, v2, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 4)
            adj_vertex->weight = 5.0;
    }

    graph_adjlist(&graph, v4, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 2)
            adj_vertex->weight = 5.0;
    }

    // Edge 2-5: weight 7
    graph_adjlist(&graph, v2, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 5)
            adj_vertex->weight = 7.0;
    }

    graph_adjlist(&graph, v5, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 2)
            adj_vertex->weight = 7.0;
    }

    // Edge 3-4: weight 6
    graph_adjlist(&graph, v3, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 4)
            adj_vertex->weight = 6.0;
    }

    graph_adjlist(&graph, v4, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 3)
            adj_vertex->weight = 6.0;
    }

    // Edge 3-5: weight 1
    graph_adjlist(&graph, v3, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 5)
            adj_vertex->weight = 1.0;
    }

    graph_adjlist(&graph, v5, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 3)
            adj_vertex->weight = 1.0;
    }

    // Edge 4-5: weight 8
    graph_adjlist(&graph, v4, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 5)
            adj_vertex->weight = 8.0;
    }

    graph_adjlist(&graph, v5, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 4)
            adj_vertex->weight = 8.0;
    }

    // Print graph information
    printf("Graph created with %zu vertices and %zu edges\n",
        graph_vcount(&graph), graph_ecount(&graph));

    // Run MST algorithm starting from vertex 1
    printf("Running MST algorithm starting from vertex %d\n", *(int*)v1->data);
    result = mist(&graph, v1, &span, match_vertex);

    if (result == 0) {
        printf("MST algorithm completed successfully.\n");
        print_mst(&span);
    } else {
        printf("MST algorithm failed with error code %d.\n", result);
    }

    // Test MST from a different starting vertex
    list_destroy(&span);
    printf("\nRunning MST algorithm starting from vertex %d\n", *(int*)v3->data);
    result = mist(&graph, v3, &span, match_vertex);

    if (result == 0) {
        printf("MST algorithm completed successfully.\n");
        print_mst(&span);
    } else {
        printf("MST algorithm failed with error code %d.\n", result);
    }

    // Clean up
    list_destroy(&span);
    graph_destroy(&graph);

    printf("\n======= Testing a different graph topology =======\n\n");

    // Test with another graph topology (line graph)
    graph_create(&graph, match_vertex, free_vertex);

    // Create new vertices
    v1 = create_vertex(10);
    v2 = create_vertex(20);
    v3 = create_vertex(30);
    v4 = create_vertex(40);

    // Insert vertices
    graph_ins_vertex(&graph, v1);
    graph_ins_vertex(&graph, v2);
    graph_ins_vertex(&graph, v3);
    graph_ins_vertex(&graph, v4);

    // Create edges (line: v1--v2--v3--v4)
    graph_ins_edge(&graph, v1, v2);
    graph_ins_edge(&graph, v2, v1);

    graph_ins_edge(&graph, v2, v3);
    graph_ins_edge(&graph, v3, v2);

    graph_ins_edge(&graph, v3, v4);
    graph_ins_edge(&graph, v4, v3);

    // list weights
    // Edge 10-20: weight 5
    graph_adjlist(&graph, v1, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 20)
            adj_vertex->weight = 5.0;
    }

    graph_adjlist(&graph, v2, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 10)
            adj_vertex->weight = 5.0;
    }

    // Edge 20-30: weight 10
    graph_adjlist(&graph, v2, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 30)
            adj_vertex->weight = 10.0;
    }

    graph_adjlist(&graph, v3, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 20)
            adj_vertex->weight = 10.0;
    }

    // Edge 30-40: weight 7
    graph_adjlist(&graph, v3, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 40)
            adj_vertex->weight = 7.0;
    }

    graph_adjlist(&graph, v4, &adjlist);
    for (node = list_head(&adjlist->adjacent); node != NULL; node = list_next(node)) {
        adj_vertex = list_data(node);
        if (*(int*)adj_vertex->data == 30)
            adj_vertex->weight = 7.0;
    }

    // Print graph information
    printf("Line graph created with %zu vertices and %zu edges\n",
        graph_vcount(&graph), graph_ecount(&graph));

    // Run MST algorithm starting from the first vertex
    printf("Running MST algorithm starting from vertex %d\n", *(int*)v1->data);
    result = mist(&graph, v1, &span, match_vertex);

    if (result == 0) {
        printf("MST algorithm completed successfully.\n");
        print_mst(&span);
    } else {
        printf("MST algorithm failed with error code %d.\n", result);
    }

    // Clean up
    list_destroy(&span);
    graph_destroy(&graph);

    return 0;
}