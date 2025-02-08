#pragma once

#include "funcs.h"

typedef struct Stack {
  i32 *data;
  i32 top;

  usize capacity;
  usize size;
} Stack;

Stack init_stack(void);
void print_stack(Stack *stack);
void destroy_stack(Stack *stack);

void push(Stack *stack, i32 el);
i32 pop(Stack *stack);
i32 peek(Stack *stack);

static void resize(Stack *stack);