#include "dlist.h"
#include "core.h"

#include <stdlib.h>
#include <string.h>

void dlist_create(DList* dlist,
    int (*match)(const void* key1, const void* key2),
    void (*destroy)(void* key))
{

    ASSERT(dlist != NULL, "null list passed to clist_create");

    dlist->destroy = destroy;
    dlist->match = match;
    dlist->head = dlist->tail = NULL;
    dlist->size = 0;
}

void dlist_destroy(DList* dlist)
{
    ASSERT(dlist->destroy != NULL, "no destroy function assigned for list when passed to list");
    if (dlist_size(dlist) == 0)
        return;

    void* data;

    while (dlist_size(dlist) != 0) {
        if (dlist_rem(dlist, dlist->tail, (void**)&data) == 0) {
            dlist->destroy(data);
        }
    }

    memset(dlist, 0, sizeof(DList));
    return;
}

int dlist_ins_next(DList* dlist, DListNode* elem, const void* data)
{

    if (dlist_size(dlist) != 0 && elem == NULL)
        return -1;

    DListNode* newElem;
    if ((newElem = malloc(sizeof(DListNode))) == NULL)
        return -1;

    newElem->data = (void*)data;

    if (dlist_size(dlist) == 0) {
        dlist->head = dlist->tail = newElem;
        dlist->head->next = dlist->head->prev = NULL;
    } else {
        newElem->next = elem->next;
        newElem->prev = elem;

        if (!elem->next)
            dlist->tail = newElem;
        else
            elem->next->prev = newElem;

        elem->next = newElem;
    }

    dlist->size++;

    return 0;
}
int dlist_ins_prev(DList* dlist, DListNode* elem, const void* data)
{
    if (!elem && dlist_size(dlist) != 0)
        return -1;

    DListNode* newElem;

    if ((newElem = malloc(sizeof(DListNode))) == NULL)
        return -1;

    newElem->data = (void*)data;
    if (dlist_size(dlist) == 0) {
        dlist->head = dlist->tail = newElem;
        newElem->next = newElem->prev = NULL;
    } else {
        newElem->next = elem;
        newElem->prev = elem->prev;

        if (elem->prev)
            elem->prev->next = newElem;
        else
            dlist->head = newElem;
        elem->prev = newElem;
    }

    dlist->size++;
    return 0;
}

int dlist_rem(DList* dlist, DListNode* elem, void** data)
{
    if (dlist_size(dlist) == 0)
        return -1;

    if (elem == dlist->head) {
        dlist->head = elem->next;

        if (dlist->head) {
            elem->next->prev = NULL;
        } else {
            dlist->tail = NULL;
        }
    } else {
        elem->prev->next = elem->next;
        if (elem->next)
            elem->next->prev = elem->prev;
        else
            dlist->tail = elem->prev;
    }

    *data = elem->data;
    dlist->destroy(elem);
    dlist->size--;
    return 0;
}
