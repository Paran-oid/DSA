#include "stack.h"
#include "funcs.h"

#include <stdio.h>
#include <stdlib.h>

// stack_t Datastructure was implemented through an array method

stack_t *init_stack(i32 val) {

  stack_t *res = malloc(sizeof(stack_t));
  res->val = val;
  res->next = NULL;
  return res;
}

void print_stack(stack_t *stack_t) {
  printf("{");
  while (stack_t != NULL) {
    printf("%d", stack_t->val);
    if (stack_t->next != NULL)
      printf(", ");
    stack_t = stack_t->next;
  }
  printf("}");
}

void destroy_stack(stack_t *stack_t) {
  while (stack_t->next != NULL) {
    stack_t *temp = stack_t;
    stack_t = stack_t->next;
    free(temp);
  }
}

void push_stack(stack_t **stack_t, i32 el) {

  stack_t *newHead = (stack_t *)malloc(sizeof(stack_t));
  newHead->val = el;
  newHead->next = *stack_t;
  *stack_t = newHead;
}

i32 pop_stack(stack_t **stack_t) {
  i32 res = (*stack_t)->val;

  stack_t *temp = (*stack_t);
  *stack_t = (*stack_t)->next;
  free(temp);

  return res;
}

i32 peek_stack(stack_t *stack_t) { return stack_t->val; }