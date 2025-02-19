#include "linked.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

listnode_t *node_init(void *val, listnode_t *next, usize tsize) {
  listnode_t *head = malloc(sizeof(listnode_t));
  if (!head) {
    perror("Failed to allocate memory for linked list\n");
    exit(EXIT_FAILURE);
  }

  head->val = malloc(tsize);
  if (!head->val) {
    perror("Failed to allocate memory for linked list value...\n");
    free(head);
    exit(EXIT_FAILURE);
  }

  memcpy(head->val, val, tsize);
  head->next = next;
  head->tsize = tsize;

  return head;
}

list_t *list_init(enum datatype type) {
  list_t *res = malloc(sizeof(list_t));
  res->head = NULL;
  res->tsize = type_map(type);

  return res;
}

void list_destroy(list_t *list) {
  listnode_t *node = list->head;
  while (node != NULL) {
    listnode_t *temp = node;
    node = node->next;
    free(temp);
  }
  free(list);
}

void list_begin_insert(list_t *list, void *val) {
  listnode_t *newHead = node_init(val, NULL, list->tsize);
  newHead->next = list->head;
  list->head = newHead;
}

void list_end_insert(list_t *list, void *val) {
  listnode_t *newNode = node_init(val, NULL, list->tsize);

  listnode_t *curr = list->head;
  while (curr->next) {
    curr = curr->next;
  }

  curr->next = newNode;
}
void list_pos_insert(list_t *list, usize pos, void *val) {
  listnode_t *prev = NULL;
  listnode_t *curr = list->head;
  while (pos > 0 && curr->next) {
    prev = curr;
    curr = curr->next;
    pos--;
  }

  listnode_t *newNode = node_init(val, NULL, list->tsize);

  if (prev) {
    prev->next = newNode;
    newNode->next = curr;
  } else {
    newNode->next = curr;
    list->head = newNode;
  }
}

void list_begin_delete(list_t *list) {
  listnode_t *temp = list->head;
  list->head = list->head->next;
  free(temp);
}
void list_end_delete(list_t *list) {
  if (!list->head)
    return;

  listnode_t *curr = list->head;
  listnode_t *prev = NULL;
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
void list_pos_delete(list_t *list, usize pos) {
  listnode_t *curr = list->head;
  listnode_t *prev = NULL;
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

listnode_t *reverse_list(listnode_t *head) {
  listnode_t *prev = NULL;
  listnode_t *curr = head;
  while (curr) {
    listnode_t *temp = curr->next;
    curr->next = prev;
    prev = curr;
    curr = temp;
  }
  return prev;
}
listnode_t *merge_two_lists(listnode_t *head1, listnode_t *head2, usize tsize) {
  ASSERT(tsize == sizeof(i32), "Must enter values of type int\n");

  listnode_t *dummy = node_init(0, NULL, tsize);
  listnode_t *ptr = dummy;

  while (head1 && head2) {
    if (head1->val < head2->val) {
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

bool has_cycle(listnode_t *head) {
  listnode_t *slow = head;
  listnode_t *fast = head;

  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) {
      return true;
    }
  }
  return false;
}