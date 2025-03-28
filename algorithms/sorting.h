#ifndef SORTING_H
#define SORTING_H

#include <stddef.h>

int insertion_sort(void* data, size_t size, size_t esize, int (*compare)(const void* key1, const void* key2));

int quick_sort(void* data, size_t, size_t esize, int left, int right, int (*comp)(const void*, const void*));

int merge_sort(void* arr, size_t size, size_t esize, int start, int end, int (*comp)(const void*, const void*));

int counting_sort(int* arr, size_t size, size_t k);

int radix_sort(int* arr, size_t size, int p, int k);

int bisearch(void* sorted, void* target, int size, int esize,
    int (*compare)(const void* key1, const void* key2));

#endif