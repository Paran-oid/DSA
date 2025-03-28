#include "graph_algorithms.h"
#include "graph.h"
#include "list.h"
#include <float.h>
#include <stdlib.h>

int mist(Graph* g, const MstVertex* start, List* span, int (*match)(const void*, const void*))
{
    ListNode *curr, *element;
    AdjList* list = NULL;
    MstVertex *vertex, *adj_vertex;
    int found = 0;
    for (curr = list_head(&g->adjlists); curr != NULL; curr = list_next(curr)) {
        vertex = ((AdjList*)list_data(curr))->vertex;
        if (match(vertex, start)) {
            vertex->key = 0;
            vertex->color = VERTEX_WHITE;
            vertex->parent = NULL;
            found = 1;
        } else {
            vertex->key = DBL_MAX;
            vertex->color = VERTEX_WHITE;
            vertex->parent = NULL;
        }
    }
    if (!found) {
        return -1;
    }
    int i = 0;
    double min;
    while (i < (int)graph_vcount(g)) {
        min = DBL_MAX;
        for (curr = list_head(&g->adjlists); curr != NULL; curr = list_next(curr)) {
            vertex = ((AdjList*)list_data(curr))->vertex;
            if (vertex->color == VERTEX_WHITE && vertex->key < min) {
                min = vertex->key;
                list = list_data(curr);
            }
        }

        if (list) {
            ((MstVertex*)list->vertex)->color = VERTEX_BLACK;
        }

        for (curr = list_head(&list->adjacent); curr != NULL; curr = list_next(curr)) {
            adj_vertex = list_data(curr);
            for (element = list_head(&g->adjlists); element != NULL; element = list_next(element)) {
                vertex = ((AdjList*)list_data(element))->vertex;
                if (match(vertex, adj_vertex)) {
                    if (vertex->color == VERTEX_WHITE && vertex->weight < adj_vertex->key) {
                        vertex->key = adj_vertex->weight;
                        vertex->parent = list->vertex;
                    }
                    break;
                }
            }
        }

        i++;
    }

    list_create(span, match, free);
    for (element = list_head(&g->adjlists); element != NULL; element = list_next(element)) {
        vertex = ((AdjList*)list_data(element))->vertex;
        if (vertex->color == VERTEX_BLACK) {
            if (list_ins_next(span, list_tail(span), vertex) != 0) {
                list_destroy(span);
                return -1;
            }
        }
    }
    return 0;
}