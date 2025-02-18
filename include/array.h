#pragma once

#include "funcs.h"

#include <stdbool.h>

typedef struct array {
  usize n;
  void **data;
  enum datatype type;
} array_t;

// Basic Functionality

array_t *array_init(void **arr, usize n, enum datatype type);
void array_destroy(array_t *arr);

// Search Algorithms

bool binary_search(array_t *arr, void *item);
bool linear_search(array_t *arr, void *item);

// Sorting Algorithms

void selection_sort(array_t *arr, bool ascending);
void bubble_sort(array_t *arr, bool ascending);
void insertion_sort(array_t *arr, bool ascending);
void cycle_sort(array_t *arr, bool ascending);

void quick_sort(array_t *arr, bool ascending);
void merge_sort(array_t *arr, bool ascending);
