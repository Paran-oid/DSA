#include "queue.h"
#include "linked.h"

#include <stdlib.h>

queue_t *queue_init(enum datatype type) {
  queue_t *res = malloc(sizeof(queue_t));
  res->tsize = type_map(type);
  res->back = NULL;
  res->front = NULL;
  res->type = type;
  return res;
}

void queue_destroy(queue_t *queue) {
  listnode_t *curr = queue->front;
  while (curr != NULL) {
    listnode_t *temp = curr;
    curr = curr->next;
    free(temp);
  }
  free(queue);
}

// FIXME
void enqueue(queue_t *q, void *n) {
  ASSERT(q != NULL, "Queue must not be NULL");

  listnode_t *newHead = node_init(n, NULL, q->tsize);

  if (q->back)
    q->back->next = newHead;

  q->back = newHead;

  if (q->front == NULL) {
    q->front = newHead;
  }
}

// FIXME
void *dequeue(queue_t *q) {
  ASSERT(q->front != NULL, "Invalid queue\n");
  void *res = q->front->val;
  listnode_t *temp = q->front;
  q->front = q->front->next;

  if (q->front == NULL) {
    q->back = NULL;
  }

  free(temp);

  return res;
}

const void *qpeek(const queue_t *queue) {
  ASSERT(queue->front != NULL, "Queue must have items...\n");
  return queue->front->val;
}