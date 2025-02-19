#include "array.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// basic functionality

array_t array_init(void *arr, usize size, enum datatype type) {
  ASSERT(size != 0, "number of elements in array size can't be \n");
  ASSERT(arr != NULL, "array passed is NULL \n");

  array_t res = {0};
  usize elsize = type_map(type);

  if (!arr) {
    void *ownArr = calloc(size, elsize);
    ASSERT(ownArr != NULL, "couldn't allocate memory for the array");
    res.data = ownArr;
    res.size = res.capacity = 0;
    res.tsize = elsize;
  }
  void *ownArr = malloc(size * elsize);

  ASSERT(ownArr != NULL, "couldn't allocate memory for the array");

  memcpy(ownArr, arr, size * elsize);

  res.data = ownArr;
  res.tsize = elsize;

  res.size = size;
  res.capacity = size;

  return res;
}

void array_destroy(array_t *arr) { free(arr->data); }

// Dynamic Functionality

void *array_get(const array_t *arr, i32 index) {
  ASSERT(arr && arr->data, "Null/Null data passed\n");
  ASSERT(index >= 0 && index < (i32)arr->size, "Index out of range");
  return (char *)arr->data + (index * arr->tsize);
}
void array_set(array_t *arr, i32 index, void *item) {
  ASSERT(arr != NULL && arr->data != NULL, "Array is NULL or uninitialized");
  ASSERT(index > 0 && index < (i32)arr->size, "Index out of range");
  memcpy((char *)arr->data + index * arr->tsize, item, arr->tsize);
}
void array_pushback(array_t *arr, void *item) {
  ASSERT(arr != NULL && arr->data != NULL, "Array is NULL or uninitialized");
  if (arr->size == arr->capacity)
    array_resize(arr);

  memcpy((char *)arr->data + arr->size * arr->tsize, item, arr->tsize);
  arr->size++;
}
void *array_popback(array_t *arr) {
  ASSERT(arr != NULL && arr->data != NULL, "Array is NULL or uninitialized");
  ASSERT(arr->size > 0, "Array is empty when you tried to pop it...\n");
  void *res = (char *)arr->data + (arr->size - 1) * arr->tsize;
  arr->size--;
  return res;
}
void array_resize(array_t *arr) {
  ASSERT(arr != NULL && arr->data != NULL, "Array is NULL or uninitialized");
  arr->capacity = arr->capacity == 0 ? 1 : 2 * arr->capacity;
  arr->data = realloc(arr->data, arr->capacity);

  if (!arr->data) {
    perror("error reallocating array\n");
    exit(EXIT_FAILURE);
  }
}

// Search Algorithms

bool binary_search(array_t *arr, void *item) {
  i32 l = 0, r = arr->size - 1;
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

bool linear_search(array_t *arr, void *item) {
  for (usize i = 0; i < arr->size; i++) {
    if (memcmp((char *)arr->data + i * arr->tsize, item, arr->tsize) == 0) {
      return true;
    }
  }
  return false;
}

// Sort Algorithms

void selection_sort(array_t *arr, bool isAscending) {
  for (usize i = 0; i < arr->size; i++) {
    usize diff = i;
    for (usize j = i + 1; j < arr->size; j++) {
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
  isize tempN = arr->size;
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
  for (usize i = 1; i < arr->size; i++) {
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

void cycle_sort(array_t *arr, bool isAscending) {
  void *temp = malloc(arr->tsize);

  for (usize cycle_start = 0; cycle_start < arr->size - 1; cycle_start++) {
    memcpy(temp, (char *)arr->data + cycle_start * arr->tsize, arr->tsize);

    usize pos = cycle_start;
    for (usize i = cycle_start + 1; i < arr->size; i++) {
      i32 comp = memcmp((char *)arr->data + i * arr->tsize, temp, arr->tsize);
      if ((isAscending && comp < 0) || (!isAscending && comp > 0)) {
        pos++;
      }
    }

    if (pos == cycle_start) {
      continue;
    }

    while (memcmp((char *)arr->data + pos * arr->tsize, temp, arr->tsize) ==
           0) {
      pos++;
    }

    if (pos != cycle_start) {
      swap((char *)arr->data + pos * arr->tsize, temp, arr->tsize);
    }

    while (pos != cycle_start) {
      pos = cycle_start;
      for (usize i = cycle_start + 1; i < arr->size; i++) {
        i32 comp = memcmp((char *)arr->data + i * arr->tsize, temp, arr->tsize);
        if ((isAscending && comp < 0) || (!isAscending && comp > 0)) {
          pos++;
        }
      }

      while (memcmp((char *)arr->data + pos * arr->tsize, temp, arr->tsize) ==
             0) {
        pos++;
      }

      if (memcmp(temp, (char *)arr->data + pos * arr->tsize, arr->tsize) != 0) {
        swap(temp, (char *)arr->data + pos * arr->tsize, arr->tsize);
      }
    }
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

// Merge Sort

static void merge(array_t *arr, isize l, isize m, isize r, bool isAscending) {
  isize n1 = m - l + 1;
  isize n2 = r - m;

  void *L = malloc(n1 * arr->tsize);
  void *R = malloc(n2 * arr->tsize);

  memcpy(L, (char *)arr->data + l * arr->tsize, n1 * arr->tsize);
  memcpy(R, (char *)arr->data + (m + 1) * arr->tsize, n2 * arr->tsize);

  isize i = 0, j = 0, k = l;

  while (i < n1 && j < n2) {
    i32 comp = memcmp((char *)L + i * arr->tsize, (char *)R + j * arr->tsize,
                      arr->tsize);

    if ((isAscending && comp <= 0) || (!isAscending && comp > 0)) {
      memcpy((char *)arr->data + k * arr->tsize, (char *)L + i * arr->tsize,
             arr->tsize);
      i++;
    } else {
      memcpy((char *)arr->data + k * arr->tsize, (char *)R + j * arr->tsize,
             arr->tsize);
      j++;
    }
    k++;
  }

  while (i < n1) {
    memcpy((char *)arr->data + k * arr->tsize, (char *)L + i * arr->tsize,
           arr->tsize);
    i++;
    k++;
  }

  while (j < n2) {
    memcpy((char *)arr->data + k * arr->tsize, (char *)R + j * arr->tsize,
           arr->tsize);
    j++;
    k++;
  }

  free(L);
  free(R);
}

void merge_sort(array_t *arr, isize l, isize r, bool isAscending) {
  if (l < r) {
    isize m = l + (r - l) / 2;
    merge_sort(arr, l, m, isAscending);
    merge_sort(arr, m + 1, r, isAscending);
    merge(arr, l, m, r, isAscending);
  }
}