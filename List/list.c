#include "list.h"
#include "core.h"

#include <string.h>

void list_create(List *list, void (*destroy)(void *data)) {
  list = malloc(sizeof(List));
  list->destroy = destroy;

  if (!destroy) {
    list->destroy = data_destroy;
  }

  list->head = list->tail = NULL;
  list->size = 0;
  return list;
}
void list_destroy(List *list) {

  void *data;

  while (list_size(list) > 0) {
    if (list_rem_next(list, NULL, (void **)&data) == 0 &&
        list->destroy != NULL) {
      list->destroy(data);
    }
  }

  memset(list, 0, sizeof(list));

  return;
}

int list_ins_next(List *list, ListNode *elem, const void *data) {
  ListNode *new_node;
  if ((new_node = malloc(sizeof(ListNode))) < 0) {
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

  free(old_elem);
  list->size--;
  return 0;
}