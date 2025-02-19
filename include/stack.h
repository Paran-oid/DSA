#pragma once

#include "funcs.h"
#include "linked.h"

typedef struct stack {
  listnode_t **items;
  listnode_t *head;
  listnode_t *tail;
  usize tsize;
} stack_t;

struct stack *stack_init(enum datatype type);
void stack_destroy(stack_t *stack);

void push(stack_t *stack, void *el);
void *pop(stack_t *stack);
void *speek(const stack_t *stack);
