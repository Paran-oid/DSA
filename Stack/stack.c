#include "stack.h"
#include "funcs.h"

#include <stdio.h>
#include <stdlib.h>

Stack *stack_create(DataType type) {
  Stack *res = malloc(sizeof(Stack));
  if (!res) {
    perror("Error allocating memory for stack");
    exit(EXIT_FAILURE);
  }
  res->element_size = type_map(type);
  res->head = NULL;
  res->tail = NULL;
  res->type = type;

  return res;
}

void stack_destroy(Stack *stack) {
  if (!stack)
    return;

  ListNode *curr = stack->head;
  while (curr) {
    ListNode *temp = curr;
    curr = curr->next;
    free(temp->val);
    free(temp);
  }
  free(stack);
}

void push(Stack *stack, void *el) {
  ListNode *newHead = node_create(el, stack->head, stack->element_size);
  stack->head = newHead;
}

void *pop(Stack *stack) {
  if (stack->head == NULL) {
    return NULL;
  }

  void *res = stack->head->val;
  ListNode *temp = stack->head;
  stack->head = stack->head->next;
  free(temp->val);
  free(temp);

  return res;
}

void *speek(const Stack *stack) {
  if (stack->head == NULL) {
    return NULL;
  }

  return stack->head->val;
}
