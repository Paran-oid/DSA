#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

typedef List Queue;

#define queue_create list_create
#define queue_destroy list_destroy

int queue_enqueue(Queue* queue, const void* data);
int queue_dequeue(Queue* queue, void** data);

#define queue_size list_size
#define queue_peek(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)

#endif