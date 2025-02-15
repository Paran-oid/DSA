#pragma once

#include "funcs.h"

// Objects
typedef struct Array {
  usize n;
  i32 *data;
} Array;

// basic functionality
Array init_arr(int arr[], usize n);
void print_arr(Array *arr);
void destroy_arr(Array *arr);

// Search Algorithms
bool binary_search_arr(Array *arr, i32 item);
bool search_arr(Array *arr, i32 item);

// Sort Algorithms
void selection_sort(Array *arr, bool isAscending);
void bubble_sort(Array *arr, bool isAscending);
void insertion_sort(Array *arr, bool isAscending);
void cycle_sort(Array *arr, bool isAscending);

// Quick Sort
void quick_sort(Array *arr, isize low, isize high, bool isAscending);

// Merge Sort
void merge_sort(Array *arr, isize l, isize r, bool isAscending);
