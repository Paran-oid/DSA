#pragma once

#include "funcs.h"

typedef struct Queue {
  i32 *arr;
  usize size;
  usize capacity;

  i32 front;
  i32 back;
} Queue;

Queue init_queue(void);
void print_queue(Queue *queue);
void destroy_queue(Queue *queue);

void enqeue_queue(Queue *queue, i32 n);
i32 dequeue_queue(Queue *queue);
i32 peek_queue(Queue *queue);

static void resize(Queue *queue);