#pragma once

#include "linked.h"

typedef struct queue {
  struct list_node *front;
  struct list_node *back;
  usize tsize;
} queue_t;

// Queue Operations
queue_t *queue_init(enum datatype type);
void queue_destroy(queue_t *q);

void queue_enqueue(queue_t *q, void *n);
void *queue_dequeue(queue_t *q);
const void *queue_peek(const queue_t *q);
