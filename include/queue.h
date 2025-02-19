#pragma once

#include "funcs.h"
#include "linked.h"

typedef struct queue {
  listnode_t *front;
  listnode_t *back;
  usize tsize;
} queue_t;

// Queue Operations
queue_t *queue_init(enum datatype type);
void queue_destroy(queue_t *q);

void enqueue(queue_t *q, void *n);
void *dequeue(queue_t *q);
const void *qpeek(const queue_t *q);
