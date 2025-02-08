#include "stack.h"
#include "funcs.h"

#include <stdio.h>
#include <stdlib.h>

// Stack Datastructure was implemented through an array method

Stack init_stack(void) {
  i32 top = -1;
  i32 *arr = malloc(sizeof(i32) * 100);

  Stack res = {arr, top, 100, 0};

  return res;
}

void print_stack(Stack *stack) {
  printf("{");
  for (usize i = 0; i < stack->size; i++) {
    printf("%d", stack->data[i]);
    if (i != stack->size - 1) {
      printf(", ");
    }
  }
  printf("}");
}

void destroy_stack(Stack *stack) { free(stack->data); }

void push(Stack *stack, i32 el) {
  if (stack->size >= stack->capacity) {
    resize(stack);
  }
  stack->top++;
  stack->size++;
  stack->data[stack->top] = el;
}
i32 pop(Stack *stack) {
  ASSERT(stack->size > 0, "Stack is empty...\n");
  i32 temp = stack->data[stack->top];
  stack->size--;
  stack->top--;
  return temp;
}
i32 peek(Stack *stack) {
  ASSERT(stack->size > 0, "Stack can't be empty when peeking...\n");
  return stack->data[stack->top];
}

static void resize(Stack *stack) {
  stack->capacity += 100;
  stack->data = realloc(stack->data, stack->capacity * sizeof(i32));
}