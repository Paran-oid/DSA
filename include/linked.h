#pragma once

#include <stdbool.h>

// SINGLE LINKED LIST
// CIRCULAR LINKED LIST

typedef struct ListNode {
  int val;
  struct ListNode *next;
} ListNode;

// DOUBLY LINKED LIST
typedef struct Node {
  int val;
  struct Node *next;
  struct Node *prev;
} Node;

/*
  All of these functions apply for Circular and singly linked list
  Because they are the most common and in order for it to not get
  too repetitive
*/

ListNode *init_node(int val);
void print_list(ListNode *head);
// TODO
void destroy_node(ListNode *node);

void begin_insert__node(ListNode **head, int val);
void end_insert_node(ListNode *head, int val);
void pos_insert_node(ListNode **head, int pos, int val);

void begin_delete_node(ListNode **head);
void end_delete_node(ListNode *head);
void pos_delete_node(ListNode **head, int pos);

// LEETCODE SECTION
ListNode *reverse_list(ListNode *head);
ListNode *merge_two_lists(ListNode *list1, ListNode *list2);
bool has_cycle(ListNode *head);