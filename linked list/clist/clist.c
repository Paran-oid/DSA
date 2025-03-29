#include "clist.h"
#include "core.h"

#include <string.h>

void clist_create(CList* clist,
    int (*match)(const void* key1, const void* key2),
    void (*destroy)(void* data))
{
    ASSERT(clist != NULL, "null list passed to clist_create");
    clist->destroy = destroy;
    clist->match = match;
    clist->head = NULL;
    clist->size = 0;
}

void clist_destroy(CList* clist)
{
    void* data;
    while (clist->size > 0) {
        if (clist_rem_next(clist, NULL, (void**)&data) == 0 && clist->destroy) {
            clist->destroy(data);
        }
    }
    clist->head = NULL;
    memset(clist, 0, sizeof(CList));
}

int clist_ins_next(CList* clist, CListNode* elem, const void* data)
{
    CListNode* new_node;
    if ((new_node = malloc(sizeof(CListNode))) == NULL) {
        return -1;
    }
    new_node->data = (void*)data;
    if (clist_size(clist) == 0) {
        if (!clist->head) {
            new_node->next = new_node;
            clist->head = new_node;
        }
        clist->head = new_node;
    } else {
        new_node->next = elem->next;
        elem->next = new_node;
    }

    clist->size++;
    return 0;
}
int clist_rem_next(CList* clist, CListNode* elem, void** data)
{
    if (clist_size(clist) == 0) {
        return -1;
    }
    CListNode* oldElem;
    *data = elem->next->data;
    if (elem->next == elem) {
        oldElem = elem->next;
        clist->head = NULL;
    } else {
        oldElem = elem->next;
        elem->next = elem->next->next;
    }
    free(oldElem);
    clist->size--;
    return 0;
}