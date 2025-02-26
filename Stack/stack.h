#pragma once

#include "models.h"

Stack *stack_create(DataType type);
void stack_destroy(Stack *stack);

void push(Stack *stack, void *el);
void *pop(Stack *stack);
void *speek(const Stack *stack);
