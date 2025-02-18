#pragma once

#include "funcs.h"

typedef struct stack {
  struct listnode **items;
  struct listnode *head;
  struct listnode *tail;
  enum datatype type;
} stack_t;

struct stack *stack_init(enum datatype type);
void destroy_stack(stack_t *stack);

void push_stack(stack_t *stack, void *el);
void *pop_stack(stack_t *stack);
void *peek_stack(const stack_t *stack);
