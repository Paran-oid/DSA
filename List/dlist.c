#include "dlist.h"

#include <string.h>

void dlist_create(DList *dlist,
                  int (*match)(const void *key1, const void *key2),
                  void (*destroy)(void *key)) {
  if ((dlist = malloc(sizeof(DList))) == NULL)
    return;

  match != NULL ? dlist->match = match : NULL;
  destroy != NULL ? dlist->destroy = destroy : NULL;

  dlist->head = dlist->tail = NULL;
}

void dlist_destroy(DList *dlist) {
  if (dlist_size(dlist) == 0)
    return;

  void *data;

  while (dlist_size(dlist) != 0) {
    if (dlist_rem_next(dlist, NULL, (void **)&data) == 0) {
      dlist->destroy(data);
    }
  }

  memset(dlist, 0, sizeof(DList));
  return;
}

int dlist_ins_next(DList *dlist, DListNode *elem, const void *data) {

  if (dlist_size(dlist) == 0 && elem == NULL)
    return -1;

  DListNode *newElem;
  if ((newElem = malloc(sizeof(DListNode))) == NULL)
    return -1;

  newElem->data = (void *)data;

  if (dlist_size(dlist) == 0) {
    dlist->head = dlist->tail = newElem;
    dlist->head->next = dlist->head->prev = NULL;
  } else {
    newElem->next = elem->next;
    newElem->prev = elem;

    if (!elem->next)
      dlist->tail = elem;
    else
      elem->next->prev = newElem;

    elem->next = elem;
  }

  dlist->size++;

  return 0;
}
int dlist_ins_prev(DList *dlist, DListNode *elem, const void *data) {
  if (!elem && dlist_size(dlist) != 0)
    return -1;

  DListNode *newElem;

  if ((newElem = malloc(sizeof(DListNode))) == NULL)
    return -1;

  newElem = (void *)data;
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

int dlist_rem_next(DList *dlist, DListNode *elem, void **data) {
  if (dlist_size(dlist) == 0)
    return -1;

  DListNode *oldElem;
  if (!elem) {
    // to remove
    oldElem = dlist->head;
    dlist->head = dlist->head->next;
    dlist->head->prev = NULL;
  } else {
    oldElem = elem->next;
    elem->next = elem->next->next;

    if (elem->next)
      elem->next->prev = elem;
  }
  dlist->destroy(oldElem);
  dlist->size--;
  return 0;
}
