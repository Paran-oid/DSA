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
    for (curr = list_head(&graph_adjlists(g)); curr != NULL; curr = list_next(curr)) {
        vertex = ((AdjList*)list_data(curr))->vertex;
        if (match(vertex, start) == 0) {
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
    curr = NULL;
    double min;
    while (i < (int)graph_vcount(g)) {
        min = DBL_MAX;
        for (curr = list_head(&graph_adjlists(g)); curr != NULL; curr = list_next(curr)) {
            vertex = ((AdjList*)list_data(curr))->vertex;
            if (vertex->color == VERTEX_WHITE && vertex->key < min) {
                min = vertex->key;
                list = list_data(curr);
            }
        }
        curr = NULL;
        ((MstVertex*)list->vertex)->color = VERTEX_BLACK;
        for (curr = list_head(&list->adjacent); curr != NULL; curr = list_next(curr)) {
            adj_vertex = list_data(curr);
            for (element = list_head(&graph_adjlists(g)); element != NULL; element = list_next(element)) {
                vertex = ((AdjList*)list_data(element))->vertex;
                if (match(vertex, adj_vertex) == 0) {
                    if (vertex->color == VERTEX_WHITE && adj_vertex->weight < vertex->key) {
                        vertex->key = adj_vertex->weight;
                        vertex->parent = list->vertex;
                    }
                    break;
                }
            }
        }
        i++;
    }

    list_create(span, match, NULL);
    for (element = list_head(&graph_adjlists(g)); element != NULL; element = list_next(element)) {
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

static void relax(PathVertex* u, PathVertex* v, double weight)
{
    if (v->d > u->d + weight) {
        v->d = u->d + weight;
        v->parent = u;
    }
}

int shortest(Graph* g, const PathVertex* start, List* paths, int (*match)(const void*, const void*))
{
    int found = 0;
    ListNode *curr, *elem;
    PathVertex *pth_vertex, *adj_vertex;
    AdjList* adjlist;
    for (curr = list_head(&graph_adjlists(g)); curr != NULL; curr = list_next(curr)) {
        pth_vertex = ((AdjList*)list_data(curr))->vertex;
        if (match(pth_vertex, start)) {
            pth_vertex->d = 0;
            pth_vertex->color = VERTEX_WHITE;
            pth_vertex->parent = NULL;
        } else {
            pth_vertex->d = DBL_MAX;
            pth_vertex->color = VERTEX_WHITE;
            pth_vertex->parent = NULL;
        }
    }

    if (!found) {
        return -1;
    }

    size_t i = 0;
    while (i < graph_vcount(g)) {
        double minimum = DBL_MAX;
        for (curr = list_head(&graph_adjlists(g)); curr != NULL; curr = list_next(curr)) {
            pth_vertex = ((AdjList*)list_data(curr))->vertex;
            if (pth_vertex->d < minimum) {
                minimum = pth_vertex->d;
                adjlist = list_data(curr);
            }
        }

        ((PathVertex*)adjlist->vertex)->color = VERTEX_BLACK;

        for (elem = list_head(&adjlist->adjacent); elem != NULL; elem = list_next(elem)) {
            adj_vertex = list_data(elem);
            for (curr = list_head(&graph_adjlists(g)); curr != NULL; curr = list_next(curr)) {
                pth_vertex = ((AdjList*)list_data(curr))->vertex;
                if (match(pth_vertex, adj_vertex)) {
                    relax(adjlist->vertex, pth_vertex, adj_vertex->weight);
                }
            }
        }
        i++;
    }

    list_create(paths, match, NULL);
    for (elem = list_head(&graph_adjlists(g)); elem != NULL; elem = list_next(elem)) {

        pth_vertex = ((AdjList*)list_data(elem))->vertex;
        if (pth_vertex->color == VERTEX_BLACK) {
            if (list_ins_next(paths, list_tail(paths), pth_vertex) != 0) {
                list_destroy(paths);
                return -1;
            }
        }
    }

    return 0;
}

int tsp(List* vertices, const TspVertex* start, List* tour, int (*match)(const void*, const void*))
{
    list_create(tour, NULL, NULL);

    ListNode* elem;
    TspVertex *tsp_vertex, *tsp_start, *selected = NULL;
    double x, y, minimum = DBL_MAX;
    int found = 0;

    for (elem = list_head(vertices); elem != NULL; elem = list_next(elem)) {
        tsp_vertex = list_data(elem);
        if (match(tsp_vertex, start)) {
            if (list_ins_next(tour, NULL, tsp_vertex) != 0) {
                list_destroy(tour);
                return -1;
            }
            tsp_start = tsp_vertex;
            x = tsp_start->x;
            y = tsp_start->y;

            tsp_vertex->color = VERTEX_BLACK;
            found = 1;
        } else {
            tsp_vertex->color = VERTEX_WHITE;
        }
    }

    if (!found) {
        list_destroy(tour);
        return -1;
    }

    size_t i = 0;
    while (i < list_size(vertices) - 1) {
        minimum = DBL_MAX;
        for (elem = list_head(vertices); elem != NULL; elem = list_next(elem)) {
            tsp_vertex = list_data(elem);
            if (tsp_vertex->color == VERTEX_WHITE) {
                double distance = sqrt(pow(tsp_vertex->x - x, 2) + pow(tsp_vertex->y - y, 2));
                if (distance < minimum) {
                    minimum = distance;
                    selected = tsp_vertex;
                }
            }
        }

        x = selected->x;
        y = selected->y;

        selected->color = VERTEX_BLACK;
        if (list_ins_next(tour, list_tail(tour), selected) != 0) {
            list_destroy(tour);
            return -1;
        }
        i++;
    }

    if (list_ins_next(tour, list_tail(tour), start) != 0) {
        list_destroy(tour);
        return -1;
    }

    return 0;
}