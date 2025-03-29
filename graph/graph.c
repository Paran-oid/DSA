#include "graph.h"
#include "list.h"
#include "set.h"
#include <stdlib.h>
#include <string.h>

void graph_create(Graph* g, int (*match)(const void*, const void*), void (*destroy)(void*))
{
    g->match = match;
    g->destroy = destroy;

    g->ecount = g->vcount = 0;

    list_create(&g->adjlists, match, destroy);
}
void graph_destroy(Graph* g)
{
    AdjList* adjlist;
    while (list_size(&g->adjlists) > 0) {
        if (list_rem_next(&g->adjlists, NULL, (void**)&adjlist) == 0) {
            set_destroy(&adjlist->adjacent);
            if (g->destroy) {
                g->destroy(adjlist->vertex);
            }
        }

        free(adjlist);
    }
    list_destroy(&g->adjlists);
    memset(g, 0, sizeof(Graph));
}

int graph_ins_vertex(Graph* g, const void* data)
{
    ListNode* curr1;
    AdjList* curr1_list;
    int retval;
    for (curr1 = list_head(&g->adjlists); curr1 != NULL; curr1 = list_next(curr1)) {
        curr1_list = (AdjList*)list_data(curr1);
        if (g->match(data, curr1_list->vertex) == 0) {
            return 1;
        }
    }

    AdjList* new_list = (AdjList*)malloc(sizeof(AdjList));
    new_list->vertex = (void*)data;
    set_create(&new_list->adjacent, g->match, NULL);

    if ((retval = list_ins_next(&g->adjlists, list_tail(&g->adjlists), new_list)) != 0) {
        return retval;
    }

    g->vcount++;
    return 0;
}
int graph_ins_edge(Graph* g, const void* data1, const void* data2)
{
    AdjList *curr1_list, *curr2_list;
    ListNode *curr1, *curr2;
    int retval;
    for (curr1 = list_head(&g->adjlists); curr1 != NULL; curr1 = list_next(curr1)) {
        curr1_list = (AdjList*)list_data(curr1);
        if (g->match(data1, curr1_list->vertex) == 0) {
            break;
        }
    }
    if (curr1 == NULL) {
        return -1;
    }

    for (curr2 = list_head(&g->adjlists); curr2 != NULL; curr2 = list_next(curr2)) {
        curr2_list = (AdjList*)list_data(curr2);
        if (g->match(data2, curr2_list->vertex) == 0) {
            break;
        }
    }

    if (curr2 == NULL) {
        return -1;
    }

    if ((retval = set_insert(&curr1_list->adjacent, data2)) != 0) {
        return retval;
    }

    g->ecount++;

    return 0;
}
int graph_rem_vertex(Graph* g, void** data)
{
    ListNode *curr, *prev;
    AdjList* curr_list;
    int found = 0, retval;
    for (curr = list_head(&g->adjlists); curr != NULL; curr = list_next(curr)) {
        curr_list = (AdjList*)list_data(curr);
        if (set_is_member((const Set*)&curr_list->adjacent, *data) == 0) {
            return -1;
        }

        if (g->match(*data, curr_list->vertex)) {
            found = 1;
        }

        if (!found) {
            prev = curr;
        }
    }

    if (!found) {
        return -1;
    }

    if (set_size(&((AdjList*)list_data(curr))->adjacent) != 0) {
        return -1;
    }

    if ((retval = list_rem_next(&g->adjlists, prev, (void**)&curr_list)) != 0) {
        return retval;
    }

    *data = curr_list->vertex;
    free(curr_list);
    g->vcount--;
    return 0;
}

int graph_rem_edge(Graph* g, const void* data1, void** data2)
{
    ListNode* curr;
    AdjList* curr_list;

    for (curr = list_head(&g->adjlists); curr != NULL; curr = list_next(curr)) {
        curr_list = (AdjList*)list_data(curr);
        if (g->match(data1, curr_list->vertex) == 0) {
            break;
        }
    }
    if (curr == NULL) {
        return -1;
    }

    if (set_rem(&curr_list->adjacent, (void**)data2) != 0) {
        return -1;
    }

    g->ecount--;
    return 0;
}
int graph_adjlist(const Graph* g, const void* data, AdjList** adjlist)
{
    ListNode* curr;
    AdjList* curr_list;

    for (curr = list_head(&g->adjlists); curr != NULL; curr = list_next(curr)) {
        curr_list = (AdjList*)list_data(curr);
        if (g->match(data, curr_list->vertex) == 0) {
            break;
        }
    }
    if (curr == NULL) {
        return -1;
    }

    *adjlist = curr_list;
    return 0;
}
int graph_is_adjacent(const Graph* g, const void* data1, const void* data2)
{
    ListNode* curr;
    AdjList* curr_list;

    for (curr = list_head(&g->adjlists); curr != NULL; curr = list_next(curr)) {
        curr_list = (AdjList*)list_data(curr);
        if (g->match(data1, curr_list->vertex) == 0) {
            break;
        }
    }
    if (curr == NULL) {
        return -1;
    }

    return set_is_member(&curr_list->adjacent, data2);
}