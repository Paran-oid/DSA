#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Assuming you already have the necessary includes for List and Graph handling
#include "graph_algorithms.h" // Replace with the actual header that contains the definitions

// Matching function to find the starting vertex (e.g., by some property)
int match(const void* v1, const void* v2)
{
    TspVertex* vertex1 = (TspVertex*)v1;
    TspVertex* vertex2 = (TspVertex*)v2;
    return (vertex1->x == vertex2->x && vertex1->y == vertex2->y);
}

// Function to print the tour for debugging purposes
void print_tour(List* tour)
{
    ListNode* node;
    ListNode* prev = NULL;
    TspVertex* prev_vertex;
    double distance = 0;
    for (node = list_head(tour); node != NULL; node = list_next(node)) {
        TspVertex* vertex = list_data(node);
        printf("Visited: (%.2f, %.2f)\n", vertex->x, vertex->y);
        if (prev) {
            prev_vertex = list_data(prev);
            distance += sqrt(pow(vertex->x - prev_vertex->x, 2) + pow(vertex->y - prev_vertex->y, 2));
        }
        prev = node;
    }
    printf("total distance traveled is %lf\n", distance);
}

int main()
{
    // Create a list of TspVertex (cities)
    List vertices;
    list_create(&vertices, NULL, NULL);

    TspVertex v1 = { NULL, 0.0, 0.0, VERTEX_WHITE };
    TspVertex v2 = { NULL, 1.0, 0.0, VERTEX_WHITE };
    TspVertex v3 = { NULL, 1.0, 1.0, VERTEX_WHITE };
    TspVertex v4 = { NULL, 0.0, 1.0, VERTEX_WHITE };

    // Add vertices to the list
    list_ins_next(&vertices, list_tail(&vertices), &v1);
    list_ins_next(&vertices, list_tail(&vertices), &v2);
    list_ins_next(&vertices, list_tail(&vertices), &v3);
    list_ins_next(&vertices, list_tail(&vertices), &v4);

    // Define the starting vertex (e.g., v1)
    TspVertex* start = &v1;

    // Create an empty list for the tour
    List tour;
    list_create(&tour, NULL, NULL);

    // Call tsp function to calculate the tour
    if (tsp(&vertices, (const TspVertex*)start, &tour, match) == 0) {
        // If tsp was successful, print the tour
        printf("Tour completed successfully:\n");
        print_tour(&tour);
    } else {
        printf("Error calculating the TSP tour.\n");
    }

    // Clean up (destroy lists if necessary)
    list_destroy(&vertices);
    list_destroy(&tour);

    return 0;
}
