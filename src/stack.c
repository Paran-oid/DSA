#include "lstack.h"
#include "funcs.h"

#include <stdio.h>
#include <stdlib.h>

// LStack Datastructure was implemented through an array method

LStack *init_lstack(i32 val) {

  LStack *res = malloc(sizeof(LStack));
  res->val = val;
  res->next = NULL;
  return res;
}

void print_lstack(LStack *stack) {
  printf("{");
  while (stack != NULL) {
    printf("%d", stack->val);
    if (stack->next != NULL)
      printf(", ");
    stack = stack->next;
  }
  printf("}");
}

void destroy_lstack(LStack *stack) {
  while (stack->next != NULL) {
    LStack *temp = stack;
    stack = stack->next;
    free(temp);
  }
}

void push_lstack(LStack **stack, i32 el) {

  LStack *newHead = (LStack *)malloc(sizeof(LStack));
  newHead->val = el;
  newHead->next = *stack;
  *stack = newHead;
}

i32 pop_lstack(LStack **stack) {
  i32 res = (*stack)->val;

  LStack *temp = (*stack);
  *stack = (*stack)->next;
  free(temp);

  return res;
}

i32 peek_lstack(LStack *stack) { return stack->val; }