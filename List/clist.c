#include "clist.h"

// TODO

void clist_create(CList *clist,
                  int (*match)(const void *key1, const void *key2),
                  void (*destroy)(void *data));
int clist_destroy(CList *clist);

int clist_ins_next(CList *clist, CListNode *elem, const void *data);
int clist_rem_next(CList *clist, CListNode *elem, void **data);