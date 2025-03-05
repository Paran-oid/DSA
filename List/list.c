#include "list.h"
#include "core.h"

#include <stdlib.h>
#include <string.h>

void list_create(List *list, int (*match)(const void *key1, const void *key2),
                 void (*destroy)(void *)) {
  match != NULL ? list->match = match : NULL;
  destroy != NULL ? list->destroy = destroy : NULL;

  list->head = list->tail = NULL;
  list->size = 0;
  return list;
}
void list_destroy(List *list) {
  ASSERT(list->destroy != NULL, "invalid destroy function passed to list\n");

  void *data;

  while (list_size(list) > 0) {
    if (list_rem_next(list, NULL, (void **)&data) == 0) {
      ;
    }
  }

  memset(list, 0, sizeof(list));

  return;
}

int list_ins_next(List *list, ListNode *elem, const void *data) {
  ListNode *new_node;
  if ((new_node = malloc(sizeof(ListNode))) == NULL) {
    return -1;
  }

  new_node->data = data;
  if (!elem) {
    if (list_size(list) == 0) {
      list->tail = new_node;
    }
    new_node->next = list->head;
    list->head = new_node;
  } else {
    if (!elem->next) {
      list->tail = new_node;
    }
    new_node->next = elem->next;
    elem->next = new_node;
  }

  list->size++;

  return 0;
}
int list_rem_next(List *list, ListNode *elem, void **data) {
  ListNode *old_elem;

  if (list_size(list) == 0) {
    return -1;
  }

  if (!elem) {
    *data = list->head->data;
    old_elem = list->head;
    list->head = list->head->next;
    if (list_size(list) == 1) {
      list->tail = NULL;
    }
  } else {
    *data = elem->next->data;
    old_elem = elem->next;
    elem->next = elem->next->next;

    if (!elem->next) {
      list->tail = elem;
    }
  }

  list->destroy(old_elem);
  list->size--;
  return 0;
}