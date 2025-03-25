#include "graph_traversal.h"
#include "graph.h"
#include "list.h"
#include "queue.h"

// FIXME

int bfs(Graph* graph, BfsVertex* start, List* hops)
{
    ListNode *curr, *member;

    BfsVertex *clr_vertex, *adj_vertex;
    AdjList* clr_adjst;

    for (curr = list_head(&graph->adjlists); curr != NULL; curr = list_next(curr)) {
        clr_vertex = (BfsVertex*)((AdjList*)list_data(curr))->vertex;
        if (graph->match(clr_vertex, start) == 0) {
            clr_vertex->color = VERTEX_GRAY;
            clr_vertex->hops = 0;
        } else {
            clr_vertex->color = VERTEX_WHITE;
            clr_vertex->hops = -1;
        }
    }

    Queue q;
    queue_create(&q, graph->match, graph->destroy);
    if (graph_adjlist(graph, start, &clr_adjst) != 0) {
        queue_destroy(&q);
        return -1;
    }

    if (queue_enqueue(&q, clr_adjst) != 0) {
        queue_destroy(&q);
        return -1;
    }
    // FIXME
    while (queue_size(&q) > 0) {
        AdjList* adj_list = queue_peek(&q);
        for (member = list_head(&adj_list->adjacent); member != NULL; member = list_next(member)) {
            adj_vertex = (BfsVertex*)list_data(member);
            if (graph_adjlist(graph, adj_vertex, &clr_adjst) != 0) {
                queue_destroy(&q);
                return -1;
            }
            clr_vertex = clr_adjst->vertex;

            if (clr_vertex->color == VERTEX_WHITE) {
                clr_vertex->color = VERTEX_GRAY;
                clr_vertex->hops = ((BfsVertex*)adj_vertex)->hops + 1;

                if (queue_enqueue(&q, clr_adjst) != 0) {
                    queue_destroy(&q);
                    return -1;
                }
            }
        }
    }
    queue_destroy(&q);

    list_create(hops, graph->match, graph->destroy);
    for (member = list_head(&graph_adjlists(graph)); member != NULL; member = list_next(member)) {
        clr_vertex = (BfsVertex*)((AdjList*)list_data(member))->vertex;
        if (clr_vertex->hops != -1) {
            if (list_ins_next(hops, list_tail(hops), clr_vertex) != 0) {
                list_destroy(hops);
                return -1;
            }
        }
    }
    return 0;
}

static int dfs_main(Graph* graph, AdjList* list, List* ordered)
{
    ListNode* member;

    DfsVertex *adj_vertex, *clr_vertex;

    AdjList* adj_list;

    ((DfsVertex*)list->vertex)->color = VERTEX_GRAY;
    for (member = list_head(&list->adjacent); member != NULL; member = list_next(member)) {
        adj_vertex = list_data(member);
        if (graph_adjlist(graph, adj_vertex, &adj_list) != 0) {
            return -1;
        }
        clr_vertex = adj_list->vertex;

        if (clr_vertex->color == VERTEX_WHITE) {
            if (dfs_main(graph, list, ordered) != 0) {
                return -1;
            }
        }

        ((DfsVertex*)adj_list->vertex)->color = VERTEX_BLACK;

        if (list_ins_next(ordered, NULL, (DfsVertex*)adj_list->vertex) != 0) {
            return -1;
        }

        return 0;
    }
}

int dfs(Graph* graph, List* ordered)
{
    ListNode* element;
    DfsVertex* vertex;
    for (element = list_head(&graph_adjlists(graph)); element != NULL; element = list_next(element)) {
        vertex = ((AdjList*)list_data(element))->vertex;
        vertex->color = VERTEX_WHITE;
    }

    list_create(ordered, graph->match, graph->destroy);
    for (element = list_head(&graph_adjlists(graph)); element != NULL; element = list_next(element)) {
        vertex = ((AdjList*)list_data(element))->vertex;
        if (vertex->color == VERTEX_WHITE) {
            if (dfs_main(graph, (AdjList*)list_data(element), ordered) != 0) {
                list_destroy(ordered);
                return -1;
            }
        }
    }
    return 0;
}