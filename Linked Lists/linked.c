#include "linked.h"
#include "funcs.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ListNode *node_create(void *val, ListNode *next, size_t element_size) {
  ListNode *head = malloc(sizeof(ListNode));
  if (!head) {
    perror("Failed to allocate memory for linked list\n");
    exit(EXIT_FAILURE);
  }

  head->value = malloc(element_size);
  if (!head->value) {
    perror("Failed to allocate memory for linked list value...\n");
    free(head);
    exit(EXIT_FAILURE);
  }

  memcpy(head->value, val, element_size);
  head->next = next;
  head->element_size = element_size;

  return head;
}

List *list_create(DataType type) {
  List *res = malloc(sizeof(List));
  res->head = NULL;
  res->element_size = type_map(type);
  res->type = type;

  return res;
}

void list_destroy(List *list) {
  ListNode *node = list->head;
  while (node != NULL) {
    ListNode *temp = node;
    node = node->next;
    free(temp);
  }
  free(list);
}

void list_begin_insert(List *list, void *val) {
  ListNode *newHead = node_create(val, NULL, list->element_size);
  newHead->next = list->head;
  list->head = newHead;
}

void list_end_insert(List *list, void *val) {
  ListNode *newNode = node_create(val, NULL, list->element_size);

  ListNode *curr = list->head;
  while (curr->next) {
    curr = curr->next;
  }

  curr->next = newNode;
}
void list_pos_insert(List *list, size_t pos, void *val) {
  ListNode *prev = NULL;
  ListNode *curr = list->head;
  while (pos > 0 && curr->next) {
    prev = curr;
    curr = curr->next;
    pos--;
  }

  ListNode *newNode = node_create(val, NULL, list->element_size);

  if (prev) {
    prev->next = newNode;
    newNode->next = curr;
  } else {
    newNode->next = curr;
    list->head = newNode;
  }
}

void list_begin_delete(List *list) {
  ListNode *temp = list->head;
  list->head = list->head->next;
  free(temp);
}
void list_end_delete(List *list) {
  if (!list->head)
    return;

  ListNode *curr = list->head;
  ListNode *prev = NULL;
  while (curr->next) {
    prev = curr;
    curr = curr->next;
  }

  if (!prev) {
    free(curr);
    list->head = NULL;
  } else {
    prev->next = NULL;
    free(curr);
  }
}
void list_pos_delete(List *list, size_t pos) {
  ListNode *curr = list->head;
  ListNode *prev = NULL;
  while (pos > 0 && curr->next) {
    prev = curr;
    curr = curr->next;
    pos--;
  }

  if (prev) {
    prev->next = curr->next;
    free(curr);
  } else {
    list->head = curr->next;
    free(curr);
  }
}

// LEETCODE SECTION

ListNode *reverse_list(ListNode *head) {
  ListNode *prev = NULL;
  ListNode *curr = head;
  while (curr) {
    ListNode *temp = curr->next;
    curr->next = prev;
    prev = curr;
    curr = temp;
  }
  return prev;
}
ListNode *merge_two_lists(ListNode *head1, ListNode *head2,
                          size_t element_size) {
  ASSERT(element_size == sizeof(int), "Must enter values of type int\n");

  ListNode *dummy = node_create(0, NULL, element_size);
  ListNode *ptr = dummy;

  while (head1 && head2) {
    if (head1->value < head2->value) {
      ptr->next = head1;
      head1 = head1->next;
      ptr = ptr->next;
    } else {
      ptr->next = head2;
      head2 = head2->next;
      ptr = ptr->next;
    }
  }

  while (head1) {
    ptr->next = head1;
    head1 = head1->next;
    ptr = ptr->next;
  }

  while (head2) {
    ptr->next = head2;
    head2 = head2->next;
    ptr = ptr->next;
  }

  return dummy->next;
}

bool has_cycle(ListNode *head) {
  ListNode *slow = head;
  ListNode *fast = head;

  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) {
      return true;
    }
  }
  return false;
}