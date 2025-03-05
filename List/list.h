#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct ListNode_ {
  void *data;
  struct ListNode_ *next;
} ListNode;

typedef struct {
  ListNode *head;
  ListNode *tail;

  int (*match)(const void *key1, const void *key2);
  void (*destroy)(void *data);

  size_t size;
} List;

void list_create(List *list, int (*match)(const void *key1, const void *key2),
                 void (*destroy)(void *));
void list_destroy(List *list);

int list_ins_next(List *list, ListNode *elem, const void *data);
int list_rem_next(List *list, ListNode *elem, void **data);

#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)

#define list_is_head(list, el) ((list)->head == (el) ? 1 : 0)
#define list_is_tail(list, el) ((list)->tail == (el) ? 1 : 0)

#define list_data(el) ((el)->data)
#define list_next(el) ((el)->next)

#endif