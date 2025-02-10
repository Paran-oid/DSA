#pragma once

#include "funcs.h"

typedef struct Queue {
  int *arr;
  int size;
  int capacity;

  int front;
  int back;
} Queue;

Queue init_queue(void);
void print_queue(Queue *queue);
void destroy_queue(Queue *queue);

void enqeue_queue(Queue *queue, int n);
i32 dequeue_queue(Queue *queue);
i32 peek_queue(Queue *queue);

static void resize(Queue *queue);