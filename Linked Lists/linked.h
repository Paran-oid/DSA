#pragma once

#include "models.h"

#include <stdbool.h>

ListNode *node_create(void *val, ListNode *next, size_t element_size);
List *list_create(DataType type);
void list_destroy(List *list);

void list_begin_insert(List *list, void *val);
void list_pos_insert(List *list, size_t pos, void *val);
void list_end_insert(List *list, void *val);

void list_begin_delete(List *list);
void list_end_delete(List *list);
void list_pos_delete(List *list, size_t pos);

/*
  LeetCode Section - Singly Linked List Problems
*/
ListNode *reverse_list(ListNode *head);
ListNode *merge_two_lists(ListNode *head1, ListNode *head2,
                          size_t element_size);
bool has_cycle(ListNode *head);
