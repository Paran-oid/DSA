#include "linked.h"

#include <stdio.h>
#include <stdlib.h>

ListNode *init_node(int val) {
  ListNode *head = malloc(sizeof(ListNode));
  head->val = val;
  head->next = NULL;
  return head;
}
void print_list(ListNode *head) {
  while (head) {
    if (head->next) {
      printf("%d->", head->val);
    } else {
      printf("%d", head->val);
    }
    head = head->next;
  }
}

void begin_insert__node(ListNode **head, int val) {
  ListNode *newHead = init_node(val);
  newHead->next = *head;
  *head = newHead;
}
void end_insert_node(ListNode *head, int val) {
  ListNode *newNode = init_node(val);

  ListNode *curr = head;
  while (curr->next) {
    curr = curr->next;
  }

  curr->next = newNode;
}
void pos_insert_node(ListNode **head, int pos, int val) {
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

void begin_delete_node(ListNode **head) {
  ListNode *temp = *head;
  *head = (*head)->next;
  free(temp);
}
void end_delete_node(ListNode *head) {
  ListNode *curr = head;
  ListNode *prev = NULL;
  while (curr->next) {
    prev = curr;
    curr = curr->next;
  }
  prev->next = NULL;
}

void pos_delete_node(ListNode **head, int pos) {
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
ListNode *merge_two_lists(ListNode *list1, ListNode *list2) {

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