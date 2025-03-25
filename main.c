#include "graph.h"
#include "graph_traversal.h"
#include <stdio.h>
#include <stdlib.h>

// Example match function to compare two vertices
int match(const void* vertex1, const void* vertex2)
{
    return vertex1 - vertex2;
}

// Example destroy function to free the vertex data (if needed)
void destroy(void* data)
{
    free(data); // Assume each vertex is dynamically allocated
}

// Simple data structure for vertices

// Helper to print BFS results
void print_bfs_results(List* hops)
{
    printf("BFS Traversal Results:\n");
    for (ListNode* node = list_head(hops); node != NULL; node = list_next(node)) {
        BfsVertex* curr = (BfsVertex*)(node->data);
        printf("Vertex value: %d, Hops: %d\n", (int)curr->data, curr->hops);
    }
}

// Helper to print DFS results
void print_dfs_results(List* ordered)
{
    printf("DFS Traversal Results:\n");
    for (ListNode* node = list_head(ordered); node != NULL; node = list_next(node)) {
        DfsVertex* dfs_vertex = (DfsVertex*)list_data(node);
        printf("Vertex value: %d\n", *(int*)dfs_vertex->data);
    }
}

int main()
{
    // Create graph
    Graph graph;
    graph_create(&graph, match, destroy);

    // Create vertices
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4;

    // Insert vertices into the graph
    graph_ins_vertex(&graph, &v1);
    graph_ins_vertex(&graph, &v2);
    graph_ins_vertex(&graph, &v3);
    graph_ins_vertex(&graph, &v4);

    // Insert edges into the graph
    graph_ins_edge(&graph, &v1, &v2); // Edge from v1 to v2
    graph_ins_edge(&graph, &v1, &v3); // Edge from v1 to v3
    graph_ins_edge(&graph, &v2, &v4); // Edge from v2 to v4

    // Create List to store BFS hops and DFS order
    List hops, ordered;
    list_create(&hops, match, destroy);
    list_create(&ordered, match, destroy);
    AdjList* list = NULL;
    graph_adjlist(&graph, &v1, &list);

    // Perform BFS starting from v1
    if (bfs(&graph, (BfsVertex*)list->vertex, &hops) == 0) {
        print_bfs_results(&hops);
    } else {
        printf("BFS failed\n");
    }

    // Perform DFS
    if (dfs(&graph, &ordered) == 0) {
        print_dfs_results(&ordered);
    } else {
        printf("DFS failed\n");
    }

    // Clean up
    graph_destroy(&graph);
    return 0;
}
