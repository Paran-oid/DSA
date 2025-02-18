#include "linked.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct listnode *node_init(void *val, enum datatype type) {
  struct listnode *head = malloc(sizeof(struct listnode));
  head->val = val;
  head->next = NULL;
  return head;
}
void list_print(struct list *head) {
  printf("{");
  while (head) {
    if (head->next) {
      printf("%d->", head->val);
    } else {
      printf("%d", head->val);
    }
    head = head->next;
  }
  printf("}");
}
void list_destroy(struct list *node) {
  while (node != NULL) {
    ListNode *temp = node;
    node = node->next;
    free(temp);
  }
}

void list_begin_insret(struct list **head, void *val) {
  ListNode *newHead = init_node(val);
  newHead->next = *head;
  *head = newHead;
}
void list_end_insert(struct list *head, i32 val) {
  ListNode *newNode = init_node(val);

  ListNode *curr = head;
  while (curr->next) {
    curr = curr->next;
  }

  curr->next = newNode;
}
void list_pos_insert(struct list **head, usize pos, i32 val) {
  ListNode *prev = NULL;
  ListNode *curr = *head;
  while (pos > 0 && curr->next) {
    prev = curr;
    curr = curr->next;
    pos--;
  }

  ListNode *newNode = init_node(val);

  if (prev) {
    prev->next = newNode;
    newNode->next = curr;
  } else {
    newNode->next = curr;
    *head = newNode;
  }
}

void list_begin_delete(struct list **head) {
  ListNode *temp = *head;
  *head = (*head)->next;
  free(temp);
}
void list_end_delete(struct list *head) {
  ListNode *curr = head;
  ListNode *prev = NULL;
  while (curr->next) {
    prev = curr;
    curr = curr->next;
  }
  prev->next = NULL;
}
void list_pos_delete(struct list **head, usize pos) {
  ListNode *curr = *head;
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
    *head = curr->next;
    free(curr);
  }
}

// LEETCODE SECTION

struct listnode *reverse_list(struct listnode *head) {
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
struct listnode *merge_two_lists(struct listnode *list1,
                                 struct listnode *list2) {

  ListNode *dummy = init_node(0);
  ListNode *ptr = dummy;

  while (list1 && list2) {
    if (list1->val < list2->val) {
      ptr->next = list1;
      list1 = list1->next;
      ptr = ptr->next;
    } else {
      ptr->next = list2;
      list2 = list2->next;
      ptr = ptr->next;
    }
  }

  while (list1) {
    ptr->next = list1;
    list1 = list1->next;
    ptr = ptr->next;
  }

  while (list2) {
    ptr->next = list2;
    list2 = list2->next;
    ptr = ptr->next;
  }

  return dummy->next;
}

bool has_cycle(struct listnode *head) {
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