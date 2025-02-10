#include "queue.h"
#include "funcs.h"

#include <stdio.h>
#include <stdlib.h>

Queue init_queue(void) {
  Queue res;
  res.arr = (int *)calloc(5, sizeof(int));
  res.size = 0;
  res.capacity = 5;

  res.back = 0;
  res.front = 0;

  return res;
};

void print_queue(Queue *queue) {
  printf("{");
  for (usize i = queue->front; i < queue->size; i++) {
    if (i != queue->size - 1)
      printf("%d, ", queue->arr[i]);
    else
      printf("%d", queue->arr[i]);
  }
  printf("}");
}

void destroy_queue(Queue *queue) { free(queue->arr); }

void enqeue_queue(Queue *queue, int n) {
  queue->arr[queue->back] = n;
  queue->back += 1;
}

i32 dequeue_queue(Queue *queue) {
  i32 res = queue->arr[queue->front];
  queue->front += 1;
  return res;
}
i32 peek_queue(Queue *queue) { return queue->arr[queue->front]; }

static void resize(Queue *queue) {
  queue->arr = realloc(queue->arr, sizeof(int));
  queue->capacity += 100;
}