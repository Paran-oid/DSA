#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "funcs.h"
#include <stdbool.h>

enum datatype { TYPE_INT, TYPE_FLOAT, TYPE_DOUBLE, TYPE_CHAR, TYPE_STRING };

// SINGLE LINKED LIST (CIRCULAR & NORMAL)
typedef struct listnode {
  void *val;
  struct listnode *next;
  enum datatype type;
} listnode_t;

// DOUBLY LINKED LIST
typedef struct dlistnode {
  void *val;
  struct dlistnode *next;
  struct dlistnode *prev;
  enum datatype type;
} dlistnode_t;

listnode_t *list_init(void *val, void *next, enum datatype type);
void list_destroy(listnode_t *head);

void list_begin_insert(listnode_t **head, void *val);
void list_pos_insert(listnode_t **head, usize pos, void *val);
void list_end_insert(listnode_t **head, void *val);

void list_begin_delete(listnode_t **head);
void list_end_delete(listnode_t **head);
void list_pos_delete(listnode_t **head, usize pos);

/*
  LeetCode Section - Singly Linked List Problems
*/
listnode_t *reverse_list(listnode_t *head);
listnode_t *merge_two_lists(listnode_t *list1, listnode_t *list2);
bool has_cycle(listnode_t *head);

#endif // LINKED_LIST_H
