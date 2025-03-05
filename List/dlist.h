#ifndef DLIST_H
#define DLIST_H

#include <stddef.h>

typedef struct DListNode_ {

  void *data;
  struct DListNode_ *prev;
  struct DListNode_ *next;

} DListNode;

typedef struct DList_ {
  DListNode *head;
  DListNode *tail;

  void (*destroy)(void *data);
  int (*match)(const void *key1, const void *key2);

  size_t size;
} DList;

void dlist_create(DList *dlist,
                  int (*match)(const void *key1, const void *key2),
                  void (*destroy)(void *key));
void dlist_destroy(DList *dlist);

int dlist_ins_next(DList *dlist, DListNode *elem, const void *data);
int dlist_ins_prev(DList *dlist, DListNode *elem, const void *data);

int dlist_rem_next(DList *dlist, DListNode *elem, void **data);

#define dlist_size(dlist) ((dlist)->size)
#define dlist_head(dlist) ((dlist)->head)
#define dlist_tail(dlist) ((dlist)->tail)

#define dlist_is_head(tist, elem) ((dlist)->head == (elem) ? 1 : 0)
#define dlist_is_tail(dlist, elem) ((dlist)->tail == (elem) ? 1 : 0)

#define dlist_data(elem) ((elem)->data)
#define dlist_next(elem) ((elem)->next)
#define dlist_prev(elem) ((elem)->prev)

#endif