#ifndef STACK_H
#define STACK_H

#include "list.h"

typedef List Stack;

#define stack_create list_create
#define stack_destroy list_destroy

int stack_push(Stack* stack, const void* data);
int stack_pop(Stack* stack, void** data);

#define stack_peek(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)
#define stack_size list_size

#endif