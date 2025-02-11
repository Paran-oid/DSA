#include "lqueue.h"
#include "linked.h"

#include <stdlib.h>

LQueue *init_lqueue(i32 val) {
  LQueue *res = (LQueue *)malloc(sizeof(LQueue));
  res->back = init_node(val);
  res->front = res->back;
  return res;
}

void print_lqueue(LQueue *queue) {
  ListNode *curr = queue->front;
  printf("{");
  while (curr != NULL) {
    printf("%d", curr->val);
    if (curr->next != NULL) {
      printf(", ");
    }
    curr = curr->next;
  }
  printf("}");
}
void destroy_lqueue(LQueue *queue) {
  ListNode *curr = queue->front;
  while (curr != NULL) {
    ListNode *temp = curr;
    curr = curr->next;
    free(temp);
  }
}

void enqeue_lqueue(LQueue **queue, i32 n) {
  ListNode *newHead = init_node(n);
  (*queue)->back->next = newHead;
  (*queue)->back = newHead;
}

i32 dequeue_lqueue(LQueue **queue) {
  ASSERT((*queue)->front != NULL, "Invalid queue\n");
  i32 res = (*queue)->front->val;
  ListNode *temp = (*queue)->front;
  (*queue)->front = (*queue)->front->next;
  free(temp);
}
i32 peek_lqueue(LQueue *queue) { return queue->front->val; }