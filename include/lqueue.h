#pragma once

#include "linked.h"

typedef struct LQueue {
  ListNode *front;
  ListNode *back;
} LQueue;

LQueue *init_lqueue(i32 val);
void print_lqueue(LQueue *queue);
void destroy_lqueue(LQueue *queue);

void enqeue_lqueue(LQueue **queue, i32 n);
i32 dequeue_lqueue(LQueue **queue);
i32 peek_lqueue(LQueue *queue);