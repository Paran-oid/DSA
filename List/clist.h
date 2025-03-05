#ifndef CLIST_H
#define CLIST_H

#include <stddef.h>

typedef struct CListNode_ {
  void *data;
  struct CListNode_ *next;
} CListNode;

typedef struct CList {
  CListNode *head;

  void (*destroy)(void *data);
  int (*match)(const void *key1, const void *key2);
} CList;

void clist_create(CList *clist,
                  int (*match)(const void *key1, const void *key2),
                  void (*destroy)(void *data));
int clist_destroy(CList *clist);

int clist_ins_next(CList *clist, CListNode *elem, const void *data);
int clist_rem_next(CList *clist, CListNode *elem, void **data);

#define clist_size(clist) ((clist)->size)
#define clist_head(clist) ((clist)->head)

#define clist_data(node) ((node)->data)
#define clist_next(node) ((node)->next)

#endif