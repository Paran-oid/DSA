#pragma once

#include "funcs.h"
#include <stdbool.h>

// SINGLE LINKED LIST (CIRCULAR & NORMAL)
typedef struct listnode {
  void *val;
  struct listnode *next;
  usize tsize;
} listnode_t;

// DOUBLY LINKED LIST
typedef struct dlistnode {
  void *val;
  struct dlistnode *next;
  struct dlistnode *prev;
  usize tsize;
} dlistnode_t;

typedef struct list {
  listnode_t *head;
  usize tsize;
  enum datatype type;
} list_t;

typedef struct dlist {
  dlistnode_t *head;
  usize tsize;
} dlist_t;

listnode_t *node_create(void *val, listnode_t *next, usize tsize);
list_t *list_create(enum datatype type);
void list_destroy(list_t *list);

void list_begin_insert(list_t *list, void *val);
void list_pos_insert(list_t *list, usize pos, void *val);
void list_end_insert(list_t *list, void *val);

void list_begin_delete(list_t *list);
void list_end_delete(list_t *list);
void list_pos_delete(list_t *list, usize pos);

/*
  LeetCode Section - Singly Linked List Problems
*/
listnode_t *reverse_list(listnode_t *head);
listnode_t *merge_two_lists(listnode_t *head1, listnode_t *head2, usize tsize);
bool has_cycle(listnode_t *head);
