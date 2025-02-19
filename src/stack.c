#include "stack.h"
#include "funcs.h"

#include <stdio.h>
#include <stdlib.h>

// stack_t Datastructure was implemented through an array method

stack_t *stack_init(enum datatype type) {

  stack_t *res = malloc(sizeof(stack_t));
  res->tsize = type_map(type);
  res->tail = NULL;
  res->head = NULL;
  return res;
}

void stack_destroy(stack_t *stack) {

  listnode_t *curr = stack->head;
  while (curr) {
    listnode_t *temp = curr;
    curr = curr->next;
    free(temp);
  }
  free(stack);
}

void push(stack_t *stack, void *el) {

  listnode_t *newHead = node_init(el, stack->head, stack->tsize);
  stack->head = newHead;
}

void *pop(stack_t *stack) {
  void *res = stack->head->val;

  listnode_t *temp = stack->head;
  stack->head = stack->head->next;
  free(temp);

  return res;
}

void *speek(const stack_t *stack) { return stack->head->val; }