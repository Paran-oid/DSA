#pragma once

#include "funcs.h"

typedef struct LStack {
  i32 val;
  struct LStack *next;
} LStack;

LStack *init_lstack(i32 val);
void print_lstack(LStack *stack);
void destroy_lstack(LStack *stack);

void push_lstack(LStack **stack, i32 el);
i32 pop_lstack(LStack **stack);
i32 peek_lstack(LStack *stack);
