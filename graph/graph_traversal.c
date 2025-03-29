#include "graph_traversal.h"
#include "graph.h"
#include "list.h"
#include "queue.h"

int bfs(Graph* graph, BfsVertex* start, List* list_res)
{
    ListNode *curr, *member;

    BfsVertex *clr_vertex, *adj_vertex;
    AdjList *clr_adjst, *adj_list;

    for (curr = list_head(&graph->adjlists); curr != NULL; curr = list_next(curr)) {
        clr_vertex = (BfsVertex*)((AdjList*)list_data(curr))->vertex;
        if (graph->match(clr_vertex, start) == 0) {
            clr_vertex->color = VERTEX_GRAY;
        } else {
            clr_vertex->color = VERTEX_WHITE;
        }
    }

    Queue q;
    queue_create(&q, graph->match, NULL);
    if (graph_adjlist(graph, start, &clr_adjst) != 0) {
        queue_destroy(&q);
        return -1;
    }

    if (queue_enqueue(&q, clr_adjst) != 0) {
        queue_destroy(&q);
        return -1;
    }

    list_create(list_res, graph->match, NULL);
    while (queue_size(&q) > 0) {
        adj_list = queue_peek(&q);
        for (member = list_head(&adj_list->adjacent); member != NULL; member = list_next(member)) {
            adj_vertex = list_data(member);
            if (graph_adjlist(graph, adj_vertex, &clr_adjst) != 0) {
                queue_destroy(&q);
                return -1;
            }
            clr_vertex = clr_adjst->vertex;

            if (clr_vertex->color == VERTEX_WHITE) {
                clr_vertex->color = VERTEX_GRAY;

                if (queue_enqueue(&q, clr_adjst) != 0) {
                    queue_destroy(&q);
                    return -1;
                }
            }
        }
        if (queue_dequeue(&q, (void**)&adj_list) == 0) {
            ((BfsVertex*)(adj_list->vertex))->color = VERTEX_BLACK;
            if (list_ins_next(list_res, list_tail(list_res), adj_list->vertex) != 0) {
                queue_destroy(&q);
                list_destroy(list_res);
                return -1;
            }
        } else {
            queue_destroy(&q);
            return -1;
        }
    }
    queue_destroy(&q);
    return 0;
}

static int dfs_main(Graph* graph, AdjList* adjlist, List* ordered)
{
    ListNode* member;

    DfsVertex *adj_vertex, *clr_vertex;

    AdjList* clr_adj;

    ((DfsVertex*)adjlist->vertex)->color = VERTEX_GRAY;
    for (member = list_head(&adjlist->adjacent); member != NULL; member = list_next(member)) {
        adj_vertex = list_data(member);
        if (graph_adjlist(graph, adj_vertex, &clr_adj) != 0) {
            return -1;
        }
        clr_vertex = clr_adj->vertex;

        if (clr_vertex->color == VERTEX_WHITE) {
            if (dfs_main(graph, clr_adj, ordered) != 0) {
                return -1;
            }
        }
    }

    ((DfsVertex*)adjlist->vertex)->color = VERTEX_BLACK;

    if (list_ins_next(ordered, NULL, (DfsVertex*)adjlist->vertex) != 0) {
        return -1;
    }
    return 0;
}

int dfs(Graph* graph, List* ordered)
{
    ListNode* element;
    DfsVertex* vertex;
    for (element = list_head(&graph_adjlists(graph)); element != NULL; element = list_next(element)) {
        vertex = ((AdjList*)list_data(element))->vertex;
        vertex->color = VERTEX_WHITE;
    }

    list_create(ordered, graph->match, NULL);
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