#pragma once

#include "funcs.h"

#include <stdbool.h>

typedef struct array {
  void *data;
  usize tsize, size, capacity;
  enum datatype type;
} array_t;

// Basic Functionality

array_t array_create(void *arr, usize n, enum datatype type);
void array_destroy(array_t *arr);

// Dynamic Functionality
void *array_get(const array_t *arr, i32 index);
void array_set(array_t *arr, i32 index, void *item);
void array_pushback(array_t *arr, void *item);
void *array_popback(array_t *arr);
void array_resize(array_t *arr);

// Search Algorithms

bool binary_search(array_t *arr, void *item);
bool linear_search(array_t *arr, void *item);

// Sorting Algorithms

void selection_sort(array_t *arr, bool ascending);
void bubble_sort(array_t *arr, bool ascending);
void insertion_sort(array_t *arr, bool ascending);
void cycle_sort(array_t *arr, bool ascending);

void quick_sort(array_t *arr, isize low, isize high, bool isAscending);
void merge_sort(array_t *arr, isize l, isize r, bool isAscending);
