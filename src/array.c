#include "array.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// basic functionality
array_t array_init(void *arr, usize n, enum datatype type) {
  ASSERT(n != 0, "number of elements in array n can't be 0\n");
  ASSERT(arr != NULL, "array passed is NULL\n");

  usize elsize = type_map(type);
  void *ownArr = malloc(n * elsize);

  ASSERT(ownArr != NULL, "couldn't allocate memory for the array");

  memcpy(ownArr, arr, n * elsize);

  array_t res;
  res.data = ownArr;
  res.n = n;
  res.tsize = elsize;

  return res;
}

void destroy_arr(array_t *arr) { free(arr->data); }

// Search Algorithms
bool binary_search_arr(array_t *arr, void *item) {
  i32 l = 0, r = arr->n - 1;
  while (l <= r) {
    i32 mid = l + (r - l) / 2;
    i32 comp = memcmp((char *)arr->data + mid * arr->tsize, item, arr->tsize);
    if (comp == 0) {
      return true;
    } else if (comp < 0) {
      l = ++mid;
    } else {
      r = --mid;
    }
  }
  return false;
}

bool search_arr(array_t *arr, void *item) {
  for (usize i = 0; i < arr->n; i++) {
    if (memcmp((char *)arr->data + i * arr->tsize, item, arr->tsize) == 0) {
      return true;
    }
  }
  return false;
}

// Sort Algorithms
void selection_sort(array_t *arr, bool isAscending) {
  for (usize i = 0; i < arr->n; i++) {
    usize diff = i;
    for (usize j = i + 1; j < arr->n; j++) {
      i32 res = memcmp((char *)arr->data + j * arr->tsize,
                       (char *)arr->data + diff * arr->tsize, arr->tsize);
      if ((!isAscending && res < 0) || (isAscending && res > 0)) {
        diff = j;
      }
    }
    if (memcmp((char *)arr->data + i * arr->tsize,
               (char *)arr->data + diff * arr->tsize, arr->tsize) != 0) {
      void *temp = malloc(arr->tsize);
      memcpy(temp, (char *)arr->data + i * arr->tsize, arr->tsize);
      memcpy((char *)arr->data + i * arr->tsize,
             (char *)arr->data + diff * arr->tsize, arr->tsize);
      memcpy((char *)arr->data + diff * arr->tsize, temp, arr->tsize);
      free(temp);
    }
  }
}

void bubble_sort(array_t *arr, bool isAscending) {
  bool isSorted = false;
  isize tempN = arr->n;
  while (!isSorted) {
    isSorted = true;
    for (isize i = 1; i < tempN; i++) {
      i32 res = memcmp((char *)arr->data + (i - 1) * arr->tsize,
                       (char *)arr->data + i * arr->tsize, arr->tsize);

      if ((res < 0 && !isAscending) || (res > 0 && isAscending)) {
        isSorted = false;
        void *temp = malloc(arr->tsize);
        memcpy(temp, (char *)arr->data + (i - 1) * arr->tsize, arr->tsize);
        memcpy((char *)arr->data + (i - 1) * arr->tsize,
               (char *)arr->data + i * arr->tsize, arr->tsize);
        memcpy((char *)arr->data + i * arr->tsize, temp, arr->tsize);
        free(temp);
      }
    }
    tempN--;
  }
}

void insertion_sort(array_t *arr, bool isAscending) {
  void *temp = malloc(arr->tsize);
  for (usize i = 1; i < arr->n; i++) {
    memcpy(temp, (char *)arr->data + i * arr->tsize, arr->tsize);
    isize j = i - 1;

    while (j >= 0) {
      i32 res = memcmp((char *)arr->data + j * arr->tsize, temp, arr->tsize);
      if (!((res < 0 && !isAscending) || (res > 0 && isAscending))) {
        break;
      }
      memcpy((char *)arr->data + (j + 1) * arr->tsize,
             (char *)arr->data + j * arr->tsize, arr->tsize);
      j--;
    }
    memcpy((char *)arr->data + (j + 1) * arr->tsize, temp, arr->tsize);
  }
  free(temp);
}

// Quick Sort
static isize partition(array_t *arr, isize low, isize high, bool isAscending) {
  isize i = low - 1;
  for (isize j = low; j < high; j++) {
    i32 res = memcmp((char *)arr->data + j * arr->tsize,
                     (char *)arr->data + high * arr->tsize, arr->tsize);
    if ((res < 0 && isAscending) || (res >= 0 && !isAscending)) {
      i++;
      void *temp = malloc(arr->tsize);
      memcpy(temp, (char *)arr->data + i * arr->tsize, arr->tsize);
      memcpy((char *)arr->data + i * arr->tsize,
             (char *)arr->data + j * arr->tsize, arr->tsize);
      memcpy((char *)arr->data + j * arr->tsize, temp, arr->tsize);
      free(temp);
    }
  }
  void *temp = malloc(arr->tsize);
  memcpy(temp, (char *)arr->data + (i + 1) * arr->tsize, arr->tsize);
  memcpy((char *)arr->data + (i + 1) * arr->tsize,
         (char *)arr->data + high * arr->tsize, arr->tsize);
  memcpy((char *)arr->data + high * arr->tsize, temp, arr->tsize);
  free(temp);

  return i + 1;
}

void quick_sort(array_t *arr, isize low, isize high, bool isAscending) {
  if (low < high) {
    isize pivot = partition(arr, low, high, isAscending);
    quick_sort(arr, low, pivot - 1, isAscending);
    quick_sort(arr, pivot + 1, high, isAscending);
  }
}