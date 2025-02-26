#pragma once

#include "models.h"

#include <stdbool.h>

// Basic Functionality

Array array_create(void *arr, size_t n, DataType type);
void array_destroy(Array *arr);

// Dynamic Functionality
void *array_get(const Array *arr, int index);
void array_set(Array *arr, int index, void *item);
void array_pushback(Array *arr, void *item);
void *array_popback(Array *arr);
void array_resize(Array *arr);

// Search Algorithms

bool binary_search(Array *arr, void *item);
bool linear_search(Array *arr, void *item);

// Sorting Algorithms

void selection_sort(Array *arr, bool ascending);
void bubble_sort(Array *arr, bool ascending);
void insertion_sort(Array *arr, bool ascending);
void cycle_sort(Array *arr, bool ascending);

void quick_sort(Array *arr, int low, int high, bool isAscending);
void merge_sort(Array *arr, int l, int r, bool isAscending);
