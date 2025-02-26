#include "queue.h"
#include "funcs.h"
#include "linked.h"

#include <stdlib.h>
#include <tree.h>

Queue *queue_create(DataType type) {
  Queue *res = malloc(sizeof(Queue));
  res->element_size = type_map(type);
  res->back = NULL;
  res->front = NULL;
  res->type = type;
  return res;
}

void queue_destroy(Queue *queue) {
  ListNode *curr = queue->front;
  while (curr != NULL) {
    ListNode *temp = curr;
    curr = curr->next;
    free(temp);
  }
  free(queue);
}

void enqueue(Queue *q, void *n) {
  ASSERT(q != NULL, "Queue must not be NULL");

  ListNode *newHead = node_create(n, NULL, q->element_size);

  if (q->back)
    q->back->next = newHead;

  q->back = newHead;

  if (q->front == NULL) {
    q->front = newHead;
  }
}

void *dequeue(Queue *q) {
  ASSERT(q->front != NULL, "Invalid queue\n");
  void *res = q->front->val;

  ListNode *temp = q->front;

  q->front = q->front->next;

  if (q->front == NULL) {
    q->back = NULL;
  }

  free(temp);

  return res;
}

const void *qpeek(const Queue *queue) {
  ASSERT(queue->front != NULL, "Queue must have items...\n");
  return queue->front->val;
}