#pragma once

#include "models.h"

// Queue Operations
Queue *queue_create(DataType type);
void queue_destroy(Queue *q);

void enqueue(Queue *q, void *n);
void *dequeue(Queue *q);
const void *qpeek(const Queue *q);
